#include "include_asm.h"

#include "kynapse/hide_agent.hpp"
using namespace HideViews;
extern char D_00404400[];
const char rodata_00404400[56] __asm__("D_00404400") __attribute__((aligned(8))) = "CHideAgent" "\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim11CGraphPoint" "\000\000\000";
extern unsigned int D_0044F018,D_003E2AE0,D_003E3428[];
extern unsigned int *D_0044F128;
extern int (*D_003C87E0)(void *);
extern "C" void *func_002D3C90();
extern "C" int func_002DFF98(HideAgent *,int);
extern "C" void func_002E00F0(void *,const char *,void *(*)(),int,int,int);

extern "C" void func_002D5008(int initialize,int priority) {
    if (priority==0xffff) {
        if (initialize) {
            func_002E00F0(&D_0044F018,D_00404400,func_002D3C90,0,0,0);
            return;
        }
        D_0044F128=&D_003E2AE0;
    }
}
extern "C" int func_002D50E8(HideAgent *self,int flags) {
    *(void **)self=D_003E3428;
    if (self->dangerous)D_003C87E0(self->dangerous);
    if (self->nodes)D_003C87E0(self->nodes);
    func_002DFF98(self,0);
    int result=flags&1;
    if (result)result=D_003C87E0(self);
    return result;
}
extern "C" const Vec3 *func_002D5368(HideAgent *self) {
    if (self->found) {
        if (self->fresh)return &self->destination;
    }
    return &self->context->actor->position;
}
namespace HideViews {
    int HideAgent::AddDangerous(Actor *actor) {
        if (dangerousCount>=maxDangerous)return 0;
        dangerous[dangerousCount]=actor;
        ++dangerousCount;
        return 1;
    }
}
extern "C" void func_002D53B0() {
    func_002D5008(1,0xffff);
}
extern "C" void func_002D53D0() {
    func_002D5008(0,0xffff);
}












