#include "include_asm.h"
#include "ps2/prelude.h"
extern void func_00283C10(void*, f32);
extern void func_00283C18(void*, f32);
extern s32 func_00281238(void*, void*, void*);
extern void func_00283B10(void*, void*);
extern u8 D_00443180[];
extern void func_00283AC8(void*, s128);
extern void func_00283B80(void*, f32);
extern void func_00283B90(void*, f32);
extern void func_00283648(void*, f32, f32, f32, f32, f32, f32, u8);
extern void func_00283B60(void*, f32);
extern void func_00283B38(void*, f32);
extern void func_00283BC0(void*, s32);
extern void func_00283BA0(void*, s32);
extern void func_00281200(void*, f32);
extern s32 D_003C0E08;
// Partial native provider operations; original class identities and names are UNVERIFIED.
static inline void SetProviderPosition(void* self, s128 value) {
    void* table = M2C_FIELD(self, void**, 0);
    M2C_FIELD(table, void (**)(void*, s128), 0x34)((u8*)self + M2C_FIELD(table, s16*, 0x30), value);
}
static inline s32 NextProviderId(void) {
    s32 id = D_003C0E08++;
    return id;
}
static inline u64 ProviderFlag(u64 value, u32 bit) { return (value >> bit) & 1; }
static inline void SetProviderDirection(void* self, s128 value) {
    void* table = M2C_FIELD(self, void**, 0);
    M2C_FIELD(table, void (**)(void*, s128), 0x4C)((u8*)self + M2C_FIELD(table, s16*, 0x48), value);
}
// Native transport is a quadword; the backend stores only the three float components.
typedef struct ProviderVector3 {
    f32 x, y, z;
} ProviderVector3;

extern s32 func_00283C38(void*, void*);
extern s32 func_00283E78(void*, void*, void*);
extern s32 func_002842E8();
extern s32 func_00328140(void *, s32);
extern void func_003281B0(void*, f32);
extern void func_00328180(void*, f32);
extern s32 func_00328108(s32, s32);
extern s32 func_00281198();
extern s32 func_00319C70(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 func_00285258(void*, void*);
extern s32 func_00284BF0(void*, void*, void*);
extern s32 func_00319E28(s32, s32);
extern f32 func_003106F0(s32, M2C_UNK, M2C_UNK);
extern void func_00319DE0(void*, s32);

typedef struct {
    u8 unk_00[0x30];
    s32 *status;
} Recovered_ProviderBackend;

typedef struct {
    u8 unk_00[0x8A];
    u8 flags;
} Recovered_ProviderVoice;

typedef struct {
    u8 unk_00[0x2C];
    u8 state;
    u8 unk_2D[3];
    u16 flags;
    u8 unk_32[2];
    Recovered_ProviderVoice *voice;
    Recovered_ProviderBackend *backend;
} Recovered_ProviderState; /* Field roles UNVERIFIED. */
extern s32 func_002851E0(Recovered_ProviderState*);

// The native spatial hook carries a kind byte and six float parameters.
// This backend ignores them; the original class and parameter names are UNVERIFIED.
void func_00283648(void* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, u8 kind) {}

void func_00283650(void* self, void* parameters) { func_00283C38(self, parameters); }

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_283648", func_00283670);

s32 func_00283858(void* arg0, void* arg1) {
    return func_00283E78(arg0, arg1, 0);
}

void func_00283878(void) {
    func_00284298();
}

void func_00283898(void *arg0) {
    func_002842E8(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_283648", func_002838B8);
void func_00283A78(void* self, s128 position) {
    ProviderVector3 output;
    f32* values = (f32*)&position;
    output.x = values[0];
    output.y = values[1];
    output.z = values[2];
    *(ProviderVector3*)((u8*)M2C_FIELD(self, void**, 0x38) + 0x68) = output;
}

void func_00283AC0(void) {

}

void func_00283AC8(void* self, s128 position) {
    ProviderVector3 output;
    f32* values = (f32*)&position;
    output.x = values[0];
    output.y = values[1];
    output.z = values[2];
    *(ProviderVector3*)((u8*)M2C_FIELD(self, void**, 0x38) + 0x74) = output;
}

void func_00283B10(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    func_00328140(M2C_FIELD(arg0, void **, 0x38), M2C_FIELD(arg1, s32 *, 0x18));
}

void func_00283B38(void *arg0, f32 value) {
    if (M2C_FIELD(arg0, u8 *, 0x35) == 0) {
        func_003281B0(M2C_FIELD(arg0, void **, 0x38), value);
    }
}

void func_00283B60(void *arg0, f32 value) {
    func_00328180(M2C_FIELD(arg0, void **, 0x38), value);
}

void func_00283B80(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), f32 *, 0xB4) = fparg0;
}

void func_00283B90(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x24) = fparg0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), f32 *, 0xB8) = fparg0;
}

