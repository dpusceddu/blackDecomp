/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SAMPLINGPIPELINE_H
#define RECOVERED_SAMPLINGPIPELINE_H
#include "ps2/prelude.h"

typedef struct Recovered_SamplingPipeline {
    s32 field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
} Recovered_SamplingPipeline;
typedef char assert_Recovered_SamplingPipeline_0[(((int)&((Recovered_SamplingPipeline *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_SamplingPipeline_4[(((int)&((Recovered_SamplingPipeline *)0)->field_4) == 4) ? 1 : -1];
#endif
