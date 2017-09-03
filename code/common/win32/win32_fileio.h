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

#ifndef __WIN32_FILEIO_H__
#define __WIN32_FILEIO_H__

#include <windows.h>

internal bool32 win32_CreateFile(File *file, char *filename, uint32 flags)
{
  bool32 result = 0;
  
  DWORD creationDisposition = (flags & FILE_OVERRIDE) ? CREATE_ALWAYS : CREATE_NEW;
  DWORD attributes = (flags & FILE_HIDDEN) ? FILE_ATTRIBUTE_HIDDEN : FILE_ATTRIBUTE_NORMAL;
  
  //TODO(adm244): more flags?
  HANDLE fileHandle = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ,
    0, creationDisposition, attributes, 0);
  
  if( fileHandle == INVALID_HANDLE_VALUE ) {
    //TODO(adm244): error checking
  } else {
    file->handle = fileHandle;
    file->flags = flags;
    result = 1;
  }
  
  return result;
}

internal bool32 win32_OpenFile(File *file, char *filename)
{
  bool32 result = 0;
  
  HANDLE fileHandle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ,
    0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  
  if( fileHandle == INVALID_HANDLE_VALUE ) {
    //TODO(adm244): error checking
  } else {
    file->handle = fileHandle;
    file->flags = 0;
    result = 1;
  }
  
  return result;
}

internal bool32 win32_FileExists(char *filename)
{
  //TODO(adm244): implement this...
}

internal void win32_DeleteFile(File *file)
{
  //TODO(adm244): implement this...
}

internal bool32 win32_CloseFile(File *file)
{
  bool32 result = 0;
  
  if( file && file->handle ) {
    result = CloseHandle(file->handle);
  }
  
  return result;
}

internal bool32 win32_ReadBuffer(File *file, void *buffer, uint size)
{
  bool32 result = 0;
  
  if( file && file->handle && buffer ) {
    DWORD bytesRead;
    
    //TODO(adm244): check bytesRead
    result = ReadFile(file->handle, buffer, size, &bytesRead, 0);
  }
  
  return result;
}

internal bool win32_WriteBuffer(File *file, void *buffer, uint size)
{
  bool result = false;
  
  if( file && file->handle ) {
    DWORD bytesWritten;
    
    //TODO(adm244): check bytesWritten
    BOOL writeResult = WriteFile((HANDLE)file->handle, buffer, size, &bytesWritten, 0);
    if( writeResult == TRUE ) {
      result = true;
    }
  }
  
  return result;
}

#endif
