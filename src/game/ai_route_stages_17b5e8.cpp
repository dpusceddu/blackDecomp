// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_route_stages_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x17b5e8
// A candidate node is usable when a swept volume of radius 0.35 from the lifted search origin to the
// node point is free.
// Unmatched: Xbox private register contract and the volume query's private callee contract.
bool NodeSearch::TestCandidate(const RouteNode* node) const
{
    Vec raised = Add3(Load(origin), Load(gRouteLift));
    return !IsVolumeBlocked(&Manager()->probeWorld, raised, WidenVec(node->position), 0x23, 0.35f);
}

}  // namespace BlackGame
