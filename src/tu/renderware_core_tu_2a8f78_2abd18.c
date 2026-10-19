#include "ps2/renderware_inline.h"
extern u8 D_00449438[];
RwImagePS2 *func_002ABD18(RwImagePS2 *image) {return RwReleaseImagePixelsPS2(image,M2C_FIELD(D_00449438,void (**)(void *),0x10c));}
