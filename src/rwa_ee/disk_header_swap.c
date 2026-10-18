#include "rwa_ee/bank.h"
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
    func_00316438(header->name);
    *(RwaName *)cursor=*(RwaName *)header->name;
    cursor+=16;
    func_00318600(&cursor,&header->field28,4);
    *header=copy;
}
