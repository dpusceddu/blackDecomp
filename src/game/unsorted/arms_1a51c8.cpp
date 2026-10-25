#include "animation/arms/owner.hpp"
namespace ArmsAnimation {
// Unmatched: Initialize retains a compiler scheduling or layout difference.
#ifdef ARMS_TICK_ONLY
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
#endif
// Unmatched: CommitPrimary retains a compiler scheduling or layout difference.
// Unmatched: CommitSecondary retains a compiler scheduling or layout difference.
// Unmatched: Neutral retains a compiler scheduling or layout difference.
// Unmatched: Request retains a compiler scheduling or layout difference.
#if !defined(ARMS_TICK_ONLY)
void Owner::RequestAction(const Action* action) {
    ProfileScope profile(5);char name[16];name[0]=0;Component(entity);
    if(!primary->collection)return;
    {
        switch(action->kind) {
        case 1:selector->Slot8(name,entity,action->key);StopSecondary(this);break;
        case 11:selector->Slot3(name,entity,action->mode,action->flag);break;
        case 12:selector->Slot21(name,entity);break;
        case 18:selector->Slot14(name,entity);break;
        case 19:selector->Slot20(name,entity,action->flag);break;
        case 10:selector->Slot4(name,entity,action->flag,action->mode);break;
        case 6:selector->Slot11(name,entity);break;
        case 7:selector->Slot12(name,entity);break;
        case 8:selector->Slot15(name,entity);break;
        case 5:selector->Slot9(name,entity,action->flag,action->mode,action->value,action->key);break;
        case 2:selector->Slot7(name,entity,action->key,action->flag);break;
        case 3:selector->Slot6(name,entity,action->key,action->flag);break;
        case 13:selector->Slot10(name,entity,action->value,action->flag);break;
        case 14:selector->Slot16(name,entity);break;
        case 15:selector->Slot17(name,entity);break;
        case 17:selector->Slot18(name,entity,action->value,action->key);break;
        case 9:if(action->key==0x26)selector->Slot19(name,entity,action->flag);break;
        case 20:selector->Slot22(name,entity);break;
        case 21:Action21(selector,name,entity);break;
        case 22:selector->Slot13(name,entity);break;
        case 23:Action23(selector,name,entity);break;
        case 24:Action24(selector,name,entity);break;
        default:return;
        }
        Request(name);
    }

}
#endif
// Unmatched: Event retains a compiler scheduling or layout difference.
// Unmatched: Permitted retains a compiler scheduling or layout difference.
#if !defined(ARMS_TICK_ONLY)
Matrix* Owner::Attachment(int index) {int offset=index*4;int state=*(int*)((char*)(offset+(char*)selector)+0x34);if(state<0)return (Matrix*)&gIdentity;return attachments[index];}
#endif
// Unmatched: BoneDirection retains a compiler scheduling or layout difference.
#if !defined(ARMS_TICK_ONLY)
Vector Owner::BoneDelta() {
    if(primary&&mode<3&&!b7){float* first=(float*)((char*)primary->selectedMatrices+bone1*64);float* second=(float*)((char*)primary->selectedMatrices+bone2*64);Game::Position4 p;Game::Store(p,Game::Make3(second[12]-first[12],second[13]-first[13],second[14]-first[14]));return Game::Load(p);}
    return gZero;
}
#endif
#if !defined(ARMS_TICK_ONLY)
Vector Owner::BonePosition() {
    if(primary&&Data(entity)->At<int>(0)){float* bone=(float*)((char*)primary->selectedMatrices+bone1*64);Game::Position4 p;Game::Store(p,Game::Make3(bone[12],bone[13],bone[14]));return Game::Load(p);}
    return gDefault;
}
#endif
// Unmatched: BoneMatrix retains a compiler scheduling or layout difference.
// Unmatched: UpdateAttachments retains a compiler scheduling or layout difference.
// Unmatched: Submit retains a compiler scheduling or layout difference.
// Unmatched: Heading retains a compiler scheduling or layout difference.
#if !defined(ARMS_TICK_ONLY)
void Owner::PrepareOverride() {
    if(!b9){b9=1;SetOverride(primary,(char*)this+0x10,5,5);At<float>(0x10)=0.0f;At<float>(0x14)=0.0f;At<float>(0x18)=0.0f;At<float>(0x1c)=1.0f;}
}
#endif
#if !defined(ARMS_TICK_ONLY)
int Owner::ChannelFlag() {if(rows[0])return rows[0]->channelFlag;return 0;}
#endif
#if !defined(ARMS_TICK_ONLY)
void Owner::ActorReset() {ResetActor(entity,0.0f,4.0f);}
#endif
// Unmatched: Locator retains a compiler scheduling or layout difference.
// Unmatched: HasPending retains a compiler scheduling or layout difference.
// Unmatched: Capture retains a compiler scheduling or layout difference.
// Unmatched: Velocities retains a compiler scheduling or layout difference.
#if !defined(ARMS_TICK_ONLY)
long Owner::CanTransition(int graph) {
    for(int i=0;i<TransitionCount(primary->collection);++i){int* row=TransitionRow(primary->collection,i);if((row[0]==-1||row[0]==(int)primary->graphHash)&&row[5]==graph)return 1;}
    return 0;
}
#endif
#if !defined(ARMS_TICK_ONLY)
long Owner::RequestState(int channel,int key) {
    Row* current=rows[channel];Row* requested=pendingRows[channel];
    if(current&&current->key==key)return Permitted(channel,0)?2:0;
    if(requested&&requested->key==key)return 1;
    return 3;
}
#endif
// Unmatched: Prepare retains a compiler scheduling or layout difference.
// Unmatched: Publish retains a compiler scheduling or layout difference.
}
