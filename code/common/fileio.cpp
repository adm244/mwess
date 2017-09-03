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

#ifndef __FILEIO_H__
#define __FILEIO_H__

#define FILE_OVERRIDE 1
#define FILE_HIDDEN 2

struct File{
  void *handle;
  uint32 flags;
};

#include "win32/win32_fileio.h"

internal inline bool32 CreateFile(File *file, char *filename, uint32 flags)
{
  return win32_CreateFile(file, filename, flags);
}

internal inline bool32 OpenFile(File *file, char *filename)
{
  return win32_OpenFile(file, filename);
}

internal inline bool32 FileExists(char *filename)
{
  return win32_FileExists(filename);
}

internal inline void DeleteFile(File *file)
{
  return win32_DeleteFile(file);
}

internal inline bool32 CloseFile(File *file)
{
  return win32_CloseFile(file);
}

internal inline bool32 ReadBuffer(File *file, void *buffer, uint size)
{
  return win32_ReadBuffer(file, buffer, size);
}

internal inline bool32 ReadInt8(File *file, int8 *value)
{
  return ReadBuffer(file, value, 1);
}

internal inline bool32 ReadInt16(File *file, int16 *value)
{
  return ReadBuffer(file, value, 2);
}

internal inline bool32 ReadInt32(File *file, int32 *value)
{
  return ReadBuffer(file, value, 4);
}

internal inline bool32 WriteBuffer(File *file, void *buffer, uint size)
{
  return win32_WriteBuffer(file, buffer, size);
}

internal inline bool32 WriteInt8(File *file, int8 value)
{
  return WriteBuffer(file, &value, 1);
}

internal inline bool32 WriteInt16(File *file, int16 value)
{
  return WriteBuffer(file, &value, 2);
}

internal inline bool32 WriteInt32(File *file, int32 value)
{
  return WriteBuffer(file, &value, 4);
}

#endif
