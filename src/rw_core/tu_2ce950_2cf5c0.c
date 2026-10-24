#include "include_asm.h"
#include "ps2/prelude.h"
#include "rw_core/plugin.h"
#include "types_ghidra.h"

extern M2C_UNK D_0040A991;

s32 func_002CF5C0(void) {
    return 1;
}

s32 func_002CF5C8(void) {
    return 1;
}

void func_002CF5D0(void) {

}

void func_002CF5D8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF5F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF878);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF888);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CF990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFAC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFDE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFDF8);

/* Walk registered plugins from the tail towards the head, invoking destructors. */
RwRegistryPS2 *func_002CFE90(RwRegistryPS2 *registry, s32 object) {
    RwPluginPS2 *plugin = registry->last;
    if (plugin != NULL) {
        do {
            ((s32 (*)(s32, s32, s32))plugin->destruct)(object, plugin->offset, plugin->size);
            plugin = plugin->previous;
        } while (plugin != NULL);
    }
    return registry;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFEF0);

s32 func_002CFF40(s32 arg0) {
    return arg0;
}

s32 func_002CFF48(s32 arg0) {
    return arg0;
}

s32 func_002CFF50(s32 arg0) {
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFF58);

s32 func_002CFFB0(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFFB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002CFFC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D00F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0280);

void func_002D0678(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0680);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D06B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0758);

s8 * func_002D07C8(s8 *text) {
    s8 *cursor;
    s8 character;

    if (text != NULL) {
        cursor = text;
        if (*text != 0) {
            do {
                character = *cursor;
                if ((u32) (character - 0x61) < 0x1AU) {
                    *cursor = character - 0x20;
                }
                cursor += 1;
            } while (*cursor != 0);
        }
    }
    return text;
}

s8 * func_002D0810(s8 *text) {
    s8 *cursor;
    s8 character;

    if (text != NULL) {
        cursor = text;
        if (*text != 0) {
            do {
                character = *cursor;
                if ((u32) (character - 0x41) < 0x1AU) {
                    *cursor = character + 0x20;
                }
                cursor += 1;
            } while (*cursor != 0);
        }
    }
    return text;
}

s8 * func_002D0890(s8 *arg0, s8 arg1) {
    s8 *var_4;
    s8 *var_6;
    s8 *var_7;
    s8 temp_3;

    var_4 = arg0;
    var_7 = NULL;
    var_6 = var_4;
    do {
        temp_3 = *var_6;
        var_6 += 1;
        var_7 = ((temp_3 ^ arg1) == 0) ? var_4 : var_7;
        var_4 += 1;
    } while (temp_3 != 0);
    return var_7;
}

/* Find the first signed-byte character, including the terminator. */
s8 *func_002D0858(s8 *text,s8 character) {
 s8 *result=0,*cursor=text; s8 value;
 do {value=*cursor++;if(value==character){result=text;break;}text++;}while(value);
 return result;
}

s32 func_002D08C8(void *arg0) {
    s32 var_5;
    s8 temp_3;

    var_5 = 0;
    if ((arg0 != NULL) && ((temp_3 = M2C_FIELD(arg0, s8 *, 0), (temp_3 == 0x5C)) || ((M2C_FIELD((temp_3 + ((s32) &D_0040A991)), u8 *, 0) & 3) && (M2C_FIELD(arg0, s8 *, 1) == 0x3A)))) {
        var_5 = 1;
    }
    return var_5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0A08);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002D1530(void *, s32, u32, u32, u32);
extern M2C_UNK D_003C3370;

s32 func_002D0A18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_002D1530(&D_003C3370, arg0, (u32) arg1, (u32) arg2, (u32) arg3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0A78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0D98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0DA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D0FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D11C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D11D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D1570);
