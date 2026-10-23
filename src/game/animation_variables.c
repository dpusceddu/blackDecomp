#include "auto/prelude.h"
typedef float (*BkAnimationCallbackPS2)(void *);
typedef struct { const char *name; BkAnimationCallbackPS2 callback; } BkAnimationVariablePS2;
extern BkAnimationVariablePS2 D_0048F708[13];
extern float func_001AC268(void *),func_001AC278(void *),func_001AC398(void *),func_001AC3F8(void *),func_001AC440(void *),func_001AC4B8(void *),func_001AC568(void *),func_001AC330(void *),func_001AC5B8(void *),func_001AC648(void *);
extern void func_00348A10(BkAnimationVariablePS2 *,int);
void func_001ABA98(void) {
 D_0048F708[0].name="unknown";D_0048F708[0].callback=0;
 D_0048F708[1].name="true";D_0048F708[1].callback=func_001AC268;
 D_0048F708[2].name="false";D_0048F708[2].callback=0;
 D_0048F708[3].name="frame number";D_0048F708[3].callback=0;
 D_0048F708[4].name="player_move_rate";D_0048F708[4].callback=func_001AC278;
 D_0048F708[5].name="player_direction";D_0048F708[5].callback=func_001AC398;
 D_0048F708[6].name="crouching";D_0048F708[6].callback=func_001AC3F8;
 D_0048F708[7].name="aim_pitch";D_0048F708[7].callback=func_001AC440;
 D_0048F708[8].name="aim_bearing";D_0048F708[8].callback=func_001AC4B8;
 D_0048F708[9].name="torso_pitch";D_0048F708[9].callback=func_001AC568;
 D_0048F708[10].name="run_rate_multiplier";D_0048F708[10].callback=func_001AC330;
 D_0048F708[11].name="cowering";D_0048F708[11].callback=func_001AC5B8;
 D_0048F708[12].name="shot_on_air";D_0048F708[12].callback=func_001AC648;
 func_00348A10(D_0048F708,13);
}
