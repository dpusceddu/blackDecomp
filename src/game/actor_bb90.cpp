#include "game/actor/actor_command.hpp"
namespace CampaignActor {
extern "C" {extern CommandWorld*D_0040F514;void func_0018D7A0(Steering*,int);}
inline CommandWorld*World(){return D_0040F514;}
void ModeCommand::Execute(){
 signed char mode=data->mode;
 for(int i=0;i<data->count;++i){
  for(int j=0;j<World()->count;++j){CommandActor*actor=World()->actors[j];
   if(actor&&actor->Agent()&&actor->Agent()->kind==1&&actor->id==data->ids[i]){func_0018D7A0(&actor->Agent()->steering,mode);break;}
  }
 }
}
}