void func_00283BA0(void *arg0, s32 arg1) {
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_6, u16 *, 0x5C) = (u16) (M2C_FIELD(temp_6, u16 *, 0x5C) | 0x80);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 0x30), s32 *, 0x18) = arg1;
}

void func_00283BC0(void *arg0, s32 arg1) {
    u16 temp_2;
    u16 var_2;

    func_00328108(M2C_FIELD(arg0, s32 *, 0x38), arg1 != 0);
    temp_2 = M2C_FIELD(arg0, u16 *, 0x30);
    if (arg1 != 0) {
        var_2 = temp_2 | 0x80;
    } else {
        var_2 = temp_2 & 0xFF7F;
    }
    M2C_FIELD(arg0, u16 *, 0x30) = var_2;
}

void func_00283C10(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
}

void func_00283C18(void *arg0, f32 value) {
    func_00328180(M2C_FIELD(arg0, void **, 0x38), value);
}

s32 func_00283C38(void* arg0, void* arg1) {
    s32 temp_3_2;
    void* temp_2;
    void* temp_2_3;
    void* temp_3;
    void* temp_5;

    if (func_002842E8((Recovered_ProviderState*)arg0) != 0) {
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 3) & 1) {
            M2C_FIELD(arg0, f32*, 0x10) = (f32)M2C_FIELD(arg1, f32*, 0x54);
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 5) & 1) {
            M2C_FIELD(arg0, f32*, 0x14) = (f32)M2C_FIELD(arg1, f32*, 0x5C);
        }
        temp_5 = M2C_FIELD(arg0, void**, 4);
        temp_3 = M2C_FIELD(temp_5, void**, 0x10);
        if (M2C_FIELD(temp_3, s32(**)(void*), 0xC)((void*)(((s8*)temp_5) + M2C_FIELD(temp_3, s16*, 8))) != 0) {
            if ((u8)M2C_FIELD(arg1, s32*, 0xA4) & 1) { SetProviderPosition(arg0, M2C_FIELD(arg1, s128*, 0x30)); }
            if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 1) & 1) { func_00283AC8(arg0, M2C_FIELD(arg1, s128*, 0x40)); }
            if (M2C_FIELD(arg1, u8*, 0xA5) & 1) { func_00283B80(arg0, M2C_FIELD(arg1, f32*, 0x74)); }
            if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 9) & 1) { func_00283B90(arg0, M2C_FIELD(arg1, f32*, 0x70)); }
            if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                temp_2_3 = (void*)(((s8*)arg1) + 0x88);
                func_00283648(arg0, M2C_FIELD(arg1, f32*, 0x88), M2C_FIELD(temp_2_3, f32*, 8),
                              M2C_FIELD(temp_2_3, f32*, 4), M2C_FIELD(temp_2_3, f32*, 12),
                              M2C_FIELD(temp_2_3, f32*, 16), M2C_FIELD(temp_2_3, f32*, 20), M2C_FIELD(arg1, u8*, 0xAB));
            }
        } else {
            if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA5), 7) != 0) { func_00283C10(arg0, M2C_FIELD(arg1, f32*, 0x7C)); }
            temp_3_2 = M2C_FIELD(arg1, s32*, 0xA4);
            if ((temp_3_2 >> 0x10) & 1) {
                func_00283C18(arg0, M2C_FIELD(arg1, f32*, 0x78));
            } else if ((temp_3_2 >> 6) & 1) {
                func_00283B60(arg0, M2C_FIELD(arg1, f32*, 0x60));
            }
            if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                temp_2 = (void*)(((s8*)arg1) + 0x88);
                func_00283648(arg0, M2C_FIELD(arg1, f32*, 0x88), M2C_FIELD(temp_2, f32*, 8), M2C_FIELD(temp_2, f32*, 4),
                              M2C_FIELD(temp_2, f32*, 12), M2C_FIELD(temp_2, f32*, 16), M2C_FIELD(temp_2, f32*, 20),
                              M2C_FIELD(arg1, u8*, 0xAB));
            }
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 4) & 1) { func_00283B38(arg0, M2C_FIELD(arg1, f32*, 0x58)); }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xE) & 1) {
            M2C_FIELD(arg0, f32*, 0x18) = (f32)M2C_FIELD(arg1, f32*, 0x64);
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xD) & 1) { func_00281200(arg0, M2C_FIELD(arg1, f32*, 0x6C)); }
    }
    return 1;
}
s32 func_00283E78(void* arg0, void* arg1, void* arg2) {
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    s32 temp_2_2;
    s32 temp_4;
    u16 var_2_2;
    u16 var_2_3;
    u8 var_2;
    void* temp_2;
    void* temp_2_3;
    void* temp_3;
    void* temp_5;
    void* temp_5_2;

    if (!func_00281238(arg0, arg1, arg2)) return 0;
    {
        void* defaults = D_00443180;
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 2) & 1) {
            func_00283B10(arg0, M2C_FIELD(arg1, void**, 0x50));
        } else {
            func_00283B10(arg0, M2C_FIELD(defaults, void**, 0x50));
        }
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 3) & 1)) {
            var_f0 = M2C_FIELD(arg1, f32*, 0x54);
        } else {
            var_f0 = M2C_FIELD(defaults, f32*, 0x54);
        }
        M2C_FIELD(arg0, f32*, 0x10) = var_f0;
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 5) & 1)) {
            var_f0_2 = M2C_FIELD(arg1, f32*, 0x5C);
        } else {
            temp_5 = M2C_FIELD(arg0, void**, 4);
            temp_2 = M2C_FIELD(temp_5, void**, 0x10);
            var_f0_2 = M2C_FIELD(temp_2, f32(**)(void*), 0x2C)((void*)(((s8*)temp_5) + M2C_FIELD(temp_2, s16*, 0x28)));
        }
        M2C_FIELD(arg0, f32*, 0x14) = var_f0_2;
        temp_5_2 = M2C_FIELD(arg0, void**, 4);
        temp_3 = M2C_FIELD(temp_5_2, void**, 0x10);
        temp_2_2 = M2C_FIELD(temp_3, s32(**)(void*), 0xC)((void*)(((s8*)temp_5_2) + M2C_FIELD(temp_3, s16*, 8)));
        if (temp_2_2 != 0) {
            if ((u8)M2C_FIELD(arg1, s32*, 0xA4) & 1) {
                SetProviderPosition(arg0, M2C_FIELD(arg1, s128*, 0x30));
            } else {
                SetProviderPosition(arg0, M2C_FIELD(defaults, s128*, 0x30));
            }
            if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 1) & 1)) {
                func_00283AC8(arg0, M2C_FIELD(arg1, s128*, 0x40));
            } else {
                func_00283AC8(arg0, M2C_FIELD(defaults, s128*, 0x40));
            }
            if ((M2C_FIELD(arg1, u8*, 0xA5) & 1)) {
                func_00283B80(arg0, M2C_FIELD(arg1, f32*, 0x74));
            } else {
                func_00283B80(arg0, M2C_FIELD(defaults, f32*, 0x74));
            }
            if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 9) & 1)) {
                func_00283B90(arg0, M2C_FIELD(arg1, f32*, 0x70));
            } else {
                func_00283B90(arg0, M2C_FIELD(defaults, f32*, 0x70));
            }
            {
                void* selected;
                u8 kind;
                if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                    selected = (u8*)arg1 + 0x88;
                    kind = M2C_FIELD(arg1, u8*, 0xAB);
                } else {
                    selected = (u8*)defaults + 0x88;
                    kind = M2C_FIELD(defaults, u8*, 0xAB);
                }
                func_00283648(arg0, M2C_FIELD(selected, f32*, 0), M2C_FIELD(selected, f32*, 8),
                              M2C_FIELD(selected, f32*, 4), M2C_FIELD(selected, f32*, 12),
                              M2C_FIELD(selected, f32*, 16), M2C_FIELD(selected, f32*, 20), kind);
            }
        } else {
            if (((M2C_FIELD(arg1, s32*, 0xA4) >> 6) & 1)) {
                func_00283B60(arg0, M2C_FIELD(arg1, f32*, 0x60));
            } else {
                func_00283B60(arg0, M2C_FIELD(defaults, f32*, 0x60));
            }
            {
                void* selected;
                u8 kind;
                if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                    selected = (u8*)arg1 + 0x88;
                    kind = M2C_FIELD(arg1, u8*, 0xAB);
                } else {
                    selected = (u8*)defaults + 0x88;
                    kind = M2C_FIELD(defaults, u8*, 0xAB);
                }
                func_00283648(arg0, M2C_FIELD(selected, f32*, 0), M2C_FIELD(selected, f32*, 8),
                              M2C_FIELD(selected, f32*, 4), M2C_FIELD(selected, f32*, 12),
                              M2C_FIELD(selected, f32*, 16), M2C_FIELD(selected, f32*, 20), kind);
            }
        }
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 4) & 1)) {
            func_00283B38(arg0, M2C_FIELD(arg1, f32*, 0x58));
        } else {
            func_00283B38(arg0, M2C_FIELD(defaults, f32*, 0x58));
        }
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xE) & 1)) {
            var_f0_3 = M2C_FIELD(arg1, f32*, 0x64);
        } else {
            var_f0_3 = M2C_FIELD(defaults, f32*, 0x64);
        }
        M2C_FIELD(arg0, f32*, 0x18) = var_f0_3;
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xC) & 1)) {
            func_00283BC0(arg0, (s32)M2C_FIELD(arg1, u8*, 0xA9));
        } else {
            func_00283BC0(arg0, (s32)M2C_FIELD(defaults, u8*, 0xA9));
        }
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xA) & 1)) {
            func_00283BA0(arg0, M2C_FIELD(arg1, s32*, 0xA0));
        } else {
            func_00283BA0(arg0, M2C_FIELD(defaults, s32*, 0xA0));
        }
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xB) & 1)) {
            var_2 = M2C_FIELD(arg1, u8*, 0xA8);
        } else {
            var_2 = M2C_FIELD(defaults, u8*, 0xA8);
        }
        M2C_FIELD(arg0, u8*, 0x2E) = var_2;
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xD) & 1)) {
            func_00281200(arg0, M2C_FIELD(arg1, f32*, 0x6C));
        } else {
            func_00281200(arg0, M2C_FIELD(defaults, f32*, 0x6C));
        }
        if ((M2C_FIELD(arg1, s32*, 0xA4) >> 21) & 1) {
            if (M2C_FIELD(arg1, u8*, 0xAD))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x10;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x10;
        } else {
            if (M2C_FIELD(defaults, u8*, 0xAD))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x10;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x10;
        }
        if ((M2C_FIELD(arg1, s32*, 0xA4) >> 22) & 1) {
            if (M2C_FIELD(arg1, u8*, 0xAC))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x20;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x20;
        } else {
            if (M2C_FIELD(defaults, u8*, 0xAC))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x20;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x20;
        }
        M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x100);
        M2C_FIELD(arg0, s32*, 8) = NextProviderId();
        *M2C_FIELD(M2C_FIELD(arg0, void**, 0x38), s32**, 0x30) = 2;
        return 1;
    }
    return 0;
}

