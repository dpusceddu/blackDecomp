#include "include_asm.h"
#include "game/aligned_buffer.h"
#include "game/effects/random_state.h"
#include "game/stream_buffer.h"
#include "game/audio_runtime.h"
#include "game/frontend_resources.hpp"
#include "apt/apt_value.hpp"

#include "game/graphics/sound_envelopes.hpp"
using namespace Graphics;

// Partial native sound views; original class names and the unused fields are UNVERIFIED.
struct Recovered_RandomSound {
    unsigned char unknown00[0x248];
    BkEffectRandomStatePS2 random;
    int unknown250;
    unsigned char unknown254[0x38];
    float unknown28C;
    unsigned char enabled, unknown291;
};

struct Recovered_SoundPlayback {
    unsigned char pool[0x244];
    int state;
    Recovered_StreamBuffer* pending;
    void* bank;
    float gain;
    unsigned char stereo;
};
typedef char SoundPlaybackStateOffset[(u32) & ((Recovered_SoundPlayback*)0)->state == 0x244 ? 1 : -1];

// Partial native handle view. Generation checks and invalidation are confirmed
// by the consumers below; original identities, unused bytes and the byte-result typedef are UNVERIFIED.
struct Recovered_SoundHandleTarget {
    u8 unknown00[8];
    int generation;
};
struct Recovered_SoundHandle {
    int unknown00;
    u8 valid;
    u8 unknown05[3];
    Recovered_SoundHandleTarget* object;
    int generation;
};
typedef char SoundHandleObjectOffset[(u32) & ((Recovered_SoundHandle*)0)->object == 8 ? 1 : -1];
typedef char SoundHandleGenerationOffset[(u32) & ((Recovered_SoundHandle*)0)->generation == 12 ? 1 : -1];

// Partial initializer descriptors; original types, callback roles and untouched bytes are UNVERIFIED.
struct Recovered_AudioMemoryCallbacks {
    int (*allocate)(int);
    void (*reset)();
    int (*first)();
    int (*second)();
};
struct Recovered_AudioBackendCallbacks {
    int (*first)();
    void (*reset)();
    int (*second)();
};
struct Recovered_AudioRuntimeBinding {
    int unknown00;
    void* device;
    void* bank;
    unsigned char unknown0C[0x2C];
    void* deviceCopy;
};
struct Recovered_AudioRuntimeSizes {
    unsigned char unknown00[0x10];
    int first, second;
};
typedef char AudioMemoryCallbackSize[sizeof(Recovered_AudioMemoryCallbacks) == 0x10 ? 1 : -1];
typedef char AudioBackendCallbackSize[sizeof(Recovered_AudioBackendCallbacks) == 0xC ? 1 : -1];
typedef char AudioRuntimeBindingSize[sizeof(Recovered_AudioRuntimeBinding) == 0x3C ? 1 : -1];

// Partial indexed sound-object collection. The native callback receives its
// signed this adjustment and the index; its ignored return contract and original identities are UNVERIFIED.
struct Recovered_SoundIndexVtable {
    u8 unknown00[8];
    s16 adjustment;
    u16 unknown0A;
    int (*setIndex)(void*, u32);
};
struct Recovered_SoundIndexedObject {
    u8 unknown00[0x60];
    Recovered_SoundIndexVtable* vtable;
};
struct Recovered_SoundObjectList {
    Recovered_SoundIndexedObject* objects[2];
    u32 count;
};
typedef char SoundIndexedVtableOffset[(u32) & ((Recovered_SoundIndexedObject*)0)->vtable == 0x60 ? 1 : -1];
typedef char SoundObjectCountOffset[(u32) & ((Recovered_SoundObjectList*)0)->count == 8 ? 1 : -1];

struct Recovered_SoundBankSizes {
    unsigned char unknown00[8];
    int first, second;
};

// Only the fields used by these playback requests are modeled. Flag meanings,
// untouched storage and the original parameter-class identity are UNVERIFIED.
struct Recovered_SoundParameters {
    unsigned char unknown00[0x50];
    void* sound;
    float gain;
    int unknown58;
    unsigned char unknown5C[4];
    float pan;
    unsigned char unknown64[0x24];
    float unknown88, unknown8C, unknown90, unknown94, unknown98, unknown9C;
    unsigned char unknownA0[4];
    unsigned flags;
    unsigned char kind, unknownA9, unknownAA, enabled;
    unsigned char unknownAC[4];
    Recovered_SoundParameters() : flags(0) {}
};
typedef char SoundParameterSize[sizeof(Recovered_SoundParameters) == 0xB0 ? 1 : -1];

