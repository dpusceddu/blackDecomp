/* Medium-confidence TU: shared-data joins and calls; names in access views are inferred. */

#ifdef NONMATCHING_RWA_3168C8
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/emitter.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_RwaFormat.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 * D_0040E1B0;
extern RwaEmitter *D_0040E788;
extern s32 D_0040E1C0;
extern s32 D_0040E1B8;
extern s32 func_003175C8(void *);
extern s32 func_003107E0(void *, s32, s32, void *);
extern s32 func_003105E8(void *, s32, s32, s32);
extern s32 func_00310698(void *, s32, s32, void *);
extern s32 D_0040E1C4;
extern s32 func_00314F08(Recovered_RwaFormat *, s32);
extern void * func_00310870(void *, s32, s32, void *);
extern s32 func_003106F0(void *, s32, s32, f32);
extern s32 func_00310640(void *, s32, s32, s32);
extern s32 func_00310590(void *, s32, s32, void *);

s32 func_003168C8(void) {
    RwaEmitter *temp_18;
    RwaEmitter *var_16;
    f32 var_f2;
    s32 *var_2;
    u32 temp_2;
    s32 temp_5;
    s32 var_19;
    s32 var_2_2;
    u32 temp_2_2;
    u32 temp_3_3;
    u8 temp_3;
    u8 temp_3_2;
    void *temp_17;
    void *temp_2_3;
    void *temp_4;

    var_2 = D_0040E1B0;
    if (var_2 != NULL) {
        var_16 = D_0040E788;
        var_19 = 0;
        if (var_16 != &D_0040E788) {
            do {
                temp_17 = var_16->handle;
                temp_18 = var_16->next;
                if (var_19 < (D_0040E1C0 - D_0040E1B8)) {
                    temp_3 = var_16->flags;
                    if (temp_3 & 0x10) {
                        func_003175C8(var_16);
                    } else if (temp_17 != NULL) {
                        if (temp_3 & 8) {
                            var_2_2 = var_16->start_bytes;
                        } else {
                            var_2_2 = func_003107E0(temp_17, 9, 2, NULL);
                        }
                        var_16->position_bytes = var_2_2;
                        func_003105E8(temp_17, 8, 1, 0);
                        func_00310698(temp_17, 0xB, 1, NULL);
                        func_00310698(var_16->handle, 0xE, 1, NULL);
                        var_16->handle = NULL;
                        var_16->last_tick = (s32) D_0040E1C4;
                    }
                    temp_3_2 = var_16->flags;
                    if ((temp_3_2 & 1) && !(temp_3_2 & 8)) {
                        temp_4 = var_16->sound;
                        temp_5 = func_00314F08(temp_4 + 0x10, M2C_FIELD(temp_4, s32 *, 0x18));
                        temp_2 = D_0040E1C4 - var_16->last_tick;
                        var_f2 = (f32)temp_2;
                        temp_3_3 = var_16->position_bytes + (s32) ((var_f2 * var_16->pitch) / 1000.0f);
                        var_16->position_bytes = (s32) temp_3_3;
                        if (temp_3_3 >= (u32) temp_5) {
                            if (var_16->flags & 4) {
                                do {
                                    temp_2_2 = var_16->position_bytes - temp_5;
                                    var_16->position_bytes = (s32) temp_2_2;
                                } while (temp_2_2 >= (u32) temp_5);
                            } else {
                                func_003175C8(var_16);
                                var_16->handle = NULL;
                            }
                        }
                        var_16->last_tick = (s32) D_0040E1C4;
                    }
                } else if (temp_17 == NULL) {
                    temp_2_3 = func_00310870(D_0040E1B0, 4, 2, NULL);
                    var_16->handle = temp_2_3;
                    if (temp_2_3 != NULL) {
                        func_00310698(temp_2_3, 0xB, 1, var_16->sound);
                        func_003106F0(temp_2_3, 6, 1, var_16->pitch);
                        func_003106F0(temp_2_3, 7, 1, (f32) var_16->gain / 255.0f);
                        func_003105E8(temp_2_3, 0xA, 1, ((u8) var_16->flags >> 2) & 1);
                        if (!(var_16->flags & 8)) {
                            func_00310640(temp_2_3, 9, 1, var_16->position_bytes);
                        }
                        func_003106F0(temp_2_3, 0xC, 1, (f32) var_16->pan);
                        func_00310590(temp_2_3, 0, 1, (u8 *)var_16 + 8);
                        func_00310590(temp_2_3, 1, 1, (u8 *)var_16 + 0x14);
                        func_003106F0(temp_2_3, 4, 1, var_16->min_distance);
                        func_003106F0(temp_2_3, 5, 1, var_16->max_distance);
                        func_003106F0(temp_2_3, 0xD, 1, (f32) var_16->field5e / 255.0f);
                        func_003105E8(temp_2_3, 8, 1, 1);
                        func_00310698(temp_2_3, 0xE, 1, var_16->user);
                    }
                }
                var_2 = (s32 *) var_16->channels;
                var_16 = temp_18;
                var_19 = (s32) (var_19 + var_2);
            } while (var_16 != &D_0040E788);
        }
    }
    return (s32) var_2;
}

#endif

#ifdef NONMATCHING_RWA_316C38
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "auto/prelude.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern void * func_00311DB8(s8 *);
extern s8 D_00409610;
extern s8 D_00409400;
extern s32 * func_00312C48(s32, s32);
extern s32 func_003176D0(s32, void *);
extern s32 * func_00310338(void *, void *, void *);
extern s32 * D_0040E1B0;
extern s32 * func_00312C70(s32 *);
extern s32 * D_0040E790;
extern s32 * func_00310478(s32 *, s32);
extern s32 D_0040E1B8;
extern s32 D_0040E1AC;
extern s32 func_00310698(void *, s32, s32, void *);
extern void * D_0040E1B4;
extern void * func_00310870(void *, s32, s32, void *);