s32 func_00284298(void *arg0) {
    *M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 **, 0x30) = 1;
    func_00328140(M2C_FIELD(arg0, void **, 0x38), 0);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) (M2C_FIELD(arg0, u16 *, 0x30) & 1);
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: status-result normalization and register allocation differ.
s32 func_002842E8(Recovered_ProviderState *self) {
    switch (self->state) {
    case 0:
    case 1:
    case 3:
        if (self->flags & 0x80) {
            return (self->flags >> 8) & 1;
        } else {
            s32 status = *self->backend->status;
            s32 active = 0;
            if (status != 3) {
                active = status != 1;
            }
            return active;
        }
    case 2:
        return (self->flags & 8) != 0;
    default:
        return 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_283648", func_002842E8);
#endif

s32 func_00284378(void *arg0) {
    if (func_002842E8(arg0) == 0) {
        return 0;
    }
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 0x30), s32 *, 0x14);
}

void func_002843B0(void *arg0, void *arg1) {
    func_00281198();
    M2C_FIELD(arg0, s32 *, 0x34) = func_00319C70(0, 0, 0, 0, 0);
    M2C_FIELD(arg0, u8 *, 0x32) = (u8) M2C_FIELD(arg1, u8 *, 0x1C);
}

s32 func_00284408(void* self, void* parameters) {
    func_00285258(self, parameters);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_283648", func_00284428);

s32 func_00284628(void* arg0, void* arg1) { return func_00284BF0(arg0, arg1, 0); }

void func_00284648(void) {
    func_00285190();
}

void func_00284668(void *arg0) {
    func_002851E0(arg0);
}


void func_002848A0(void) {

}


void func_00284918(void) {

}


void func_00284990(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_00319E28(M2C_FIELD(arg0, s32 *, 0x34), M2C_FIELD(arg1, s32 *, 0x18));
}


void func_00284A60(void *arg0, f32 fparg0) {
    s32 temp_4;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), f32 *, 0x7C) = fparg0;
    temp_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), s32 *, 0x60);
    if (temp_4 != 0) {
        func_003106F0(temp_4, 4, 1);
    }
}

