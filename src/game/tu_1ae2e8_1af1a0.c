/* Translation unit tu_1ae2e8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_001AF180();
extern M2C_UNK func_001CA258;
extern M2C_UNK func_001CA208;
extern s32 func_001AF1C0();
extern s32 func_001AF298();

s32 func_001AF1A0(void *draw_list, s32 batches, s32 sort_entries, s32 capacity) {
    M2C_FIELD(draw_list, s32 *, 4) = sort_entries;
    M2C_FIELD(draw_list, s32 *, 0xC) = capacity;
    M2C_FIELD(draw_list, s32 *, 0) = batches;
    M2C_FIELD(draw_list, s32 *, 8) = 0;
    return 1;
}

void func_001AF1B8(void *draw_list) {
    M2C_FIELD(draw_list, s32 *, 8) = 0;
}

/* Assembly between the functions: func_001AF1C0 (216 bytes), func_001AF298 (552 bytes) */

void func_001AF4C0(void *actor) {
    func_001AF180(actor + 0xCA58, 0, &func_001CA258);
    func_001AF180(actor + 0xCA70, 1, &func_001CA258);
    func_001AF180(actor + 0xCA88, 2, &func_001CA208);
    func_001AF180(actor + 0xCAA0, 3, NULL);
    func_001AF180(actor + 0xCAB8, 4, NULL);
    func_001AF180(actor + 0xCAD0, 5, NULL);
    func_001AF180(actor + 0xCAE8, 6, NULL);
}

/* Assembly between the functions: func_001AF580 (336 bytes), func_001AF6D0 (104 bytes) */

void * func_001AF738(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    return func_001AF1C0(arg0 + ((M2C_FIELD(arg1, u8 *, 9) * 0x18) + 0xCA58), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

void func_001AF768(s32 actor_address, s32 index)
{
  int record_offset;
  s32 record_address;
 do { record_offset = (index * 0x18) + 0xCA58; record_address = record_offset; } while (0);
  func_001AF298(actor_address + record_address, record_address);
}
