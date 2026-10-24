#include "kynapse/behaviors/hide.hpp"
extern const float kNearestLimit;
namespace HideRecovery {
void HideAgent::Reset() {
    farLimit=0;
    nearLimit=kNearestLimit;
}
}
const float kNearestLimit=3.4028234663852886e+38F;
