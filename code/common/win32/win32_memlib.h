/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

//IMPORTANT(adm244): SCRATCH VERSION JUST TO GET IT WORKING

#ifndef __WIN32_MEMLIB_H__
#define __WIN32_MEMLIB_H__

#include <windows.h>

internal MemBlock win32_AllocMem(ptrsize bytes, uint32 flags)
{
  MemBlock block = {0};
  
  HANDLE heap = GetProcessHeap();
  void *address = HeapAlloc(heap, flags, bytes);
  
  if( address ) {
    block.address = address;
    block.size = bytes;
  }
  
  return block;
}

internal bool32 win32_FreeMem(MemBlock *block)
{
  bool32 result = 0;
  
  if( block ) {
    result = HeapFree(GetProcessHeap(), 0, block->address);
    
    block->address = 0;
    block->size = 0;
  }
  
  return result;
}

#endif
