#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001B1EF0();
extern s32 func_001B2B60(s32);
extern s32 func_001BDEE8(void *);
extern s32 func_001B3F50(void *);
extern s32 func_001BCDF8(void *);
extern s32 func_001B89C8(void *);
extern s32 func_001B2710(s32);
extern s32 func_001BE960(void *);
extern s32 func_001B64C0(void *);
extern s32 func_001B7758(s32);
extern s32 func_001C02A0(s32);
extern s32 func_001C1810(void *);
extern s32 func_001BE330(void *);
extern s32 func_001BECD0(s32);
extern void * func_001C22A0(void *, f32);
extern void * D_0040F4D0;

void * func_001B1CB8(s32 arg0) {
    func_001B1EF0();
    func_001B2B60(arg0 + 0x33C40);
    func_001BDEE8(arg0 + 0x4EED0);
    func_001B3F50(arg0 + 0x512E0);
    func_001BCDF8(arg0 + 0x4EE00);
    func_001B89C8(arg0 + 0x54AB0);
    func_001B2710(arg0 + 0x83710);
    func_001BE960(arg0 + 0x83D24);
    func_001B64C0(arg0 + 0x66290);
    func_001B7758(arg0 + 0x696F0);
    func_001C02A0(arg0);
    func_001C1810(arg0 + 0x2DC30);
    func_001BE330(arg0 + 0x83720);
    func_001BECD0(arg0 + 0x83FB0);
    return func_001C22A0(arg0 + 0x83CA0, M2C_FIELD(D_0040F4D0, f32 *, 0x1C));
}
