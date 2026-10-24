#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/graphics/timed_matrix.hpp"

using namespace BlackGame;
using namespace BlackPS2::VU0;
extern "C" {
extern void func_00107928(float, unsigned, int);
extern void func_001108D0(unsigned, unsigned);
extern float func_00113FE8(float, float, float, const float *);
extern Vec func_00114170(CampaignGraphics::TimedMatrix *, const Vec *, float);
extern unsigned D_0040F0E8;
extern unsigned char *D_0040F4D0;
extern Vec D_0040F070, D_0040F080, D_0040F090;
extern float D_003BC64C,D_003BC66C,D_003BC6AC,D_003BC70C,D_003BC74C;
extern float D_003BC76C,D_003BC78C,D_003BC7AC,D_003BC7CC,D_003BC7EC,D_003BC80C,D_003BC82C;
extern float D_003BC668[],D_003BC688[],D_003BC6A8[],D_003BC6C8[];
extern float D_003BC6E8[],D_003BC708[],D_003BC728[],D_003BC748[];
extern float D_003BC768[],D_003BC788[],D_003BC7A8[],D_003BC7C8[],D_003BC7E8[],D_003BC808[],D_003BC828[];
}
static inline int FloatBits(float f) { union {float f;int i;}u;u.f=f;return u.i;}
static inline float Greater(float a,float b) { asm("max.s av, av, bv" : "+f av"(a) : "f bv"(b) : "memory"); return a; }

// Unmatched: Reset retains 52 instruction differences in max/copy inline contracts and scheduling.
int CampaignGraphics::TimedMatrix::Reset()
{
    elapsed = 0.0f;
    switch (kind) {
    case 1: duration=D_003BC6AC; func_00107928(1.0f,D_0040F0E8,2); break;
    case 2:
        func_00107928(1.0f,D_0040F0E8,0);
        duration=Greater(Greater(D_003BC76C,D_003BC78C),D_003BC7AC);
        duration=Greater(Greater(duration,D_003BC7CC),D_003BC7EC);
        duration=Greater(Greater(duration,D_003BC80C),D_003BC82C);
        break;
    case 3: duration=D_003BC66C; func_00107928(1.0f,D_0040F0E8,3); break;
    case 6:
        curvePoints[0]=D_0040F070;curvePoints[1]=D_0040F070;
        curvePoints[2]=D_0040F080;curvePoints[3]=D_0040F080;
        duration=0.63300001621246338f;
        func_00107928(1.0f,D_0040F0E8,1); break;
    case 8:
        curvePoints[0]=D_0040F070;curvePoints[1]=D_0040F070;
        curvePoints[2]=D_0040F090;curvePoints[3]=D_0040F090;
        duration=0.63300001621246338f;
        func_00107928(1.0f,D_0040F0E8,1); break;
    case 4: duration=D_003BC70C; func_00107928(1.0f,D_0040F0E8,2); break;
    case 5: duration=D_003BC74C; func_00107928(1.0f,D_0040F0E8,2); break;
    case 10: duration=D_003BC64C; break;
    }
    return 1;
}

// Unmatched: Update (5676 bytes) needs verified axis rotation and quaternion/matrix inline contracts.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00112808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001129B8);
#endif
