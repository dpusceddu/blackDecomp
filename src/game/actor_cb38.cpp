#include "game/actor/renderable_state.hpp"
namespace CampaignActor {
extern "C" {
void func_0014BD18(void *); void func_0014EE48(void *);
void func_0014BE20(void *, float);
BlackGame::PositionArg func_0025D8E0(void *); void func_0025DC80(void *);
void func_0014F708(void *); void func_00129240(void *, void *, int);
void func_00168618(void *, void *, unsigned char, void *);
void func_00126D78(void *, void *, int);
void func_00129108(void *, void *, int, int, long);
extern char *D_0040F4D0, *D_0040F4E4, *D_0040F4F4;
}
void RenderableState::Update(float delta)
{
    func_0014BE20(this, delta);
    if (body && BlackPS2::VU0::ReadXWord(BlackGame::SumSquares3(func_0025D8E0(body))) > 0.05f)
        func_0025DC80(body);
    if (rebuild) { func_0014F708(this); rebuild = 0; }
    if (pending && ready) {
        func_00129240(D_0040F4D0, this, 0);
        flags &= 0xFB; pending = 0;
        if (pendingActor && pendingActor->target)
            func_00168618(D_0040F4F4, pendingActor->target, pendingActor->mode, D_0040F4D0 + 0x30);
        Finish();
    }
}
void RenderableState::Release()
{
    if (flags & 8) {
        flags &= 0xF7;
        func_00126D78(D_0040F4E4, this, 0);
    } else if (!(flags & 4)) {
        func_00129108(D_0040F4D0, this, 0, 0, -1L);
        flags |= 4;
    }
}
}

// Unmatched: 0x14BD58 RGB component load/store allocation.
// Unmatched: 0x14F498 visibility-mask helper and render-loop register allocation.
