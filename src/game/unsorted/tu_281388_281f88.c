#include "include_asm.h"
#include "game/value_ratio.h"
#include "game/partitioned_buffer.h"

void ValueRatio_Initialize(Recovered_ValueRatioSource* self) {
    self->unk_00 = 0;
    self->unk_08 = 0;
    self->unk_0C = 0;
    self->unk_0D = 0;
}

f32 ValueRatio_Get(Recovered_ValueRatioSource* self) {
    s32 numerator = self->methods->numerator.call((u8*)self + self->methods->numerator.adjustment);
    f32 denominator = self->methods->denominator.call((u8*)self + self->methods->denominator.adjustment);
    return numerator / denominator;
}

#ifdef NON_MATCHING
// Unmatched: five argument-setup moves differ across the two nested allocation/bind calls.
void PartitionedBuffer_Initialize(Recovered_PartitionedBuffer* self, void* buffer, u32 bytes, u32 firstBytes,
                                  u32 secondBytes, u32 alignment) {
    AlignedBuffer_Initialize(&self->storage);
    AlignedBuffer_Initialize(&self->first);
    AlignedBuffer_Initialize(&self->second);
    AlignedBuffer_Bind(&self->storage, buffer, bytes);
    AlignedBuffer_SetAlignment(&self->storage, alignment);
    AlignedBuffer_Bind(&self->first, AlignedBuffer_Allocate(&self->storage, firstBytes), firstBytes);
    AlignedBuffer_SetAlignment(&self->first, alignment);
    AlignedBuffer_Bind(&self->second, AlignedBuffer_Allocate(&self->storage, secondBytes), secondBytes);
    AlignedBuffer_SetAlignment(&self->second, alignment);
    self->state = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_281f88", func_00282008);
#endif