s32 func_00316C38(void *input, s32 operation, s32 length) {
    u8 sp[64] __attribute__((aligned(16)));
    s32 *temp_2_2;
    s32 *temp_2_3;
    s32 *temp_3;
    s32 *temp_4;
    s32 *var_18;
    s32 temp_2_4;
    s32 var_17_2;
    s32 var_2;
    u32 var_17;
    void *temp_16;
    void *temp_2;

    temp_16 = func_00311DB8(&D_00409610);
    temp_2 = func_00311DB8(&D_00409400);
    temp_2_2 = func_00312C48(((length + 1) * 0x18) + ((M2C_FIELD(temp_16, u16 *, 0x14) * 8) + ((M2C_FIELD(temp_16, u16 *, 0x16) * 8) + 0x1C)) + ((M2C_FIELD(temp_2, u16 *, 0x14) * 8) + ((M2C_FIELD(temp_2, u16 *, 0x16) * 8) + 0x28)) + (length * 4), 0x3080E);
    var_2 = 0;
    if (temp_2_2 != NULL) {
        *(s32 *)(sp + 24) = 0;
        *(s32 *)(sp + 16) = 2;
        *(s32 *)(sp + 20) = 0;
        *(s32 * *)(sp + 48) = (s32 *)((u8 *)temp_2_2 + 0x18);
        *(s32 *)(sp + 28) = func_003176D0;
        *(s32 ** *)(sp + 32) = (sp + 48);
        *(s32 * *)(sp + 36) = temp_2_2;
        temp_2_3 = func_00310338(input, temp_16, (sp + 16));
        D_0040E1B0 = temp_2_3;
        if (temp_2_3 == NULL) {
            func_00312C70(temp_2_2);
            return 0;
        }
        var_17 = 0;
        D_0040E790 = *(s32 * *)(sp + 48);
        var_18 = (s32 *)((u8 *)*(s32 **)(sp + 48) + length * 4);
        if (length != 0) {
loop_6:
            *(s32 * *)(sp + 48) = (s32 *)((u8 *)var_18 + 0x18);
            *(s32 * *)(sp + 36) = var_18;
            D_0040E790[var_17] = func_00310338(M2C_FIELD(((var_17 * 4) + operation), u32 *, 0), temp_2, (sp + 16));
            if (D_0040E790[var_17] != 0) {
                var_17 += 1;
                var_18 = *(s32 * *)(sp + 48);
                if (var_17 >= (u32) length) {
                    goto block_15;
                }
                goto loop_6;
            }
            var_17_2 = var_17 - 1;
            temp_4 = D_0040E1B0;
            if (var_17_2 != 0xFFFFFFFF) {
                temp_3 = D_0040E790;
                do {
                    temp_2_4 = var_17_2 * 4;
                    var_17_2 -= 1;
                    func_00310478(M2C_FIELD((temp_2_4 + temp_3), s32 **, 0), 0);
                } while (var_17_2 != 0xFFFFFFFF);
            }
            func_00310478(temp_4, 0);
            D_0040E1B8 = 0;
            D_0040E1B0 = NULL;
            return 0;
        }
block_15:
        *(s32 *)(sp + 0) = length;
        *(s32 * *)(sp + 4) = D_0040E790;
        D_0040E1AC = 1;
        D_0040E1B8 = length;
        func_00310698(D_0040E1B0, 5, 1, sp);
        D_0040E1B4 = func_00310870(D_0040E1B0, 1, 2, NULL);
        var_2 = 1;
        /* Duplicate return node #16. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}

#endif

#ifdef NONMATCHING_RWA_316E90
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/emitter.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 func_00310768(void *, s32, s32, void *);
extern s32 func_003105E8(void *, s32, s32, s32);
extern s32 func_00310698(void *, s32, s32, void *);
extern void * D_0040E780;
extern s32 D_0040E1BC;
extern s32 D_0040E1C0;
extern s32 func_00317030(void *);
extern s32 * D_0040E1B0;
extern M2C_UNK D_0040A0F0;

void func_00316E90(RwaEmitter *input) {
    u8 temp_2;
    void *temp_17;
    void *temp_4;

    if (input->flags & 1) {
        input->previous->next = input->next;
        M2C_FIELD(input->next, void ***, 4) = (void **) input->previous;
        temp_17 = input->handle;
        if (temp_17 != NULL) {
            if (func_00310768(temp_17, 8, 2, NULL) != 0) {
                func_003105E8(temp_17, 8, 1, 0);
            }
            func_00310698(temp_17, 0xB, 1, NULL);
            func_00310698(temp_17, 0xE, 1, NULL);
            input->handle = NULL;
        }
        input->previous = &D_0040E780;
        input->next = (void *) D_0040E780;
        M2C_FIELD(D_0040E780, void **, 4) = input;
        D_0040E780 = input;
        D_0040E1BC -= 1;
        D_0040E1C0 -= input->channels;
        input->level = 0;
        input->channels = 0U;
        input->position_bytes = (s32) input->start_bytes;
        input->flags = (u8) (input->flags & 0xFC);
    }
    func_00317030(input);
    input->channels = 1U;
    temp_4 = input->sound;
    input->flags = (u8) (input->flags | 2);
    input->start_bytes = 0;
    input->channels = (u8) M2C_FIELD(temp_4, u8 *, 0x1D);
    if ((M2C_FIELD(temp_4, s32 *, 0x54) & 2) && (func_00310768(D_0040E1B0, 3, 2, NULL) == 4) && (*M2C_FIELD(*D_0040E1B0, s32 **, 0) == &D_0040A0F0)) {
        input->channels = 2U;
    }
    temp_2 = input->channels;
    D_0040E1C0 += temp_2;
    D_0040E1BC += 1;
    return;
}

#endif

#ifdef NONMATCHING_RWA_317030
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/emitter.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 func_003178F0(void *, void *, void *, void *, s32, s32);
extern void * D_0040E1B4;
extern M2C_UNK * D_0040E788;

void func_00317030(RwaEmitter *input) {
    u8 sp[48] __attribute__((aligned(16)));
    f32 temp_f2;
    f32 temp_f3;
    f32 var_f0;
    f32 var_f1;
    f32 var_f4;
    u8 temp_2;
    void *temp_2_2;
    void *temp_3;
    void *var_5;

    input->level = 0U;
    if (input->gain != 0) {
        if (((s32) M2C_FIELD(input->sound, s32 *, 0x54) >> 1) & 1) {
            *(s64 *)(sp + 0) = M2C_UNALIGNED64(input, 8);
            *(s32 *)(sp + 8) = M2C_FIELD(input, s32 *, 0x10);
            *(s64 *)(sp + 12) = M2C_UNALIGNED64(input, 0x14);
            *(s32 *)(sp + 20) = M2C_FIELD(input, s32 *, 0x1C);
            *(f32 *)(sp + 24) = input->min_distance;
            *(f32 *)(sp + 28) = input->max_distance;
            func_003178F0(D_0040E1B4, (u8 *)input - 0xFA0, sp, (sp + 32), 0, 1);
            M2C_UNALIGNED64(input, 0x20) = *(s64 *)(sp + 0);
            M2C_FIELD(input, s32 *, 0x28) = *(s32 *)(sp + 8);
            M2C_UNALIGNED64(input, 0x2C) = *(s64 *)(sp + 12);
            M2C_FIELD(input, s32 *, 0x34) = *(s32 *)(sp + 20);
            var_f4 = *(f32 *)(sp + 32) * ((f32) input->gain / 255.0f);
        } else {
            var_f4 = 1.0f;
        }
        if (var_f4 > 0.0f) {
            temp_f3 = (f32) input->blend / 255.0f;
            input->level = (u8) (s32) ((var_f4 * 255.0f * (1.0f - temp_f3)) + (((f32) input->priority / 255.0f) * 255.0f * temp_f3));
        }
    }
    var_5 = input;
    if (input->flags & 1) {
        temp_f2 = (f32) input->level / 255.0f;
loop_8:
        temp_2_2 = M2C_FIELD(var_5, void **, 0);
        temp_3 = M2C_FIELD(var_5, void **, 4);
        if (temp_2_2 == &D_0040E788) {
            var_f1 = 2.0f;
        } else {
            var_f1 = (f32) M2C_FIELD(temp_2_2, u8 *, 0x60) / 255.0f;
        }
        if (temp_3 != &D_0040E788) {
            var_f0 = (f32) M2C_FIELD(temp_3, u8 *, 0x60) / 255.0f;
        } else {
            var_f0 = -1.0f;
        }
        if (var_f1 < temp_f2) {
            var_5 = M2C_FIELD(var_5, void **, 0);
            goto loop_8;
        }
        if (temp_f2 < var_f0) {
            var_5 = M2C_FIELD(var_5, void **, 4);
            goto loop_8;
        }
        if (var_5 != input) {
            input->previous->next = (void *) input->next;
            M2C_FIELD(input->next, void **, 4) = (void *) input->previous;
            input->previous = (void *) M2C_FIELD(var_5, void **, 4);
            input->next = var_5;
            goto block_38;
        }
    } else {
        input->previous->next = (void *) input->next;
        M2C_FIELD(input->next, void **, 4) = (void *) input->previous;
        var_5 = M2C_FIELD(&D_0040E788, M2C_UNK **, 0);
        if (var_5 == &D_0040E788) {
            goto block_36;
        }
loop_29:
        if ((u8) input->level >= (u8) M2C_FIELD(var_5, u8 *, 0x60)) {
            var_5 = M2C_FIELD(var_5, void **, 0);
            if (var_5 == &D_0040E788) {
                goto block_36;
            }
            goto loop_29;
        }
        if (var_5 != &D_0040E788) {
            input->next = var_5;
            input->previous = (void *) M2C_FIELD(var_5, void **, 4);
block_38:
            *M2C_FIELD(var_5, void ***, 4) = input;
            M2C_FIELD(var_5, void **, 4) = input;
        } else {
block_36:
            input->next = &D_0040E788;
            input->previous = M2C_FIELD(&D_0040E788, void **, 4);
            *M2C_FIELD(&D_0040E788, void ***, 4) = input;
            M2C_FIELD(&D_0040E788, void **, 4) = input;
        }
    }
    temp_2 = input->flags | 1;
    input->flags = temp_2;
    return;
}

#endif

#ifdef NONMATCHING_RWA_317340
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/emitter.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern void func_00317030(void *);
extern s32 func_00310768(void *, s32, s32, void *);
extern s32 func_003105E8(void *, s32, s32, s32);
extern s32 func_00310698(void *, s32, s32, void *);
extern void * D_0040E780;
extern s32 D_0040E1BC;
extern s32 D_0040E1C0;
extern void func_00316E90(void *);

void func_00317340(RwaEmitter *input, s32 operation) {
    s32 var_2;
    u8 temp_2;
    void *temp_17;

    switch (operation) {                                 /* irregular */
    case 2:
        var_2 = input->flags & 1;
        if (var_2 != 0) {
            func_00317030(input);
        }
        return;
    case 1:
        var_2 = input->flags & 1;
        if (var_2 != 0) {
            input->previous->next = input->next;
            M2C_FIELD(input->next, void ***, 4) = (void **) input->previous;
            temp_17 = input->handle;
            if (temp_17 != NULL) {
                if (func_00310768(temp_17, 8, 2, NULL) != 0) {
                    func_003105E8(temp_17, 8, 1, 0);
                }
                func_00310698(temp_17, 0xB, 1, NULL);
                func_00310698(temp_17, 0xE, 1, NULL);
                input->handle = NULL;
            }
            input->previous = &D_0040E780;
            input->next = (void *) D_0040E780;
            M2C_FIELD(D_0040E780, void **, 4) = input;
            D_0040E780 = input;
            D_0040E1BC -= 1;
            D_0040E1C0 -= input->channels;
            input->channels = 0U;
            temp_2 = input->flags & 0xFC;
            input->level = 0;
            input->position_bytes = (s32) input->start_bytes;
            input->flags = temp_2;
            return;
        }
        /* Duplicate return node #15. Try simplifying control flow for better match */
        return;
    case 0:
        func_00316E90(input); return;
    default:
        return;
    }
}

