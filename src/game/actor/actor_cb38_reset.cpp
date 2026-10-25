#include "include_asm.h"

#include "game/actor/renderable_state.hpp"
namespace ActorParts {
extern "C" {
void func_0014BD18(void *); void func_0014EE48(void *);
void func_0014BE20(void *, float);
Game::PositionArg func_0025D8E0(void *); void func_0025DC80(void *);
void func_0014F708(void *); void func_00129240(void *, void *, int);
void func_00168618(void *, void *, unsigned char, void *);
void func_00126D78(void *, void *, int);
void func_00129108(void *, void *, int, int, long);
extern char *D_0040F4D0, *D_0040F4E4, *D_0040F4F4;
}

void RenderableState::Reset()
{
    func_0014BD18(this);
    data = 0; model = 0; state = 7;
    func_0014EE48(this);
    pendingActor = 0; mode = 5; body = 0; flag13A = 0; control = 0;
    flags16 = 0; pending = 0; flags = 0; flag153 = 0;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014EE48);
