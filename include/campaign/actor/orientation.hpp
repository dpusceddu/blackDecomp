#ifndef BLACK_CAMPAIGN_ACTOR_ORIENTATION_HPP
#define BLACK_CAMPAIGN_ACTOR_ORIENTATION_HPP
namespace CampaignActor {
// Provisional class identity. Begin verifies the named fields below; the opaque
// prefix includes other state and does not establish an allocation size or base.
struct OrientationState {
    unsigned char unknown00[0x90];
    int state;
    unsigned char unknown94[0x24];
    unsigned char active, locked;
    unsigned char unknownBA[2];
    int elapsed;
    unsigned char started, changed;
    unsigned char unknownC2[2];
    int previousState;

    int Begin(void *actor);
    int Attach(void *actor) __asm__("func_0013EC38");
};
}
#endif
