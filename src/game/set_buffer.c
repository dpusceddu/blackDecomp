#include "game/actor/render_state.h"
extern int func_0027B2E0(void *,void *);
int func_001AE938(BkActorRenderPS2 *actor,int index,void *data) {
 void *buffer=0;
 switch(index){case 0:buffer=&actor->buffers[0];break;case 1:buffer=&actor->buffers[1];break;case 2:buffer=&actor->buffers[2];break;}
 return func_0027B2E0(buffer,data);
}
