#include "include_asm.h"
#include "ps2/prelude.h"

/* Offsets in serialized objects become addresses relative to the object base.
 * Relocation wrappers forward the payload even when their own bodies do not
 * inspect it; the embedded-offset handler consumes it at the end of the chain. */
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

// Partial relocation view; the pointed-to data is UNVERIFIED.
typedef struct {
    u32 offset00, unknown04, offset08;
} Recovered_RelocationPair;

struct RelocatableEffect;

extern void reloc_base_58(void *) __asm__("func_00287658");
extern void reloc_base_18(void *) __asm__("func_00287618");
extern void reloc_base_38(void *) __asm__("func_00287638");

extern void func_00287600(void*);
extern void func_00287698(Recovered_RelocatableObject*);

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

extern void func_00287E68(void*);
extern void func_002876E0(void*);
extern void func_00287700(void*);
extern void func_00287720(void*);
extern void func_00287740(void*);
extern void func_00287760(Recovered_RelocatableObject *);
extern void func_00287780(Recovered_RelocatableObject *);
extern void func_002877A0(Recovered_RelocatableObject *);
extern void func_002877C0(Recovered_RelocatableObject *);
extern void func_002877E0(Recovered_RelocatableObject *);
extern void func_00287800(Recovered_RelocatableObject *);
extern void func_00287820(Recovered_RelocatableObject *);
extern void func_002879F8(void*);
extern void func_00287A18(Recovered_RelocatableObject *);
extern void func_00287A60(void*);
extern void func_00287A90(void*);
extern void func_00287AB0(void*);
extern void func_00287AD0(void*);
extern void func_00287AF0(void*);
extern void func_00287B10(void*);
extern void func_00287B30(void*);
extern void func_00287B50(void*);
extern void func_002879B0(Recovered_RelocatableObject *);
extern void func_00287BD0(void*);
extern void func_00287BF0(void*);
extern void func_00287C68(void*);
extern void func_00287C10(void*);
extern void func_00287C30(void*);
extern void func_00287C38(void*);
extern void func_00287C40(void*);
extern void func_00287C48(void*);
extern void func_00287C88(void*);
extern void func_00287CA8(void*);
extern void func_00287CC8(void*);
extern void func_00287840(Recovered_RelocationPair *);
extern void func_00287940(Recovered_RelocationPair *);
extern void func_00287978(Recovered_RelocationPair *);
extern void func_00287CE8(void*);
extern void func_00287878(Recovered_RelocationPair *);
extern void func_002878B0(Recovered_RelocationPair *);
extern void func_002878E8(Recovered_RelocationPair *);
extern void func_00287920(void*);
extern void func_00287D70(struct RelocatableEffect *);
extern void func_00287D08(struct RelocatableEffect *);
extern void func_00287DF8(struct RelocatableEffect *);
extern void func_00287E30(struct RelocatableEffect *);
extern void func_00287EC8(struct RelocatableEffect *);
extern void func_00288020(struct RelocatableEffect *);
extern void func_00288078(struct RelocatableEffect *);
extern void func_002880C0(struct RelocatableEffect *);
extern void func_00288108(struct RelocatableEffect *);
extern void func_00288150(struct RelocatableEffect *);
extern void func_00287EC0(void*);
extern void func_00287B70(void*);
extern void func_00287B90(void*);
extern void func_00287BB0(void*);
extern void func_00287E88(struct RelocatableEffect *);
extern void func_00287EA0(void*);

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
void func_00287218(void* record) {
    u32 offset;
    u32 kind;

    offset = M2C_FIELD(record, u32*, 4);
    if (offset != 0) M2C_FIELD(record, u32*, 4) = offset + (u32)record;
    kind = M2C_FIELD(record, u32*, 0);
    switch (kind) {
        case 0x41: func_00287E68(M2C_FIELD(record, void**, 4)); return;
        case 0x0: func_002876E0(M2C_FIELD(record, void**, 4)); return;
        case 0x1: func_00287700(M2C_FIELD(record, void**, 4)); return;
        case 0x2: func_00287720(M2C_FIELD(record, void**, 4)); return;
        case 0xA: func_00287740(M2C_FIELD(record, void**, 4)); return;
        case 0x3: func_00287760(M2C_FIELD(record, void**, 4)); return;
        case 0x4: func_00287780(M2C_FIELD(record, void**, 4)); return;
        case 0x5: func_002877A0(M2C_FIELD(record, void**, 4)); return;
        case 0x6: func_002877C0(M2C_FIELD(record, void**, 4)); return;
        case 0x7: func_002877E0(M2C_FIELD(record, void**, 4)); return;
        case 0x8: func_00287800(M2C_FIELD(record, void**, 4)); return;
        case 0x9: func_00287820(M2C_FIELD(record, void**, 4)); return;
        case 0xB: func_002879F8(M2C_FIELD(record, void**, 4)); return;
        case 0xC: func_00287A18(M2C_FIELD(record, void**, 4)); return;
        case 0x12: func_00287A60(M2C_FIELD(record, void**, 4)); return;
        case 0xF: func_00287A90(M2C_FIELD(record, void**, 4)); return;
        case 0x10: func_00287AB0(M2C_FIELD(record, void**, 4)); return;
        case 0x11: func_00287AD0(M2C_FIELD(record, void**, 4)); return;
        case 0x13: func_00287AF0(M2C_FIELD(record, void**, 4)); return;
        case 0x14: func_00287B10(M2C_FIELD(record, void**, 4)); return;
        case 0x34: func_00287B30(M2C_FIELD(record, void**, 4)); return;
        case 0x15: func_00287B50(M2C_FIELD(record, void**, 4)); return;
        case 0x1E: func_002879B0(M2C_FIELD(record, void**, 4)); return;
        case 0x19: func_00287BD0(M2C_FIELD(record, void**, 4)); return;
        case 0x1A: func_00287BF0(M2C_FIELD(record, void**, 4)); return;
        case 0x36: func_00287C68(M2C_FIELD(record, void**, 4)); return;
        case 0x2D: func_00287C10(M2C_FIELD(record, void**, 4)); return;
        case 0x2E: func_00287C30(M2C_FIELD(record, void**, 4)); return;
        case 0x33: func_00287C38(M2C_FIELD(record, void**, 4)); return;
        case 0x2B: func_00287C40(M2C_FIELD(record, void**, 4)); return;
        case 0x2C:
        case 0x2F: func_00287C48(M2C_FIELD(record, void**, 4)); return;
        case 0x32: func_00287C88(M2C_FIELD(record, void**, 4)); return;
        case 0x30: func_00287CA8(M2C_FIELD(record, void**, 4)); return;
        case 0x31: func_00287CC8(M2C_FIELD(record, void**, 4)); return;
        case 0x1B:
            func_00287840(M2C_FIELD(record, void**, 4));
            return;
        case 0x25:
            func_00287940(M2C_FIELD(record, void**, 4));
            return;
        case 0x26:
            func_00287978(M2C_FIELD(record, void**, 4));
            return;
        case 0x23: func_00287CE8(M2C_FIELD(record, void**, 4)); return;
        case 0x27:
            func_00287878(M2C_FIELD(record, void**, 4));
            return;
        case 0x28:
            func_002878B0(M2C_FIELD(record, void**, 4));
            return;
        case 0x29:
            func_002878E8(M2C_FIELD(record, void**, 4));
            return;
        case 0x2A: func_00287920(M2C_FIELD(record, void**, 4)); return;
        case 0x37:
            func_00287D70(M2C_FIELD(record, void**, 4));
            return;
        case 0x38:
            func_00287D08(M2C_FIELD(record, void**, 4));
            return;
        case 0x39:
            func_00287DF8(M2C_FIELD(record, void**, 4));
            return;
        case 0x3A:
            func_00287E30(M2C_FIELD(record, void**, 4));
            return;
        case 0x3B:
            func_00287EC8(M2C_FIELD(record, void**, 4));
            return;
        case 0x3C:
            func_00288020(M2C_FIELD(record, void**, 4));
            return;
        case 0x3D:
            func_00288078(M2C_FIELD(record, void**, 4));
            return;
        case 0x3E:
            func_002880C0(M2C_FIELD(record, void**, 4));
            return;
        case 0x3F:
            func_00288108(M2C_FIELD(record, void**, 4));
            return;
        case 0x40:
            func_00288150(M2C_FIELD(record, void**, 4));
            return;
        case 0x44: func_00287EC0(M2C_FIELD(record, void**, 4)); return;
        case 0x16: func_00287B70(M2C_FIELD(record, void**, 4)); return;
        case 0x17: func_00287B90(M2C_FIELD(record, void**, 4)); return;
        case 0x18: func_00287BB0(M2C_FIELD(record, void**, 4)); return;
        case 0x35:
            func_00287E88(M2C_FIELD(record, void**, 4));
            return;
        case 0x43:
            func_00287EA0(M2C_FIELD(record, void**, 4));
            /* fallthrough */
        default: return;
    }
}

