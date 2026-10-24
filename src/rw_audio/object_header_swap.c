#include "include_asm.h"

#include "rw_audio/sound.h"

typedef struct {void *next,*previous;u32 tag;} RwaRuntimeHeader;
extern void func_00318600(u8 **,const void *,u32);

void func_003164D0(RwaRuntimeHeader *header) {
    RwaRuntimeHeader copy;
    u8 *cursor=(u8 *)&copy;
    func_00318600(&cursor,&header->next,4);
    func_00318600(&cursor,&header->previous,4);
    func_00318600(&cursor,&header->tag,4);
    *header=copy;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316548);
