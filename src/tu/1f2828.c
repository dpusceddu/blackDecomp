#include "auto/prelude.h"

extern s32 func_001F1B98(void *, s32);
extern void * D_0040F518;
extern s32 func_001F1C00();
extern s32 func_001F3EE8();
extern void *D_0040F518;
extern s32 func_001F44B8();
extern s32 func_001F76E8();
extern void func_001F4D88();
extern s32 func_002019A0();
extern void func_001F4DE0();

void func_001F2828(void) {

}

s32 func_001F2830(void) {
    return 1;
}

void func_001F2838(s32 arg0, s8 arg1, s32 arg2) {
    func_001F1B98(D_0040F518 + (arg1 * 0xA8), arg2);
}

s32 func_001F2870(s32 arg0, s8 arg1) {
    return M2C_FIELD(((arg1 * 0xA8) + D_0040F518), s32 *, 0x8C);
}

void func_001F2898(s32 arg0, s8 arg1, s32 arg2) {
    func_001F1C00(D_0040F518 + (arg1 * 0xA8), arg2);
}

void func_001F28D0(s32 arg0, s8 arg1, s32 arg2)
{
  void *new_var;
  if (1)
  {
  }
  func_001F3EE8(*((s32 *) (((s8 *) (new_var = D_0040F518 + (arg1 * 0xA8))) + ((0, 8)))), arg2);
}

void func_001F2910(void) {

}

void func_001F2918(s32 arg0, s8 arg1, s32 arg2)
{
  int new_var;
  new_var = arg1 * 0xA8;
  func_001F44B8(*((s32 *) (((s8 *) (D_0040F518 + new_var)) + 0x20)), arg2);
}

void func_001F2958(s32 arg0, s8 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  func_001F76E8(*((s32 *) (((s8 *) (D_0040F518 - (-(arg1 * 0xA8)))) + 0xC)), arg2, arg3 & 0xFF, arg4);
}

void func_001F29A0(s32 arg0, s32 arg1, s32 arg2) {
    func_001F4D88(M2C_FIELD(D_0040F518, s32 *, 0x14));
    func_002019A0(M2C_FIELD(D_0040F518, s32 *, 0x2C), arg2);
}

void func_001F29E8(s32 arg0, s32 arg1, s32 arg2) {
    func_001F4DE0(M2C_FIELD(D_0040F518, s32 *, 0x14));
    func_002019A0(M2C_FIELD(D_0040F518, s32 *, 0x2C), arg2);
}
