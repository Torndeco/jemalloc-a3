#ifdef ARMA_EXTENSION
#include <windows.h>
#ifndef __cplusplus
typedef BOOL bool;
#endif

#include "jemalloc.h"
#include "jemalloc/internal/jemalloc_internal.h"
#include <stdlib.h>

__declspec(dllexport) size_t __stdcall MemTotalCommitted() { return MappedMemory; }
__declspec(dllexport) size_t __stdcall MemTotalReserved() { return MappedMemory; }

__declspec(dllexport) size_t __stdcall MemFlushCache(size_t size) { return size; }
__declspec(dllexport) void __stdcall MemFlushCacheAll() { tcache_flush(); }
__declspec(dllexport) size_t __stdcall MemSize(void *mem) { return je_malloc_usable_size(mem); }
__declspec(dllexport) void *__stdcall MemAlloc(size_t size) { return je_malloc(size); }
__declspec(dllexport) void __stdcall MemFree(void *mem) { je_free(mem); }

BOOL WINAPI DllMain( HINSTANCE hInst, DWORD callReason, LPVOID c)
{
  if (callReason==DLL_PROCESS_ATTACH)
  {
    je_init();
  }
  else if (callReason==DLL_PROCESS_DETACH)
  {
	je_uninit();
  }
  return TRUE;
}
#endif
