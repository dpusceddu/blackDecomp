#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001C1B78(void *);
extern s32 func_001C2990(void *);
extern s32 * func_001BFED0(s32);
extern s32 func_001C1578(void *);
extern s32 * func_001B6250(void *);
extern s32 * func_001B7590(s32);
extern s32 func_001B2408(void *);
extern s32 func_001B2A78(s32);
extern s32 func_001BCC18(void *);
extern s32 func_001BD620(void *);
extern s32 func_001B8630(s32);
extern s32 func_001B3D38(s32);
extern s32 func_001BE2E0(s32);
extern s32 func_001BE938(s32);
extern s128 func_001BEC18(s32);
extern s32 func_001C1C40(s32);
extern s32 func_001D4068(s32);
extern s32 func_00382348(void *, s32);
extern M2C_UNK D_00418590;

s32 func_001B19E8(s32 arg0) {
    func_001C1B78(arg0 + 0x66280);
    func_001C2990(arg0 + 0x66288);
    func_001BFED0(arg0);
    func_001C1578(arg0 + 0x2DC30);
    func_001B6250(arg0 + 0x66290);
    func_001B7590(arg0 + 0x696F0);
    func_001B2408(arg0 + 0x83710);
    func_001B2A78(arg0 + 0x33C40);
    func_001BCC18(arg0 + 0x4EE00);
    func_001BD620(arg0 + 0x4EED0);
    func_001B8630(arg0 + 0x54AB0);
    func_001B3D38(arg0 + 0x512E0);
    func_001BE2E0(arg0 + 0x83720);
    func_001BE938(arg0 + 0x83D24);
    func_001BEC18(arg0 + 0x83FB0);
    func_001C1C40(arg0 + 0x83CE0);
    func_001D4068(arg0 + 0x83D20);
    return func_00382348(&D_00418590, 0x02B9D6F8);
}