typedef void (*Recovered_SoundMixFunction)(void*, void*, void*, float, float, float);
typedef void (*Recovered_SoundFinishFunction)(void*, void*, void*);
typedef void (*Recovered_SoundNotifyFunction)(int, int, int, int, int, void*, int, void*);
struct Recovered_SoundMixChannel {
    Recovered_SoundMixFunction function;
    void* context;
};
struct Recovered_SoundMixConfiguration {
    void* first;
    void* second;
    Recovered_SoundMixChannel channels[4];
    Recovered_SoundFinishFunction finish;
    void* context;
    Recovered_SoundNotifyFunction notify;
    void* device;
    unsigned char enabled;
};
typedef char SoundMixConfigurationSize[sizeof(Recovered_SoundMixConfiguration) == 0x3C ? 1 : -1];

extern "C" {

int func_001D5E10(int);
void func_001D5E50();
int func_001D5E40();
int func_001D5E48();
void func_002859F8(void*, int, int, int, Recovered_AudioMemoryCallbacks*);
extern FrontendCallbackQueue* D_0040F4C4;
int func_00324650();
void func_003676F0(int, int);
void func_00285AD0(void*, int);
void func_00286410(void*, int, int);
void func_00283108(void*, Recovered_AudioRuntimeBinding*);
int func_002859A0();
void func_002859B8();
int func_002859D0();
void func_00328CC0(Recovered_AudioBackendCallbacks*);
extern void* D_003BDA5C;
int func_00282008(void*, void*, int, int, int, int);

// Callback signatures and configuration field roles remain UNVERIFIED.
void func_00285CC8(void*, void*, void*, float, float, float);
void func_00285EE8(void*, void*, void*);
void func_001D7100(int, int, int, int, int, void*, int, void*);
int func_00285B60(void*, Recovered_SoundMixConfiguration*);
void ConfigureSoundStream(void*, int, int, float, float, float) __asm__("func_00285C60");
void func_00285C40(void*);
void func_00285C80(void*);
void* func_00285510(void*);
void* func_00285548(void*);
int func_00280A38(void*, void**, int);
void* func_0027FCF8(void*, const EeU64*, int);
void* func_00280BC0(void*);
void func_00283E78(void*, Recovered_SoundParameters*, void*);
int func_002851E0(void*);
void func_00285190(void*);
void func_00285258(void*, void*);
extern float D_003BDA4C, D_003BDA50, D_003BDA54, D_003BDA58;
Recovered_StreamBuffer* func_001D8478(void*);
void func_001D84C8(void*, Recovered_StreamBuffer*);
Recovered_SoundBankSizes* func_001E89B0(void*, EeU64);
void* func_0027FF78(void*, const char*, int, void*, int, int, int, void*, int);
void func_00382348(void*, int);
int func_00280A08(void*);
int func_00280B10(void*);
int func_00280100(void*, void*);
int func_0035D728(char*, const char*, ...);
void* func_0035CBC0(void*, const void*);
u32 func_0035CCD8(const void*);
void func_001EF8D0(Recovered_SoundPlayback*, const char*);
void func_001EF9C0(Recovered_SoundPlayback*, const char*);
EeU64 func_002723B0(const char*);
void func_00280CD0(void*, EeU64);
extern const char D_003F8BD8[], D_003F8BE0[], D_003F8BE8[];
}

static inline u8 SoundHandleValid(Recovered_SoundHandle* self) {
    if (self->valid && self->object && self->object->generation == self->generation && func_002851E0(self->object)) {
        return 1;
    }
    self->valid = 0;
    return 0;
}

