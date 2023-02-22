#include "pch.h"

#include "tier0.h"
#include "Memory.h"

decltype(IMemAlloc::VTable::Alloc) Alloc;
decltype(IMemAlloc::VTable::Realloc) Realloc;
decltype(IMemAlloc::VTable::Free) Free;
decltype(IMemAlloc::VTable::GetSize) GetSize;
decltype(IMemAlloc::VTable::DumpStats) DumpStats;
decltype(IMemAlloc::VTable::heapchk) heapchk;

__forceinline void* internal_malloc(size_t size) {
    if (!g_pMemAllocSingleton) [[unlikely]] g_pMemAllocSingleton = CreateGlobalMemAlloc();
    if (!Alloc) [[unlikely]] Alloc = g_pMemAllocSingleton->m_vtable->Alloc;
    return Alloc(g_pMemAllocSingleton, size);
}

__forceinline void internal_free(void* p) {
    if (!g_pMemAllocSingleton) [[unlikely]] g_pMemAllocSingleton = CreateGlobalMemAlloc();
    if (!Free) [[unlikely]] Free = g_pMemAllocSingleton->m_vtable->Free;
    return Free(g_pMemAllocSingleton, p);
}

__forceinline void* internal_calloc(size_t n, size_t size) {
    if (!g_pMemAllocSingleton) [[unlikely]] g_pMemAllocSingleton = CreateGlobalMemAlloc();
    if (!Alloc) [[unlikely]] Alloc = g_pMemAllocSingleton->m_vtable->Alloc;
    void* p = Alloc(g_pMemAllocSingleton, n * size);
    memset(p, 0, n * size);
    return p;
}

__forceinline void* internal_realloc(void* old_ptr, size_t size) {
    if (!g_pMemAllocSingleton) [[unlikely]] g_pMemAllocSingleton = CreateGlobalMemAlloc();
    if (!Realloc) [[unlikely]] Realloc = g_pMemAllocSingleton->m_vtable->Realloc;
    return Realloc(g_pMemAllocSingleton, old_ptr, size);
}

__forceinline size_t internal_getsize(void* p)
{
    if (!g_pMemAllocSingleton) [[unlikely]] g_pMemAllocSingleton = CreateGlobalMemAlloc();
    if (!GetSize) [[unlikely]] GetSize = g_pMemAllocSingleton->m_vtable->GetSize;
    return GetSize(g_pMemAllocSingleton, p);
}

__forceinline void internal_dumpstats(void)
{
    if (!g_pMemAllocSingleton) [[unlikely]] g_pMemAllocSingleton = CreateGlobalMemAlloc();
    if (!DumpStats) [[unlikely]] DumpStats = g_pMemAllocSingleton->m_vtable->DumpStats;
    return DumpStats(g_pMemAllocSingleton);
}

__forceinline int internal_heapchk(void)
{
    if (!g_pMemAllocSingleton) [[unlikely]] g_pMemAllocSingleton = CreateGlobalMemAlloc();
    if (!heapchk) [[unlikely]] heapchk = g_pMemAllocSingleton->m_vtable->heapchk;
    return heapchk(g_pMemAllocSingleton);
}

