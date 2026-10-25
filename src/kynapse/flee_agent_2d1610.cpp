#include "include_asm.h"

#include "kynapse/flee_agent.hpp"
using namespace FleeViews;
extern unsigned int D_003E2A58[],D_003E2AE0,D_0044ECD0;
extern unsigned int *D_0044EDE0;
extern "C" void func_002E00F0(void *,const char *,void *(*)(),int,int,int);
extern "C" void *func_002D1610();
extern "C" int func_002DFF98(FleeAgent *,int);
extern int (*D_003C87E0)(void *);

extern "C" void func_002D2CE8(int initialize,int priority) {
    if (priority==0xffff) {
        if (initialize) {
            func_002E00F0(&D_0044ECD0,"CFleeAgent",func_002D1610,0,0,0);
            return;
        }
        D_0044EDE0=&D_003E2AE0;
    }
}
extern "C" int func_002D2DB8(FleeAgent *self,int flags) {
    *(void **)self=D_003E2A58;
    if (self->points)D_003C87E0((char *)self->points-0x10);
    if (self->entities)D_003C87E0(self->entities);
    func_002DFF98(self,0);
    int result=flags&1;
    if (result)result=D_003C87E0(self);
    return result;
}
extern "C" void func_002D2EE8(FleeAgent *self) {
    self->pointCount=0;
    self->pathId=0x7fffffff;
}
extern "C" void func_002D2F40(FleeAgent *self) {
    self->entityCount=0;
}
namespace FleeViews {
    float FleeAgent::Rate(void *,int blocked,float sum,int depth) {
        return (sum/(float)(depth+1))/(float)(blocked*10+1);
    }
    int FleeAgent::AddPoint(const Vec3 *point) {
        if (pointCount>=maxPoints)return 0;
        points[pointCount]=*point;
        ++pointCount;
        return 1;
    }
    int FleeAgent::AddEntity(Actor *actor) {
        if (entityCount>=maxEntities)return 0;
        entities[entityCount]=actor;
        ++entityCount;
        return 1;
    }
}
extern "C" void func_002D2FB8() {
    func_002D2CE8(1,0xffff);
}
extern "C" void func_002D2FD8() {
    func_002D2CE8(0,0xffff);
}











#ifdef NON_MATCHING
namespace FleeViews {
// Unmatched: independent initialization stores are scheduled differently.
    FleeAgent::FleeAgent(Context *context):Behavior(context),graphSlot((unsigned int)-1) {
        maxEntities=20;
        pathId=0x7fffffff;
        provider=0;
        graph=0;
        unknown18=0;
        perception=0;
        maxPoints=20;
        points=0;
        entities=0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2D48);
#endif