#endif

#ifdef NONMATCHING_RWA_3176E0
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/emitter.h"
extern void func_002A75F0(RwaVec3 *,const RwaVec3 *);
void func_003176E0(RwaVec3 *value,const RwaListener *listener) {
    RwaVec3 forward __attribute__((aligned(16)));
    RwaVec3 right __attribute__((aligned(16)));
    RwaVec3 up __attribute__((aligned(16)));
    RwaVec3 velocity;
    f32 x,y,z;
    func_002A75F0(&forward,&listener->forward);
    func_002A75F0(&right,&listener->right);
    func_002A75F0(&up,&listener->up);
    x=value[0].x-listener->position.x;
    y=value[0].y-listener->position.y;
    z=value[0].z-listener->position.z;
    value[0].x=forward.x*x+forward.y*y+forward.z*z;
    value[0].z=up.x*x+up.y*y+up.z*z;
    value[0].y=right.x*x+right.y*y+right.z*z;
    x=value[1].x-listener->velocity.x;
    y=value[1].y-listener->velocity.y;
    z=value[1].z-listener->velocity.z;
    velocity.x=x;velocity.y=y;velocity.z=z;
    value[1].z=up.x*x+up.y*y+up.z*z;
    value[1].x=forward.x*x+forward.y*y+forward.z*z;
    value[1].y=right.x*x+right.y*y+right.z*z;
}

