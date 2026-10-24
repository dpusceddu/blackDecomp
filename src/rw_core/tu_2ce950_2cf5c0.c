/* Translation unit renderware_core/tu_2ce950 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "rw_core/plugin.h"

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

/* Assembly between the functions: func_002CF5E0 (24 bytes), func_002CF5F8 (24 bytes), func_002CF610 (312 bytes), func_002CF748 (8 bytes), func_002CF750 (296 bytes), func_002CF878 (16 bytes), func_002CF888 (136 bytes), func_002CF910 (128 bytes), func_002CF990 (304 bytes), func_002CFAC0 (728 bytes), func_002CFD98 (80 bytes), func_002CFDE8 (16 bytes) ... */

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

/* Assembly between the functions: func_002CFEF0 (80 bytes) */

s32 func_002CFF40(s32 arg0) {
    return arg0;
}

s32 func_002CFF48(s32 arg0) {
    return arg0;
}

s32 func_002CFF50(s32 arg0) {
    return arg0;
}

/* Assembly between the functions: func_002CFF58 (88 bytes) */

s32 func_002CFFB0(void) {
    return 1;
}

/* Assembly between the functions: func_002CFFB8 (8 bytes), func_002CFFC0 (184 bytes), func_002D0078 (120 bytes), func_002D00F0 (88 bytes), func_002D0148 (48 bytes), func_002D0178 (264 bytes), func_002D0280 (1016 bytes) */

void func_002D0678(void) {

}

/* Assembly between the functions: func_002D0680 (56 bytes), func_002D06B8 (160 bytes), func_002D0758 (112 bytes) */

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

/* Assembly between the functions: func_002D0858 (56 bytes) */

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
