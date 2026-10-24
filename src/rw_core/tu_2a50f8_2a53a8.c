#include "include_asm.h"
#include "ps2/prelude.h"
#include "rw_core/stream.h"
#include "ps2/renderware_inline.h"

extern RwStreamPS2 *func_002A71E0(RwStreamPS2 *,const void *,u32);
extern M2C_UNK D_00449540;

RwStreamPS2 *func_002A53A8(RwStreamPS2 *stream,const void *buffer,u32 size) {func_002A71E0(stream,buffer,size);return stream;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A53D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A55B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A55D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A55D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5850);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5A78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5A90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5AC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5B48);

RwMatrixPS2 *func_002A5B60(RwMatrixPS2 *matrix) {
    return RwInvalidateMatrixFlagsPS2(matrix);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5B80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5C80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A5CE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6340);

M2C_UNK * func_002A65E0(void) {
    return &D_00449540;
}
