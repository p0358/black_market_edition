#include "pch.h"
#include "TTFSDK.h"
#include "VTableHooking.h"
#include "SigScanning.h"
#include "IFileSystem.h"
#include "FileSystemManager.h"
#include <set>

#ifdef _DEBUG
#define READ_FROM_FILESYSTEM
#else
#define READ_FROM_BSP
#endif

#ifdef READ_FROM_BSP
#include "FilesystemContents.h"
std::set<std::string> fileSystemContentsSet{ FILES_COMMA_SEPARATED };
//std::set<std::string> fileSystemContentsBlockedFromCacheSet{};
#endif

namespace fs = std::filesystem;

FileSystemManager& FSManager()
{
    return SDK().GetFSManager();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&FileSystemManager::##name), &FileSystemManager::##name, decltype(&FSManager), &FSManager>::Call

HookedVTableFunc<decltype(&IFileSystem::VTable::AddSearchPath), &IFileSystem::VTable::AddSearchPath> IFileSystem_AddSearchPath;
HookedVTableFunc<decltype(&IFileSystem::VTable::ReadFromCache), &IFileSystem::VTable::ReadFromCache> IFileSystem_ReadFromCache;
HookedVTableFunc<decltype(&IFileSystem::VTable::MountVPK), &IFileSystem::VTable::MountVPK> IFileSystem_MountVPK;
HookedFunc<FileHandle_t, VPKData*, __int32*, const char*> ReadFileFromVPK("filesystem_stdio.dll", "\x48\x89\x5C\x24\x00\x57\x48\x81\xEC\x00\x00\x00\x00\x49\x8B\xC0\x48\x8B\xDA", "xxxx?xxxx????xxxxxx");
HookedFuncStatic<unsigned __int64 __fastcall, __int64> RemoveAllMapSearchPaths("filesystem_stdio.dll", 0x16570); // this is vtable function

std::regex FileSystemManager::s_mapFromVPKRegex("client_(.+)\\.bsp");

HookedFuncStatic<char __fastcall, const char*, __int64, __int64, __int64> _sub_18019FB30("engine.dll", 0x19FB30);

char __fastcall sub_18019FB30(const char* a1, __int64 a2, __int64 a3, __int64 a4)
{
/*
sub_18019FB30: a1 = vpk/client_mp_common.bsp, a2 = 1, a3 = 0, a4 = 0
IFileSystem::AddSearchPath: path = ., pathID = MAIN, addType = 1
sub_18019FB30: a1 = vpk/mp_lobby.bsp, a2 = 2, a3 = 1, a4 = 293339137
sub_18019FB30: a1 = vpk/mp_lobby.bsp, a2 = 2, a3 = 0, a4 = 0
IFileSystem::AddSearchPath: path = maps/mp_lobby.bsp, pathID = GAME, addType = 0
IFileSystem::AddSearchPath: path = maps/mp_lobby.bsp, pathID = GAME, addType = 0

sub_18019FB30: a1 = vpk/mp_fracture.bsp, a2 = 2, a3 = 0, a4 = 0 // in lobby
*/
    SPDLOG_LOGGER_TRACE(spdlog::get("logger"), "sub_18019FB30: a1 = {}, a2 = {}, a3 = {}, a4 = {}", a1, a2, a3, a4);
    char res = _sub_18019FB30(a1, a2, a3, a4);
    //_sub_18019FB30("vpk/client_mp_bme.bsp", 1, 0, 0); // no crash
    //_sub_18019FB30("vpk/mp_bme.bsp", 2, 0, 0);
    //_sub_18019FB30("vpk/mp_bme.bsp", 2, 1, 0); // no crash, but slow, and on map load it yeets "BSP Version is too old. Please recompile the map."
    return res;
}

FileSystemManager::FileSystemManager(const std::string& basePath, ConCommandManager& conCommandManager) :
    m_engineFileSystem("filesystem_stdio.dll", "VFileSystem017")
{
    m_logger = spdlog::get("logger");
    if (basePath[basePath.size()] == '\\' || basePath[basePath.size()] == '/')
    {
        m_basePath = basePath.substr(0, basePath.size() - 1);
    }
    else
    {
        m_basePath = basePath;
    }

    m_logger->info("Base path: {}", m_basePath);
    //m_compiledPath = m_basePath / "compiled_assets";
    m_compiledPath = m_basePath / "r1_modsrc";
    m_dumpPath = m_basePath / "assets_dump";
    m_modsPath = m_basePath / "mods";
    m_savesPath = m_basePath / "saves";
    m_spawnlistsPath = m_basePath / "spawnlists";

    m_requestingOriginalFile = false;
    m_blockingRemoveAllMapSearchPaths = false;
    //CacheMapVPKs();
    //EnsurePathsCreated();

    // Hook functions
    IFileSystem_AddSearchPath.Hook(m_engineFileSystem->m_vtable, WRAPPED_MEMBER(AddSearchPathHook));
//#ifdef READ_FROM_FILESYSTEM
    IFileSystem_ReadFromCache.Hook(m_engineFileSystem->m_vtable, WRAPPED_MEMBER(ReadFromCacheHook));
//#endif
    IFileSystem_MountVPK.Hook(m_engineFileSystem->m_vtable, WRAPPED_MEMBER(MountVPKHook));
    ReadFileFromVPK.Hook(WRAPPED_MEMBER(ReadFileFromVPKHook));
    RemoveAllMapSearchPaths.Hook(WRAPPED_MEMBER(RemoveAllMapSearchPathsHook));
    conCommandManager.RegisterCommand("dump_scripts", WRAPPED_MEMBER(DumpAllScripts), "Dump all scripts to development folder", 0);

#ifdef _DEBUG
    _sub_18019FB30.Hook(sub_18019FB30);
#endif

#ifdef READ_FROM_BSP
    SPDLOG_LOGGER_DEBUG(m_logger, "Amount of files in fileSystemContentsSet: {}", fileSystemContentsSet.size());
#endif
}



void FileSystemManager::CacheMapVPKs()
{
    for (auto& file : fs::directory_iterator("vpk"))
    {
        if (!fs::is_regular_file(file))
        {
            continue;
        }

        std::string fileName = file.path().filename().generic_string();
        std::smatch m;
        std::regex_search(fileName, m, s_mapFromVPKRegex);
        if (!m.empty())
        {
            std::string path = "vpk/" + m[0].str();
            if (std::find(m_mapVPKs.begin(), m_mapVPKs.end(), path) == m_mapVPKs.end())
            {
                m_logger->info("Found map VPK: {}", path);
                m_mapVPKs.emplace_back(path);
                m_mapNames.emplace_back(m[1].str());
            }
        }
    }
}

void FileSystemManager::EnsurePathsCreated()
{
    fs::create_directories(m_basePath);
    fs::create_directories(m_dumpPath);
    fs::create_directories(m_compiledPath);
    fs::create_directories(m_modsPath);
    fs::create_directories(m_savesPath);
    fs::create_directories(m_spawnlistsPath);
}

// TODO: Do we maybe need to add the search path in a frame hook or will this do?
// TODO: If the search path has been added and this class is destroyed, should remove the search path
void FileSystemManager::AddSearchPathHook(IFileSystem* fileSystem, const char* pPath, const char* pathID, SearchPathAdd_t addType)
{
    /*
[19:53:11] [thread 27944] [trace] IFileSystem::AddSearchPath: path = C:\Program Files (x86)\Origin Games\Titanfall\TitanFall.exe\platform\config, pathID = CONFIG, addType = 1
[19:53:11] [thread 27944] [trace] IFileSystem::AddSearchPath: path = platform, pathID = PLATFORM, addType = 1
[19:53:16] [thread 27944] [info] RunFrame called for the first time
[19:53:18] [thread 27944] [trace] IFileSystem::AddSearchPath: path = ., pathID = MAIN, addType = 1
[19:53:18] [thread 27944] [trace] IFileSystem::AddSearchPath: path = ., pathID = MAIN, addType = 1
[19:53:18] [thread 27944] [trace] IFileSystem::AddSearchPath: path = ., pathID = MAIN, addType = 1
    */

    SPDLOG_LOGGER_TRACE(m_logger, "IFileSystem::AddSearchPath: path = {}, pathID = {}, addType = {}", pPath, pathID != nullptr ? pathID : "", addType);

    // Add the path as intended
    IFileSystem_AddSearchPath(fileSystem, pPath, pathID, addType);

    // Add our search path to the head again to make sure we're first
#ifdef READ_FROM_FILESYSTEM
    //IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    //IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
#else
    //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "GAME", PATH_ADD_TO_HEAD);
    //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "MAIN", PATH_ADD_TO_HEAD);
    m_blockingRemoveAllMapSearchPaths = true;
    IFileSystem_AddSearchPath(fileSystem, (m_basePath / "bme_test/maps/mp_bme.bsp").string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, (m_basePath / "bme_test/maps/mp_bme.bsp").string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
    m_blockingRemoveAllMapSearchPaths = false;
#endif
}

bool FileSystemManager::ReadFromCacheHook(IFileSystem* fileSystem, const char* path, void* result)
{
    // If the path is one of our replacements, we will not allow the cache to respond
#ifdef READ_FROM_FILESYSTEM
    if (ShouldReplaceFile(path))
    {
        SPDLOG_LOGGER_TRACE(m_logger, "IFileSystem::ReadFromCache: blocking cache response for {}", path);
        return false;
    }
#else
    //std::string pstr{ path };
    //char* p = (char*)pstr.c_str();
    //Util::FixSlashes((char*)p, '/');
    if (ShouldReplaceFile(path) /*&& fileSystemContentsBlockedFromCacheSet.find(path) == fileSystemContentsBlockedFromCacheSet.end()*/)
    {
        //fileSystemContentsBlockedFromCacheSet.emplace(path); // unfortunately looks like we need to be blocking it every time
        ///////SPDLOG_LOGGER_TRACE(m_logger, "IFileSystem::ReadFromCache: blocking cache response for {}", path);
        return false;
    }
#endif

    bool res = IFileSystem_ReadFromCache(fileSystem, path, result);
    /////SPDLOG_LOGGER_TRACE(m_logger, "IFileSystem::ReadFromCache: path = {}, res = {}", path, res);

    return res;
}

FileHandle_t FileSystemManager::ReadFileFromVPKHook(VPKData* vpkInfo, __int32* b, const char* filename)
{
    // We hook the code here to build the mods before scripts.rson is loaded for the first time.
    // It can't be done in a frame hook because scripts.rson has already been loaded by the time
    // the first tick happens.
    /*static bool scriptsLoadedOnce = false;
    if (!scriptsLoadedOnce)
    {
        scriptsLoadedOnce = true;
        try
        {
            SDK().GetModManager().CompileMods();
        }
        catch (std::exception& e)
        {
            m_logger->error("Failed to compile mods: {}", e.what());
        }

        IFileSystem_AddSearchPath(m_engineFileSystem, m_compiledPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    }*/

    // If the path is one of our replacements, we will not allow the read from the VPK to happen
    if (ShouldReplaceFile(filename))
    {
        //SPDLOG_LOGGER_DEBUG(m_logger, "ReadFileFromVPK: blocking response for {} from {}", filename, vpkInfo->path);
        //FileHandle_t result = ReadFileFromVPK(IFileSystem_MountVPK(m_engineFileSystem, "c:\\program files (x86)\\origin games\\titanfall\\vpk\\client_mp_bme.bsp.pak000"), b, filename);
        //return result;
        *b = -1;
        return b;
    }

    FileHandle_t result = ReadFileFromVPK(vpkInfo, b, filename);
    /////SPDLOG_LOGGER_TRACE(m_logger, "ReadFileFromVPK: vpk = {}, file = {}, result = {}", vpkInfo->path, filename, *b);

    if (*b != -1)
    {
        std::string strVPK(vpkInfo->path);
        std::smatch m;
        std::regex_search(strVPK, m, s_mapFromVPKRegex);
        if (!m.empty())
        {
            m_lastMapReadFrom = m[1];
        }
    }

    return result;
}

// TODO: If we have mounted other VPKs and we unload the DLL, should we unmount them?
VPKData* FileSystemManager::MountVPKHook(IFileSystem* fileSystem, const char* vpkPath)
{
    /////SPDLOG_LOGGER_TRACE(m_logger, "IFileSystem::MountVPK: vpkPath = {}", vpkPath);
    // When a level is loaded, the VPK for the map is mounted, so we'll mount every
    // other map's VPK at the same time.
    // TODO: This might be better moved to a hook on the function that actually loads up the map?

    //test
#ifdef READ_FROM_FILESYSTEM
    //IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    //IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
#else
    static bool didAddAlready = false;
    if (!didAddAlready) {
        //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "GAME", PATH_ADD_TO_HEAD);
        //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "MAIN", PATH_ADD_TO_HEAD);
        m_blockingRemoveAllMapSearchPaths = true;
        IFileSystem_AddSearchPath(fileSystem, (m_basePath / "bme_test/maps/mp_bme.bsp").string().c_str(), "GAME", PATH_ADD_TO_HEAD);
        IFileSystem_AddSearchPath(fileSystem, (m_basePath / "bme_test/maps/mp_bme.bsp").string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
        m_blockingRemoveAllMapSearchPaths = false;
        didAddAlready = true;
    }
#endif

    VPKData* res = IFileSystem_MountVPK(fileSystem, vpkPath);
    
    //MountAllVPKs();
    
    return res;
}

const std::vector<std::string>& FileSystemManager::GetMapNames()
{
    return m_mapNames;
}

const std::string& FileSystemManager::GetLastMapReadFrom()
{
    return m_lastMapReadFrom;
}

void FileSystemManager::MountAllVPKs()
{
    //for (const auto& otherMapVPK : m_mapVPKs)
    //{
    //std::string otherMapVPK{"C:\\Program Files (x86)\\Origin Games\\Titanfall\\packedVPK"};
    /*std::string otherMapVPK{"c:\\program files (x86)\\origin games\\titanfall\\packedvpk\\client_mp_bme.bsp.pak000"};

        /////SPDLOG_LOGGER_TRACE(m_logger, "Mounting VPK: {}", otherMapVPK);
        VPKData* injectedRes = IFileSystem_MountVPK(m_engineFileSystem, otherMapVPK.c_str());
        if (injectedRes == nullptr)
        {
            m_logger->error("Failed to mount VPK: {}", otherMapVPK);
        }*/
    //}
}

bool FileSystemManager::FileExists(const char* fileName, const char* pathID)
{
    m_requestingOriginalFile = true;
    bool result = m_engineFileSystem->m_vtable2->FileExists(&m_engineFileSystem->m_vtable2, fileName, pathID);
    m_requestingOriginalFile = false;
    return result;
}

std::string FileSystemManager::ReadOriginalFile(const char* path, const char* pathID)
{
    std::string normalisedPath(path);
    Util::FindAndReplaceAll(normalisedPath, "\\", "/");

    m_requestingOriginalFile = true;
    FileHandle_t handle = m_engineFileSystem->m_vtable2->Open(&m_engineFileSystem->m_vtable2, normalisedPath.c_str(), "rb", "GAME", 0);
    m_requestingOriginalFile = false;

    if (handle == nullptr)
    {
        throw std::runtime_error(fmt::format("Failed to open original file {}", normalisedPath));
    }

    std::stringstream ss;
    int readBytes = 0;
    char data[4096];
    do
    {
        readBytes = m_engineFileSystem->m_vtable2->Read(&m_engineFileSystem->m_vtable2, data, std::size(data), handle);
        ss.write(data, readBytes);
    } while (readBytes == std::size(data));

    m_engineFileSystem->m_vtable2->Close(m_engineFileSystem, handle);
    return ss.str();
}

bool FileSystemManager::ShouldReplaceFile(const std::string& path)
{
    //return false;
    if (m_requestingOriginalFile)
    {
        return false;
    }

#ifdef READ_FROM_BSP
    char* p = (char*)path.c_str();
    Util::FixSlashes(p, '/');
    if (fileSystemContentsSet.find(p) != fileSystemContentsSet.end())
        return true;
    return false;
#else
    // TODO: See if this is worth optimising by keeping a map in memory of the available files
    std::ifstream f(m_compiledPath / path);
    return f.good();
#endif
}

void FileSystemManager::DumpFile(FileHandle_t handle, const std::string& dir, const std::string& path)
{
    if (handle == nullptr)
    {
        return;
    }

    fs::create_directories(m_dumpPath / dir);
    std::ofstream f(m_dumpPath / path, std::ios::binary);
    char data[4096];

    int totalBytes = 0;
    int readBytes = 0;
    do
    {
        readBytes = m_engineFileSystem->m_vtable2->Read(&m_engineFileSystem->m_vtable2, data, std::size(data), handle);
        f.write(data, readBytes);
        totalBytes += readBytes;
    } while (readBytes == std::size(data));

    SPDLOG_LOGGER_TRACE(m_logger, "Wrote {} bytes to {}", totalBytes, path);
}

void FileSystemManager::DumpVPKScripts(const std::string& vpkPath)
{
    m_logger->info("Dumping scripts from {}...", vpkPath);
    VPKData* result = IFileSystem_MountVPK(m_engineFileSystem, vpkPath.c_str());
    if (result == nullptr)
    {
        m_logger->error("Failed to dump scripts from {}", vpkPath);
        return;
    }

    for (int i = 0; i < result->numEntries; i++)
    {
        // Only process files in scripts
        if (strncmp(result->entries[i].directory, "scripts", 7) != 0)
        {
            continue;
        }

        // TODO: Better error handling here
        m_requestingOriginalFile = true;
        std::string path = fmt::format("{}/{}.{}", result->entries[i].directory, result->entries[i].filename, result->entries[i].extension);
        Util::FindAndReplaceAll(path, "\\", "/");
        SPDLOG_LOGGER_TRACE(m_logger, "Dumping {}", path);
        FileHandle_t handle = m_engineFileSystem->m_vtable2->Open(&m_engineFileSystem->m_vtable2, path.c_str(), "rb", "GAME", 0);
        SPDLOG_LOGGER_TRACE(m_logger, "Handle = {}", handle);
        DumpFile(handle, result->entries[i].directory, path); // TODO: Refactor this
        m_engineFileSystem->m_vtable2->Close(m_engineFileSystem, handle);
        m_requestingOriginalFile = false;
    }
}

void FileSystemManager::DumpAllScripts(const CCommand& args)
{
    fs::remove_all(m_dumpPath);
    for (const auto& vpk : m_mapVPKs)
    {
        DumpVPKScripts(vpk);
    }
    m_logger->info("Script dump complete!");
}

unsigned __int64 __fastcall FileSystemManager::RemoveAllMapSearchPathsHook(__int64 thisptr)
{
    if (m_blockingRemoveAllMapSearchPaths)
        return 0;
    return RemoveAllMapSearchPaths(thisptr);
}

const fs::path& FileSystemManager::GetBasePath()
{
    return m_basePath;
}

const fs::path& FileSystemManager::GetModsPath()
{
    return m_modsPath;
}

const fs::path& FileSystemManager::GetCompilePath()
{
    return m_compiledPath;
}

const fs::path& FileSystemManager::GetSavesPath()
{
    return m_savesPath;
}

const fs::path& FileSystemManager::GetSpawnlistsPath()
{
    return m_spawnlistsPath;
}