#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/actor/views.hpp"
#include "game/ai_vector.hpp"
namespace ActorEvents {

template<class T> inline T &At(void *base,int offset) { return *(T *)((char *)base+offset); }
struct CollisionEvent { Game::Position4 first,second; };
struct Matrix { Game::Position4 rows[4]; };
}
extern "C" {
void *func_001AFD80(void *,void *);
float func_001AFDB0(void *);
char *func_00147988(void *,int);
void func_0014C120(void *);
void func_001ECF80(void *,void *,void *);
void func_0025CB08(void *,void *);
void func_00149828(void *,int,int);
void func_001B1728(Game::Vec,Game::Vec,ActorEvents::Matrix *);
void func_001B7A00(void *,ActorEvents::Matrix *,long,int);
extern char *D_0040F510;
extern void *D_0040F4CC;
extern char *D_0040F4D8;
}
namespace ActorEvents {
int ActorEntries::Collision(void *raw) {
    CollisionEvent *event=(CollisionEvent *)raw;
    int result=0;
    if (At<unsigned char>(this,0x1ec) || Game::Y(Game::Load(event->second))<0.9f) return 0;
    if (Field_01F0()) func_0025CB08(D_0040F4CC,Field_00B4());
    for (int i=0;i<Field_01F5();++i) {
        void *item=func_001AFD80((char *)Field_01A0()+i*12,Field_0118());
        if (item) {
            unsigned short flags=At<unsigned short>(item,0x5a);
            if (flags&4) func_00149828(this,i,1);
            else if (flags&8) func_00149828(this,i,0);
            if (At<unsigned short>(item,0x5a)&0x1000) result=1;
            if (At<long>(item,0x20)) {
                Matrix transform;
                func_001B1728(Game::Load(event->first),Game::Load(event->second),&transform);
                func_001B7A00(D_0040F4D8+0x696f0,&transform,At<long>(item,0x20),1);
            }
        }
    }
    At<unsigned char>(this,0x1ec)=1;
    return result;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/actor_collision", func_00149798);
extern "C" {
void func_00148FF8(void*, void*, s32, s32);
void func_001AFD18(void*, void*, s32);
void func_00148BE0(void*, s8);
void func_00149260(void*, s32, void*, void*);
s32 func_001484C8(void*);
void func_001479B8(void*, s32, s32, s32, s32, s32, s32);
void func_001B6CF8(void*, void*, s32);
void func_001B37C8(void*, u16);
void func_00149BE8(void*, s32, s32);
s32 func_001AFDA8(void*);
void func_00175B60(void*, void*);
void func_0017BD10(void*, void*);
void func_001396F0(void*, void*);
extern char* D_0040F4D4;
extern void* D_0040F514;
}

extern "C" void func_00149828(void* self, s32 index, s32 mode) {
    using ActorEvents::At;
    s32 offset = index * 12;
    void* previous = func_001AFD80(At<char*>(self, 0x1A0) + offset, At<void*>(self, 0x118));
    func_00148FF8(self, previous, At<s32>(At<s32*>(self, 0x1A4) + index, 0), mode);
    func_001AFD18(At<char*>(self, 0x1A0) + offset, At<void*>(self, 0x118), mode);
    void* current = func_001AFD80(At<char*>(self, 0x1A0) + offset, At<void*>(self, 0x118));
    if (current) {
        if (At<s32>(previous, 0x54) == 3) func_00148BE0(self, (s8)index);
        At<s32>(At<char*>(self, 0x194) + index * 0x60, 0x40) = At<s32>(current, 0xC0);
        if (index < At<u8>(self, 0x1F6)) {
            func_00149260(self, index, previous, current);
            goto release_effect;
        }
    } else {
        if (index != func_001484C8(self)) {
            func_001479B8(self, index, 0, 0, 0, 0, 0);
        } else {
            At<s8>(self, 0x1ED) = 2;
            if (At<u16>(previous, 0x5A) & 0x400) func_001B6CF8(D_0040F4D8 + 0x66290, self, 1);
        }
    release_effect:
        if (index < At<u8>(self, 0x1F6)) {
            u16* handle = (u16*)(index * 2 + At<s32>(self, 0x1B0));
            if (*handle != 0xFFFF) func_001B37C8(D_0040F4D8 + 0x33C40, *handle);
        }
    }
    if (At<u16>(previous, 0x5A) & 0x800) {
        if (!At<u8>(self, 0x1F7)) {
            void* table = At<void*>(self, 0x10);
            At<void (*)(void*, s32)>(table, 0x14)((char*)self + At<s16>(table, 0x10), 0);
            At<u8>(self, 0x1F7) = 1;
        }
        if (At<u64>(At<void*>(self, 0x114), 0x40) == 0x5B40892788A8CBA5UL &&
            At<u64>(previous, 0x60) == 0x90D93D2203A3B192UL) {
            func_00149BE8(self, 0, func_001AFDA8(At<void*>(self, 0x1A0)));
            At<s8>(self, 0x1EB) = 1;
        }
    }
    func_00175B60(D_0040F4D4 + 0xA48, self);
    func_0017BD10(D_0040F4D4 + 0xCD4, self);
    func_001396F0(D_0040F514, self);
}