int LowHealthEnvelope::Begin(float value,unsigned useEndpoint)
{
    if(!initialized)func_001ED9C8(this,D_003BDA18,0);
    endpoint=high;ratio=low/high;
    ActivateEnvelopeWithArguments(this,value,useEndpoint);
    func_001EFE70(this,1);
    state=1;
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: five instruction differences: byte-store scheduling and a repeated constant.
extern "C" int func_001EE888(Recovered_RandomSound* self) {
    func_00382348(&self->random, 0x2B9D6F8);
    func_00280A08(self);
    self->unknown250 = 0;
    self->enabled = 1;
    self->unknown28C = 0.0f;
    self->unknown291 = 0;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001EE888);
#endif
extern "C" int func_001EF548(Recovered_SoundPlayback* self, void** resources, int count, const char* name, int stereo,
                             void* context) {
    switch (self->state) {
        case 0: self->state = 5;
        case 5:
            if (!func_00280A38(self, resources, count)) return 0;
            self->pending = func_001D8478(*(void**)(SoundStateSource() + 0xCBD4));
            self->state = 1;
        case 1: {
            Recovered_StreamBuffer* buffer = self->pending;
            unsigned char* runtime = SoundStateSource();
            void* data = buffer->data;
            int bytes = buffer->blockCapacity << 11;
            int first = func_001E89B0(*(void**)(runtime + 0xCBD8), 0x6C51001C37800000UL)->first;
            int second = func_001E89B0(*(void**)(SoundStateSource() + 0xCBD8), 0x6C51001C37800000UL)->second;
            self->bank = func_0027FF78(runtime, name, 0, data, bytes, first, second, context, 0);
            if (!self->bank) return 0;
            func_001D84C8(*(void**)(SoundStateSource() + 0xCBD4), self->pending);
            self->state = 2;
            self->stereo = stereo;
            self->pending = 0;
        }
        case 2:
        default: return 1;
    }
}
extern "C" int func_001EF710(Recovered_SoundPlayback* self) {
    switch (self->state) {
        case 2: self->state = 3;
        case 3:
            if (!func_00280B10(self)) return 0;
            self->state = 4;
        case 4:
            if (!func_00280100(D_0040F510, self->bank)) return 0;
            self->bank = 0;
            self->state = 5;
        case 0: self->state = 5;
        case 1:
        case 5:
        default: return 1;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001EF7A8);
extern "C" void func_001EF7B0(Recovered_SoundPlayback* self, const char* name) {
    char key[16];
    func_0035D728(key, D_003F8BD8, name);
    if (self->stereo) {
        func_001EF9C0(self, key);
    } else {
        func_001EF8D0(self, key);
    }
}
extern "C" void func_001EF808(Recovered_SoundPlayback* self, const char* name) {
    char key[16];
    func_0035D728(key, D_003F8BD8, name);
    if (self->stereo) {
        char left[16];
        char right[16];
        func_0035D728(left, D_003F8BE0, key);
        func_0035D728(right, D_003F8BE8, key);
        EeU64 leftKey = func_002723B0(left);
        EeU64 rightKey = func_002723B0(right);
        func_00280CD0(self, leftKey);
        func_00280CD0(self, rightKey);
    } else {
        func_00280CD0(self, func_002723B0(key));
    }
}
extern "C" void func_001EF8D0(Recovered_SoundPlayback* self, const char* name) {
    Recovered_SoundParameters parameters;
    EeU64 key = func_002723B0(name);
    void* sound = func_0027FCF8(self->bank, &key, 0);
    if (sound) {
        parameters.sound = sound;
        parameters.gain = 1.0f;
        parameters.kind = 0x10;
        parameters.flags = 0x85C;
        parameters.pan = 0.0f;
        parameters.unknown58 = 0;
        if (SoundStateSource()[0xCB9D]) {
            parameters.unknown88 = D_003BDA4C;
            parameters.unknown8C = D_003BDA50;
            parameters.unknown90 = D_003BDA4C;
            parameters.unknown94 = D_003BDA54;
            parameters.unknown98 = D_003BDA58;
            parameters.unknown9C = D_003BDA58;
            parameters.enabled = 1;
            parameters.flags |= 0x800000;
        }
        func_00283E78(func_00280BC0(self), &parameters, 0);
    }
}
#ifdef NON_MATCHING
// Unmatched: flag reloads fold away and parameter-address lifetimes differ (49 instructions).
extern "C" void func_001EF9C0(Recovered_SoundPlayback* self, const char* name) {
    Recovered_SoundParameters leftParameters;
    Recovered_SoundParameters rightParameters;
    char left[16], right[16];
    func_0035D728(left, D_003F8BE0, name);
    func_0035D728(right, D_003F8BE8, name);
    EeU64 leftKey = func_002723B0(left);
    EeU64 rightKey = func_002723B0(right);
    if (self->bank) {
        void* leftSound = func_0027FCF8(self->bank, &leftKey, 0);
        void* rightSound = func_0027FCF8(self->bank, &rightKey, 0);
        float gain = self->gain;
        leftParameters.flags = 0x84C;
        rightParameters.sound = rightSound;
        leftParameters.kind = 0x10;
        leftParameters.sound = leftSound;
        leftParameters.pan = -1.0f;
        rightParameters.gain = gain;
        leftParameters.gain = gain;
        rightParameters.pan = 1.0f;
        rightParameters.kind = 0x10;
        rightParameters.flags = 0x84C;
        leftParameters.unknown58 = 0;
        leftParameters.flags |= 0x10;
        rightParameters.unknown58 = 0;
        rightParameters.flags |= 0x10;
        if (SoundStateSource()[0xCB9D]) {
            leftParameters.flags |= 0x800000;
            rightParameters.unknown8C = D_003BDA50;
            rightParameters.unknown90 = D_003BDA4C;
            rightParameters.unknown94 = D_003BDA54;
            rightParameters.unknown9C = D_003BDA58;
            rightParameters.enabled = 1;
            rightParameters.flags |= 0x800000;
            leftParameters.unknown88 = D_003BDA4C;
            leftParameters.unknown8C = D_003BDA50;
            leftParameters.unknown90 = 0.0f;
            leftParameters.unknown94 = D_003BDA54;
            leftParameters.unknown98 = D_003BDA58;
            leftParameters.unknown9C = 0.0f;
            leftParameters.enabled = 1;
            rightParameters.unknown88 = 0.0f;
            rightParameters.unknown98 = 0.0f;
        }
        void* leftChannel = func_00280BC0(self);
        void* rightChannel = func_00280BC0(self);
        func_00283E78(leftChannel, &leftParameters, 0);
        func_00283E78(rightChannel, &rightParameters, 0);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001EF9C0);
#endif
#ifdef NON_MATCHING
// Unmatched: nine instruction differences in virtual-call registers and descriptor-store scheduling.
extern "C" int func_001EFBA0(Recovered_AudioRuntime* self) {
    Recovered_AudioMemoryCallbacks memory;
    Recovered_AudioBackendCallbacks backend;
    Recovered_AudioRuntimeBinding binding;
    memory.allocate = func_001D5E10;
    memory.reset = func_001D5E50;
    memory.first = func_001D5E40;
    memory.second = func_001D5E48;
    func_002859F8(self, 9, 0xAE00, 0x3000, &memory);
    D_0040F4C4->Signal();
    int thread = func_00324650();
    func_003676F0(thread, D_0040F4C4->Poll() + 2);
    self->vtable->unk_20.function((u8*)self + self->vtable->unk_20.thisAdjustment);
    self->vtable->unk_28.function((u8*)self + self->vtable->unk_28.thisAdjustment);
    func_00285AD0(self->unk_CBE0, 0);
    Recovered_AudioRuntimeSizes* sizes = (Recovered_AudioRuntimeSizes*)AudioRuntime_Global->unk_CBDC;
    func_00286410((u8*)AudioRuntime_Global->unk_CBE0 + 0x1C0, sizes->second, sizes->first);
    binding.device = self->driver;
    binding.bank = (u8*)self + 0xCB7C;
    binding.deviceCopy = self->driver;
    binding.unknown00 = 0;
    func_00283108(self, &binding);
    backend.first = func_002859A0;
    backend.reset = func_002859B8;
    backend.second = func_002859D0;
    func_00328CC0(&backend);
    return func_00282008(*(void**)((u8*)self + 0xCBF4), D_003BDA5C, 0x1EFD80, 0x70000, 0x17FD80, 0x40);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001EFBA0);
#endif
static inline int StartSoundMix(unsigned char* self, void* stream, Recovered_SoundMixConfiguration* configuration) {
    if (!func_00285B60(stream, configuration)) return 0;
    ConfigureSoundStream(*(void**)(self + 0xCBE0), 1, 0, 1.0f, 1.0f, 1.0f);
    func_00285C40(*(void**)(self + 0xCBE0));
    return 1;
}
extern "C" int func_001EFD30(unsigned char* self) {
    Recovered_SoundMixConfiguration configuration;
    configuration.first = 0;
    configuration.second = 0;
    configuration.channels[0].function = func_00285CC8;
    unsigned char* stream = *(unsigned char**)(self + 0xCBE0);
    void* channel1 = stream + 0x70;
    void* channel2 = stream + 0xE0;
    void* channel3 = stream + 0x150;
    configuration.channels[0].context = stream;
    configuration.channels[1].function = func_00285CC8;
    configuration.channels[1].context = channel1;
    configuration.channels[2].function = func_00285CC8;
    configuration.channels[2].context = channel2;
    configuration.channels[3].function = func_00285CC8;
    configuration.channels[3].context = channel3;
    configuration.finish = func_00285EE8;
    configuration.context = 0;
    void** deviceSlot = (void**)(*(unsigned char**)(self + 0xCBD8) + 0xC);
    configuration.notify = func_001D7100;
    configuration.device = *deviceSlot;
    configuration.enabled = 1;
    return StartSoundMix(self, stream, &configuration);
}
extern "C" int func_001EFE70(void* unused, int useEnvelope) {
    Recovered_SoundMixConfiguration configuration;
    func_00285C80(SoundFilter());
    configuration.channels[0].function = func_00285CC8;
    configuration.channels[0].context = SoundFilter();
    configuration.channels[1].function = func_00285CC8;
    configuration.channels[1].context = (unsigned char*)SoundFilter() + 0x70;
    configuration.channels[2].function = func_00285CC8;
    configuration.channels[2].context = (unsigned char*)SoundFilter() + 0xE0;
    configuration.channels[3].function = func_00285CC8;
    configuration.channels[3].context = (unsigned char*)SoundFilter() + 0x150;
    configuration.finish = func_00285EE8;
    configuration.context = 0;
    configuration.notify = func_001D7100;
    configuration.device = *(void**)((unsigned char*)*(void**)(SoundStateSource() + 0xCBD8) + 0xC);
    configuration.enabled = 1;
    if (useEnvelope) {
        configuration.first = func_00285510(SoundStateSource() + 0xB308);
        configuration.second = func_00285548(SoundStateSource() + 0xB308);
    } else {
        configuration.first = 0;
        configuration.second = 0;
    }
    func_00285B60(SoundFilter(), &configuration);
    ConfigureSoundStream(SoundFilter(), 1, 0, 1.0f, 1.0f, 1.0f);
    func_00285C40(SoundFilter());
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001F09C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001F1110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001F1220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001F1258);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001FC6C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001FC820);
extern "C" s128 D_0042C4F0;
extern "C" char D_0042C7C8, D_0042C770;
extern "C" void func_002765B0(void*, void*, void*);
// UNVERIFIED: array bounds and original type are inferred from field offsets.
struct Recovered_CommandContainer {
    u8 pad[0xE8];
    void* records[8];
    void* values[37];
    u8 flags[1];
};
extern "C" void func_001FC9A8(Recovered_CommandContainer* object, s16 index) {
    object->flags[index] = 0;
    *(float*)((char*)object->values[index] + 0xC) = 0.1f;
    *(s128*)((char*)object->records[index] + 0x10) = D_0042C4F0;
    func_002765B0(object->records[index], &D_0042C7C8, &D_0042C770);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_001FCA20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002041F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00204450);
// UNVERIFIED: original type and fields other than the observed offsets.
struct Recovered_SoundDispatch {
    u8 unknown00[0x10];
    s16 index;
    s8 bank;
    u8 unknown13[5];
    s32 value;
};
extern "C" s32 D_0040F518;
extern "C" void func_00278F00(void*, s32, s32);
extern "C" int func_002048D0(Recovered_SoundDispatch* self) {
    func_00278F00((void*)(self->bank * 0xA8 + D_0040F518 + 0x40), self->index, self->value);
    return 1;
}
extern "C" FrontendResourceTable D_0040F0F0;
extern "C" void* func_00107D20(u32);
extern "C" void func_00275000(void*, void*, s32);
#ifdef NON_MATCHING
// Unmatched: call setup and saved-register scheduling differ.
extern "C" u32 func_00209378(void* object) {
    int selected = D_0040F0F0.selectedIndex;
    D_0040F0F0.ClearSelection();
    D_0040F0F0.SelectBuffer(15);
    func_00275000(object, func_00107D20(0x1000), 0x1000);
    func_00275000((char*)object + 0x518, func_00107D20(0xA000), 0xA000);
    D_0040F0F0.ClearSelection();
    u32 result = D_0040F0F0.SelectBuffer(selected);
    *(int*)((char*)object + 0xA30) = 1;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00209378);
#endif
// UNVERIFIED: original type and fields other than state.
struct Recovered_StateA30 { char unknown[0xA30]; int state; };
#ifdef NON_MATCHING
// Unmatched: section is eight bytes shorter despite matching instructions.
extern "C" int func_00209430(Recovered_StateA30* object) {
    switch (object->state) {
    case 1:
    case 0x38:
        object->state = 2;
    case 2:
        object->state = 0x1C;
    case 0x1C:
        break;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00209430);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00209490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00218898);
extern "C" void* D_0043DF68;
extern "C" void* D_0043DF74;
extern "C" const char D_003FCEA0[];
extern "C" void func_00232638(void*);
extern "C" int func_00249810(void*, int, const char*);
#ifdef NON_MATCHING
// Unmatched: owned read-only data placement changes the linked image.
extern "C" void func_0021AFE0() {
    func_00232638(D_0043DF68);
    if (D_0043DF74 != 0) {
        func_00249810(D_0043DF74, 0, D_003FCEA0);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021AFE0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021B020);
extern "C" unsigned char D_003FD110[];
extern "C" int func_0021B048(void* object) {
    unsigned type = *(unsigned*)object >> 25;
    if (type == 0x25) return *(int*)((char*)object + 0xC);
    return D_003FD110[type];
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021BB00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021BDB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021BEE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021C058);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021C268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021C740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021CB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021CC70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021CC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021D188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021D348);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0021D4E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00224270);
// UNVERIFIED: original identities and callback semantics.
struct Recovered_ResetVtable { u8 unknown[0x10]; s16 adjustment; u16 unknown12; void (*reset)(void*); };
struct Recovered_ResetObject { int unknown; Recovered_ResetVtable* vtable; };
struct Recovered_ResetOwner { u8 unknown[0x2C]; Recovered_ResetObject* object; };
extern "C" Recovered_ResetObject* D_0043DF40;
extern "C" void func_00224590() {
    Recovered_ResetObject* object = ((Recovered_ResetOwner*)D_0043DF68)->object;
    if (object) object->vtable->reset((char*)object + object->vtable->adjustment);
    ((Recovered_ResetOwner*)D_0043DF68)->object = D_0043DF40;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002245F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00224788);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002249E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00224B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00224D20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00224EE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00225030);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00225270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00225490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00225650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002257D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00225958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00225C30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00226060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002263A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00226BB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00227830);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00228BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00229370);
