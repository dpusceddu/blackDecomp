#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0016B798();
extern s32 func_001B6328();
extern s32 func_001B7640();
extern s32 func_001B2438();
extern s32 func_001C1B88();
extern s32 func_001C29A0();
extern s32 func_001B90D0();
extern s32 func_001BCC30();
extern s32 func_001BD638();
extern s32 func_001B2AC8();
extern s32 func_001B3D40();
extern s32 func_001BE2F0();
extern s32 func_001BE940();
extern s32 func_001BEC68();
extern s32 func_001C2250();
extern s32 func_001C1C48();
extern s32 func_001D4070();
extern s32 func_001BFFE0();
extern s32 func_001C15D0();
extern M2C_UNK D_00418590;
extern s32 D_003C0E04;

#include "ps2/recovered_types.h"
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

s32 func_001B1B28(s32 arg0, s32 arg1)
{
  char new_var;
  func_0016B798();
  *((s32 *) (arg0 + 0x873F0)) = arg1;
  func_001B6328(arg0 + 0x66290, arg0);
  func_001B7640(arg0 + 0x696F0, arg0);
  func_001B2438(arg0 + 0x83710);
  func_001C1B88(arg0 + 0x66280);
  func_001C29A0(arg0 + 0x66288);
  func_001B90D0(arg0 + 0x54AB0);
  func_001BCC30(arg0 + 0x4EE00, arg0);
  func_001BD638((arg0 + 0x4EED0) & 0xFFFFFFFFu);
  func_001B2AC8(arg0 + 0x33C40);
  func_001B3D40(arg0 + 0x512E0);
  func_001BE2F0(arg0 + 0x83720);
  func_001BE940(arg0 + 0x83D24);
  func_001BEC68(arg0 + 0x83FB0);
  func_001C2250(arg0 + 0x83CA0);
  func_001C1C48(arg0 + 0x83CE0);
  func_001D4070(arg0 + 0x83D20);
  func_001BFFE0(arg0, M2C_FIELD(arg0, s32 *, 0x873F0));
  func_001C15D0(arg0 + 0x2DC30, M2C_FIELD(arg0, s32 *, 0x873F0));
  new_var = 4;
  *((s32 *) (((s8 *) (&D_00418590)) + new_var)) = (s32) D_003C0E04;
  *((s32 *) (((s8 *) (&D_00418590)) + 0)) = (s32) (~D_003C0E04);
  return 1;
}
