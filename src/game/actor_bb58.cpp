#include "campaign/actor/actor_command.hpp"
namespace CampaignActor {
extern "C" {extern CommandWorld*D_0040F514;}
inline CommandWorld*World(){return D_0040F514;}
void WeightCommand::Execute(){
 float value=data->value;float fraction=1.0f-data->fraction;
 for(int i=0;i<data->count;++i){
  for(int j=0;j<World()->count;++j){CommandActor*actor=World()->actors[j];
   if(actor&&actor->Agent()&&actor->Agent()->kind==1&&actor->id==data->ids[i]){
    CommandAgent*agent=actor->Agent();agent->drive.Configure(fraction,value,0);
    agent->weights.Configure(data->second,data->first);break;
   }
  }
 }
}
}
