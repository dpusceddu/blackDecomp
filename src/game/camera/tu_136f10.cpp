#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/actor/control_view.h"
#include "ps2/vu0.hpp"
#include "game/actor/bone_cache.h"

/* XYZ are (0, value, 0); W follows the shared native constructor. */
static inline Game::Vec ActorYVector(f32 value) {
    Game::Position4 point;
    Game::Store(point, Game::Make3(0.0f, value, 0.0f));
    return Game::Load(point);
}
#ifdef NON_MATCHING
#include "game/weapons/instance.hpp"
#include "ps2/vu0_lowering.h"

static inline Game::Vec ActorHorizontalSquared(Game::Vec delta) {
    Game::Vec zSquared;
    asm("vmulz.z zv, deltav, deltavz\n\tvmulx.x deltav, deltav, deltavx\n\tvaddz.x deltav, deltav, zvz"
        : "+j deltav"(delta), "=&j zv"(zSquared));
    return delta;
}
static inline Game::Vec ActorBitsVector(s32 word) {
    Game::Vec value;
    asm("qmtc2.ni wordv, valuev" : "=j valuev"(value) : "r wordv"(word));
    return value;
}
static inline s128 ActorVectorWords(Game::Vec value) {
    s128 words;
    asm("qmfc2.ni wordsv, valuev" : "=r wordsv"(words) : "j valuev"(value));
    return words;
}
static inline Game::Vec ActorVectorFromWords(s128 words) {
    Game::Vec value;
    asm("qmtc2.ni wordsv, valuev" : "=j valuev"(value) : "r wordsv"(words));
    return value;
}
static inline Game::Vec ActorFloatVector(f32 amount) {
    s32 word; Game::Vec value;
    asm("mfc1 %0, %1" : "=r"(word) : "f"(amount));
    asm("qmtc2.ni wordv, valuev" : "=j valuev"(value) : "r wordv"(word));
    return value;
}
static inline Game::Vec ActorRaiseY(Game::Vec point, Game::Vec scalar) {
    Game::Vec sum;
    asm("vaddx.y sumv, pointv, scalarvx" : "=j sumv"(sum) : "j pointv"(point), "j scalarv"(scalar));
    asm("vaddy.y resultv, vf0, sumvy" : "+j resultv"(point) : "j sumv"(sum));
    return point;
}
static inline Game::Vec ActorLowerY(Game::Vec point, Game::Vec scalar) {
    asm("vsubx.y scalarv, pointv, scalarvx" : "+j scalarv"(scalar) : "j pointv"(point));
    Game::Vec result = ActorVectorFromWords(ActorVectorWords(point));
    asm("vaddy.y resultv, vf0, scalarvy" : "+j resultv"(result) : "j scalarv"(scalar));
    return result;
}
#endif

extern "C" {
extern s32 _stricmp(const char*, const char*);
extern s32 func_00138298(Recovered_ActorBoneCache*, const char*);
#ifdef NON_MATCHING
extern const char* D_003BCE70[11];
extern const f32 D_003F5128[4];
extern void func_001415A8(void*, s32);
#endif

extern void* D_0040F4D0;
extern s32 func_0012D158(void*, s32, s32);
extern f32 func_0012D0D0(void*, f32, f32);
extern s32 func_00138320(void*);
extern f32 func_00138360(s32);
extern s128 D_004147A0;
extern f32 D_003BCE68, D_003BCE64;
/* UNVERIFIED: downstream return type is unused; the mixed-bank input values are explicit. */
extern void func_00143158(void*, s128, s128, s128, f32, f32);

extern void * D_0040F4BC;
extern s32 D_003BD140;
extern unsigned char D_004147C0;
extern M2C_UNK D_003F5138;
extern const u32 rodata_003F5168[12] __asm__("D_003F5168") __attribute__((aligned(8))) = { 0x3DCCCCCD, 0x3E800000, 0x3E19999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D851EB8, 0x3D99999A, 0x3D851EB8, 0x00000000 };
extern volatile char D_003F5168;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00136F10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137018);

void func_00137318(s64 *arg0, s64 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137320);
#ifdef NON_MATCHING
// Unmatched: body instructions agree, but native section extent is eight bytes larger.
s32 func_00137450(Recovered_ManagedActor* actor) {
    s32 active = 0;
    if (actor->unk_2A4) active = Actor_GetManagedSlot(actor)->unk_31 != 0;
    return active;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137450);
