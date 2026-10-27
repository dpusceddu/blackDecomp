#include "include_asm.h"
#include "ps2/prelude.h"

// Private allocation views; original class identities and unused spans remain UNVERIFIED.
typedef struct Recovered_PairedBank {
    void* unk_0[2];
    s8 unk_8[2];
    u8 unk_A[2];
    s8 unk_C;
} Recovered_PairedBank;

extern void* D_003DC238;
extern "C" void* func_00107D20(unsigned int);
struct Recovered_BankConstructedRecord {
    u8 unk_0[0x10];
    void* unk_10;
    u8 unk_14[0x4C];
    Recovered_BankConstructedRecord() { unk_10 = &D_003DC238; }
    static void* operator new[](unsigned int bytes) { return func_00107D20(bytes); }
};


extern "C" void func_0012FCC0(Recovered_BankConstructedRecord*);
extern "C" void func_0012FD08(Recovered_BankConstructedRecord*);
typedef char BankRecordStride[sizeof(Recovered_BankConstructedRecord) == 0x60 ? 1 : -1];
typedef char BankRecordDispatchOffset[(u32) & ((Recovered_BankConstructedRecord*)0)->unk_10 == 0x10 ? 1 : -1];

extern "C" void func_0012F060(Recovered_PairedBank* self, s8 count) {
    self->unk_C = (s8)(self->unk_C + 1) % 2;
    if (count == 0)
        self->unk_A[self->unk_C] = 0;
    else {
        s8 i;
        void** destination;
        self->unk_A[self->unk_C] = 1;
        self->unk_8[self->unk_C] = count;
        destination = &self->unk_0[self->unk_C];
        *destination = new Recovered_BankConstructedRecord[count];
        for (i = 0; i < count; i++) {
            func_0012FCC0(&((Recovered_BankConstructedRecord*)self->unk_0[self->unk_C])[i]);
            func_0012FD08(&((Recovered_BankConstructedRecord*)self->unk_0[self->unk_C])[i]);
        }
    }
}
