/* Translation unit renderware_core/tu_2a50f8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "rw_core/stream.h"
#include "ps2/renderware_inline.h"

extern RwStreamPS2 *func_002A71E0(RwStreamPS2 *,const void *,u32);
extern M2C_UNK D_00449540;

RwStreamPS2 *func_002A53A8(RwStreamPS2 *stream,const void *buffer,u32 size) {func_002A71E0(stream,buffer,size);return stream;}

/* Assembly between the functions: func_002A53D0 (80 bytes), func_002A5420 (296 bytes), func_002A5548 (64 bytes), func_002A5588 (48 bytes), func_002A55B8 (24 bytes), func_002A55D0 (8 bytes), func_002A55D8 (104 bytes), func_002A5640 (512 bytes), func_002A5840 (16 bytes), func_002A5850 (552 bytes), func_002A5A78 (24 bytes), func_002A5A90 (48 bytes) ... */

RwMatrixPS2 *func_002A5B60(RwMatrixPS2 *matrix) {
    return RwInvalidateMatrixFlagsPS2(matrix);
}

/* Assembly between the functions: func_002A5B80 (24 bytes), func_002A5B98 (48 bytes), func_002A5BC8 (184 bytes), func_002A5C80 (104 bytes), func_002A5CE8 (808 bytes), func_002A6010 (816 bytes), func_002A6340 (672 bytes) */

M2C_UNK * func_002A65E0(void) {
    return &D_00449540;
}
