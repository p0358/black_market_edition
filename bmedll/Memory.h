#pragma once

//#ifndef OVERRIDE_REDEFINE_H_
//#define OVERRIDE_REDEFINE_H_

#include <cstring>
#include <new>

class IMemAlloc
{
public:
    struct VTable
    {
        void* unknown[1]; // alloc debug
        void* (*Alloc) (IMemAlloc* memAlloc, size_t nSize);
        void* unknown2[1]; // realloc debug
        void* (*Realloc)(IMemAlloc* memAlloc, void* pMem, size_t nSize);
        void* unknown3[1]; // free #1
        void (*Free) (IMemAlloc* memAlloc, void* pMem);
        void* unknown4[2]; // nullsubs, maybe CrtSetDbgFlag
        size_t (*GetSize) (IMemAlloc* memAlloc, void* pMem);
        void* unknown5[9]; // they all do literally nothing
        void (*DumpStats) (IMemAlloc* memAlloc);
        void (*DumpStatsFileBase) (IMemAlloc* memAlloc, const char* pchFileBase);
        void* unknown6[4];
        int (*heapchk) (IMemAlloc* memAlloc);
    };

    VTable* m_vtable;
};

//void* operator new(std::size_t n);
//void operator delete(void* p) throw();

////////////////////////
////////////////////////
////////////////////////

/*__forceinline void* internal_malloc(size_t size) {
    if (!g_pMemAllocSingleton)
    {
        g_pMemAllocSingleton = CreateGlobalMemAlloc();
    }

    static auto Alloc = g_pMemAllocSingleton->m_vtable->Alloc;
    return Alloc(g_pMemAllocSingleton, size);
}

__forceinline void internal_free(void* p) {
    if (!g_pMemAllocSingleton)
    {
        g_pMemAllocSingleton = CreateGlobalMemAlloc();
    }

    static auto Free = g_pMemAllocSingleton->m_vtable->Free;
    return Free(g_pMemAllocSingleton, p);
}

__forceinline void* internal_calloc(size_t n, size_t size) {
    if (!g_pMemAllocSingleton)
    {
        g_pMemAllocSingleton = CreateGlobalMemAlloc();
    }

    static auto Alloc = g_pMemAllocSingleton->m_vtable->Alloc;
    void* p = Alloc(g_pMemAllocSingleton, n * size);
    memset(p, 0, n * size);
    return p;
}

__forceinline void* internal_realloc(void* old_ptr, size_t size) {
    if (!g_pMemAllocSingleton)
    {
        g_pMemAllocSingleton = CreateGlobalMemAlloc();
    }

    static auto Realloc = g_pMemAllocSingleton->m_vtable->Realloc;
    return Realloc(g_pMemAllocSingleton, old_ptr, size);
}*/

////////////////////////
////////////////////////
////////////////////////

void* operator new(size_t size);
void operator delete(void* p) noexcept;
void* operator new[](size_t size);
void operator delete[](void* p) noexcept;
void* operator new(size_t size, const std::nothrow_t& nt) noexcept;
void* operator new[](size_t size, const std::nothrow_t& nt) noexcept;
void operator delete(void* ptr, const std::nothrow_t& nt) noexcept;
void operator delete[](void* ptr, const std::nothrow_t& nt) noexcept;

// sized delete
void operator delete(void* p, size_t s) noexcept;
void operator delete[](void* p, size_t s) noexcept;

// aligned new/delete
void* operator new(size_t size, std::align_val_t al);
void operator delete(void* p, std::align_val_t al) noexcept;
void* operator new[](size_t size, std::align_val_t al);
void operator delete[](void* p, std::align_val_t al) noexcept;
void* operator new(size_t size, std::align_val_t al, const std::nothrow_t& nt) noexcept;
void* operator new[](size_t size, std::align_val_t al, const std::nothrow_t& nt) noexcept;
void operator delete(void* ptr, std::align_val_t al, const std::nothrow_t& nt) noexcept;
void operator delete[](void* ptr, std::align_val_t al, const std::nothrow_t& nt) noexcept;

// sized aligned delete
void operator delete(void* p, size_t s, std::align_val_t al) noexcept;
void operator delete[](void* p, size_t s, std::align_val_t al) noexcept;

extern "C" {
    void* malloc(size_t s);
    void  free(void* p);
    void* realloc(void* p, size_t s);
    void* calloc(size_t n, size_t s);
    void  cfree(void* p);
    void* memalign(size_t a, size_t s);
    void* aligned_alloc(size_t a, size_t s);
    void* valloc(size_t s);
    void* pvalloc(size_t s);
    int posix_memalign(void** r, size_t a, size_t s);
    void malloc_stats(void);
    /*int mallopt(int cmd, int v) { return tc_mallopt(cmd, v); }
#ifdef HAVE_STRUCT_MALLINFO
    struct mallinfo mallinfo(void) { return tc_mallinfo(); }
#endif*/
    size_t malloc_size(void* p);
    size_t malloc_usable_size(void* p);
}  // extern "C"

extern "C" {

    void* _malloc_base(size_t size);
    void _free_base(void* p);
    void* _calloc_base(size_t n, size_t size);
    void* _recalloc_base(void* old_ptr, size_t n, size_t size);
    void* _calloc_impl(size_t n, size_t size);
    size_t _msize_base(void* p);

}

//#endif
