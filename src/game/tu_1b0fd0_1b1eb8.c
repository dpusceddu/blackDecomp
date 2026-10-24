#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B6908(s32);
extern s32 func_001C05F8(s32);
extern void *D_0040F4CC;
extern s32 func_001DE6F0();
extern s32 func_0016B7A0();

void func_001B1EB8(s32 arg0) {
    func_001B6908(arg0 + 0x66290);
    func_001C05F8(arg0);
}

void func_001B1EF0(void)
{
  u8 sp[8];
  s32 temp_17;
  void *temp_16;
  temp_17 = M2C_FIELD(D_0040F4CC, s32 *, 0x8B00);
  temp_16 = D_0040F4CC + 0x2980;
  func_001DE6F0(sp, temp_16, temp_17);
 do { } while (0);
  func_0016B7A0(temp_16, temp_17);
}

#include "ps2/recovered_types.h"
extern s32 func_001B2D70(s32);
extern s32 func_001B5570(s32);
extern s32 func_001BCDD8(void *);
extern s32 func_001BE2A0(void *);
extern s32 func_001B8638(s32);
extern s32 func_001B78D8(s32);
extern s32 func_001B6910(void *);
extern s32 func_001B2910(void *);
extern s32 func_001BE310(s32);
extern s32 func_001BEB28(void *);
extern s32 func_001BECC8(s32);
extern s32 func_001C1CC8(s32);
extern s32 func_001D4078(s32);
extern s32 func_001C0600(s32);
extern s32 func_001C19B0(void *);
extern s32 func_001C1BA0(s32);
extern s32 func_001C29A8(s32);

s32 func_001B1F48(s32 arg0) {
    func_001B2D70(arg0 + 0x33C40);
    func_001B5570(arg0 + 0x512E0);
    func_001BCDD8(arg0 + 0x4EE00);
    func_001BE2A0(arg0 + 0x4EED0);
    func_001B8638(arg0 + 0x54AB0);
    func_001B78D8(arg0 + 0x696F0);
    func_001B6910(arg0 + 0x66290);
    func_001B2910(arg0 + 0x83710);
    func_001BE310(arg0 + 0x83720);
    func_001BEB28(arg0 + 0x83D24);
    func_001BECC8(arg0 + 0x83FB0);
    func_001C1CC8(arg0 + 0x83CE0);
    func_001D4078(arg0 + 0x83D20);
    func_001C0600(arg0);
    func_001C19B0(arg0 + 0x2DC30);
    func_001C1BA0(arg0 + 0x66280);
    func_001C29A8(arg0 + 0x66288);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2078);
