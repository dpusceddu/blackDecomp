#include "include_asm.h"
#include "game/audio/sound_object_fields.h"

extern "C" {
int func_001D5F58(void*);
void func_001D6038(void*, int);
void func_001D60B8(void*);
void func_001D6230(void*, int, unsigned char);
void func_001F0770(void*, float);
int func_00324F98(void);
extern unsigned char* D_0040F510;
void* func_00384858(void*);
void* func_003847E0(void*);
unsigned func_00286878(void*, short*, int, float, unsigned);
void func_001F07B8(void*, float);

extern unsigned char D_0040DA30;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/sound_object_state", func_001F03D0);

int func_001F05D0(register RecoveredSoundObject* self) {
    return func_001D5F58(self);
}

void func_001F0620(register RecoveredSoundObject* self, int value) {
    func_001F0770(self, self->field74);
    func_001D6038(self, value);
}

void func_001F0678(register RecoveredSoundObject* self) {
    D_0040DA30 = 0;
    if (!self->field41c) {
        if (self->field1d0) {
            int i = self->field60 - 1;
            while (i > 0) {
                self->field1ec[i] = self->field1ec[i - 1];
                i--;
            }
        }
        self->field1d0++;
        if (self->field1d0 > self->field60) self->field1d0 = self->field60;
        self->field1ec[0] = 0;
    }
    D_0040DA30 = 1;
    func_001D60B8(self);
}

void func_001F0F28(register RecoveredSoundObject* self, int mode, unsigned char active) {
    switch (mode) {
        case 0:
            self->field41c = 0;
            self->field1f4 = 0;
            break;
        case 1:
            self->field41c = 0;
            self->field1f4 = 0;
            break;
        case 2:
            self->field41c = 0;
            self->field1f4 = 1;
            break;
        case 3:
            self->field41c = 0;
            self->field1f4 = 0;
            break;
        default: break;
    }
    func_001D6230(self, mode, active);
}

void func_001F1018(register RecoveredSoundObject* self, float value) {
    float frequency = 6000.0f;
    func_00286878(func_003847E0(func_00384858(D_0040F510)), self->field210, 0x100, frequency, 0);
    self->field1e0 = self->field210;
    func_001F07B8(self, 0.0f);
}

bool func_001F10B8(register RecoveredSoundObject* self) {
    return func_00324F98() != 0;
}
}
