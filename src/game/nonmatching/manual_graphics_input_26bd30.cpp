#include "ps2/prelude.h"
// Unmatched: 13 instruction differences after native layout, argument-bank and helper probes.
#include "game/camera/pad.hpp"
extern "C"{
extern s32 func_0026C9C0(void *, s32);
extern s32 func_0029D4C0(s32, s32, void *, s32, void *);
extern s32 func_0026C9E0(s32, s32);
}
void CampaignGraphics::Controller::UpdateMotors() {
    struct MotorCommand {u8 command;u8 padding;s16 flags;};
    struct Commands {MotorCommand first,second;} commands __attribute__((aligned(16)));
    s16 var_2;
    s32 temp_2_3;
    s32 temp_4;
    u8 temp_2;
    u8 temp_2_2;

    temp_4 = this->backend;
    if (temp_4 != 0) {
        temp_2 = func_0026C9C0((void *) temp_4, this->port) == this->field_4;
        this->connected = temp_2;
        if (!Connected()) {
            this->field_49 = 0;
            this->initialized = 0;
            goto block_13;
        }
        temp_2_2 = this->field_46;
        if (this->field_4A != 0) {
            if ((this->field_47 != temp_2_2) || (this->field_49 != this->field_48)) {
                temp_2_3 = this->field_47 * 2;
                commands.first.command = 3;
                if (this->field_49 != 0) {
                    var_2 = temp_2_3 | 1;
                } else {
                    var_2 = temp_2_3 & 0xFFFF;
                }
                commands.first.flags = var_2;
                func_0029D4C0(func_0026C9E0(this->backend, this->port), 1, &commands.first.command, 2, &commands.first.flags);
                this->field_46 = this->field_47;
                this->field_48 = this->field_49;
            }
        } else if ((temp_2_2 != 0) || (this->field_48 != 0)) {
            commands.second.command = 3;
            commands.second.flags = 0;
            func_0029D4C0(func_0026C9E0(this->backend, this->port), 1, &commands.second.command, 2, &commands.second.flags);
            this->field_49 = 0;
            this->field_46 = 0;
            this->field_48 = 0;
block_13:
            this->field_47 = 0;
        }
    }
}
