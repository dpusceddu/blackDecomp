#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00334870();
extern s32 func_00334870(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_003349B8);

// Physical ABI view: arg0 is the hidden output buffer for an allocation requirement.
void * func_003349C0(void *arg0, s32 arg1, void *unusedType, s32 unusedOffset) {
    M2C_FIELD(arg0, s32 *, 4) = 0x10;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((arg1 * 0x60) + 0x40);
    return arg0;
}

#ifdef NON_MATCHING
/* Partial view; field meanings, object type and complete extent are UNVERIFIED. */
typedef struct {
    unsigned char unknown[0x20];
    int unk_20;
    int bit_count;
    u32 count;
    int unk_2c;
    void* items;
} Recovered_PhysicsListLayout;
// Unmatched: bit-count and pointer register allocation differ.
Recovered_PhysicsListLayout* func_003349E0(Recovered_PhysicsListLayout** storage, u32 count, int value, int offset) {
    Recovered_PhysicsListLayout* layout = *storage;
    if (layout) {
        u32 n;
        int bits;
        layout->unk_20 = value;
        n = count + 1;
        layout->bit_count = 0;
        layout->count = count;
        if (n) {
            bits = 0;
            do {
                n >>= 1;
                ++bits;
            } while (n);
            layout->bit_count = bits;
        }
        layout->items = (void*)(((u32)layout + offset + 15) & ~15u);
    }
    return layout;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_003349E0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334A48);
#ifdef NON_MATCHING
/* Partial view; field meanings, object type and complete extent are UNVERIFIED. */
typedef long long PhysicsBoundsQuad;
typedef struct __attribute__((aligned(16))) {
    PhysicsBoundsQuad low, high;
} Recovered_PhysicsBounds;
typedef struct Recovered_PhysicsBoundsTable {
    int unk_00;
    short adjustment;
    short unk_06;
    void (*get)(void*, int, int, Recovered_PhysicsBounds*);
} Recovered_PhysicsBoundsTable;
typedef struct Recovered_PhysicsBoundsElement {
    char unknown[0x58];
    Recovered_PhysicsBoundsTable* table;
    int unk_5c;
} Recovered_PhysicsBoundsElement;
typedef struct Recovered_PhysicsBoundsObject {
    Recovered_PhysicsBounds bounds;
    int unk_20, bits;
    u32 count;
    int unk_2c;
    Recovered_PhysicsBoundsElement* items;
} Recovered_PhysicsBoundsObject;
extern Recovered_PhysicsBounds func_00394E20(const Recovered_PhysicsBounds*, const Recovered_PhysicsBounds*);
static inline void FetchBounds(Recovered_PhysicsBoundsElement* element, Recovered_PhysicsBounds* output) {
    Recovered_PhysicsBoundsTable* table = element->table;
    table->get((char*)element + table->adjustment, 0, 0, output);
}

// Unmatched: callback dispatch and temporary register scheduling differ.
void func_00334A50(Recovered_PhysicsBoundsObject* object) {
    u32 index;
    int offset;
    if (object->count != 0) {
        index = 0;
        offset = 0;
        do {
            Recovered_PhysicsBoundsElement* element = object->items;
            if (index == 0) {
                FetchBounds(element, &object->bounds);
            } else {
                Recovered_PhysicsBounds child;
                Recovered_PhysicsBounds merged;
                element = (Recovered_PhysicsBoundsElement*)((char*)element + offset);
                FetchBounds(element, &child);
                merged = func_00394E20(&object->bounds, &child);
                object->bounds = merged;
            }
            ++index;
            offset += 0x60;
        } while (index < object->count);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334A50);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334B48);

void func_00334B58(void) {
    func_00334870(1, 0xFFFF);
}

void func_00334B78(void) {
    func_00334870(0, 0xFFFF);
}
