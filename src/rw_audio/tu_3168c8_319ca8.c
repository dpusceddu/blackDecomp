#include "ps2/prelude.h"
extern s32 D_0040E1F0;
extern s32 func_00322A78(void);
extern s32 func_0031D7A8(void *);
extern u8 D_00458550[];
s32 func_00319CA8(void) {
    if(D_0040E1F0){
        if(func_00322A78())D_0040E1F0=0;
        else return 0;
    }
    return func_0031D7A8(D_00458550);
}
