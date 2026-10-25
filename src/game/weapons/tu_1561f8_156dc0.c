#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/weapons/state.h"

extern s32 func_00155118();
extern void func_0015A830();

s32 func_00156DC0(void *arg0) {
    BkWeaponControllerPS2 *weapon=arg0;
    s32 var_2;
    void *temp_4;
    void *temp_5;

    if (weapon->owner->kind == 2) {
        var_2 = 0;
        if (func_00155118(weapon->inventory, weapon->definition->reserveIndex) != 0) {
            temp_5 = weapon->primary;
            temp_4 = weapon->definition;
            var_2 = 0;
            if (((BkWeaponInstancePS2*)temp_5)->clip != ((BkWeaponDefinitionPS2*)temp_4)->capacity) {
                weapon->outOfAmmo = 0;
                if (((BkWeaponDefinitionPS2*)temp_4)->perRound == 0) {
                    weapon->phase = 4;
                } else {
                    weapon->phase = 5;
                    weapon->flags100[1] = (s8) ((u8) ((BkWeaponDefinitionPS2*)temp_4)->capacity - (u8) ((BkWeaponInstancePS2*)temp_5)->clip);
                }
                return 1;
            }
        }
        /* Duplicate return node #8. Try simplifying control flow for better match */
        return var_2;
    }
    func_0015A830(weapon->primary);
    var_2 = 1;
    weapon->phase = 4;
    return var_2;
}
