#include "game/actor/sphere_region.hpp"
namespace CampaignActor {
long SphericalRegion::Update(PositionArg point,long message){
 using namespace BlackPS2::VU0;
 Vec delta=Sub3(point,Load(configuration->center));
 float distance=Length3Word(delta),radius=configuration->radius;
 if(radius<distance){if(inside){inside=0;Signal(message);}}
 else if(distance<=radius&&!inside){inside=1;Signal(message);}
 return 0;
}
}
// Unmatched: 0x164F50 service-pointer lifetime and saved-register allocation.
