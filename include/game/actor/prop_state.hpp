// Partial PS2 actor-state view. Class identity, inheritance and allocation size are unverified.
#ifndef BLACK_ACTOR_PROP_STATE_HPP
#define BLACK_ACTOR_PROP_STATE_HPP
#include "ps2/matrix.hpp"
namespace ActorParts {
struct RuntimeConfig {
    char toSound[0x20]; unsigned long sound;
    char toFlags[0x32]; unsigned short flags;
};
// Only the address passed to selector helpers is verified; opaque bytes describe a gap.
struct PropSelector { char opaque[8]; };
struct ContactData { Game::Position4 point, normal; };
struct PropState {
    char toReady[0x13C]; unsigned char ready;
    char toSelector[0x63]; PropSelector selector;
    char toPreviousState[0x10]; int previousState;
    char toSpawnEffect[3]; unsigned char spawnEffect;
    unsigned char pad1C0, contacted;
    Game::Position4 *StateBounds();
    bool Contact(const ContactData *);
} __attribute__((aligned(16)));
}
#endif
