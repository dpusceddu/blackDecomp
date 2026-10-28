#include "include_asm.h"
#include "ps2/prelude.h"

/* Offsets in serialized objects become addresses relative to the object base. */
typedef struct Recovered_RelocatableObject {
    u8 unk_00[0x30];
    u32 unk_30;
    u32 unk_34;
    u8 unk_38[0x18];
    u32 unk_50;
    u32 unk_54;
    u8 unk_58[0x38];
    u32 unk_90;
    u32 unk_94;
} Recovered_RelocatableObject;

extern void reloc_base_58(void *) __asm__("func_00287658");
extern void reloc_base_18(void *) __asm__("func_00287618");
extern void reloc_base_38(void *) __asm__("func_00287638");

extern s32 func_00287600();
extern void func_00287698();

typedef struct Recovered_RelocationTable {
    s32 recordCount;
    u32 records;
    u32 unk_08;
    u32 unk_0c;
    s32 pointerCount;
    u32 pointers;
    u32 unk_18;
    u32 unk_1c;
    u8 embedded[1];
} Recovered_RelocationTable;

extern void reloc_record(void *) __asm__("func_00287218");
extern void reloc_embedded(void *) __asm__("func_00287600");

void func_00287120(Recovered_RelocationTable *table) {
    s32 i;
    if (table->records) {
        table->records += (u32)table;
    }
    if (table->unk_0c) {
        table->unk_0c += (u32)table;
    }
    if (table->pointers) {
        table->pointers += (u32)table;
    }
    if (table->unk_18) {
        table->unk_18 += (u32)table;
    }
    for (i = 0; i < table->recordCount; i++) {
        reloc_record((void *)(table->records + i * 16));
    }
    reloc_embedded(table->embedded);
    for (i = 0; i < table->pointerCount; i++) {
        u32 *pointer = (u32 *)(i * 8 + table->pointers);
        if (*pointer) {
            *pointer += (u32)table;
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_287120", func_00287218);
void reloc_embedded(void* address) {
    u32* offset = (u32*)address;
    if (*offset) *offset += (u32)address;
}

void func_00287618(void) { func_00287600(); }

void func_00287638(void) {
    func_00287618();
}

void func_00287658(void) {
    func_00287618();
}

void func_00287678(void) {
    func_00287658();
}

void func_00287698(Recovered_RelocatableObject *object) {
    reloc_base_58(object);
    if (object->unk_30 != 0) {
        object->unk_30 += (u32)object;
    }
    if (object->unk_34 != 0) {
        object->unk_34 += (u32)object;
    }
}

void func_002876E0(void) {
    func_00287678();
}

void func_00287700(void) {
    func_00287678();
}

void func_00287720(void) {
    func_00287678();
}

void func_00287740(void) {
    func_00287678();
}

void func_00287760(Recovered_RelocatableObject *object) {
    func_00287698(object);
}

void func_00287780(Recovered_RelocatableObject *object) {
    func_00287698(object);
}

void func_002877A0(Recovered_RelocatableObject *object) {
    func_00287698(object);
}

void func_002877C0(Recovered_RelocatableObject *object) {
    func_00287698(object);
}

void func_002877E0(Recovered_RelocatableObject *object) {
    func_00287698(object);
}

void func_00287800(Recovered_RelocatableObject *object) {
    func_00287698(object);
}

void func_00287820(Recovered_RelocatableObject* object) { func_00287698(object); }

// Partial relocation view; the pointed-to data is UNVERIFIED.
typedef struct {
    u32 offset00, unknown04, offset08;
} Recovered_RelocationPair;

void func_00287840(Recovered_RelocationPair* self) {
    reloc_embedded(self);
    if (self->offset08) self->offset08 += (u32)self;
}

void func_00287878(Recovered_RelocationPair* self) {
    reloc_embedded(self);
    if (self->offset08) self->offset08 += (u32)self;
}

void func_002878B0(Recovered_RelocationPair* self) {
    reloc_embedded(self);
    if (self->offset08) self->offset08 += (u32)self;
}

void func_002878E8(Recovered_RelocationPair* self) {
    reloc_embedded(self);
    if (self->offset08) self->offset08 += (u32)self;
}

void func_00287920(void) { func_00287600(); }

void func_00287940(Recovered_RelocationPair* self) {
    reloc_embedded(self);
    if (self->offset08) self->offset08 += (u32)self;
}

void func_00287978(Recovered_RelocationPair* self) {
    reloc_embedded(self);
    if (self->offset08) self->offset08 += (u32)self;
}
void func_002879B0(Recovered_RelocatableObject* object) {
    reloc_base_18(object);
    if (object->unk_90 != 0) { object->unk_90 += (u32)object; }
    if (object->unk_94 != 0) { object->unk_94 += (u32)object; }
}

void func_002879F8(void) { func_00287638(); }

void func_00287A18(Recovered_RelocatableObject* object) {
    reloc_base_38(object);
    if (object->unk_50 != 0) { object->unk_50 += (u32)object; }
    if (object->unk_54 != 0) {
        object->unk_54 += (u32)object;
    }
}

void func_00287A60(void) {
    func_00287618();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_287120", func_00287A80);

void func_00287A90(void) {
    func_00287600();
}

void func_00287AB0(void) {
    func_00287600();
}

void func_00287AD0(void) {
    func_00287600();
}

void func_00287AF0(void) {
    func_00287618();
}

void func_00287B10(void) {
    func_00287618();
}

void func_00287B30(void) {
    func_00287618();
}

void func_00287B50(void) {
    func_00287618();
}

void func_00287B70(void) {
    func_00287618();
}

void func_00287B90(void) {
    func_00287618();
}

void func_00287BB0(void) {
    func_00287618();
}

void func_00287BD0(void) {
    func_00287600();
}

void func_00287BF0(void) {
    func_00287600();
}

void func_00287C10(void) {
    func_00287600();
}

void func_00287C30(void) {

}

void func_00287C38(void) {

}

void func_00287C40(void) {

}

void func_00287C48(void) {
    func_00287600();
}

void func_00287C68(void) {
    func_00287600();
}

void func_00287C88(void) {
    func_00287638();
}

void func_00287CA8(void) {
    func_00287638();
}

void func_00287CC8(void) {
    func_00287638();
}

void func_00287CE8(void) {
    func_00287618();
}