#endif

#ifdef NONMATCHING_RWA_3178F0
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "auto/prelude.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern u32 D_0040E1D0;
extern void * func_003176E0(void *, void *);
extern s32 D_0040E1D4;
extern M2C_UNK * D_0040E798;
extern f32 D_0040E1DC;
extern f32 (*D_0040E1D8)(void *, void *);
extern s32 func_0031B030(void *, void *, void *, s32, s32);

s32 func_003178F0(void *input, void *operation, void *length, void *event, s32 context, s32 flags) {
    s32 sp10;
    M2C_UNK *var_16;
    M2C_UNK *var_17;
    M2C_UNK *var_21;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f20;
    f32 var_f21;

    sp10 = flags;
    switch (D_0040E1D0) {                           /* irregular */
    case 2:
        func_003176E0(length, (void *) D_0040E1D4);
        break;
    case 3:
        var_17 = D_0040E798;
        var_f21 = D_0040E1DC;
        var_21 = NULL;
        if (var_17 != &D_0040E798) {
            var_16 = var_17 - 0x40;
            do {
                temp_f2 = M2C_FIELD(var_16, f32 *, 0x48) - M2C_FIELD(length, f32 *, 0);
                temp_f1 = M2C_FIELD(var_16, f32 *, 0x4C) - M2C_FIELD(length, f32 *, 4);
                temp_f0 = M2C_FIELD(var_16, f32 *, 0x50) - M2C_FIELD(length, f32 *, 8);
                var_f20 = (temp_f2 * temp_f2) + (temp_f1 * temp_f1) + (temp_f0 * temp_f0);
                if (D_0040E1D8 != NULL) {
                    var_f20 += D_0040E1D8(operation, var_16);
                }
                var_17 = *var_17;
                if (var_f20 < var_f21) {
                    var_21 = var_16;
                    var_f21 = var_f20;
                }
                var_16 = var_17 - 0x40;
            } while (var_17 != &D_0040E798);
        }
        func_003176E0(length, var_21);
        break;
    }
    return func_0031B030(input, length, event, context, sp10);
}

#endif

#ifdef NONMATCHING_RWA_317A78
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "auto/prelude.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 * func_00312C48(s32, s32);
extern s32 * func_0035C6EC(s32 *, s32, s32);

