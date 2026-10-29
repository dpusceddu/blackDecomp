#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern void func_00179800(void*, void*);
extern void* func_00107D20(u32);
extern u8 D_003DFFC8[];

/* Native record layout and original class identity are UNVERIFIED. */
void func_00179708(void* self, void* definition) {
    void* records;
    void* allocation;
    void* record;
    s32 count;
    s32 remainingWords;
    s32 remainingRecords;
    void* column;

    remainingWords = 1;
    column = self;
    do {
        M2C_FIELD(column, s32*, 0) = 0;
        remainingWords -= 1;
        M2C_FIELD(column, s32*, 8) = 0;
        M2C_FIELD(column, s32*, 0x10) = 0;
        M2C_FIELD(column, s32*, 0x18) = 0;
        M2C_FIELD(column, s32*, 0x20) = 0;
        column = (void*)(((s8*)column) + 4);
    } while (remainingWords >= 0);
    func_00179800(self, definition);
    count = M2C_FIELD(M2C_FIELD(self, void**, 4), s32*, 0x14);
    allocation = func_00107D20(count * 0x50);
    records = allocation;
    remainingRecords = count - 1;
    record = records;
    if (count != 0) {
        do {
            M2C_FIELD(record, void**, 0x30) = D_003DFFC8;
            remainingRecords -= 1;
            record = (void*)(((s8*)record) + 0x50);
        } while (remainingRecords != -1);
    }
    M2C_FIELD(self, void**, 0x2C) = records;
    M2C_FIELD(self, s8*, 0x35) = 0;
}
