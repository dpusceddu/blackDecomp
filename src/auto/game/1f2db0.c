#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001F5928(void *);
extern void ** D_0040F518;
extern s32 func_002019F8(void *);
extern s32 func_002019A0(void *, void *);

s32 func_001F2DB0(s32 arg0) {
    func_001F5928(M2C_FIELD(D_0040F518, void **, 0x14));
    func_002019F8(M2C_FIELD(D_0040F518, void **, 0x2C));
    return func_002019A0(M2C_FIELD(D_0040F518, void **, 0x2C), NULL);
}
