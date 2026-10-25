#include "include_asm.h"

#include "rw_audio/bank.h"
#ifdef NON_MATCHING
#include "ps2/prelude.h"
#include "rw_audio/sound.h"
#endif
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
#ifdef NON_MATCHING
extern s32 (*D_003CEC68)();
extern s32 func_00313EA8(s32);
extern void func_00324BA0(s32,void *,u32,s32,s32,void *);
extern RwaSound *func_00314488(RwaBank *,s32);
extern s32 func_00324D98(s32,s32);
extern void func_00324A88(s32,void *,u32,u32,s32,s32,void *);
extern u32 D_0040E164;
extern void func_003164D0(RwaBank *);
extern void func_003182C8(void *);
extern void func_00315B60(void *);
extern u32 func_00315168(u32);
extern void *func_00312C48(u32,u32);
extern s32 func_00313C48(RwaStream *);
extern s32 func_00324990(const char *);
extern void *func_00312CC8(u32,u32);
// Unmatched: relocation loop register allocation and one short-loop nop differ.
void func_003137D8(RwaBank *bank,s32 base,s32 initialize) {
    RwaLink *link,*sentinel,*current;u32 *sound;
    if(initialize){func_003164D0(bank);func_003182C8(&bank->list_previous);}
    if(bank->name)bank->name=(char *)bank->name+base;
    if(bank->list_previous)bank->list_previous=(RwaLink *)((char *)bank->list_previous+base);
    if(bank->first)bank->first=(RwaLink *)((char *)bank->first+base);
    if(bank->last)bank->last=(char *)bank->last+base;
    sentinel=(RwaLink *)bank->list_previous;
    link=bank->first;
    do {
        current=link;
        if(initialize)func_003182C8(current);
        if(current->object)current->object=(char *)current->object+base;
        if(current->next)current->next=(RwaLink *)((char *)current->next+base);
        if(current->previous)current->previous=(RwaLink *)((char *)current->previous+base);
        link=current->next;sound=current->object;
        if(initialize)func_00315B60(sound);
        if(sound[0])sound[0]+=base;
        if(sound[1])sound[1]+=base;
        if(sound[20])sound[20]+=base;
        if(sound[8])sound[8]+=base;
        if(sound[15])sound[15]+=base;
        sound[5]=func_00315168(sound[5]);sound[12]=func_00315168(sound[12]);
    }while(current!=sentinel);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003137D8);
#endif
#ifdef NON_MATCHING
// Unmatched: allocation/open control-flow and saved argument allocation differ.
RwaStream *func_003139A8(const char *name,void *buffer,s32 capacity,u32 data,u32 data_size,s32 unused,s32 block_size,RwaStream *stream) {
    s32 handle,status;
    if(!stream) {stream=func_00312C48(0x48,0x30808);stream->ownership=2;func_00313C48(stream);if(!stream)goto open;}
    if(stream->state!=2) {
open: stream->handle=func_00324990(name);
    }
    handle=stream->handle;
    if(!handle)return stream;
    status=2;
    if(func_00324D98(handle,0)) {
        if(!buffer){capacity=0x800;buffer=func_00312CC8(0x800,0x30808);stream->flags=0x10;}
        else {status=0x2000;if((u32)capacity<0x800)goto fail;stream->flags=0x20;}
        func_00324BA0(handle,buffer,0x800,0,0,0);stream->position=0x800;stream->state=0x30;stream->buffer=buffer;stream->data=(void *)data;stream->capacity=capacity;stream->data_size=data_size;stream->block_size=block_size;stream->mode=3;return stream;
    }
fail:stream->state=status;return stream;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003139A8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313B18);
