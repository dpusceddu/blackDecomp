#include "renderware_core/image.h"
extern u8 D_00449438[];
RwImagePS2 *func_002ABD18(RwImagePS2 *image) {M2C_FIELD(D_00449438,void (**)(void *),0x10c)(image->pixels);image->pixels=0;image->palette=0;image->flags&=~1;return image;}
