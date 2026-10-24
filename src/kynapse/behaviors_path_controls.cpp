#include "kynapse/behaviors/pathway.hpp"

namespace Kaim {
// Both motion-control pairs must have exactly one member. This occupies virtual slot 9.
bool PathWayAgent::Refresh() {
    if(!forward) {if(!turn)return false;}else if(turn)return false;
    if(!yawControl) {if(!lookControl)return false;}else if(lookControl)return false;
    return true;
}
}