char* internal_strdup(const char* src)
{
    char* str;
    char* p;
    int len = 0;

    while (src[len])
        len++;
    str = reinterpret_cast<char*>(internal_malloc(len + 1));
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

////////////////////////
////////////////////////
////////////////////////

void* operator new(size_t size) { return internal_malloc(size); }
void operator delete(void* p) noexcept { internal_free(p); }
void* operator new[](size_t size) { return internal_malloc(size);  }
void operator delete[](void* p) noexcept { internal_free(p); }
void* operator new(size_t size, const std::nothrow_t& nt) noexcept { return internal_malloc(size); }
void* operator new[](size_t size, const std::nothrow_t& nt) noexcept { return internal_malloc(size); }
void operator delete(void* ptr, const std::nothrow_t& nt) noexcept { return internal_free(ptr); }
void operator delete[](void* ptr, const std::nothrow_t& nt) noexcept { return internal_free(ptr); }

// sized delete
/*void operator delete(void* p, size_t s) noexcept { internal_free(p); }
void operator delete[](void* p, size_t s) noexcept { internal_free(p); }*/

// aligned new/delete
/*void* operator new(size_t size, std::align_val_t al) { return internal_malloc(size); }
void operator delete(void* p, std::align_val_t al) noexcept { internal_free(p); }
void* operator new[](size_t size, std::align_val_t al) { return internal_malloc(size); }
void operator delete[](void* p, std::align_val_t al) noexcept { internal_free(p); }
void* operator new(size_t size, std::align_val_t al, const std::nothrow_t& nt) noexcept { return internal_malloc(size); }
void* operator new[](size_t size, std::align_val_t al, const std::nothrow_t& nt) noexcept { return internal_malloc(size); }
void operator delete(void* ptr, std::align_val_t al, const std::nothrow_t& nt) noexcept { return internal_free(ptr); }
void operator delete[](void* ptr, std::align_val_t al, const std::nothrow_t& nt) noexcept { return internal_free(ptr); }*/

// sized aligned delete
/*void operator delete(void* p, size_t s, std::align_val_t al) noexcept { internal_free(p); }
void operator delete[](void* p, size_t s, std::align_val_t al) noexcept { internal_free(p); }*/

extern "C" {
    /*_CRTRESTRICT __declspec(noinline) void* malloc(size_t s) { return internal_malloc(s); }
    void  free(void* p) { internal_free(p); }
    _CRTRESTRICT void* realloc(void* p, size_t s) { return internal_realloc(p, s); }
    _CRTRESTRICT void* calloc(size_t n, size_t s) { return internal_calloc(n, s); }*/
    //void  cfree(void* p) { internal_free(p); }

    // hm
    /*void* memalign(size_t a, size_t s) { return internal_malloc(s); }
    void* aligned_alloc(size_t a, size_t s) { return internal_malloc(s); }
    void* valloc(size_t s) { return internal_malloc(s); }
    void* pvalloc(size_t s) { return internal_malloc(s); }
    int posix_memalign(void** r, size_t a, size_t s) {
        if (!s) return NULL;
        auto* ptr = internal_malloc(s);
        *r = ptr;
        return 0;
    }
    void malloc_stats(void) { internal_dumpstats(); }*/

    /*int mallopt(int cmd, int v) { return tc_mallopt(cmd, v); }
#ifdef HAVE_STRUCT_MALLINFO
    struct mallinfo mallinfo(void) { return tc_mallinfo(); }
#endif*/

// hm
/*size_t malloc_size(void* p) { return internal_getsize(p); }
size_t malloc_usable_size(void* p) { return internal_getsize(p); }*/

}  // extern "C"

////////////////////////
////////////////////////
////////////////////////

extern "C" {

    //void* __cdecl _malloc_base(size_t size) { return internal_malloc(size); }
    void* _malloc_base(size_t size) { return internal_malloc(size); }
    void _free_base(void* p) { internal_free(p); }
    void* _realloc_base(void* p, size_t size) { return internal_realloc(p, size); }
    _CRTRESTRICT void* _calloc_base(size_t n, size_t size) { return internal_calloc(n, size); }
    /*void* _recalloc_base(void* old_ptr, size_t n, size_t size) {
        if (!(n == 0 || (std::numeric_limits<size_t>::max)() / n >= size)) {
            errno = ENOMEM;
            return NULL;
        }

        const size_t old_size = internal_getsize(old_ptr);
        const size_t new_size = n * size;

        void* new_ptr = internal_realloc(old_ptr, new_size);

        if (new_ptr != NULL && new_size > old_size) {
            memset(static_cast<char*>(new_ptr) + old_size, 0, new_size - old_size);
        }

        return new_ptr;
    }*/
    void* _recalloc_base(void* old_ptr, size_t n, size_t size) {
        const size_t new_size = n * size;
        void* new_ptr = internal_realloc(old_ptr, new_size);
        if (!new_ptr) {
            memset(new_ptr, 0, new_size);
        }
        return new_ptr;
    }
    /*void* _recalloc_base(void* old_ptr, size_t nSize) {
        const size_t new_size = nSize;
        void* new_ptr = internal_realloc(old_ptr, nSize);
        if (!new_ptr) {
            memset(new_ptr, 0, nSize);
        }
        return new_ptr;
    }*/
    void* _calloc_impl(size_t n, size_t size) { return internal_calloc(n, size); }
    size_t _msize_base(void* p) { return internal_getsize(p); }
    size_t _msize(void* p) { return internal_getsize(p); }
    //size_t msize(void* p) { return internal_getsize(p); }

    void* __cdecl _expand_base(void* pMem, size_t nNewSize, int nBlockUse)
    {
        //Assert(0);
        return NULL;
    }

    void* __cdecl _expand(void* pMem, size_t nSize)
    {
        //Assert(0);
        return NULL;
    }

    // crt
    void* __cdecl _malloc_crt(size_t size)
    {
        return internal_malloc(size);
    }

    void* __cdecl _calloc_crt(size_t count, size_t size)
    {
        return _calloc_base(count, size);
    }

    void* __cdecl _realloc_crt(void* ptr, size_t size)
    {
        return _realloc_base(ptr, size);
    }

    void* __cdecl _recalloc_crt(void* ptr, size_t count, size_t size)
    {
        //return _recalloc_base(ptr, size * count);
        return _recalloc_base(ptr, count, size);
    }

    _CRTRESTRICT void* __cdecl _recalloc(void* memblock, size_t count, size_t size)
    {
        void* pMem = internal_realloc(memblock, size * count);
        if (!memblock)
        {
            memset(pMem, 0, size * count);
        }
        return pMem;
    }

    /*void* __cdecl _heap_alloc(size_t size) { return internal_malloc(size); }
    void* __cdecl _nh_malloc(size_t size, int) { return internal_malloc(size); }*/

    unsigned int _amblksiz = 16; //BYTES_PER_PARA;

    HANDLE _crtheap = (HANDLE)1;	// PatM Can't be 0 or CRT pukes
    int __active_heap = 1;

    /*size_t __cdecl _get_sbh_threshold(void)
    {
        return 0;
    }

    int __cdecl _set_sbh_threshold(size_t)
    {
        return 0;
    }

    int _heapchk()
    {
        return internal_heapchk();
    }

    int _heapmin()
    {
        return 1;
    }

    int __cdecl _heapadd(void*, size_t)
    {
        return 0;
    }

    int __cdecl _heapset(unsigned int)
    {
        return 0;
    }

    size_t __cdecl _heapused(size_t*, size_t*)
    {
        return 0;
    }

    int __cdecl _heapwalk(_HEAPINFO*)
    {
        return 0;
    }*/

    void* malloc_db(size_t nSize, const char* pFileName, int nLine)
    {
        return internal_malloc(nSize);
    }

    void free_db(void* pMem, const char* pFileName, int nLine)
    {
        internal_free(pMem);
    }

    void* realloc_db(void* pMem, size_t nSize, const char* pFileName, int nLine)
    {
        return internal_realloc(pMem, nSize);
    }

    /*int __cdecl _heap_init()
    {
        if (!g_pMemAllocSingleton) g_pMemAllocSingleton = CreateGlobalMemAlloc();
        return g_pMemAllocSingleton != NULL;
    }

    void __cdecl _heap_term()
    {
    }*/

}

extern "C" {
    void* sentry_malloc(size_t size) { return /*internal_malloc*/malloc(size); }
    void* sentry_realloc(void* old_ptr, size_t size) { return /*internal_realloc*/realloc(old_ptr, size); }
    void sentry_free(void* ptr) { /*internal_free*/free(ptr); }
}

#ifndef NDEBUG
#undef malloc
#undef free
#undef calloc

extern "C" void* _malloc_dbg(size_t size, int, const char*, int) {
    return internal_malloc(size);
}

extern "C" void _free_dbg(void* ptr, int) {
    internal_free(ptr);
}

extern "C" void* _calloc_dbg(size_t n, size_t size, int, const char*, int) {
    return internal_calloc(n, size);
}
#endif  // NDEBUG
