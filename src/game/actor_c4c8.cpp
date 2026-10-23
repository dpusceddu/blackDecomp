#include "campaign/actor/region_state.hpp"
namespace CampaignActor {
extern "C" {
void func_00125CD8(void *);
void func_0026AA68(int);void func_0026A840(int);
void func_001AE5E8(void *, const Matrix4 *, PositionArg, PositionArg, PositionArg);
extern char *D_0040F4C0;
extern Position4 D_00414D20, D_00414D30;
}
int RegionState::Initialize(unsigned long id,RegionConfig*data){
 func_00125CD8(this);*(unsigned long*)this=id;config=data;source=data;if(data->enabled)enabled=1;else enabled=0;
 switch(data->mode){case 0:mode=0;break;case 1:mode=1;break;case 2:mode=2;break;case 3:mode=3;break;case 4:mode=4;break;}
 switch(data->policy){case 0:policy=0;break;case 1:policy=1;break;case 2:policy=2;break;}
 if(config->enabled)enabled=1;else enabled=0;triggered=0;return 1;
}
void RegionState::RenderBox(){
 func_0026AA68(0);func_0026A840(0);PositionArg color=Load(D_00414D30);if(enabled)color=Load(D_00414D20);
 func_001AE5E8(D_0040F4C0,&world,Load(this->color),Load(halfExtent),color);
}
}

// Unmatched: 0x16C728 yaw polynomial and rigid-inverse temporary copies.
// Unmatched: 0x16C9E8 trigger predicate and callback control-flow lifetimes.
