/* Translation unit tu_16a720 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern void *D_0040F4D0;
extern s32 D_003BCEE8;
extern unsigned char func_00107D20();

s32 func_0016B788(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x48) = 0x37;
    return 1;
}

void func_0016B798(void) {

}

/* Assembly between the functions: func_0016B7A0 (632 bytes), func_0016BA18 (480 bytes), func_0016BBF8 (528 bytes) */

void func_0016BE08(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
}

void func_0016BE10(void)
{
  s32 temp_2;
  temp_2 = M2C_FIELD(D_0040F4D0, s32 *, 0x8F4);
  if (temp_2 > 0)
  {
    D_003BCEE8 = (((((((((func_00107D20(temp_2 * 0xC) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF;
    return;
  }
  D_003BCEE8 = 0;
}