s32 func_00317A78(void *input, s32 operation) {
    u8 *temp_2;
    u8 *var_13;
    s32 temp_2_2;
    s32 temp_3;
    s32 temp_7;
    s32 var_2;
    s32 var_2_3;
    s32 var_4;
    s32 var_9;
    u32 temp_18;
    u32 var_12;
    u32 var_8;
    u8 *var_11;
    u8 *var_2_2;
    u8 temp_10;
    void *temp_15;

    temp_15 = input + 0x10;
    var_4 = 0;
    var_13 = M2C_FIELD(input, s32 **, 0x10);
    temp_18 = M2C_FIELD(input, u32 *, 8);
    if (var_13 != temp_15) {
        var_2_2 = var_13 + 8;
loop_2:
        var_9 = M2C_FIELD(input, s32 *, 4);
        var_12 = 0;
        if (temp_18 != 0) {
            var_11 = var_2_2;
loop_4:
            temp_10 = *var_11;
            if (temp_10 == 0xFF) {
                var_9 -= 8;
            } else {
                var_8 = 0;
                if (var_9 != 0) {
                    var_2_3 = 0x80 >> 0;
loop_9:
                    temp_7 = var_2_3 & 0xFF;
                    if (!(temp_10 & temp_7)) {
                        *var_11 |= temp_7;
                        temp_3 = M2C_FIELD(input, s32 *, 0xC);
                        var_4 = (((u32)(var_13 + (temp_18 + 8) + temp_3) - 1) & -temp_3) + (((var_12 * 8) + var_8) * M2C_FIELD(input, s32 *, 0));
                    } else {
                        var_8 += 1;
                        var_9 -= 1;
                        if (var_8 < 8U) {
                            var_2_3 = 0x80 >> var_8;
                            if (var_9 == 0) {

                            } else {
                                goto loop_9;
                            }
                        }
                    }
                }
            }
            if (var_4 == 0) {
                var_12 += 1;
                var_11 += 1;
                if (var_12 < temp_18) {
                    goto loop_4;
                }
            }
        }
        var_13 = *(u8 **)var_13;
        if (var_13 != temp_15) {
            var_2_2 = var_13 + 8;
            if (var_4 == 0) {
                goto loop_2;
            }
        }
    }
    var_2 = var_4;
    if (var_4 == 0) {
        temp_2 = func_00312C48(temp_18 + ((M2C_FIELD(input, s32 *, 4) * M2C_FIELD(input, s32 *, 0)) + 8) + M2C_FIELD(input, s32 *, 0xC), operation);
        if (temp_2 == NULL) {
            return 0;
        }
        func_0035C6EC(temp_2 + 8, 0, (s32) temp_18);
        M2C_FIELD(temp_2, void **, 4) = (void *) (input + 0x10);
        M2C_FIELD(temp_2, s32 *, 0) = (s32) M2C_FIELD(input, s32 **, 0x10);
        M2C_FIELD(M2C_FIELD(input, s32 **, 0x10), s32 **, 4) = temp_2;
        M2C_FIELD(input, s32 **, 0x10) = temp_2;
        M2C_FIELD(temp_2, s8 *, 8) = 0x80;
        temp_2_2 = M2C_FIELD(input, s32 *, 0xC);
        var_2 = (s32) ((temp_2 + (temp_18 + 8) + temp_2_2) - 1) & -temp_2_2;
        /* Duplicate return node #24. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}

#endif

#ifdef NONMATCHING_RWA_317C20
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/emitter.h"
extern void func_00312C70(void *);
void func_00317C20(RwaPool *pool,void *allocation) {
    RwaPoolBlock *block,*sentinel;
    u8 *bitmap,*slot;
    u32 bytes,index,i;
    s32 sum;
    sentinel=&pool->blocks;
    block=pool->blocks.next;
    bytes=pool->bitmap_bytes;
    while(block!=sentinel){
        slot=(u8 *)block+bytes+8;
        if((u32)allocation>=(u32)slot && (u32)(slot+pool->count*pool->stride)>=(u32)allocation){
            index=((u32)allocation-(u32)slot)/pool->stride;
            bitmap=(u8 *)block+8;
            bitmap[index>>3]&=~((0x80>>(index%8))&0xff);
            block->previous->next=block->next;
            block->next->previous=block->previous;
            if(pool->blocks.next==sentinel || !(M2C_FIELD(pool,u32 *,0x18)&2)){
                block->next=pool->blocks.next;
                block->previous=sentinel;
            }else{
                i=0;sum=0;
                if(bytes)do{sum+=bitmap[i];++i;}while(i<bytes);
                if(!sum){func_00312C70(block);return;}
                block->previous=sentinel;
                block->next=pool->blocks.next;
            }
            pool->blocks.next->previous=block;
            pool->blocks.next=block;
            return;
        }
        block=block->next;
    }
}

#endif

#ifdef NONMATCHING_RWA_317E40
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "auto/prelude.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 * D_0040E1E4;
extern s32 func_00317A78(void *, s32);
extern s32 * func_00312C48(s32, s32);
extern s32 * func_0035C6EC(s32 *, s32, s32);
extern s32 * func_00318080(s32 *);
extern M2C_UNK * D_0040E7A0;

s32 * func_00317E40(s32 input, s32 operation, s32 length, s32 event, u8 *context, s32 flags) {
    u8 *temp_2;
    u8 *temp_2_2;
    s32 *temp_4_2;
    u8 *var_16;
    s32 *var_2;
    s32 temp_19;
    s32 temp_20;
    s32 temp_4;
    s32 var_17;
    s32 var_2_2;
    s32 var_2_3;
    s32 var_4;
    u32 temp_18;

    var_16 = context;
    var_17 = event;
    temp_20 = (length != 0) ? length : 1;
    if (var_16 == NULL) {
        if (D_0040E1E4 != NULL) {
            var_2_2 = func_00317A78(D_0040E1E4, 0x30800);
        } else {
            var_2_2 = func_00312C48(0x24, flags);
        }
        var_16 = (u8 *) var_2_2;
        var_2 = NULL;
        if (var_16 != NULL) {
            var_2_3 = 2;
            goto block_8;
        }
        /* Duplicate return node #13. Try simplifying control flow for better match */
        return var_2;
    }
    var_2_3 = 3;
block_8:
    M2C_FIELD(var_16, s32 *, 0x18) = var_2_3;
    temp_4 = (input - 1 + temp_20) & -temp_20;
    temp_18 = (u32) (operation + 7) >> 3;
    temp_2 = var_16 + 0x10;
    M2C_FIELD(var_16, s32 *, 0) = temp_4;
    M2C_FIELD(var_16, s32 *, 4) = operation;
    M2C_FIELD(var_16, s32 *, 0xC) = temp_20;
    M2C_FIELD(var_16, u32 *, 8) = temp_18;
    M2C_FIELD(var_16, s32 **, 0x10) = temp_2;
    M2C_FIELD(var_16, s32 **, 0x14) = temp_2;
    if (var_17 != 0) {
        temp_19 = temp_18 + ((operation * temp_4) + 8);
        var_4 = temp_19 + temp_20;
loop_10:
        temp_2_2 = func_00312C48(var_4, flags);
        if (temp_2_2 != NULL) {
            M2C_FIELD(temp_2_2, s32 **, 4) = NULL;
            M2C_FIELD(temp_2_2, s32 *, 0) = 0;
            var_17 -= 1;
            M2C_FIELD(temp_2_2, s32 **, 4) = temp_2;
            M2C_FIELD(temp_2_2, s32 *, 0) = (s32) M2C_FIELD(var_16, s32 **, 0x10);
            M2C_FIELD(M2C_FIELD(var_16, s32 **, 0x10), s32 **, 4) = temp_2_2;
            M2C_FIELD(var_16, s32 **, 0x10) = temp_2_2;
            func_0035C6EC(temp_2_2 + 8, 0, (s32) temp_18);
            var_4 = temp_19 + temp_20;
            if (var_17 == 0) {
                goto block_12;
            }
            goto loop_10;
        }
        func_00318080(var_16);
        return NULL;
    }
block_12:
    M2C_FIELD(var_16, M2C_UNK ***, 0x20) = &D_0040E7A0;
    temp_4_2 = var_16 + 0x1C;
    M2C_FIELD(var_16, M2C_UNK **, 0x1C) = (M2C_UNK *) D_0040E7A0;
    var_2 = var_16;
    M2C_FIELD(D_0040E7A0, s32 **, 4) = temp_4_2;
    D_0040E7A0 = (M2C_UNK *) temp_4_2;
    return var_2;
}