void func_00284A98(void *arg0, f32 fparg0) {
    s32 temp_4;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), f32 *, 0x80) = fparg0;
    temp_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), s32 *, 0x60);
    if (temp_4 != 0) {
        func_003106F0(temp_4, 5, 1);
    }
    M2C_FIELD(arg0, f32 *, 0x24) = fparg0;
}


/* Recovered_Vtable_003E26E8: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003E26E8 {
    u8 unk_0[4];
    u32 unk_4;
    u8 unk_8[4];
    s32 unk_C;
    u8 unk_10[20];
    f32 unk_24;
    u8 unk_28[4];
    u8 unk_2C;
    u8 unk_2D;
    u8 unk_2E[6];
    void * unk_34;
} Recovered_Vtable_003E26E8;

#include "ps2/recovered_types.h"

s32 func_00284BB0(Recovered_Vtable_003E26E8 *arg0, f32 fparg0) {
    s32 temp_f0;

    temp_f0 = (s32) (fparg0 * 255.0f);
    M2C_FIELD(arg0->unk_34, s8 *, 0x84) = (s8) temp_f0;
    return temp_f0;
}

s32 func_00284BD0(Recovered_Vtable_003E26E8 *arg0, f32 fparg0) {
    s32 temp_f0;

    temp_f0 = (s32) (fparg0 * 255.0f);
    M2C_FIELD(arg0->unk_34, s8 *, 0x87) = (s8) temp_f0;
    return temp_f0;
}

s32 func_00284BF0(void* arg0, void* arg1, void* arg2) {
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    s32 temp_2_4;
    u8 var_2;
    u8 var_5;
    u8 var_5_2;
    void* temp_2;
    void* temp_2_11;
    void* temp_2_2;
    void* temp_2_3;
    void* temp_2_9;
    void* temp_3;
    void* temp_5;
    void* temp_5_2;
    void* var_6;
    void* var_6_2;

    if (!func_00281238(arg0, arg1, arg2)) return 0;
    {
        void* defaults = D_00443180;
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 2) & 1) {
            temp_2 = M2C_FIELD(arg0, void**, 0);
            M2C_FIELD(temp_2, void (**)(void*, s32), 0x54)((void*)(((s8*)arg0) + M2C_FIELD(temp_2, s16*, 0x50)),
                                                           M2C_FIELD(arg1, s32*, 0x50));
        } else {
            temp_2_2 = M2C_FIELD(arg0, void**, 0);
            M2C_FIELD(temp_2_2, void (**)(void*, s32), 0x54)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_2, s16*, 0x50)),
                                                             M2C_FIELD(defaults, s32*, 0x50));
        }
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 3) & 1)) {
            var_f0 = M2C_FIELD(arg1, f32*, 0x54);
        } else {
            var_f0 = M2C_FIELD(defaults, f32*, 0x54);
        }
        M2C_FIELD(arg0, f32*, 0x10) = var_f0;
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 5) & 1)) {
            var_f0_2 = M2C_FIELD(arg1, f32*, 0x5C);
        } else {
            temp_5 = M2C_FIELD(arg0, void**, 4);
            temp_2_3 = M2C_FIELD(temp_5, void**, 0x10);
            var_f0_2 =
                M2C_FIELD(temp_2_3, f32(**)(void*), 0x2C)((void*)(((s8*)temp_5) + M2C_FIELD(temp_2_3, s16*, 0x28)));
        }
        M2C_FIELD(arg0, f32*, 0x14) = var_f0_2;
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xE) & 1)) {
            var_f0_3 = M2C_FIELD(arg1, f32*, 0x64);
        } else {
            var_f0_3 = M2C_FIELD(defaults, f32*, 0x64);
        }
        M2C_FIELD(arg0, f32*, 0x18) = var_f0_3;
        temp_5_2 = M2C_FIELD(arg0, void**, 4);
        temp_3 = M2C_FIELD(temp_5_2, void**, 0x10);
        temp_2_4 = M2C_FIELD(temp_3, s32(**)(void*), 0xC)((void*)(((s8*)temp_5_2) + M2C_FIELD(temp_3, s16*, 8)));
        if (temp_2_4 != 0) {
            if ((u8)M2C_FIELD(arg1, s32*, 0xA4) & 1) {
                SetProviderPosition(arg0, M2C_FIELD(arg1, s128*, 0x30));
            } else {
                SetProviderPosition(arg0, M2C_FIELD(defaults, s128*, 0x30));
            }
            if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 1) & 1) {
                SetProviderDirection(arg0, M2C_FIELD(arg1, s128*, 0x40));
            } else {
                SetProviderDirection(arg0, M2C_FIELD(defaults, s128*, 0x40));
            }
            if (M2C_FIELD(arg1, u8*, 0xA5) & 1) {
                M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                          0x6C)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x68)),
                                M2C_FIELD(arg1, f32*, 0x74));
            } else {
                M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                          0x6C)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x68)),
                                M2C_FIELD(defaults, f32*, 0x74));
            }
            if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 9) & 1) {
                M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                          0x74)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x70)),
                                M2C_FIELD(arg1, f32*, 0x70));
            } else {
                M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                          0x74)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x70)),
                                M2C_FIELD(defaults, f32*, 0x70));
            }
            if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                var_6 = (u8*)arg1 + 0x88;
                var_5 = M2C_FIELD(arg1, u8*, 0xAB);
            } else {
                var_5 = M2C_FIELD(defaults, u8*, 0xAB);
                var_6 = (void*)(((s8*)defaults) + 0x88);
            }
            temp_2_9 = M2C_FIELD(arg0, void**, 0);
            M2C_FIELD(temp_2_9, void (**)(void*, f32, f32, f32, f32, f32, f32, u8),
                      0x44)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_9, s16*, 0x40)), M2C_FIELD(var_6, f32*, 0),
                            M2C_FIELD(var_6, f32*, 8), M2C_FIELD(var_6, f32*, 4), M2C_FIELD(var_6, f32*, 0xC),
                            M2C_FIELD(var_6, f32*, 0x10), M2C_FIELD(var_6, f32*, 0x14), var_5);
        } else {
            if ((M2C_FIELD(arg1, s32*, 0xA4) >> 6) & 1) {
                M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                          0x64)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x60)),
                                M2C_FIELD(arg1, f32*, 0x60));
            } else {
                M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                          0x64)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x60)),
                                M2C_FIELD(defaults, f32*, 0x60));
            }
            if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                var_6_2 = (u8*)arg1 + 0x88;
                var_5_2 = M2C_FIELD(arg1, u8*, 0xAB);
            } else {
                var_5_2 = M2C_FIELD(defaults, u8*, 0xAB);
                var_6_2 = (void*)(((s8*)defaults) + 0x88);
            }
            temp_2_11 = M2C_FIELD(arg0, void**, 0);
            M2C_FIELD(temp_2_11, void (**)(void*, f32, f32, f32, f32, f32, f32, u8),
                      0x44)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_11, s16*, 0x40)), M2C_FIELD(var_6_2, f32*, 0),
                            M2C_FIELD(var_6_2, f32*, 8), M2C_FIELD(var_6_2, f32*, 4), M2C_FIELD(var_6_2, f32*, 0xC),
                            M2C_FIELD(var_6_2, f32*, 0x10), M2C_FIELD(var_6_2, f32*, 0x14), var_5_2);
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 4) & 1) {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32), 0x5C)(
                (void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x58)), M2C_FIELD(arg1, f32*, 0x58));
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                      0x5C)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x58)),
                            M2C_FIELD(defaults, f32*, 0x58));
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xC) & 1) {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, u8), 0x84)(
                (void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x80)), M2C_FIELD(arg1, u8*, 0xA9));
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, u8),
                      0x84)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x80)),
                            M2C_FIELD(defaults, u8*, 0xA9));
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xA) & 1) {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, s32), 0x7C)(
                (void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x78)), M2C_FIELD(arg1, s32*, 0xA0));
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, s32),
                      0x7C)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x78)),
                            M2C_FIELD(defaults, s32*, 0xA0));
        }
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xB) & 1)) {
            var_2 = M2C_FIELD(arg1, u8*, 0xA8);
        } else {
            var_2 = M2C_FIELD(defaults, u8*, 0xA8);
        }
        M2C_FIELD(arg0, u8*, 0x2E) = var_2;
        if ((((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xD) & 1)) {
            func_00281200(arg0, M2C_FIELD(arg1, f32*, 0x6C));
        } else {
            func_00281200(arg0, M2C_FIELD(defaults, f32*, 0x6C));
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0x13) & 1) {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32), 0x8C)(
                (void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x88)), M2C_FIELD(arg1, f32*, 0x84));
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                      0x8C)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x88)),
                            M2C_FIELD(defaults, f32*, 0x84));
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0x12) & 1) {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32), 0x8C)(
                (void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x88)), M2C_FIELD(arg1, f32*, 0x80));
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void**, 0), void (**)(void*, f32),
                      0x8C)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x88)),
                            M2C_FIELD(defaults, f32*, 0x80));
        }
        if ((M2C_FIELD(arg1, s32*, 0xA4) >> 21) & 1) {
            if (M2C_FIELD(arg1, u8*, 0xAD))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x10;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x10;
        } else {
            if (M2C_FIELD(defaults, u8*, 0xAD))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x10;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x10;
        }
        if ((M2C_FIELD(arg1, s32*, 0xA4) >> 22) & 1) {
            if (M2C_FIELD(arg1, u8*, 0xAC))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x20;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x20;
        } else {
            if (M2C_FIELD(defaults, u8*, 0xAC))
                M2C_FIELD(arg0, u16*, 0x30) |= 0x20;
            else
                M2C_FIELD(arg0, u16*, 0x30) &= ~0x20;
        }
        if (ProviderFlag((u8)M2C_FIELD(arg1, s32*, 0xA4), 7) != 0) {
            M2C_FIELD(arg0, f32*, 0x28) = (f32)M2C_FIELD(arg1, f32*, 0x68);
            M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 3);
        } else {
            M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) & 0xFFFD);
            M2C_FIELD(arg0, f32*, 0x28) = (f32)M2C_FIELD(defaults, f32*, 0x68);
        }
        M2C_FIELD(arg0, u16*, 0x30) = (u16)(M2C_FIELD(arg0, u16*, 0x30) | 0x100);
        M2C_FIELD(arg0, s32*, 8) = NextProviderId();
        if (ProviderFlag((u8)M2C_FIELD(arg1, s32*, 0xA4), 7) == 0) { func_00319DE0(M2C_FIELD(arg0, void**, 0x34), 1); }
        return 1;
    }
    return 0;
}

s32 func_00285190(void *arg0) {
    func_00319DE0(M2C_FIELD(arg0, s32 *, 0x34), 0);
    func_00319E28(M2C_FIELD(arg0, s32 *, 0x34), 0);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) (M2C_FIELD(arg0, u16 *, 0x30) & 1);
    return 1;
}

s32 func_002851E0(Recovered_ProviderState *self) {
    switch (self->state) {
    case 0:
    case 1:
    case 3:
        if (self->flags & 0x80) {
            return (self->flags >> 8) & 1;
        }
        return (self->voice->flags >> 1) & 1;
    case 2:
        return (self->flags >> 3) & 1;
    default:
        return 0;
    }
}
s32 func_00285258(void* arg0, void* arg1) {
    s32 temp_2;
    void* temp_2_10;
    void* temp_2_11;
    void* temp_2_4;
    void* temp_2_5;
    void* spatialTable;
    void* temp_2_7;
    void* otherSpatialTable;
    void* temp_2_9;
    void* temp_3;
    void* temp_5;
    void* spatial;

    if (func_002851E0(arg0) != 0) {
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 3) & 1) {
            M2C_FIELD(arg0, f32*, 0x10) = (f32)M2C_FIELD(arg1, f32*, 0x54);
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 5) & 1) {
            M2C_FIELD(arg0, f32*, 0x14) = (f32)M2C_FIELD(arg1, f32*, 0x5C);
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xE) & 1) {
            M2C_FIELD(arg0, f32*, 0x18) = (f32)M2C_FIELD(arg1, f32*, 0x64);
        }
        temp_5 = M2C_FIELD(arg0, void**, 4);
        temp_3 = M2C_FIELD(temp_5, void**, 0x10);
        temp_2 = M2C_FIELD(temp_3, s32(**)(void*), 0xC)((void*)(((s8*)temp_5) + M2C_FIELD(temp_3, s16*, 8)));
        if (temp_2 != 0) {
            if ((u8)M2C_FIELD(arg1, s32*, 0xA4) & 1) { SetProviderPosition(arg0, M2C_FIELD(arg1, s128*, 0x30)); }
            if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 1) & 1) {
                SetProviderDirection(arg0, M2C_FIELD(arg1, s128*, 0x40));
            }
            if (M2C_FIELD(arg1, u8*, 0xA5) & 1) {
                temp_2_4 = M2C_FIELD(arg0, void**, 0);
                M2C_FIELD(temp_2_4, void (**)(void*, f32), 0x6C)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_4, s16*, 0x68)),
                                                                 M2C_FIELD(arg1, f32*, 0x74));
            }
            if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 9) & 1) {
                temp_2_5 = M2C_FIELD(arg0, void**, 0);
                M2C_FIELD(temp_2_5, void (**)(void*, f32), 0x74)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_5, s16*, 0x70)),
                                                                 M2C_FIELD(arg1, f32*, 0x70));
            }
            if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                spatialTable = M2C_FIELD(arg0, void**, 0);
                spatial = (void*)(((s8*)arg1) + 0x88);
                M2C_FIELD(spatialTable, void (**)(void*, f32, f32, f32, f32, f32, f32, u8),
                          0x44)((void*)(((s8*)arg0) + M2C_FIELD(M2C_FIELD(arg0, void**, 0), s16*, 0x40)),
                                M2C_FIELD(arg1, f32*, 0x88), M2C_FIELD(spatial, f32*, 8), M2C_FIELD(spatial, f32*, 4),
                                M2C_FIELD(spatial, f32*, 0xC), M2C_FIELD(spatial, f32*, 0x10),
                                M2C_FIELD(spatial, f32*, 0x14), M2C_FIELD(arg1, u8*, 0xAB));
            }
        } else {
            if ((M2C_FIELD(arg1, s32*, 0xA4) >> 6) & 1) {
                temp_2_7 = M2C_FIELD(arg0, void**, 0);
                M2C_FIELD(temp_2_7, void (**)(void*, f32), 0x64)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_7, s16*, 0x60)),
                                                                 M2C_FIELD(arg1, f32*, 0x60));
            }
            if (ProviderFlag(M2C_FIELD(arg1, u8*, 0xA6), 7) != 0) {
                otherSpatialTable = M2C_FIELD(arg0, void**, 0);
                spatial = (void*)(((s8*)arg1) + 0x88);
                M2C_FIELD(otherSpatialTable, void (**)(void*, f32, f32, f32, f32, f32, f32, u8), 0x44)(
                    (void*)(((s8*)arg0) + M2C_FIELD(otherSpatialTable, s16*, 0x40)), M2C_FIELD(arg1, f32*, 0x88),
                    M2C_FIELD(spatial, f32*, 8), M2C_FIELD(spatial, f32*, 4), M2C_FIELD(spatial, f32*, 0xC),
                    M2C_FIELD(spatial, f32*, 0x10), M2C_FIELD(spatial, f32*, 0x14), M2C_FIELD(arg1, u8*, 0xAB));
            }
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 4) & 1) {
            temp_2_9 = M2C_FIELD(arg0, void**, 0);
            M2C_FIELD(temp_2_9, void (**)(void*, f32), 0x5C)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_9, s16*, 0x58)),
                                                             M2C_FIELD(arg1, f32*, 0x58));
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0xD) & 1) { func_00281200(arg0, M2C_FIELD(arg1, f32*, 0x6C)); }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0x13) & 1) {
            temp_2_10 = M2C_FIELD(arg0, void**, 0);
            M2C_FIELD(temp_2_10, void (**)(void*, f32), 0x8C)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_10, s16*, 0x88)),
                                                              M2C_FIELD(arg1, f32*, 0x84));
        }
        if (((s32)M2C_FIELD(arg1, s32*, 0xA4) >> 0x12) & 1) {
            temp_2_11 = M2C_FIELD(arg0, void**, 0);
            M2C_FIELD(temp_2_11, void (**)(void*, f32), 0x8C)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_11, s16*, 0x88)),
                                                              M2C_FIELD(arg1, f32*, 0x80));
        }
    }
    return 1;
}

s32 func_00285510(s32 arg0) {
    s32 var_3;
    s32 var_5;
    void *var_4;

    var_4 = arg0 + 0xE00;
    var_5 = 0;
    var_3 = 0;
    do {
        if (M2C_FIELD(var_4, u8 *, 0x35) != 0) {
            var_5 |= 1 << var_3;
        }
        var_3 += 1;
        var_4 += 0x3C;
    } while (var_3 < 0x18);
    return var_5;
}
