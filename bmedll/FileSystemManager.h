#pragma once

#include "pch.h"
#include "IFileSystem.h"

struct PathEqual
{
public:
    bool operator()(const fs::path& p1, const fs::path& p2) const
    {
        return p1 == p2;
    }
};

struct PathHash
{
public:
    size_t operator()(const fs::path& p) const
    {
        return fs::hash_value(p);
    }
};

class FileSystemManager
{
private:
    static std::regex s_mapFromVPKRegex;

    std::shared_ptr<spdlog::logger> m_logger;
    SourceInterface<IFileSystem> m_engineFileSystem;
    fs::path m_basePath;
    fs::path m_bspPath;
    fs::path m_customFilesPath;
    bool m_requestingOriginalFile;
    bool m_blockingRemoveAllMapSearchPaths;
    std::unordered_set<fs::path, PathHash, PathEqual> m_replacementsCachedPaths;

    bool ShouldReplaceFile(const std::string_view& path);

public:
    FileSystemManager(const std::string& basePath);
    ~FileSystemManager();

    void AddSearchPathHook(IFileSystem* fileSystem, const char* pPath, const char* pathID, SearchPathAdd_t addType);
    bool ReadFromCacheHook(IFileSystem* fileSystem, const char* path, void* result);
    FileHandle_t ReadFileFromVPKHook(VPKData* vpkInfo, __int32* b, const char* filename);
    unsigned __int64 __fastcall RemoveAllMapSearchPathsHook(__int64 thisptr);
    VPKData* MountVPKHook(IFileSystem* fileSystem, const char* vpkPath);
    void AddVPKFileHook(IFileSystem* fileSystem, char const* pBasename, void* a3, bool a4, SearchPathAdd_t addType, bool a6);

    bool FileExists(const char* fileName, const char* pathID);
    std::string ReadOriginalFile(const char* path, const char* pathID);

    void RefreshReplacementsCache(bool debugLogLoadedFiles);
    void RefreshReplacementsCacheCC(const CCommand& args);

    const fs::path& GetBasePath();
    const fs::path& GetCustomFilesPath();
};