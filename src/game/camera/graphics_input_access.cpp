#include "game/camera/pad_backend.hpp"
#include "ps2/prelude.h"

using namespace Graphics;

bool Controller::Pressed(unsigned index)const {if(index>=28)return false;bool result=false;if(*((const EeU8*)this+index+42))result=previousStates[index]==0;return result;}

bool Controller::Released(unsigned index)const {if(index>=28)return false;bool result=false;if(!*((const EeU8*)this+index+42))result=previousStates[index]!=0;return result;}

unsigned char Controller::Button(unsigned index) const {if(index>=28)return 0;return *((const EeU8*)this+index+42);}

int Controller::Rumble(unsigned enabled) {
    if (!Connected()) return 0;
    if (enabled) {
        field_49 = 1;
        return 1;
    }
    field_49 = 0;
    return 0;
}

extern "C" {
extern s32 func_0026C9C0(void*, s32);
extern s32 func_0029D4C0(s32, s32, void*, s32, void*);
extern s32 func_0026C9E0(s32, s32);
}
void Graphics::Controller::UpdateMotors() {
    struct MotorCommand {
        u8 command;
        u8 padding;
        s16 flags;
    };
    struct Commands {
        MotorCommand first, second;
    } commands __attribute__((aligned(16)));
    u16 flags;
    s32 motorBits;
    s32 backendHandle;
    u8 connectedNow;

    backendHandle = this->backend;
    if (backendHandle != 0) {
        connectedNow = func_0026C9C0((void*)backendHandle, this->port) == this->field_4;
        this->connected = connectedNow;
        if (!Connected()) {
            this->field_49 = 0;
            this->initialized = 0;
            goto clearMotor;
        }

        if (this->field_4A != 0) {
            if ((this->field_47 != this->field_46) || (this->field_49 != this->field_48)) {
                motorBits = this->field_47 * 2;
                commands.first.command = 3;
                if (this->field_49 != 0) {
                    flags = motorBits | 1;
                } else {
                    flags = (u16)motorBits;
                }
                commands.first.flags = flags;
                func_0029D4C0(func_0026C9E0(this->backend, this->port), 1, &commands.first.command, 2,
                             &commands.first.flags);
                this->field_46 = this->field_47;
                this->field_48 = this->field_49;
            }
        } else if ((this->field_46 != 0) || (this->field_48 != 0)) {
            commands.second.command = 3;
            commands.second.flags = 0;
            func_0029D4C0(func_0026C9E0(this->backend, this->port), 1, &commands.second.command, 2, &commands.second.flags);
            this->field_49 = 0;
            this->field_46 = 0;
            this->field_48 = 0;
clearMotor:
            this->field_47 = 0;
        }
    }
}

float Controller::Smooth(float value, float step) {
    float limit = axisLimit;
    float threshold;
    if (value > 0.0f) {
        if (value > limit) value = limit;
        threshold = deadZone + step;
        value -= threshold;
        if (value < 0.0f) value = 0.0f;
        value *= 1.0f / (limit - threshold);
    } else {
        if (value < -limit) value = -limit;
        threshold = deadZone + step;
        value += threshold;
        if (value > 0.0f) value = 0.0f;
        value *= 1.0f / (limit - threshold);
    }
    return value;
}

extern "C" void func_0026CBA8(PadBackend*, int);

void PadBackend::Poll() {
    int i = 0;
    func_0026CBA8(this, 0);
    if (!singlePort) func_0026CBA8(this, 1);
    Controller** it = controllers;
    do {
        if (*it) (*it)->Update();
        ++i;
        ++it;
    } while (i < 2);
    if (!lastMode) {
        if (controllers[1]) controllers[1]->UpdateMotors();
        lastMode = 1;
    } else {
        if (controllers[0]) controllers[0]->UpdateMotors();
        lastMode = 0;
    }
}

int PadBackend::GetState(unsigned port){if(port>=2)return 0;return state[port];}

int PadBackend::GetHandle(unsigned port){if(port>=2)return 0;return handles[port];}

void PadBackend::SetFeedback(int enabled){if(enabled!=feedback){Controller **it=controllers;feedback=enabled;int i=1;do{if(*it)(*it)->SetFeedback(feedback);--i;++it;}while(i>=0);}}