#endif

#ifdef NONMATCHING_RWA_318D28
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/request.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 D_0040E214;
extern void func_003678A0(); /* WaitSema */
extern s32 D_00458490;
extern s32 D_004584C4;
extern s32 func_0031D2A8(void *);
extern s32 D_004584C0;
extern s32 D_00456480;
extern void func_00367880(); /* SignalSema */
extern void * func_00318E80(s32, s32, s32, s32, void *);

void func_00318D28(void *input) {
    s32 temp_16;
    s32 temp_16_2;
    s32 var_20;
    RwaRequestLink *temp_17;
    void *temp_3;

    temp_17 = input + 4;
    temp_16 = D_0040E214;
    var_20 = 0;
    if (temp_16 == 2) {
        func_003678A0(D_00458490);
        if (D_0040E214 == temp_16) {
            func_003678A0(D_004584C4);
        }
    }
    if (func_0031D2A8(&D_004584C0) == 0) {
        if (M2C_FIELD(&D_004584C0, s32 *, 0x10) == temp_17) {
            temp_17->remaining = 0;
            temp_17->state = 3;
            var_20 = 1;
        }
        if (M2C_FIELD(&D_00456480, s32 *, 0x2000) == temp_17) {
            M2C_FIELD(&D_00456480, s32 *, 0x2004) = 0;
            M2C_FIELD(&D_00456480, s32 *, 0x2000) = 0;
        }
    } else if (D_0040E214 == 2) {
        func_00367880(M2C_FIELD(&D_004584C0, s32 *, 0));
    }
    temp_3 = M2C_FIELD(input, void **, 4);
    if (temp_3 != NULL) {
        *M2C_FIELD(temp_17, void ***, 4) = temp_3;
        M2C_FIELD(M2C_FIELD(input, void **, 4), void ***, 4) = (void **) M2C_FIELD(temp_17, void ***, 4);
        temp_17->state = 1;
        M2C_FIELD(input, void **, 4) = NULL;
    }
    temp_16_2 = D_0040E214;
    if (temp_16_2 == 2) {
        func_00367880(D_004584C4);
        if (D_0040E214 == temp_16_2) {
            func_00367880(D_00458490);
        }
    }
    if (var_20 != 0) {
        func_00318E80(temp_17->handle, 0, 2, 1, input);
    }
}

#endif

#ifdef NONMATCHING_RWA_318E80
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/request.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 D_0040E214;
extern void func_003678A0(); /* WaitSema */
extern s32 D_00458490;
extern s32 D_00456480;
extern s32 * func_0035C544(s32 *, s32, s32);
extern void * func_00324BA0(s32, s32 *, s32, s32, s32, void *);
extern void * func_00324CB0(s32, s32, s32, void *);
extern s32 D_004584C4;
extern void ** D_004584C8;
extern void func_00367880(); /* SignalSema */
extern s32 D_004584C0;