// UNVERIFIED: original types and callback semantics.
struct Recovered_StackVtable {
    u8 unknown[8];
    s16 adjustment;
    u16 unknown0A;
    void (*invoke)(void*);
    s16 releaseAdjustment;
    u16 unknown12;
    void (*release)(void*);
};
struct Recovered_StackObject { int unknown; Recovered_StackVtable* vtable; };
struct Recovered_ObjectStack {
    int count, unknown;
    Recovered_StackObject** objects;
    u8 unknown0C[0x2C];
    Recovered_StackObject** lookup;
};
extern "C" void func_00229700(Recovered_ObjectStack* self) {
    int index = self->count;
    Recovered_StackObject* object = self->objects[index - 1];
    self->objects[index] = object;
    self->count = index + 1;
    object->vtable->invoke((char*)object + object->vtable->adjustment);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00229748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002297C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00229BB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00229F40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022A1C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022A440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022AE88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022B0A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022B290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022B480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022B670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022B860);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022BA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022BFB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022C368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022C468);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022C6A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022C810);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022C908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022CA00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022CB30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022CFE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022D198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022D2D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022D3C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022D570);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022D8E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022DA38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022DB88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022DC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022DD88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022DE90);
extern "C" void func_0022DF90(Recovered_ObjectStack* self) {
    int index = self->count;
    Recovered_StackObject* object = (Recovered_StackObject*)D_0043DF40;
    self->objects[index] = object;
    self->count = index + 1;
    object->vtable->invoke((char*)object + object->vtable->adjustment);
}
extern "C" void func_0022DFE0(Recovered_ObjectStack* self) {
    int index = self->count;
    Recovered_StackObject* object = (Recovered_StackObject*)D_0043DF40;
    self->objects[index] = object;
    self->count = index + 1;
    object->vtable->invoke((char*)object + object->vtable->adjustment);
}
extern "C" void func_00225030(void*, void*);
extern "C" void func_0022A440(void*, void*);
extern "C" void func_00252B10(AptViews::PendingValues*);
extern "C" void func_0022E030(Recovered_ObjectStack* self, void* arg) {
    func_00225030(self, arg);
    if (self->count > 0) {
        Recovered_StackObject* object = self->objects[self->count - 1];
        object->vtable->release((char*)object + object->vtable->releaseAdjustment);
        self->count--;
    }
    if (AptViews::D_003BE8E0->count != 0 && self->count == 0) func_00252B10(AptViews::D_003BE8E0);
}
extern "C" void func_00223678(void*, void*);
extern "C" void func_00252B10(AptViews::PendingValues*);
extern "C" void func_00225030(void*, void*);
extern "C" void func_0022E0B8(void** self, void* arg) {
    func_00225030(self, arg);
    func_00223678(self, arg);
    if (AptViews::D_003BE8E0->count != 0 && *self == 0) func_00252B10(AptViews::D_003BE8E0);
}
extern "C" void func_0022E120(Recovered_ObjectStack* self, void* arg) {
    func_0022A440(self, arg);
    if (self->count > 0) {
        Recovered_StackObject* object = self->objects[self->count - 1];
        object->vtable->release((char*)object + object->vtable->releaseAdjustment);
        self->count--;
    }
    if (AptViews::D_003BE8E0->count != 0 && self->count == 0) func_00252B10(AptViews::D_003BE8E0);
}
extern "C" void func_0022A440(void*, void*);
extern "C" void func_0022E1A8(void** self, void* arg) {
    func_0022A440(self, arg);
    func_00223678(self, arg);
    if (AptViews::D_003BE8E0->count != 0 && *self == 0) func_00252B10(AptViews::D_003BE8E0);
}
// UNVERIFIED: source descriptor and constructor parameter meanings.
struct Recovered_StackInput { int unknown; void* data; int size; };
extern "C" char D_0043DC18[];
extern "C" Recovered_StackObject* func_0021E420(Recovered_ObjectStack*, void*, int, void*, int, int, int);
#ifdef NON_MATCHING
// Unmatched: global address and offset are folded into one relocation.
extern "C" void func_0022E210(Recovered_ObjectStack* self, Recovered_StackInput* input) {
    Recovered_StackObject* object = func_0021E420(self, input->data, input->size, D_0043DC18 + 0x290, 1, 1, 0);
    int index = self->count;
    self->objects[index] = object;
    self->count = index + 1;
    object->vtable->invoke((char*)object + object->vtable->adjustment);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022E210);
