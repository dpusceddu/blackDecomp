#include "game/audio/sound_object_fields.h"

extern unsigned char* D_0040F510;
extern unsigned char D_0048FF50[];

void* memset(void*, int, unsigned);
void func_001D5E58(RecoveredSoundObject*, unsigned);
void func_001F0810(RecoveredSoundObject*, float);
void func_001F0958(RecoveredSoundObject*, float);
void func_001F1018(RecoveredSoundObject*, float);
void* func_00384858(void*);
void func_00384800(void*, float);
void* func_00388E18(void*);
float func_00384790(void*, int);
float func_00384880(void*);
int func_003848A8(void*, float);
float func_00384740(float, float, float);
void func_00286140(void*, float, float, void*, void*);
void func_002860F0(void*, float, void*, void*);

void func_001F0770(RecoveredSoundObject*, float);

void func_001F0320(register RecoveredSoundObject* self, unsigned value) {
    self->field84 = 7;
    self->field414 = 0;
    memset(&self->field1d0, 0, 0x30);
    func_001F0958(self, 1.0f);
    func_001F0770(self, 1.0f);
    self->field41c = 0;
    func_001F1018(self, 4125.0f);
    func_001D5E58(self, value);
}

void func_001F03C0(register RecoveredSoundObject* self) {
    self->field84 = 0;
}

void func_001F0770(register RecoveredSoundObject* self, float value) {
    func_001F0810(self, value);
    func_00384800(self, value);
}

void func_001F07B8(register RecoveredSoundObject* self, float value) {
    value = func_00384740(value, 0.0f, 1.0f);
    self->field1dc = func_003848A8(self, value);
}

void func_001F0810(register RecoveredSoundObject* self, float value) {
    register void* object = func_00388E18(D_0040F510);
    register float amplitude = func_00384790(object, 1);
    self->field424 = ((value * 0.6886523f) * self->field418 * amplitude) * func_00384880(D_0040F510);
    self->field1d4 = func_003848A8(self, self->field424);
    self->field1d8 = func_003848A8(self, self->field424 * 0.5f);
}

void func_001F08E8(register RecoveredSoundObject* self, float a, float b, float c) {
    func_00286140(func_00384858(D_0040F510), a, b, D_0048FF50, D_0048FF50);
    self->field418 = c;
}

void func_001F0958(register RecoveredSoundObject* self, float value) {
    self->field418 = 1.0f;
    func_002860F0(func_00384858(D_0040F510), value, D_0048FF50, D_0048FF50);
}