void func_00318E80(s32 input, s32 operation, s32 length, s32 event, void *context) {
    s32 sp0;
    s32 *temp_4;
    s32 *temp_5_2;
    s32 temp_2;
    s32 temp_4_2;
    s32 temp_6_2;
    s32 var_30;
    s32 var_5;
    s32 var_8;
    u32 temp_16;
    u32 temp_16_2;
    u32 temp_3;
    u32 temp_3_2;
    u32 temp_6;
    u32 var_18;
    RwaRequestLink *var_17;
    void *temp_5;
    void *var_20;

    var_20 = context;
    var_17 = (void *)((u8 *)var_20 + 4);
    var_30 = length;
    sp0 = input;
    switch (event) {                                 /* irregular */
    case 2:
        var_17->result = operation;
        /* fallthrough */
    default:
        if (var_17->state != 5) {
            M2C_FIELD(var_17, M2C_UNK (**)(s32, s32, s32, s32), 0x38)(sp0, operation, event, var_17->user);
            return;
        }
        var_17->state = 3;
    case 5:
    case 1:
        if (D_0040E214 == 2) {
            func_003678A0(D_00458490, operation);
        }
loop_15:
        if (var_17->state == 4) {
            var_17->state = 3;
            if ((var_30 != 4) && (operation == var_17->block_size)) {
                if (var_17->buffer != &D_00456480) {
                    var_17->destination = (s32 *) (var_17->destination + operation);
                    var_17->position = (u32) (var_17->position + operation);
                    var_17->remaining = (u32) (var_17->remaining - operation);
                } else {
                    M2C_FIELD(&D_00456480, s32 *, 0x200C) = operation;
                    M2C_FIELD(&D_00456480, void ***, 0x2000) = var_17;
                    M2C_FIELD(&D_00456480, s32 *, 0x2004) = sp0;
                    M2C_FIELD(&D_00456480, s32 *, 0x2008) = (s32) var_17->block_position;
                }
                goto block_24;
            }
            goto block_36;
        }
block_24:
        var_18 = var_17->position;
        var_8 = (var_18 >> 0xD) << 0xD;
        if ((M2C_FIELD(&D_00456480, void ***, 0x2000) == var_17) && (M2C_FIELD(&D_00456480, s32 *, 0x2008) == var_8)) {
            temp_2 = var_18 - var_8;
            temp_16 = var_17->remaining;
            temp_5 = temp_2 + ((s32) &D_00456480);
            temp_3 = M2C_FIELD(&D_00456480, s32 *, 0x200C) - temp_2;
            var_30 = 2;
            temp_16_2 = (temp_3 < temp_16) ? temp_3 : temp_16;
            temp_6 = temp_16_2;
            var_18 += temp_16_2;
            func_0035C544(var_17->destination, (s32) temp_5, (s32) temp_6);
            var_8 = (var_18 >> 0xD) << 0xD;
            var_17->destination = (s32 *) (var_17->destination + temp_16_2);
            var_17->remaining = (u32) (var_17->remaining - temp_16_2);
            var_17->position = (u32) (var_17->position + temp_16_2);
        }
        temp_3_2 = var_17->remaining;
        if (temp_3_2 != 0) {
            temp_4 = var_17->destination;
            if (!((s32) temp_4 & 0x3F) && (var_18 == var_8) && (temp_3_2 >= 0x800U)) {
                var_17->buffer = temp_4;
                var_5 = (temp_3_2 >> 0xB) << 0xB;
                if (var_17 == M2C_FIELD(&D_00456480, void ***, 0x2000)) {
                    M2C_FIELD(&D_00456480, s32 *, 0x2004) = 0;
                    M2C_FIELD(&D_00456480, void ***, 0x2000) = NULL;
                }
            } else {
                M2C_FIELD(&D_00456480, void ***, 0x2000) = NULL;
                M2C_FIELD(&D_00456480, s32 *, 0x2004) = 0;
                M2C_FIELD(&D_00456480, s32 *, 0x2008) = -1;
                var_5 = 0x2000;
                var_17->buffer = &D_00456480;
            }
            if (M2C_FIELD(var_20, s32 *, 0x60) == var_8) {
                var_17->block_size = var_5;
                var_17->block_position = var_8;
                var_17->state = 4;
                M2C_FIELD(var_20, s32 *, 0x60) = (s32) (M2C_FIELD(var_20, s32 *, 0x60) + var_5);
                temp_6_2 = var_17->block_size;
                temp_4_2 = var_17->handle;
                temp_5_2 = var_17->buffer;
                var_17 = NULL;
                func_00324BA0(temp_4_2, temp_5_2, temp_6_2, 0, (s32) func_00318E80, var_20);
                goto block_48;
            }
            var_17->state = 5;
            M2C_FIELD(var_20, s32 *, 0x60) = var_8;
            func_00324CB0(M2C_FIELD(var_20, s32 *, 0x5C), var_8, (s32) func_00318E80, var_20);
        } else {
block_36:
            var_17->state = 1;
            M2C_FIELD(var_17, M2C_UNK (**)(s32, s32, s32, s32, s32), 0x38)(var_17->handle, var_17->length, var_30, event, var_17->user);
            var_17 = NULL;
            if (D_0040E214 == 2) {
                func_003678A0(D_004584C4);
            }
            if (D_004584C8 != &D_004584C8) {
                var_17 = D_004584C8;
                if (M2C_FIELD(&D_00456480, void ***, 0x2000) != NULL) {
                    var_17 = M2C_FIELD(&D_00456480, void ***, 0x2000);
                    if (*M2C_FIELD(&D_00456480, void ***, 0x2000) == NULL) {
                        var_17 = D_004584C8;
                    }
                }
                *M2C_FIELD(var_17, void ***, 4) = M2C_FIELD(var_17, void **, 0);
                M2C_FIELD(M2C_FIELD(var_17, void **, 0), void ***, 4) = (void **) M2C_FIELD(var_17, void ***, 4);
                M2C_FIELD(var_17, void **, 0) = NULL;
                var_17->state = 3;
                var_20 = var_17->owner;
                goto block_45;
            }
            if (D_0040E214 == 2) {
                func_00367880(M2C_FIELD(D_004584C8, s32 *, -8));
block_45:
                if (D_0040E214 == 2) {
                    func_00367880(D_004584C4);
                }
            }
            M2C_FIELD(&D_004584C0, void ***, 0x10) = var_17;
block_48:
            if (var_17 != NULL) {
                goto loop_15;
            }
        }
        if (D_0040E214 == 2) {
            func_00367880(D_00458490);
        }
        return;
    }
}

