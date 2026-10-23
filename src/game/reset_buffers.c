#include "game/actor/render_state.h"
extern void func_001B08A8(void *,int,int,int),func_0027B2F0(void *,float);
void func_001AE860(BkActorRenderPS2 *actor) {
 int *position=(int *)actor;
 func_001B08A8(&actor->buffers[0],position[0],position[1],position[2]);
 func_001B08A8(&actor->buffers[1],0,0,0);
 func_001B08A8(&actor->buffers[2],0,0,0);
 func_0027B2F0(&actor->buffers[0],30.0f);
 actor->resource=0;
}
