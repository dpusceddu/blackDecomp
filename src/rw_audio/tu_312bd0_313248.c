#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "rw_audio/sound.h"
#endif

extern s32 func_003131C0();
extern s32 func_00312BC8();
extern s32 func_00313F50();
extern s32 func_00313F90();
extern s32 func_00312C48();
extern void func_00313C48(void *arg0);
extern s32 func_00324E38();
extern s32 func_00324D98();
extern s32 func_00316618();
extern s32 func_003165C8();
extern s32 func_00318250(s32);
extern s32 func_00318288(s32);
extern s32 func_003183C0(s32);

void func_00313248(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) == func_003131C0) {
        func_00312BC8();
    }
}

#ifdef NON_MATCHING
extern void func_00313650(RwaDiskHeader *);
extern void *func_00312CC8(u32,u32);
extern void *func_0035C544(void *,const void *,u32);
extern void func_00312D08(void *);
extern void func_00324BA0(s32,void *,u32,s32,s32,void *);
extern void func_00314278(RwaBank *);
extern void func_003137D8(RwaBank *,s32,s32);
extern s32 func_00316400(void *,const char *);
extern void *D_0040E15C;
extern void func_00313F00(void *,void *);
extern void *func_00313C90(RwaBank *,u32);
extern RwaBank *D_0040E178,*D_0040E174;
extern RwaLink D_0040E778;
extern void func_00313DC8(RwaBank *);
extern void func_00315F28(void *);
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313278);
#endif
#ifdef NON_MATCHING
extern void func_00324A88(s32,void *,u32,u32,s32,s32,void *);
extern u32 D_0040E164;
extern void func_003164D0(RwaBank *);
extern void func_003182C8(void *);
extern void func_00315B60(void *);
extern u32 func_00315168(u32);
extern s32 func_00324990(const char *);
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003134E0);
#endif

s32 func_00313948(s32 arg0) {
    return func_003143D8(arg0, (s32) func_00313F50, M2C_FIELD(arg0, s32 *, 0x28));
}

s32 func_00313970(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_003143D8(arg0, (s32) func_00313F90, M2C_FIELD(arg0, s32 *, 0x28));
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    return temp_v0;
}


void * func_00313BF0(void *arg0) {
    s32 var_2;
    void *var_16;

    var_16 = arg0;
    if (var_16 == NULL) {
        var_16 = func_00312C48(0x48, 0x30808);
        var_2 = 2;
    } else {
        var_2 = 1;
    }
    M2C_FIELD(var_16, s32 *, 0x30) = var_2;
    func_00313C48(var_16);
    return var_16;
}


void func_00313E60(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) | M2C_FIELD(arg1, u8 *, 8));
}

void func_00313E88(void) {
    func_00324E38();
}

s32 func_00313EA8(s32 arg0) {
    return func_00324D98(arg0, 0);
}

void * func_00313EC8(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), M2C_UNK (**)(), 0x24)();
    return arg0;
}


s32 func_00314330(s32 arg0, s32 arg1, s32 arg2) {
    func_00316618(arg0, arg1);
    func_003165C8(arg0, arg2);
    return arg0;
}


void func_003143D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_17;
    s32 temp_4;
    void *var_16;

    temp_17 = arg0 + 0xC;
    var_16 = M2C_FIELD(arg0, void **, 0x10);
    if (var_16 != temp_17) {
loop_1:
        temp_4 = M2C_FIELD(var_16, s32 *, 8);
        var_16 = M2C_FIELD(var_16, void **, 4);
        if (((s32 (*)(s32, s32)) arg1)(temp_4, arg2) != 0) {
            if (var_16 != temp_17) {
                goto loop_1;
            }
        }
    }
}

s32 func_00314440(s32 arg0) {
    return (~func_00318250(arg0 + 0xC) == 0) ? 0 : arg0;
}


void func_00314488(s32 arg0) {
    func_00318288(arg0 + 0xC);
}

void func_003144A8(s32 arg0) {
    func_003183C0(arg0 + 0xC);
}
