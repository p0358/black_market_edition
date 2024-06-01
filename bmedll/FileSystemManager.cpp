#include "pch.h"
#include "TTFSDK.h"
#include "VTableHooking.h"
#include "SigScanning.h"
#include "IFileSystem.h"
#include "FileSystemManager.h"
#include <set>

#ifdef _DEBUG
//#define READ_FROM_FILESYSTEM
#define READ_FROM_VPK
#else
#define READ_FROM_BSP
#endif

#ifdef READ_FROM_BSP
#include "FilesystemContents.h"
std::unordered_set<std::string> fileSystemContentsSet{ FILES_COMMA_SEPARATED };
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
HookedVTableFunc<decltype(&IFileSystem::VTable::AddVPKFile), &IFileSystem::VTable::AddVPKFile> IFileSystem_AddVPKFile;
HookedSigScanFunc<FileHandle_t, VPKData*, __int32*, const char*> ReadFileFromVPK("filesystem_stdio.dll", "\x48\x89\x5C\x24\x00\x57\x48\x81\xEC\x00\x00\x00\x00\x49\x8B\xC0\x48\x8B\xDA", "xxxx?xxxx????xxxxxx");
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

VPKData* IFileSystem_MountVPK_Hook(IFileSystem* fileSystem, const char* vpkPath)
{
    if (IsSDKReady())
        return FSManager().MountVPKHook(fileSystem, vpkPath);
    return IFileSystem_MountVPK(fileSystem, vpkPath);
}

FileSystemManager::FileSystemManager(const std::string& basePath)
    : m_engineFileSystem("filesystem_stdio.dll", "VFileSystem017")
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

    m_logger->info("Base path: {}", m_basePath.string());
    m_bspPath = m_basePath / "bme" / "bme.bsp";
    m_customFilesPath = m_basePath / "r1_mod";
    if (!fs::exists(m_bspPath))
        m_logger->error("bsp file does not exist at: {}", m_bspPath.string().c_str());
    if (!fs::exists(m_customFilesPath))
        fs::create_directories(m_customFilesPath);

    m_requestingOriginalFile = false;
    m_blockingRemoveAllMapSearchPaths = false;

    // Hook functions
    IFileSystem_AddSearchPath.Hook(m_engineFileSystem->m_vtable, WRAPPED_MEMBER(AddSearchPathHook));
#ifndef READ_FROM_VPK
    IFileSystem_ReadFromCache.Hook(m_engineFileSystem->m_vtable, WRAPPED_MEMBER(ReadFromCacheHook));
#endif
    //IFileSystem_MountVPK.Hook(m_engineFileSystem->m_vtable, WRAPPED_MEMBER(MountVPKHook));
    IFileSystem_MountVPK.Hook(m_engineFileSystem->m_vtable, IFileSystem_MountVPK_Hook);
    /*using my_lambda_type = VPKData* (*)(IFileSystem*, const char*);
    //my_lambda_type my_func = [this](void* a1, HWND a2, UINT a3, WPARAM a4, LPARAM a5) -> int {return 0;/ *this->WindowProcHook(a1, a2, a3, a4, a5);* / };
    my_lambda_type a = [](IFileSystem* a1, const char* a2) -> VPKData* {
        //if (&UIMan() == nullptr) return 0;
        if (isProcessTerminating) return IFileSystem_MountVPK(a1, a2);
        if (&FSManager() == nullptr) return IFileSystem_MountVPK(a1, a2);
        return FSManager().MountVPKHook(a1, a2);
    };
    IFileSystem_MountVPK.Hook(m_engineFileSystem->m_vtable, a);*/

    IFileSystem_AddVPKFile.Hook(m_engineFileSystem->m_vtable, WRAPPED_MEMBER(AddVPKFileHook));
    ReadFileFromVPK.Hook(WRAPPED_MEMBER(ReadFileFromVPKHook));
    RemoveAllMapSearchPaths.Hook(WRAPPED_MEMBER(RemoveAllMapSearchPathsHook));
    ConCommandManager& conCommandManager = SDK().GetConCommandManager();
    conCommandManager.RegisterCommand("fs_replacements_cache_refresh", WRAPPED_MEMBER(RefreshReplacementsCacheCC), "", 0);

#ifdef _DEBUG
    _sub_18019FB30.Hook(sub_18019FB30);
#endif

#ifdef READ_FROM_BSP
    SPDLOG_LOGGER_DEBUG(m_logger, "Amount of files in fileSystemContentsSet: {}", fileSystemContentsSet.size());
#endif
}

