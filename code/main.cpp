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

/*
  REd:
    TES3
    GLOB
    CLAS
    SCPT(?)
*/

#include "common/types.h"
#include "common/memlib.cpp"
#include "common/fileio.cpp"

/*
  SpecInfo:
    (single) - block appears only once
    (many) - block can appear many times
    (?) - needs to be checked
    (???) - just a wild guess
    ??? - yet to be REd
  END
*/
/*
  //NOTE(adm244): in theory all blocks are optional
  // the only required one is TES3 block (header)
  // also they can appear in different order
  
  ESS file: // Morrowind Save File
    TES3 block
    (many) GLOB block
    (single) CLAS block
    (many) SCPT block
    (many) REGN block
  END
  
//--------TES3--------
  TES3 block: // Save File Information
    HEADER:
      (4 bytes) Block Signature (0x54455333 = "TES3")
      (4 bytes) Data Size (?)
      (4 bytes) ???
      (4 bytes) ???
    DATA:
      (single) HEDR block
      (many) MAST block
      (single) GMDT block
      (single) SCRD block
      (single) SCRS block
  END
  
  HEDR block: // Basic Information
    HEADER:
      (4 bytes) File Signature (0x48454452 = "HEDR")
      (4 bytes) Data Size
    DATA:
      (4 bytes) File Version (?) (float)
      (4 bytes) Flags (???)
      (32 bytes) Title (null terminated)
      (256 bytes) Description (null terminated)
      (4 bytes) Number of Records (?)
  END
  
  MAST block: // Master\Plugin File Information
    HEADER:
      (4 bytes) Block Signature (0x4D415354 = "MAST")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Plugin File Name (null terminated)
      
      DATA block
  END
  
  DATA block: // Master\Plugin File Additional Information
    HEADER:
      (4 bytes) Block Signature (0x44415441 = "DATA")
      (4 bytes) Data Size
    DATA:
      (4 bytes) ??? (some kind of a size?)
      (4 bytes) Flags (???)
  END
  
  GMDT block: // Game Data Information
    HEADER:
      (4 bytes) Block Signature (0x474D4454 = "GMDT")
      (4 bytes) Data Size
    DATA:
      (4 bytes) Current Players Health (float)
      (4 bytes) Maximum Players Health (float)
      (4 bytes) Time (float) (?)
      (4 bytes) Date Month (float) (???)
      (4 bytes) Date Day (float) (???)
      (4 bytes) Date Year (float) (???)
      (64 bytes) Current Cell Name (null terminated)
      (4 bytes) Days Passed (float)
      (32 bytes) Character Name
  END
  
  SCRD block: // Screenshot Color Information (?)
    HEADER:
      (4 bytes) Block Signature (0x53435244 = "SCRD")
      (4 bytes) Data Size
    DATA:
      (4 bytes) Color Mask R (???)
      (4 bytes) Color Mask G (???)
      (4 bytes) Color Mask B (???)
      (4 bytes) Color Mask A (???)
      (4 bytes) Flags (???)
  END
  
  SCRS block: // Screenshot Data
    HEADER:
      (4 bytes) Block Signature (0x53435253 = "SCRS")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Raw Image Data (BGRA32 format, 128x128)
  END
//--------#TES3--------
  
//--------GLOB--------
  GLOB block: // Global Variable
    HEADER:
      (4 bytes) Block Signature (0x474C4F42 = "GLOB")
      (4 bytes) Data Size
      (4 bytes) ???
      (4 bytes) ???
    DATA:
      NAME block
      FNAM block
      FLTV block
  END
  
  NAME block: // Global Variable Name
    HEADER:
      (4 bytes) Block Signature (0x4E414D45 = "NAME")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Variable Name (null terminated)
  END
  
  FNAM block: // Global Variable Type
    HEADER:
      (4 bytes) Block Signature (0x464E414D = "FNAM")
      (4 bytes) Data Size
    DATA:
      (1 byte) Variable Type (s - short, l - long, f - float)
  END
  
  FLTV block: // Global Variable Value
    HEADER:
      (4 bytes) Block Signature (0x464C5456 = "FLTV")
      (4 bytes) Data Size
    DATA:
      (4 bytes) Variable Value (float)
  END
//--------#GLOB--------

//--------CLAS--------
  CLAS block: // Created Custom Class
    HEADER:
      (4 bytes) Block Signature (0x434C4153 = "CLAS")
      (4 bytes) Data Size
      (4 bytes) ???
      (4 bytes) ???
    DATA:
      (single) NAME block
      (single) FNAM block
      (single) CLDT block
      (single) DESC block
  END
  
  NAME block: // Variable to store custom class?
    HEADER:
      (4 bytes) Block Signature (0x4E414D45 = "NAME")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Variable Name (null terminated) (?)
  END
  
  FNAM block: // Custom Class Name
    HEADER:
      (4 bytes) Block Signature (0x464E414D = "FNAM")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Class Name (null terminated)
  END
  
  CLDT block: // Custom Class Information
    HEADER:
      (4 bytes) Block Signature (0x434C4454 = "CLDT")
      (4 bytes) Data Size
    DATA:
      (4 bytes) Attribute 01 ID
      (4 bytes) Attribute 02 ID
      (4 bytes) Specialization ID
      (4 bytes) Minor Skill 01 ID
      (4 bytes) Major Skill 01 ID
      (4 bytes) Minor Skill 02 ID
      (4 bytes) Major Skill 02 ID
      (4 bytes) Minor Skill 03 ID
      (4 bytes) Major Skill 03 ID
      (4 bytes) Minor Skill 04 ID
      (4 bytes) Major Skill 04 ID
      (4 bytes) Minor Skill 05 ID
      (4 bytes) Major Skill 05 ID
      (4 bytes) Flags
      (4 bytes) Auto Calculate Flags
  END
  
  DESC block: // Custom Class Description
    HEADER:
      (4 bytes) Block Signature (0x44455343 = "DESC")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Class Description (NOT null terminated)
  END
//--------#CLAS--------

//--------SCPT--------
  SCPT block: // Script Information
    HEADER:
      (4 bytes) Block Signature (0x53435054 = "SCPT")
      (4 bytes) Data Size
      (4 bytes) ???
      (4 bytes) ???
    DATA:
      (single) SCHD block
      (single) SLCS block
      (single) SLSD block
      (single) SLFD block
      (single) RNAM block
  END
  
  SCHD block: // Script Header Data
    HEADER:
      (4 bytes) Block Signature (0x53434844 = "SCHD")
      (4 bytes) Data Size
    DATA:
      (32 bytes) Script Name (null terminated)
      (4 bytes) Number of Shorts
      (4 bytes) Number of Longs
      (4 bytes) Number of Floats
      (4 bytes) Script Size (bytes)
      (4 bytes) Local Variables Size (bytes)
  END
  
  SLCS block: // Script Header Data for Construction Set(???)
    HEADER:
      (4 bytes) Block Signature (0x534C4353 = "SLCS")
      (4 bytes) Data Size
    DATA:
      (4 bytes) Number of Shorts (?)
      (4 bytes) Number of Longs (?)
      (4 bytes) Number of Floats (?)
  END
  
  SLSD block: // Script Short Values
    HEADER:
      (4 bytes) Block Signature (0x534C5344 = "SLSD")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Variables Value Array (each 4 bytes)
  END
  
  SLLD block: // Script Long Values(???)
    HEADER:
      (4 bytes) Block Signature (0x534C4353 = "SLCS")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Variables Value Array (each 4 bytes)
  END
  
  SLFD block: // Script Float Values
    HEADER:
      (4 bytes) Block Signature (0x534C4644 = "SLFD")
      (4 bytes) Data Size
    DATA:
      (data size bytes) Variables Value Array (each 4 bytes)
  END
  
  RNAM block:
    HEADER:
      (4 bytes) Block Signature (0x524E414D = "RNAM")
      (4 bytes) Data Size
    DATA:
      (data size bytes) ???
  END
//--------#SCPT--------

//--------REGN--------
  REGN block: // Region Information
    ???
  END
//--------#REGN--------
*/

internal int main(int argc, char *argv[])
{
  //NOTE(adm244): no code yet...
  return(0);
}
