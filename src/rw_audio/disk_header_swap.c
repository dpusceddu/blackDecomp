#include "include_asm.h"

#include "rw_audio/bank.h"
extern void func_00318600(u8 **,const void *,u32);
extern void func_00316438(void *);

void func_00313650(RwaDiskHeader *header) {
    RwaDiskHeader copy;
    u8 *cursor=(u8 *)&copy;
    func_00318600(&cursor,&header->tag,4);
    *cursor=header->endian;
    *++cursor=header->version;
    *++cursor=header->flags;
    *++cursor=header->format;
    ++cursor;
    func_00318600(&cursor,&header->size,4);
    func_00318600(&cursor,&header->bank_offset,4);
    func_00318600(&cursor,&header->field10,4);
    func_00318600(&cursor,&header->bank_size,4);
    func_00316438(header->bank_id);
    *(RwaIdBytes *)cursor=*(RwaIdBytes *)header->bank_id;
    cursor+=16;
    func_00318600(&cursor,&header->field28,4);
    *header=copy;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003137C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003137D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003139A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313B18);