#endif

#ifdef NONMATCHING_RWA_3196D8
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/request.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern void * func_00319828(void *, s32, s32, s32, void *);
extern void * func_00319628(s32, s32, s32, s32, void *);
extern s32 func_0032A938(void *);
extern void * func_00324CB0(s32, s32, s32, void *);
extern void * func_00318E80(s32, s32, s32, s32, void *);

void * func_003196D8(s32 input, s32 operation, s32 length, s32 event, RwaAsyncFile *context) {
    M2C_UNK var_5;
    s32 temp_2;
    s32 var_6;
    void *temp_3;
    void *var_4;

    var_6 = length;
    if (var_6 == 4) {
        context->pending = 0;
        M2C_FIELD(context->header, s32 *, 0) = 0;
        M2C_FIELD(context->header, s32 *, 4) = 0;
        M2C_FIELD(context->header, s32 *, 8) = 0;
        var_5 = 0;
        var_6 = 4;
        var_4 = M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC);
        goto block_10;
    }
    if (context->read_header != 0) {
        context->read_header = 0;
        return func_00319828(context, (s32) context->header, 0xC, (s32) func_00319628, context);
    }
    if (M2C_FIELD(context->header, s32 *, 0) == context->target) {
        context->pending = 0;
        var_5 = 0xC;
        var_4 = M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC);
        goto block_11;
    }
    context->read_header = 1;
    temp_2 = func_0032A938(M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC));
    if (temp_2 >= 0) {
        temp_3 = context->header;
        context->position = (s32) (temp_2 + M2C_FIELD(temp_3, s32 *, 4));
        return func_00324CB0(context->handle, temp_2 + M2C_FIELD(temp_3, s32 *, 4), (s32) func_00318E80, context);
    }
    M2C_FIELD(context->header, s32 *, 0) = 0;
    M2C_FIELD(context->header, s32 *, 4) = 0;
    M2C_FIELD(context->header, s32 *, 8) = 0;
    var_5 = 0;
    var_6 = 4;
    var_4 = M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC);
block_10:
block_11:
    return M2C_FIELD(context, void *(**)(void *, M2C_UNK, s32, s32, s32), 0x48)(var_4, var_5, var_6, event, M2C_FIELD(context, s32 *, 0x4C));
}

#endif

#ifdef NONMATCHING_RWA_319B00
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
#include "rwa_ee/request.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 * func_0031DE30(s32 *, s32, s32);
extern s32 D_004096D0;
extern s32 func_003186B0(s32);
extern M2C_UNK D_003C3228;
extern void * func_00319ED0(void *, s32, void *);
extern s32 func_00319F80(void *);
extern void * func_00319FD0(void *);
extern s32 func_0031A058(s32, s32 *);

s32 func_00319B00(RwaCallbackObject *input) {
    s32 var_2;
    s32 var_2_2;
    s32 var_2_3;

    func_0031DE30(input, (s32) &D_004096D0, 0);
    input->flags = 0x64;
    if ((1 << func_003186B0(0x28)) & 0xFFFF) {
        func_003186B0(0x28);
    }
    if (((1 << func_003186B0(0x28)) & 0xFFFF) && ((1 << func_003186B0(0x28)) & 0xFF00)) {
        if (!((1 << func_003186B0(0x28)) & 0xFFFF)) {
            var_2 = 0;
        } else {
            var_2 = (s32) ((1 << func_003186B0(0x28)) & 0xFFFF) >> 8;
        }
        var_2_2 = M2C_FIELD((((s32) &D_003C3228) + var_2), s8 *, 0) + 7;
    } else {
        if (!((1 << func_003186B0(0x28)) & 0xFFFF)) {
            var_2_3 = 1;
        } else {
            var_2_3 = (1 << func_003186B0(0x28)) & 0xFFFF;
        }
        var_2_2 = M2C_FIELD((((s32) &D_003C3228) + var_2_3), s8 *, 0) - 1;
    }
    input->flags = (s32) (0x64 | (var_2_2 << 0x1C));
    M2C_FIELD(input, void *(**)(void *, s32, void *), 0x28) = func_00319ED0;
    M2C_FIELD(input, s32 (**)(void *), 0x34) = func_00319F80;
    M2C_FIELD(input, void *(**)(void *), 0x2C) = func_00319FD0;
    M2C_FIELD(input, s32 (**)(s32, s32 *), 0x3C) = func_0031A058;
    input->kind = 4;
    return 4;
}

#endif

#ifdef RWA_MATCH_317838
#include "auto/prelude.h"
extern M2C_UNK *D_0040E79C,*D_0040E798;
extern s32 D_0040E1CC;
extern s32 *func_0031AA20(void);
s32 func_00317838(void) {
    D_0040E79C=(D_0040E798=&D_0040E798);
    D_0040E1CC=1;
    func_0031AA20();
    return 1;
}

#endif

#ifdef RWA_MATCH_319CA8
#include "auto/prelude.h"
extern s32 D_0040E1F0;
extern s32 func_00322A78(void);
extern s32 func_0031D7A8(void *);
extern u8 D_00458550[];
s32 func_00319CA8(void) {
    if(D_0040E1F0){
        if(func_00322A78())D_0040E1F0=0;
        else return 0;
    }
    return func_0031D7A8(D_00458550);
}

#endif