#endif
extern "C" Recovered_StackObject* D_003BFABC;
extern "C" void func_0022E288(Recovered_ObjectStack* self) {
    int index = self->count;
    Recovered_StackObject* object = D_003BFABC;
    self->objects[index] = object;
    self->count = index + 1;
    object->vtable->invoke((char*)object + object->vtable->adjustment);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022E2D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022E3E8);
extern "C" void func_0022E590(Recovered_ObjectStack* self, u8** cursor) {
    u8 index = *(*cursor)++;
    int count = self->count;
    Recovered_StackObject* object = self->lookup[index];
    self->objects[count] = object;
    self->count = count + 1;
    object->vtable->invoke((char*)object + object->vtable->adjustment);
}
extern "C" void func_0022E5F8(Recovered_ObjectStack* self, u8** cursor) {
    u8* bytes = *cursor;
    unsigned low = *bytes++;
    unsigned high = *bytes++;
    *cursor = bytes;
    unsigned index = low | (high << 8);
    int count = self->count;
    Recovered_StackObject* object = self->lookup[index];
    self->objects[count] = object;
    self->count = count + 1;
    object->vtable->invoke((char*)object + object->vtable->adjustment);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022E670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022E798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022E958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022EB18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022ECD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022ED80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022EE08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022EEF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022EFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022F098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022F158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022F2D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022F3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022F508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022F648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022F728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022FA78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022FBE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022FE00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0022FFF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002303A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00230680);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00234758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00234A68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00234C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00234D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00234ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00235260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00235368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002356A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002357B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00235BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00235DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002361D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00236390);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00236440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00236508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00236668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002368E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00241B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00241BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00241C88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00241E90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024A7F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024A978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024AB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024AEF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024B178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024B3A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024B3B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024C4F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024C650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024C6D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0024CBB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002509E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00250DA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00250E98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00250FC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002516A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00259950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00259DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00268AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00268C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002697E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00269820);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00269880);