FileSystemManager::~FileSystemManager()
{
    SPDLOG_LOGGER_DEBUG(m_logger, "FileSystemManager destructor");
    IFileSystem_AddSearchPath.Unhook();
    IFileSystem_ReadFromCache.Unhook();
    IFileSystem_MountVPK.Unhook();
    IFileSystem_AddVPKFile.Unhook();
    ReadFileFromVPK.Unhook();
    RemoveAllMapSearchPaths.Unhook();
    _sub_18019FB30.Unhook();
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

    m_logger->debug("IFileSystem::AddSearchPath: path = {}, pathID = {}, addType = {}", pPath, pathID != nullptr ? pathID : "", (int)addType);

    // Add the path as intended
    IFileSystem_AddSearchPath(fileSystem, pPath, pathID, addType);

    // Add our search path to the head again to make sure we're first
#ifdef READ_FROM_FILESYSTEM
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MOD", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MATERIALS", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "CONTENT", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "PLATFORM", PATH_ADD_TO_HEAD);
#else
#ifdef READ_FROM_BSP
    //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "GAME", PATH_ADD_TO_HEAD);
    //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "MAIN", PATH_ADD_TO_HEAD);
    m_blockingRemoveAllMapSearchPaths = true;
    IFileSystem_AddSearchPath(fileSystem, m_bspPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_bspPath.string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
    m_blockingRemoveAllMapSearchPaths = false;
#else
#ifdef READ_FROM_VPK
    static bool didAddAlready = false;
    if (!didAddAlready) {
        //fileSystem->AddVPKFile((m_basePath / "packedVPK/pak000.vpk").string().c_str(), PATH_ADD_TO_HEAD);
    }
#endif
#endif
#endif
    IFileSystem_AddSearchPath(fileSystem, m_customFilesPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_customFilesPath.string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
}

void FileSystemManager::AddVPKFileHook(IFileSystem* fileSystem, char const* pBasename, void* a3, bool a4, SearchPathAdd_t addType, bool a6)
{
    m_logger->debug("IFileSystem::AddVPKFile: {} {} {} {} {}", pBasename, a3, a4, (int)addType, a6);
    // IFileSystem::AddVPKFile: 16426288 vpk/client_mp_common.bsp.pak000
    // IFileSystem::AddVPKFile: vpk/client_mp_common.bsp.pak000 12233712 140716965429248 1 140717081273089
    // IFileSystem::AddVPKFile: vpk/client_mp_common.bsp.pak000 18524032 140716965429248 1 140717081273089
    // IFileSystem::AddVPKFile: vpk/client_mp_fracture.bsp.pak000 18521936 140716965429248 1 140717081273089
    // IFileSystem::AddVPKFile: vpk/client_mp_corporate.bsp.pak000 18521936 140716965429248 1 140717081273089

    //IFileSystem_AddVPKFile(fileSystem, "packedVPK/pak000", PATH_ADD_TO_HEAD, 1, 1, 0);
    //IFileSystem_AddVPKFile(fileSystem, "packedVPK/pak000", addType, a1, a2, a3);

    IFileSystem_AddVPKFile(fileSystem, pBasename, a3, a4, addType, a6);
#ifdef READ_FROM_VPK
    //static bool didAddAlready = false;
    //if (!didAddAlready) {
        //fileSystem->AddVPKFile((m_basePath / "packedVPK/pak000.vpk").string().c_str(), PATH_ADD_TO_HEAD);
        //IFileSystem_AddVPKFile(fileSystem, (m_basePath / "packedVPK/pak000.vpk").string().c_str(), PATH_ADD_TO_HEAD, 1, 1, 0);
        //IFileSystem_AddVPKFile(fileSystem, "packedVPK/pak000", PATH_ADD_TO_HEAD, 1, 1, 0);
        //IFileSystem_AddVPKFile(fileSystem, "packedVPK/pak000", addType, a1, a2, a3);
        //IFileSystem_AddVPKFile(fileSystem, "packedVPK/pak000", (SearchPathAdd_t)18521936, a1, a2, a3);
    //}
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

    /*if (*b != -1)
    {
        std::string strVPK(vpkInfo->path);
        std::smatch m;
        std::regex_search(strVPK, m, s_mapFromVPKRegex);
        if (!m.empty())
        {
            m_lastMapReadFrom = m[1];
        }
    }*/

    return result;
}

// TODO: If we have mounted other VPKs and we unload the DLL, should we unmount them?
VPKData* FileSystemManager::MountVPKHook(IFileSystem* fileSystem, const char* vpkPath)
{
    //m_logger->debug("IFileSystem::MountVPK: vpkPath = {}", vpkPath); // spams while in main menu???
    // When a level is loaded, the VPK for the map is mounted, so we'll mount every
    // other map's VPK at the same time.
    // TODO: This might be better moved to a hook on the function that actually loads up the map?

#ifdef READ_FROM_FILESYSTEM
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
    /*IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MOD", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "MATERIALS", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "CONTENT", PATH_ADD_TO_HEAD);
    IFileSystem_AddSearchPath(fileSystem, m_compiledPath.string().c_str(), "PLATFORM", PATH_ADD_TO_HEAD);*/
#else
#ifdef READ_FROM_BSP
    static bool didAddAlready = false;
    if (!didAddAlready) {
        //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "GAME", PATH_ADD_TO_HEAD);
        //IFileSystem_AddSearchPath(fileSystem, "maps/mp_bme.bsp", "MAIN", PATH_ADD_TO_HEAD);
        m_blockingRemoveAllMapSearchPaths = true;
        IFileSystem_AddSearchPath(fileSystem, m_bspPath.string().c_str(), "GAME", PATH_ADD_TO_HEAD);
        IFileSystem_AddSearchPath(fileSystem, m_bspPath.string().c_str(), "MAIN", PATH_ADD_TO_HEAD);
        m_blockingRemoveAllMapSearchPaths = false;
        didAddAlready = true;
    }
#else
#ifdef READ_FROM_VPK
    static bool didAddAlready = false;
    if (!didAddAlready) {
        //fileSystem->AddVPKFile((m_basePath / "packedVPK/pak000.vpk").string().c_str(), PATH_ADD_TO_HEAD);
    }
#endif
#endif
#endif

    VPKData* res = IFileSystem_MountVPK(fileSystem, vpkPath);

    //SPDLOG_LOGGER_TRACE(m_logger, "IFileSystem::MountVPK: vpkPath = {}, addr1 = {}, addr2 = {}, numEntries = {}, entry1 = ", res->path, (void*)res, (void*)&res, res->numEntries/*, res->entries->directory*/);
    
    //MountAllVPKs();
    
    return res;
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

bool FileSystemManager::ShouldReplaceFile(const std::string_view& path)
{
    //return false;
    if (m_requestingOriginalFile)
    {
        return false;
    }

    if (m_replacementsCachedPaths.size() > 0)
    {
        std::string copy{ path };
        _strlwr_s(&copy[0], copy.size() + 1);
        fs::path path{ copy };
        path = path.lexically_normal();
        if (m_replacementsCachedPaths.contains(path))
            return true;
    }

#ifdef READ_FROM_BSP
    //char* p = (char*)path.data();
    std::string copy{ path };
    char* p = (char*)copy.c_str();
    Util::FixSlashes(p, '/');
    if (fileSystemContentsSet.find(p) != fileSystemContentsSet.end())
        return true;
    return false;
#else
#ifdef READ_FROM_FILESYSTEM
    // TODO: See if this is worth optimising by keeping a map in memory of the available files
    std::ifstream f(m_compiledPath / path);
    return f.good();
#else
#ifdef READ_FROM_VPK
    return false;
#endif
#endif
#endif
}

unsigned __int64 __fastcall FileSystemManager::RemoveAllMapSearchPathsHook(__int64 thisptr)
{
    if (m_blockingRemoveAllMapSearchPaths)
        return 0;
    return RemoveAllMapSearchPaths(thisptr);
}

void FileSystemManager::RefreshReplacementsCache(bool debugLogLoadedFiles)
{
    auto startTime = std::chrono::system_clock::now();
    try
    {
        std::vector<fs::path> replacements_cached_paths_new{};
        auto& scanpath = m_customFilesPath;

        if (fs::exists(scanpath))
        {
            for (auto& entry : fs::recursive_directory_iterator(scanpath))
            {
                if (!entry.is_directory())
                {
                    // apparently fs::relative is super expensive for whatever reason
                    ////auto filepath = fs::relative(entry.path(), scanpath);// .lexically_normal(); // lexically_normal in this case changed literally nothing
                    ////_wcslwr_s((wchar_t*)filepath.native().c_str(), filepath.native().length() * 2); // lower case, fucky way but it works
                    if (entry.path().native().length() <= scanpath.native().length() + 1) [[unlikely]]
                    {
                        spdlog::error("[RefreshReplacementsCache] invalid path \"{}\"", Util::Narrow(entry.path().native()));
                        continue;
                    }
                    std::wstring_view filepath{ entry.path().native().c_str() + scanpath.native().length() + 1 }; // no copy
                    _wcslwr_s((wchar_t*)filepath.data(), filepath.length() * 2); // lower case, fucky way but it works

                    auto filepath_narrow = Util::Narrow(filepath);

                    if (FileExists(filepath_narrow.c_str(), "GAME") || FileExists(filepath_narrow.c_str(), "MAIN"))
                    {
                        replacements_cached_paths_new.push_back(filepath);
                        if (debugLogLoadedFiles)
                            spdlog::debug("[RefreshReplacementsCache] Adding: {}", filepath_narrow.c_str());
                    }
                }
            }
        }

        m_replacementsCachedPaths.clear();
        m_replacementsCachedPaths.reserve(replacements_cached_paths_new.size());
        std::copy(replacements_cached_paths_new.begin(), replacements_cached_paths_new.end(), std::inserter(m_replacementsCachedPaths, m_replacementsCachedPaths.end()));
    }
    catch (std::exception& e)
    {
        // it will throw errors if paths are not found...
        spdlog::error("Error in fs_replacements_cache_refresh: {}", e.what());
    }
    spdlog::info("Refreshed replacements cache, amount of loaded files: {} (took {} ms)",
        m_replacementsCachedPaths.size(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count());
}

void FileSystemManager::RefreshReplacementsCacheCC(const CCommand& args)
{
    RefreshReplacementsCache(args.ArgC() > 1);
}

const fs::path& FileSystemManager::GetBasePath()
{
    return m_basePath;
}

const fs::path& FileSystemManager::GetCustomFilesPath()
{
    return m_customFilesPath;
}
