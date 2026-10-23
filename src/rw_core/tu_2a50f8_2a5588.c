#include "rw_core/error.h"
extern u8 D_00449438[];extern s32 D_0040E5A0,D_0040E5A4;
void *func_002A5588(void *instance,s32 offset) {RwErrorRecordPS2 *error=(RwErrorRecordPS2 *)(D_00449438+offset);D_0040E5A4++;error->error_code=0x80000000;D_0040E5A0=offset;error->plugin_id=0;return instance;}