// UNVERIFIED: original type and virtual callback identity.
struct Recovered_NotifyVtable { u8 unknown[0x30]; s16 adjustment; u16 unknown32; int (*notify)(void*, int); };
struct Recovered_NotifyObject { u8 unknown[0x18]; int active; u8 unknown1C[0xC]; Recovered_NotifyVtable* vtable; };
extern "C" int func_002698F8(Recovered_NotifyObject* self) {
    if (!self->active) return 0;
    return self->vtable->notify((char*)self + self->vtable->adjustment, 0);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00269940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00269AB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00269CC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00269DF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026BA20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026BAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026CD28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026D378);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026D6F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026DA20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026DB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026DC70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026DC88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026E318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026E770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026ED40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026F0B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026F190);
extern "C" u8 D_0040DEB2;
extern "C" s32 D_003C0E00;
extern "C" s32 func_0029D000();
#ifdef NON_MATCHING
// Unmatched: initial global load and branch use different scheduling and registers.
extern "C" s32 func_0026F2E0() {
    if (D_0040DEB2 != 0) return D_003C0E00;
    return func_0029D000() == 2;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0026F2E0);
#endif
extern "C" int func_00367750();
extern "C" void func_00271368(int priority) {
    int thread = func_00367750();
    func_003676F0(thread, priority + 1);
}
// UNVERIFIED: original thread descriptor identity and untouched fields.
struct Recovered_ThreadDescriptor { int unknown; void* entry; void* stack; int stackSize; void* gp; int priority; };
extern "C" char D_004157F0[];
extern "C" int func_00367660(Recovered_ThreadDescriptor*);
extern "C" void func_00368738(int, void*);
#ifdef NON_MATCHING
// Unmatched: stack frame size and instruction scheduling differ.
extern "C" int func_00271398(void* entry, void* arg, void* stack, int stackSize, int priority) {
    Recovered_ThreadDescriptor desc;
    desc.entry = entry;
    desc.stack = stack;
    desc.stackSize = stackSize;
    desc.gp = D_004157F0;
    desc.priority = priority + 1;
    int thread = func_00367660(&desc);
    func_00368738(thread, arg);
    return thread;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00271398);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00271400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00271408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00271478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00271480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00271558);
