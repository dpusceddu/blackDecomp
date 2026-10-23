#include "animation/graph.h"
#include "animation/parameter_bank.h"

/* Names are inferred from the fixed-capacity parameter bank operations. */
AnimationParameterBank *AnimationParameterBank_Initialize(AnimationParameterBank *bank)
    ANIMATION_FUNCTION(00350060);
AnimationParameterBank *AnimationParameterBank_Initialize(AnimationParameterBank *bank) {
    bank->count = 0;
    AnimationParameterMemory_Set(bank, 0, 0x118);
    return bank;
}

void AnimationParameterBank_Clear(AnimationParameterBank *bank) ANIMATION_FUNCTION(00350098);
void AnimationParameterBank_Clear(AnimationParameterBank *bank) {
    bank->count = 0;
}

unsigned int AnimationParameterBank_Count(AnimationParameterBank *bank) ANIMATION_FUNCTION(003500A0);
unsigned int AnimationParameterBank_Count(AnimationParameterBank *bank) {
    return bank->count;
}

void AnimationParameterBank_Copy(AnimationParameterBank *bank, const AnimationParameterBank *source)
    ANIMATION_FUNCTION(003500A8);
void AnimationParameterBank_Copy(AnimationParameterBank *bank, const AnimationParameterBank *source) {
    if (bank != source) {
        bank->count = source->count;
        AnimationParameterMemory_Copy(bank, source, source->count * 4);
    }
}

float *AnimationParameterBank_At(AnimationParameterBank *bank, unsigned int index)
    ANIMATION_FUNCTION(00350130);
float *AnimationParameterBank_At(AnimationParameterBank *bank, unsigned int index) {
    return (float *)(bank->slots + index);
}

#ifdef NONMATCHING
// Unmatched: assembler inserts two branch hazard NOPs inside the loop; PS2 has one.
float *AnimationParameterBank_GrowAt(AnimationParameterBank *bank, unsigned int index)
    __asm__("func_003500E0");
float *AnimationParameterBank_GrowAt(AnimationParameterBank *bank, unsigned int index) {
    unsigned int required = index + 1;
    for (unsigned int i = bank->count; i < required; ++i)
        bank->slots[i] = 0;
    if (bank->count < required)
        bank->count = required;
    return (float *)(bank->slots + index);
}
#endif