#endif
void func_00137490(Recovered_ManagedActor* actor, f32 firstValue, f32 secondValue) {
    void* control = actor->unk_26C;
    if (control) {
        s128 first = ActorYVector(firstValue);
        s128 second = ActorYVector(secondValue);
        func_00143158(control, first, second,
            D_004147A0, D_003BCE68, D_003BCE64);
    }
}
void func_001374F8(Recovered_ManagedActor* actor, s32 index) {
    Actor_IndexedRecord(actor, index)->unk_4C = 0.0f;
}
/* The record address uses the low 16 bits; the table lookup receives the full index. */
void func_00137520(Recovered_ManagedActor* actor, s32 index) {
    Recovered_ActorIndexedControl* record = Actor_IndexedRecord(actor, index);
    record->unk_4C = func_00138360(index);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137718);

f32 func_001378F0(Recovered_ManagedActor* actor) {
    return actor->unk_C0 * M2C_FIELD(D_0040F4BC, f32 *, 0x1660);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137908);
#ifdef NON_MATCHING
// Unmatched: inlined layer predicate and register allocation differ.
s32 func_00137A78(Recovered_ManagedActor* actor) {
    s32 result = 0;
    if (Actor_LayerHasEntry(actor)) {
        if (func_00138320(actor->unk_328) == 0x28) result = 1;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137A78);
#endif

s32 func_00137AE0(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x2A4);
    if (temp_2 != NULL) {
        return M2C_FIELD(M2C_FIELD(temp_2, void **, 0xE8), s32 *, 0xC) + 0x10;
    }
    return D_003BD140;
}

void func_00137B08(Recovered_ManagedActor* actor, u8 flag) {
    s32 integer;
    actor->unk_3AC = flag;
    integer = func_0012D158(D_0040F4D0, -128, 0);
    actor->unk_258 = integer - func_0012D0D0(D_0040F4D0, 0.6f, 0.9999f);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137B88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137CA0);
#ifdef NON_MATCHING
// Unmatched: vertical byte-result lowering and XZ helper scheduling differ.
s32 func_00137E88(Recovered_ManagedActor* actor, s128 point, f32 margin) {
    Game::Vec delta = Game::Sub3(point, actor->transform.position);
    bool outside = actor->unk_2E8 < Game::Y(delta) || Game::Y(delta) < 0.0f;
    if (outside) return 0;
    f32 radius = actor->unk_318 * 0.5f + margin;
    return !(radius * radius < __ee_vu_read_x(ActorHorizontalSquared(delta)));
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137E88);
#endif
#ifdef NON_MATCHING
// Unmatched: VU copy scheduling and the call delay slot differ.
void func_00137F30(Recovered_ManagedActor* actor) {
    Weapons::Hit hit;
    Game::Vec center = ActorRaiseY(actor->transform.position, ActorFloatVector(actor->unk_2E8 * 0.5f));
    s128 start = ActorVectorWords(center);
    s128 end = ActorVectorWords(ActorLowerY(center, ActorBitsVector(0x40000000)));
    if (Weapons::func_0012AE58((Weapons::Frame*)D_0040F4D0, start, end, 2, NULL, 0, &hit)) {
        actor->unk_320 = hit.entity;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137F30);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00137FB8);
/* Native behavior returns index zero both for the first name and for no match. */
s32 func_00138298(Recovered_ActorBoneCache* cache, const char* name) {
    s32 index = 0;
    if (cache->catalog->count > 0) {
        do {
            if (_stricmp(cache->catalog->names[index], name) == 0) return index;
            ++index;
        } while (index < cache->catalog->count);
    }
    return 0;
}

s32 func_00138320(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00138328);

void func_00138338(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

s32 func_00138340(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 8);
}

f32 func_00138348(s32 arg0) {
    return M2C_FIELD(((arg0 * 4) + ((s32) &D_003F5138)), f32 *, 0);
}

f32 func_00138360(s32 arg0)
{
  return *((f32 *) (((s8 *) ((arg0 * 4) + (&D_003F5168))) + 0));
}

void *func_00138378(s32 arg0)
{
  int new_var;
  new_var = arg0 & 0xFFFFFFFFFFFFFFFF;
  return (new_var << 6) + (&D_004147C0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00138390);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_00138468);

void func_00138470(void *arg0, void *arg1) {
    f32 var_f1;

    var_f1 = 0.0f;
    M2C_FIELD(arg0, void **, 0) = arg1;
    if (M2C_FIELD(arg1, f32 *, 0x308) > 0.0f) {
        var_f1 = 1.0f / func_001378F0((Recovered_ManagedActor*)arg1);
    }
    M2C_FIELD(arg0, f32 *, 4) = var_f1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_136f10", func_001384C8);

}