extern "C" void func_002715F0();
extern "C" void func_003675E0(u32, void (*)(), int);
extern "C" void func_00367780();
extern "C" void func_00271610(u32 arg0) {
    int thread = func_00367750();
    func_003675E0(arg0 & 0xFFFF, func_002715F0, thread);
    func_00367780();
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00272300);
void* AlignedBuffer_Allocate(Recovered_AlignedBuffer* self, u32 bytes) {
    u32 cursor = (u32)self->cursor - 1;
    u32 alignment = self->alignment;
    u8* aligned = (u8*)((cursor + alignment) & -alignment);
    u8* next = aligned + bytes;
    if (self->end < next) {
        self->lastAllocation = NULL;
        return NULL;
    }
    self->cursor = next;
    self->lastAllocation = aligned;
    return aligned;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00275000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00275060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002750B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002775A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002778C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00277940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00277A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00277CB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00277FA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00278480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00278520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00278528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002789C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00278AD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027BD20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027BDC0);
// UNVERIFIED: original type and untouched fields.
struct Recovered_DisplayDefaults { int mode; float rate; u8 unknown08[8]; float scale; };
extern "C" Recovered_DisplayDefaults* D_003C0DF0;
#ifdef NON_MATCHING
// Unmatched: float constant load scheduling differs.
extern "C" void func_0027C2F8(Recovered_DisplayDefaults* self) {
    float rate = 20.0f;
    float scale = 0.5f;
    D_003C0DF0 = self;
    self->rate = rate;
    self->scale = scale;
    self->mode = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027C2F8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027C370);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027C3F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027CEA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027CF58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027CF78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027D020);

