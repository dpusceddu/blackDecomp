#include "include_asm.h"
#include "ps2/prelude.h"

void func_001F1A70(void *arg0) {
    void *temp_16;
    void *temp_3;
    void *var_17;

    var_17 = M2C_FIELD(arg0, void **, 0xA0);
    if (var_17 != NULL) {
        do {
            temp_3 = M2C_FIELD(var_17, void **, 0x14);
            temp_16 = M2C_FIELD(var_17, void **, 4);
            M2C_FIELD(temp_3, M2C_UNK (**)(void *), 0x1C)(var_17 + M2C_FIELD(temp_3, s16 *, 0x18));
            M2C_FIELD(var_17, void **, 4) = NULL;
            var_17 = temp_16;
        } while (var_17 != NULL);
    }
    M2C_FIELD(arg0, void **, 0xA0) = NULL;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1a70", func_001F1AD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1a70", func_001F1B90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1a70", func_001F1B98);
