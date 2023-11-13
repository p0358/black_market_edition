#pragma once

typedef void* FileHandle_t;

#pragma pack(push,1)
struct VPKFileEntry
{
    char* directory;
    char* filename;
    char* extension;
    unsigned char unknown[0x38];
};
#pragma pack(pop)

#pragma pack(push,1)
struct VPKData
{
    unsigned char unknown[5];
    char path[255];
    unsigned char unknown2[0x134];
    int32_t numEntries;
    unsigned char unknown3[12];
    VPKFileEntry* entries;
};
#pragma pack(pop)

enum SearchPathAdd_t
{
    PATH_ADD_TO_HEAD,		// First path searched
    PATH_ADD_TO_TAIL,		// Last path searched
};

class CSearchPath
{
public:
    unsigned char unknown[0x18];
    const char* debugPath;
};

class IFileSystem
{
public:
    struct VTable
    {
        void* unknown[10];
        void(*AddSearchPath) (IFileSystem* fileSystem, const char* pPath, const char* pathID, SearchPathAdd_t addType); // +80
        /*void(*RemoveSearchPath) (IFileSystem* fileSystem, const char* pPath, const char* pathID, SearchPathAdd_t addType); // +88 (11)
        void* unknown2[4];
        void(*GetSearchPath) (IFileSystem* fileSystem, const char* pathID, bool bGetPackFiles, char* pPath, int nMaxLen); // +128 (16)
        void* unknown3[78];*/
        //void* unknown2[83];


        void* unknown2[84];
        bool(*ReadFromCache) (IFileSystem* fileSystem, const char* path, void* result); // +760
        void* unknown4[15];
        VPKData* (*MountVPK) (IFileSystem* fileSystem, const char* vpkPath); // +888
        void* unknown5[22];
        //void* unknown6[1];
        void (*AddVPKFile) (IFileSystem* fileSystem, char const* pBasename, void* a3, bool a4, SearchPathAdd_t addType, bool a6); // +1072
    };

    struct VTable2
    {
        int(*Read) (IFileSystem::VTable2** fileSystem, void* pOutput, int size, FileHandle_t file);
        void* unknown[1];
        FileHandle_t(*Open) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pOptions, const char* pathID, int64_t unknown);
        void(*Close) (IFileSystem* fileSystem, FileHandle_t file);
        void* unknown2[6];
        bool(*FileExists)(IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPathID);
    };

    VTable* m_vtable;
    VTable2* m_vtable2;

    void AddVPKFile(const char* pPath, SearchPathAdd_t addType) // + 1072
    {
        typedef void(__thiscall* OriginalFn)(PVOID, const char*, SearchPathAdd_t);
        return getvfunc<OriginalFn>(this, 134)(this, pPath, addType);
    }

    // +1080 = RemoveVPKFile
    // +1088 = GetVPKFileNames
};