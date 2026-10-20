#ifndef BLACK_MOD_CAMERA_AIM_HPP
#define BLACK_MOD_CAMERA_AIM_HPP
#include "ps2/vector_storage.hpp"

namespace ModCamera {
// Instruction views from 1409C0/12BB60, not source-verified class identities.
// Xbox counterparts 1BD3D0/1CDA60 have different actor/player/manager offsets.
struct AimActor {
    unsigned char unknown00[0x70];
    BlackGame::Position4 world[4];
    unsigned char unknownb0[0xc];
    void *animation;
    unsigned char unknownc0[0x2e4];
    int eligibility;
};
struct AimCandidate {
    BlackGame::Position4 point;
    float projection, perpendicularSquared;
    AimActor *actor;
};
struct PlayerAim {
    unsigned char unknown00[0x9c];
    AimActor *selected;
    float perpendicularSquared, projection;
};
struct AimActorList {
    unsigned char unknown00[0x79a4];
    int count;
    unsigned char unknown79a8[4];
    AimActor **actors;
};
typedef char AimEligibility3A4[(unsigned)&((AimActor*)0)->eligibility==0x3a4?1:-1];
typedef char AimCandidateActor18[(unsigned)&((AimCandidate*)0)->actor==0x18?1:-1];
// These declarations only expose accessed prefixes. Query argument order,
// callback NaN behavior and the original inline matrix operators remain open.
}
#endif
