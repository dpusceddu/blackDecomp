#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001092F8();

void func_001ABEB8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x6C) = func_001092F8();
}

/* UNVERIFIED: original event and callback-owner class identities. */
typedef void (*AssetCallback)(u64, void*);
typedef struct CallbackOwner {
    u8 unknown[0x948];
    AssetCallback callbacks[10];
} CallbackOwner;
typedef struct CallbackDescriptor {
    s32 mode;
    u32 slot;
    s32 kind;
    const char* name;
} CallbackDescriptor;
typedef struct CallbackEvent {
    u8 unknown[8];
    u8 kind;
    u8 unknown9[3];
    CallbackDescriptor* descriptor;
} CallbackEvent;
extern u64 func_002723B0(const char*);
extern void* func_001AC040(void*);
extern void func_003528E0(void);
extern s32 D_003BFB28;
void func_001ABEE0(CallbackOwner* self, void* peer, CallbackEvent* event) {
    u8 kind = event->kind;
    if (kind == 2) {
        CallbackDescriptor* descriptor = event->descriptor;
        if (descriptor->mode == 0 || descriptor->kind == kind) {
            u32 slot = descriptor->slot;
            if (slot < 10) {
                u64 key = func_002723B0(descriptor->name);
                AssetCallback callback = self->callbacks[slot];
                if (callback) {
                    callback(key, func_001AC040(peer));
                    if (D_003BFB28 != 1) {
                        func_003528E0();
                        D_003BFB28 = 1;
                    }
                }
            }
        }
    }
}
