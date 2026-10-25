#include "animation/arms/owner.hpp"
namespace ArmsAnimation {
// Unmatched: Initialize retains a compiler scheduling or layout difference.
void Owner::Tick(float delta,int defer) {
    ++gTick;if(b7){delta*=2.0f;b7=0;defer=0;}if(changed)defer=0;
    if(!active)return;
    ProfileScope profile(0);if(!ba)delta=0;if(gReady!=1){SetupGlobals();gReady=1;}
    Prepare();Matrix previous[11];
    Capture(previous);CommitPrimary();CommitSecondary();if(b9)ServiceB9(this);
    if(rows[0]) {
        if(defer)b7=1;
        else {ProfileEnter(3);SetAux(gBank,0);SetBank(gBank,publication);primary->Update(delta);b7=0;ProfileLeave(3);OwnerService(this,delta);if(rows[0]->reissue||Complete(primary,0))permits[0]=1;}
    }
    if(!rows[1]||!secondary||rows[1]->reissue||Complete(secondary,0))permits[1]=1;
    Velocities(previous,delta);Publish(7);if(entity->At<int>(0xc4)!=2)SetActorPosition(entity,BonePosition());
    RetirePose(1);changed=0;gPoseCount=0x2c;gPoseSize=0x1c;gPoseScratch=0;
}
// Unmatched: CommitPrimary retains a compiler scheduling or layout difference.
// Unmatched: CommitSecondary retains a compiler scheduling or layout difference.
// Unmatched: Neutral retains a compiler scheduling or layout difference.
// Unmatched: Request retains a compiler scheduling or layout difference.
// Unmatched: Event retains a compiler scheduling or layout difference.
// Unmatched: Permitted retains a compiler scheduling or layout difference.
// Unmatched: BoneDirection retains a compiler scheduling or layout difference.
// Unmatched: BoneMatrix retains a compiler scheduling or layout difference.
// Unmatched: UpdateAttachments retains a compiler scheduling or layout difference.
// Unmatched: Submit retains a compiler scheduling or layout difference.
// Unmatched: Heading retains a compiler scheduling or layout difference.
// Unmatched: Locator retains a compiler scheduling or layout difference.
// Unmatched: HasPending retains a compiler scheduling or layout difference.
// Unmatched: Capture retains a compiler scheduling or layout difference.
// Unmatched: Velocities retains a compiler scheduling or layout difference.
// Unmatched: Prepare retains a compiler scheduling or layout difference.
// Unmatched: Publish retains a compiler scheduling or layout difference.
}
