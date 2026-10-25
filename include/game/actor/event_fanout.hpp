#ifndef BLACK_ACTOR_EVENT_FANOUT_HPP
#define BLACK_ACTOR_EVENT_FANOUT_HPP
namespace ActorEvents {
// Provisional identities. Exact Dispatch verifies these PS2 offsets, not complete class sizes.
struct EventItem3 { unsigned char unknown00[0x10]; char *table; };
struct ActorFanout3 {
    unsigned char unknown00[8];
    EventItem3 **items;
    unsigned char count;
    // Code-compatible argument width; the original semantic event type is unverified.
    void Dispatch(int event);
};
}
#endif
