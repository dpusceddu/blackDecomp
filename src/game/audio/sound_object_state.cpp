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
// SN omits extern object sizes at -O0; the assembler needs this byte's size for GP addressing.
__asm__(".extern D_0040DA30, 1");

struct SoundDataView {
    unsigned char unknown00[0x28];
    int bytes;
    short samples[1];
};
extern "C" void func_002726D0(EeU64, void*);
extern "C" int func_001D5EA8(void*, EeU64, EeU64, int, int);
extern "C" void func_001F0F28(RecoveredSoundObject*, int, unsigned char);

int func_001F03D0(register RecoveredSoundObject* self, EeU64 arg1, EeU64 arg2, void* data, int arg4, int arg5,
                  unsigned char special) {
    switch (self->field84) {
        case 7:
            func_002726D0(arg2, self->unknown64);
            if (special) self->unknown64[0] = 0x53;
            self->field410 = data;
            D_0040DA30 = 0;
            self->field1d0 = 0;
            for (int i = 0; i < 2; i++) self->field1ec[i] = 0;
            self->field1f4 = 0;
            self->field414 = (int)((SoundDataView*)self->field410)->samples;
            self->field1e4 = ((SoundDataView*)self->field410)->bytes;
            self->field1e4 -= self->field1e4 % 128;
            self->field1e8 = ((self->field414 + 127) / 128) * 128;
            D_0040DA30 = 1;
            self->field84 = 1;
        case 1:
            if (!func_001D5EA8(self, arg1, arg2, arg4, arg5)) break;
        case 2:
            func_001F0F28(self, 0, 0);
            self->field84 = 3;
        case 3:
            return 1;
            break; // The unoptimized native switch retains this case exit.
        case 0:
        case 4:
        case 5:
        case 6:
        case 8:
        default: break;
    }
    return 0;
}

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