// UNVERIFIED: original types and callback semantics.
struct Recovered_CommandVtable {
    u8 unknown[8];
    s16 adjustment;
    u16 unknown0A;
    void (*dispatch)(void*, int, int, int, int);
};
struct Recovered_CommandTarget { u8 unknown[12]; Recovered_CommandVtable* vtable; };
struct Recovered_CommandSender { Recovered_CommandTarget* target; int value; };
extern "C" void func_0027D098(Recovered_CommandSender* self) {
    Recovered_CommandTarget* target = self->target;
    if (target) target->vtable->dispatch((char*)target + target->vtable->adjustment, 4, self->value, 0, 0);
}
extern "C" void func_0027D0D8(Recovered_CommandSender* self, int a, int b) {
    Recovered_CommandTarget* target = self->target;
    if (target) target->vtable->dispatch((char*)target + target->vtable->adjustment, 5, self->value, a, b);
}
// UNVERIFIED: original table identity and unused fields.
struct Recovered_OffsetEntry { s64 key; s32 offset; s32 unknown; };
struct Recovered_OffsetTable { u8 unknown[8]; Recovered_OffsetEntry* entries; };
extern "C" void* func_0027D118(Recovered_OffsetTable* self, s64 key) {
    Recovered_OffsetEntry* entry = self->entries;
    while (entry->key != 0) {
        if (entry->key == key) return (char*)self + entry->offset;
        entry++;
    }
    return 0;
}
extern "C" void func_0027D158(Recovered_CommandSender* self, int a, int b) {
    Recovered_CommandTarget* target = self->target;
    if (target) target->vtable->dispatch((char*)target + target->vtable->adjustment, 2, self->value, a, b);
}
extern "C" void func_0027D198(Recovered_CommandSender* self, int a, int b) {
    Recovered_CommandTarget* target = self->target;
    if (target) target->vtable->dispatch((char*)target + target->vtable->adjustment, 3, self->value, a, b);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_0027FBD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00280360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00280400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00280448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_002804F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00280500);
extern "C" int func_00280528(Recovered_SoundObjectList* self, u32 count) {
    self->count = count;
    for (u32 i = 0; i < count; i++) {
        Recovered_SoundIndexedObject* object = self->objects[i];
        object->vtable->setIndex((u8*)object + object->vtable->adjustment, i);
    }
    return 1;
}
extern "C" int func_00280E10(s8 input, u8* output) {
    int character = input;
    if ((u32)(character - 'A') < 26) {
        *output = character - 'A' + 10;
        return 1;
    }
    if ((u32)(character - 'a') < 26) {
        *output = character - 'a' + 10;
        return 1;
    }
    character -= '0';
    if ((u8)character < 10) {
        *output = character;
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00280E70);
extern "C" void func_00280E78(const char* source, s8* destination) {
    func_0035CBC0(destination, source);
    u32 length = func_0035CCD8(destination);
    for (u32 i = 0; i < length; i++, destination++) {
        if (*destination == '/') *destination = 0x5C;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00280EE0);
extern "C" u8 func_00281010(Recovered_SoundHandle* self, void* parameters) {
    u8 valid = SoundHandleValid(self);
    if (valid) func_00285258(self->object, parameters);
    return valid;
}
extern "C" u8 func_002810A0(Recovered_SoundHandle* self) {
    u8 valid = SoundHandleValid(self);
    if (valid) func_00285190(self->object);
    return valid;
}
extern "C" int func_00281120(Recovered_SoundHandle* self) {
    if (SoundHandleValid(self)) return func_002851E0(self->object);
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00281238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/audio/graphics_sound_1ee5e0", func_00281380);
