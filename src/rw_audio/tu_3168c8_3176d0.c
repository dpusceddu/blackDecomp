#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#ifdef NON_MATCHING
#include "rw_audio/emitter.h"
#endif

s32 func_003176D0(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (temp_2 + arg0);
    return temp_2;
}

#ifdef NON_MATCHING
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
extern void func_002A75F0(RwaVec3 *,const RwaVec3 *);
void func_003176E0(RwaVec3 *value,const RwaListener *listener) {
    RwaVec3 forward __attribute__((aligned(16)));
    RwaVec3 right __attribute__((aligned(16)));
    RwaVec3 up __attribute__((aligned(16)));
    RwaVec3 velocity;
    f32 x,y,z;
    func_002A75F0(&forward,&listener->forward);
    func_002A75F0(&right,&listener->right);
    func_002A75F0(&up,&listener->up);
    x=value[0].x-listener->position.x;
    y=value[0].y-listener->position.y;
    z=value[0].z-listener->position.z;
    value[0].x=forward.x*x+forward.y*y+forward.z*z;
    value[0].z=up.x*x+up.y*y+up.z*z;
    value[0].y=right.x*x+right.y*y+right.z*z;
    x=value[1].x-listener->velocity.x;
    y=value[1].y-listener->velocity.y;
    z=value[1].z-listener->velocity.z;
    velocity.x=x;velocity.y=y;velocity.z=z;
    value[1].z=up.x*x+up.y*y+up.z*z;
    value[1].x=forward.x*x+forward.y*y+forward.z*z;
    value[1].y=right.x*x+right.y*y+right.z*z;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003176E0);
#endif
