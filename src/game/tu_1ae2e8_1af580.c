#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_001AF1A0(void *, s32, s32, s32);

s32 func_001AF580(s32 actor_address, const int *counts)
{
  s32 count0;
  int sort_entries_offset;
  s32 count01;
  s32 count012;
  s32 count0123;
  int batch_address;
  s32 count01234;
  func_001AF1A0(actor_address + 0xCA58, actor_address, actor_address + (sort_entries_offset = 0x9088), counts[0]);
  count0 = counts[0];
  func_001AF1A0(actor_address + 0xCA70, (count0 * 0x14) + actor_address, actor_address + ((count0 * 8) + sort_entries_offset), M2C_FIELD(counts, s32 *, 4));
  count01 = count0 + (M2C_FIELD(counts, s32 *, 4));
  batch_address = (count01 * 0x14) + actor_address;
  func_001AF1A0(actor_address + 0xCA88, batch_address, actor_address + ((count01 * 8) + sort_entries_offset), M2C_FIELD(counts, s32 *, 8));
  count012 = count01 + (M2C_FIELD(counts, s32 *, 8));
  func_001AF1A0(actor_address + 0xCAA0, (count012 * 0x14) + actor_address, 0, counts[3]);
  count0123 = count012 + (counts[3]);
  func_001AF1A0(actor_address + 0xCAB8, (count0123 * 0x14) + actor_address, 0, counts[4]);
  count01234 = count0123 + (counts[4]);
  func_001AF1A0(actor_address + 0xCAD0, (count01234 * 0x14) + actor_address, 0, counts[5]);
  func_001AF1A0(actor_address + 0xCAE8, ((count01234 + (counts[5])) * 0x14) + actor_address, 0, counts[6]);
  return 1;
}
