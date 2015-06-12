#include <windows.h>
#ifndef __cplusplus
typedef BOOL bool;
#endif

#include "jemalloc.h"
#include "jemalloc/internal/jemalloc_internal.h"
#include <stdlib.h>	

#define DLL_EXPORT __declspec(dllexport)

DLL_EXPORT size_t __stdcall MemTotalCommitted() { return MappedMemory; }
DLL_EXPORT size_t __stdcall MemTotalReserved() { return MappedMemory; }

DLL_EXPORT size_t __stdcall MemFlushCache(size_t size) { return size; }
DLL_EXPORT void __stdcall MemFlushCacheAll() { tcache_flush(); }
DLL_EXPORT size_t __stdcall MemSize(void *mem) { return je_malloc_usable_size(mem); }
DLL_EXPORT void *__stdcall MemAlloc(size_t size) { return je_malloc(size); }
DLL_EXPORT void __stdcall MemFree(void *mem) { je_free(mem); }

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
