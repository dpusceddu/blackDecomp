/* Translation unit tu_204a50 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002050B0();
extern s32 func_00278F00();
extern void * D_003BDCC8;
extern s32 func_00204FF0();
extern s32 func_00276728();

s32 func_00206F08(void) {
    func_002050B0();
    return 1;
}

/* Assembly between the functions: func_00206F28 (8 bytes), func_00206F30 (240 bytes), func_00207020 (240 bytes), func_00207110 (176 bytes) */

void func_002071C0(void) {

}

s32 func_002071C8(void *arg0) {
    func_00278F00(D_003BDCC8, 0, M2C_FIELD(arg0, s32 *, 0x18));
    return 1;
}

void func_002071F8(void) {
    func_00204FF0();
}

/* Assembly between the functions: func_00207218 (136 bytes) */

void func_002072A0(void *arg0) {
    func_00276728(M2C_FIELD(arg0, s32 *, 0x84), arg0 + 0x40, arg0 + 0x50, arg0 + 0x58, M2C_FIELD(arg0, s128 *, 0x20), M2C_FIELD(arg0, s32 *, 0x88), arg0 + 0x68, arg0 + 0x70, 0);
}

/* Assembly between the functions: func_002072E0 (784 bytes) */

void func_002075F0(void) {
    func_00204FF0();
}

/* Assembly between the functions: func_00207610 (152 bytes), func_002076A8 (80 bytes), func_002076F8 (576 bytes) */

s32 func_00207938(void *arg0)
{
  s8 *new_var;
  new_var = (s8 *) arg0;
  func_002050B0();
  func_00278F00(*((void **) (new_var + 8)), *((s32 *) (new_var + 0x64)), *((s32 *) (new_var + 0x7C)));
  return 1;
}
