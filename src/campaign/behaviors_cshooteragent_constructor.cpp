#include "campaign/behaviors/shooter.hpp"
namespace Kaim {
ShooterAgent::ShooterAgent(BehaviorContext* c):Behavior(c) {
 gunRange=0;dangerousConeAngle=0;maxInaccuracy=0;targetDistance=0;
 target=0;provider=0;perception=0;
 aimOrigin.y=gunRange;aimOrigin.x=gunRange;aimOrigin.z=gunRange;
}
}
