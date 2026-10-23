#include "rw_core/error.h"
extern u8 D_00449438[];extern s32 D_0040E5A0;
RwErrorRecordPS2 *func_002A55D8(RwErrorRecordPS2 *error) {
 RwErrorRecordPS2 *current=(RwErrorRecordPS2 *)(D_00449438+D_0040E5A0);
 if(!current->plugin_id && current->error_code==(s32)0x80000000) {
  if(error->error_code<0)current->plugin_id=0;else current->plugin_id=error->plugin_id;
  ((RwErrorRecordPS2 *)(D_00449438+D_0040E5A0))->error_code=error->error_code;
 }
 return error;
}
