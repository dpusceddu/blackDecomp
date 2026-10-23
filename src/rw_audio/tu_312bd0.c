/* Medium-confidence bank/stream TU: call and shared-data edges. */
#ifdef NONMATCHING_RWA_BANK_STREAM
#include "rw_audio/sound.h"
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
// Unmatched: stream mode dispatch and min-limit scheduling differ.
RwaStream *func_003134E0(RwaStream *stream) {
    u32 amount=0, remaining=stream->remaining, block;
    if(func_00313EA8(stream->handle)) {
        switch(stream->mode) {
        case 1:
            block=stream->block_size;
            if(remaining<block)block=remaining;
            amount=block;
            func_00324BA0(stream->handle,stream->data,block,0,0,0);
            break;
        case 3: {
            RwaSound *sound=func_00314488(stream->bank,0);
            block=D_0040E164;
            if(block>=stream->block_size)block=stream->block_size;
            amount=sound->driver->read(stream->handle,stream->data,stream->cursor,remaining>=block?block:remaining);
            break; }
        case 2:
            block=stream->block_size;
            if(remaining<block)block=remaining;
            if(func_00324D98(stream->handle,0)) {
                amount=block;
                func_00324A88(stream->handle,stream->data,stream->position,stream->format,0,0,0);
            }
            break;
        }
        stream->position+=amount;stream->cursor+=amount;stream->remaining-=amount;
    }
    return stream;
}
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

#endif

#ifdef NONMATCHING_RWA_BANK_STATE
#include "rw_audio/sound.h"
extern s32 func_00313EA8(s32);
extern void func_00313650(RwaDiskHeader *);
extern void *func_00312CC8(u32,u32);
extern void *func_0035C544(void *,const void *,u32);
extern void func_00312D08(void *);
extern void func_00324BA0(s32,void *,u32,s32,s32,void *);
extern void func_00314278(RwaBank *);
extern void func_003137D8(RwaBank *,s32,s32);
extern s32 func_00316400(void *,const char *);
extern void *D_0040E15C;
extern void func_003143D8(RwaBank *,void *,void *);
extern void func_00313F00(void *,void *);
extern void *func_00313C90(RwaBank *,u32);
extern RwaStream *func_003134E0(RwaStream *);
extern RwaBank *D_0040E178,*D_0040E174;
extern RwaLink D_0040E778;
extern void func_00313DC8(RwaBank *);
extern void func_00315F28(void *);
extern void *func_00314440(RwaBank *,void *);
extern void func_00318340(void *);
extern void func_003145D0(RwaBank *);
// Unmatched: stack descriptor lifetimes and state-machine scheduling differ.
RwaStream *func_00313278(RwaStream *stream) {
    s32 handle=stream->handle,swapped=0;
    RwaDiskHeader *header;
    RwaBank *bank;
    struct {s32 field0, flags, unused,driver,first,last;} saved;
    if(handle && !func_00313EA8(handle))return stream;
    header=stream->buffer;
    switch(stream->state){
    case 0x30:
        if(header->endian){swapped=1;func_00313650(header);}
        if(stream->position<header->size) {
            if(stream->flags&0x20){if(stream->capacity<header->size){stream->state=0x2000;return stream;}}
            else {header=func_00312CC8(header->size,0x30808);func_0035C544(header,stream->buffer,stream->capacity);func_00312D08(stream->buffer);stream->buffer=header;stream->capacity=header->size;}
            {u32 position=stream->position;func_00324BA0(handle,(char *)stream->buffer+position,header->size-position,0,0,0);}
            stream->state=0x50;stream->position=stream->capacity;return stream;
        }
    case 0x50:
        bank=(RwaBank *)((char *)stream->buffer+header->bank_offset);
        stream->read_size=stream->position;stream->bank=bank;stream->format=header->bank_size;stream->field38=0;stream->remaining=header->bank_size;stream->field3c=0;
        saved.driver=(s32)bank->list_previous;saved.first=(s32)bank->first;saved.last=(s32)bank->last;
        func_00314278(bank);bank->flags1b=stream->flags;bank->list_previous=(RwaLink *)saved.driver;bank->first=(RwaLink *)saved.first;bank->last=(void *)saved.last;bank->allocation=stream->buffer;
        func_003137D8(bank,(s32)stream->buffer,swapped);
        func_00316400(D_0040E15C,(char *)header->bank_id);
        saved.field0=1;saved.flags=stream->ownership;
        func_003143D8(bank,(void *)func_00313F00,&saved);
        if(stream->ownership&4)stream->state=0x300;
        else {
            void *data=stream->data;stream->state=0x70;
            if(!data){stream->data=func_00313C90(bank,stream->format);bank->flags1b|=0x40;}
            else {bank->data=data;bank->data_size=stream->data_size;}
            func_003134E0(stream);
        }
        return stream;
    default:return stream;
    }
}
// Unmatched: shared-bank list traversal scheduling and register allocation differ.
void func_00313FD0(RwaBank *bank) {
    RwaLink *link,*owner,*sentinel=(RwaLink *)&bank->list_previous;
    *bank->previous=bank->next;bank->next->previous=bank->previous;
    if(bank==D_0040E178)D_0040E178=D_0040E174;
    if((bank->flags1b&0x40)&&(bank->data||(bank->flags1a&1)))func_00313DC8(bank);
    if(!(bank->flags1b&0x20)) {
        if(bank->flags1b&0x10)func_00312D08(bank->allocation);
        else {
            link=bank->first;
            if(link!=sentinel){
                owner=D_0040E778.previous;
                do {
                    s32 retained=0;void *sound=link->object;
                    if(owner==&D_0040E778)func_00315F28(sound);
                    while(owner!=&D_0040E778){if(func_00314440((RwaBank *)((char *)owner-0x1c),sound)){retained=1;break;}owner=owner->previous;}
                    if(!retained)func_00315F28(sound);
                    link=link->next;owner=D_0040E778.previous;
                }while(link!=sentinel);
            }
            func_00318340(sentinel);func_003145D0(bank);
        }
    }
}

#endif
