#include "mod/camera/aim.hpp"
namespace ModCamera {
extern char *world __asm__("D_0040F4D0");
extern PlayerAim *CurrentPlayer(void*) __asm__("func_00135550");
// Callback entry; the containing TU and historical class identity are unverified.
void AimSelection::Select(const AimCandidate *candidate) {
 PlayerAim *player=CurrentPlayer(world+0x30);
 AimActor *actor=candidate->actor;
 if(actor->eligibility){
  if(!player->selected)player->selected=actor;
  else{float previous=player->perpendicularSquared; float next=candidate->perpendicularSquared; if(!(next<previous))return;player->selected=actor;}
  player->perpendicularSquared=candidate->perpendicularSquared;
  player->projection=candidate->projection;
 }
}
}