void reloc_embedded(void* address) {
    u32* offset = (u32*)address;
    if (*offset) *offset += (u32)address;
}

void func_00287618(void* payload) { func_00287600(payload); }

void func_00287638(void* payload) {
    func_00287618(payload);
}

void func_00287658(void* payload) {
    func_00287618(payload);
}

void func_00287678(void* payload) {
    func_00287658(payload);
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

void func_002876E0(void* payload) {
    func_00287678(payload);
}

void func_00287700(void* payload) {
    func_00287678(payload);
}

void func_00287720(void* payload) {
    func_00287678(payload);
}

void func_00287740(void* payload) {
    func_00287678(payload);
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

void func_00287920(void* payload) { func_00287600(payload); }

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

void func_002879F8(void* payload) { func_00287638(payload); }

void func_00287A18(Recovered_RelocatableObject* object) {
    reloc_base_38(object);
    if (object->unk_50 != 0) { object->unk_50 += (u32)object; }
    if (object->unk_54 != 0) {
        object->unk_54 += (u32)object;
    }
}

void func_00287A60(void* payload) {
    func_00287618(payload);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_287120", func_00287A80);

void func_00287A90(void* payload) {
    func_00287600(payload);
}

void func_00287AB0(void* payload) {
    func_00287600(payload);
}

void func_00287AD0(void* payload) {
    func_00287600(payload);
}

void func_00287AF0(void* payload) {
    func_00287618(payload);
}

void func_00287B10(void* payload) {
    func_00287618(payload);
}

void func_00287B30(void* payload) {
    func_00287618(payload);
}

void func_00287B50(void* payload) {
    func_00287618(payload);
}

void func_00287B70(void* payload) {
    func_00287618(payload);
}

void func_00287B90(void* payload) {
    func_00287618(payload);
}

void func_00287BB0(void* payload) {
    func_00287618(payload);
}

void func_00287BD0(void* payload) {
    func_00287600(payload);
}

void func_00287BF0(void* payload) {
    func_00287600(payload);
}

void func_00287C10(void* payload) {
    func_00287600(payload);
}

void func_00287C30(void* payload) {

}

void func_00287C38(void* payload) {

}

void func_00287C40(void* payload) {

}

void func_00287C48(void* payload) {
    func_00287600(payload);
}

void func_00287C68(void* payload) {
    func_00287600(payload);
}

void func_00287C88(void* payload) {
    func_00287638(payload);
}

void func_00287CA8(void* payload) {
    func_00287638(payload);
}

void func_00287CC8(void* payload) {
    func_00287638(payload);
}

void func_00287CE8(void* payload) {
    func_00287618(payload);
}
