// Partial native PS2 view; semantic class identity and complete allocation remain unverified.
#ifndef BLACK_CAMPAIGN_ACTOR_RENDERABLE_STATE_HPP
#define BLACK_CAMPAIGN_ACTOR_RENDERABLE_STATE_HPP
#include "ps2/vu0.hpp"
namespace CampaignActor {
struct RenderablePrefix { char prefix[0x10]; };
// The intermediate virtual base preserves the PS2 vptr at0x10. Unused slots are provisional.
class RenderableInterface : public RenderablePrefix {
public:
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2();
    // The result is unused here; its semantic type/width remain unverified.
    virtual int Finish();
};
struct PendingActor { void *target; unsigned char mode; };
class RenderableState : public RenderableInterface {
public:
    char toBody[0xA0]; void *body;
    char toState[0xC]; int state;
    char toControl[0x48]; void *control, *data, *model;
    char toFlag13A[0x1E];
    unsigned char flag13A, flag13B, ready, flag13D, visible, flag13F;
    int mode; char toFlags[0xC]; unsigned short flags16;
    unsigned char flags, flag153, pending, rebuild;
    char toPendingActor[2]; PendingActor *pendingActor;
    void Reset(); void Update(float); void Release();
};
}
#endif
