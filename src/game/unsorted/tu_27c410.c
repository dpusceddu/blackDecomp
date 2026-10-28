#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003C0DFC;

// Partial lookup argument; the original type and other fields are UNVERIFIED.
typedef struct {
    char unknown00[12];
    const char* key;
} NameLookupInput;
extern u32 D_003C0DF4;
extern char D_0049A798[][5];
extern s32 D_0040EBA0[];

s32 func_0027C410(NameLookupInput* input) {
    u32 i = 0;
    while (i < D_003C0DF4) {
        if (D_0049A798[i] == input->key) return D_0040EBA0[i];
        ++i;
    }
    return 0;
}

s32 func_0027C460(s32 arg0, s32 arg1) {
    return M2C_FIELD(func_0027C410((NameLookupInput*)arg0), s32 *, 0x10C) + (arg1 * 0x70);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C770);
extern void func_0035D1A0(char*, const char*, int);
extern int func_00360938(const char*, const char*, int);

s32 func_0027C778(const char* name) {
    s32 result = D_003C0DFC;
    u32 i;
    char prefix[16];
    for (i = 0; i < 4; i++) {
        if (name[i] == ':') {
            u32 size = i + 1;
            func_0035D1A0(prefix, name, size);
            prefix[size] = 0;
            for (i = 0; i < D_003C0DF4; i++) {
                if (func_00360938(prefix, D_0049A798[i], 4) == 0) {
                    result = D_0040EBA0[i];
                    break;
                }
            }
            break;
        }
    }
    return result;
}

s8 *func_0027C860(s8 *arg0)
{
  s8 *var_5;
  u32 var_6;
  var_5 = arg0;
  var_6 = 0;
 do { } while (0);
  if ((*var_5) == 0x3A)
  {
    var_5 += 1;
  }
  else
  {
    loop_3:
    var_6 += 1;

    if (var_6 < 4U)
    {
 do { } while (0);
      if (!((*(var_5 + var_6)) == 0x3A))
      {
        goto loop_3;
      }
      else
      {
        var_5 += var_6 + 1;
      }
    }
  }
  return var_5;
}

#ifdef NON_MATCHING
// Unmatched: saved-register allocation and loop scheduling differ.
extern s32 func_0035CCD8(const char*);
extern char* func_0035CBC0(char*, const char*);
char* func_0027C8B0(char* out, s32 capacity, const char* base, const char* name, char separator) {
    s32 nameLength;
    s32 baseLength;
    s32 i;
    baseLength = func_0035CCD8(base);
    nameLength = func_0035CCD8(name);
    if (capacity - 1 < baseLength + nameLength) return 0;
    func_0035CBC0(out, base);
    if (nameLength >= 0) {
        char* dst = out + baseLength;
        for (i = 0; i <= nameLength; i++, dst++) {
            if (name[i] == '/' || name[i] == '\\') *dst = separator;
            else *dst = ((const unsigned char*)name)[i];
        }
    }
    return out;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C8B0);
#endif

void func_0027C990(s32 arg0) {
    D_003C0DFC = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C9A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CAB8);
extern const char D_00400388[];
extern int func_00369FF0(char*, int, const char*, const char*);

s32 func_0027CBC0(char* out, const char* name) {
    return func_00369FF0(out, 256, D_00400388, name);
}
#ifdef NON_MATCHING
// Unmatched: the three independent flag combinations use reversed operands.
// Partial file-handle view; original type and operation names are UNVERIFIED.
typedef struct {
    char unknown00[0x10];
    u64 position;
    char unknown18[0x48];
    void* resource;
} FileOpenHandleDraft;
extern void* func_0027CAB8(s32, const char*, u32);
s32 func_0027CBE8(void* unused, FileOpenHandleDraft* self, const char* name, u32 flags) {
    u32 mode = flags & 1;
    s32 driver;
    if (flags & 2) mode |= 2;
    mode |= flags & 4;
    mode |= flags & 8;
    mode |= flags & 16;
    driver = func_0027C778(name);
    if (driver) {
        self->resource = func_0027CAB8(driver, name, mode);
        if (self->resource) {
            self->position = 0;
            return 1;
        }
    }
    return 3;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CBE8);
#endif
#ifdef NON_MATCHING
// Unmatched: vtable and callback registers are swapped.
// Partial views; the callback signature and original types are UNVERIFIED.
typedef s32 (*FileControlCallbackDraft)(void*);
typedef struct { s16 adjustment, unknown02; FileControlCallbackDraft callback; } FileControlEntryDraft;
typedef struct { char unknown00[0x10]; FileControlEntryDraft operation; } FileControlTableDraft;
typedef struct { char unknown00[0x28]; FileControlTableDraft* table; } FileControlResourceDraft;
typedef struct { char unknown00[0x60]; FileControlResourceDraft* resource; } FileControlHandleDraft;
s32 func_0027CC78(FileControlHandleDraft* self) {
    FileControlResourceDraft* resource = self->resource;
    return resource->table->operation.callback((char*)resource + resource->table->operation.adjustment);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CC78);
#endif
// Partial dispatch views; original types and operation names are UNVERIFIED.
typedef u32 (*FileIoCallback)(void*, void*, u32);
typedef struct {
    s16 adjustment;
    s16 unknown02;
    FileIoCallback callback;
} FileIoEntry;
typedef struct {
    char unknown00[0x18];
    FileIoEntry operation18;
    FileIoEntry operation20;
} FileIoVtable;
typedef struct {
    char unknown00[0x28];
    FileIoVtable* vtable;
} FileIoResource;
typedef struct {
    char unknown00[0x10];
    u64 position;
    char unknown18[0x48];
    FileIoResource* resource;
} FileIoHandle;

u32 func_0027CCA8(FileIoHandle* self, void* buffer, u32 count) {
    FileIoResource* resource = self->resource;
    u32 result = resource->vtable->operation18.callback((char*)resource + resource->vtable->operation18.adjustment,
                                                       buffer, count);
    self->position += result;
    return result;
}

u32 func_0027CCF8(FileIoHandle* self, void* buffer, u32 count) {
    FileIoResource* resource = self->resource;
    u32 result = resource->vtable->operation20.callback((char*)resource + resource->vtable->operation20.adjustment,
                                                       buffer, count);
    self->position += result;
    return result;
}

s32 func_0027CD48(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x60);
    return M2C_FIELD(temp_3, s64 *, 0x10) >= M2C_FIELD(temp_3, s64 *, 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CD60);
// Partial driver dispatch views; original type and method names are UNVERIFIED.
typedef s32 (*DriverLookupCallback)(void*, const char*);
typedef struct {
    s16 adjustment;
    s16 unknown02;
    DriverLookupCallback callback;
} DriverLookupEntry;
typedef struct {
    char unknown00[8];
    DriverLookupEntry operation;
} DriverLookupTable;
typedef struct {
    char unknown00[0x110];
    DriverLookupTable* table;
} DriverLookupView;

s32 func_0027CE50(void* unused, const char* name) {
    DriverLookupView* driver = (DriverLookupView*)func_0027C778(name);
    if (!driver) return 0;
    return driver->table->operation.callback((char*)driver + driver->table->operation.adjustment, name);
}
