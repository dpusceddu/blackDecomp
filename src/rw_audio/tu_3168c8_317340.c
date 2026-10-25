#include "rw_audio/emitter.h"

#include "ps2/prototypes.h"

extern s32 D_0040E1C0;
extern void func_003175C8(RwaEmitter *);
extern s32 func_003105E8(void *, s32, s32, s32);
extern s32 func_00310698(void *, s32, s32, void *);

extern s32 func_00310768(void *, s32, s32, void *);
extern void * D_0040E780;
extern s32 D_0040E1BC;
extern void func_00317030(RwaEmitter *);

extern void func_00316E90(RwaEmitter *);
void func_00317340(RwaEmitter *input, u32 operation) {
    s32 active;
    u8 flags;
    void *handle;

    switch (operation) {
    case 1:
        active = input->flags & 1;
        if (active != 0) {
            input->previous->next = input->next;
            input->next->previous=input->previous;
            handle = input->handle;
            if (handle != NULL) {
                if (func_00310768(handle, 8, 2, NULL) != 0) {
                    func_003105E8(handle, 8, 1, 0);
                }
                func_00310698(handle, 0xB, 1, NULL);
                func_00310698(handle, 0xE, 1, NULL);
                input->handle = NULL;
            }
            input->previous = (RwaEmitter *)&D_0040E780;
            M2C_FIELD(input,void **,0)=D_0040E780;
            M2C_FIELD(D_0040E780, void **, 4) = input;
            D_0040E780 = input;
            D_0040E1BC -= 1;
            D_0040E1C0 -= input->channels;
            /* Preserve the reset scope and its matching loop-label setting. */
            do {
                input->channels = 0;
                flags = input->flags & 0xFC;
                input->level = 0;
                input->position_bytes = input->start_bytes;
            } while (0);
            input->flags = flags;
            return;
        }
        return;
    case 0:
        func_00316E90(input); return;
    case 2:
        active = input->flags & 1;
        if (active != 0) {
            func_00317030(input);
        }
        return;
    default:
        return;
    }
}
void func_003175C8(RwaEmitter *input) {
    s32 active;
    u8 flags;
    void *handle;

    active = input->flags & 1;
    if (active != 0) {
        input->previous->next = input->next;
        input->next->previous=input->previous;
        handle = input->handle;
        if (handle != NULL) {
            if (func_00310768(handle, 8, 2, NULL) != 0) {
                func_003105E8(handle, 8, 1, 0);
            }
            func_00310698(handle, 0xB, 1, NULL);
            func_00310698(handle, 0xE, 1, NULL);
            input->handle = NULL;
        }
        input->previous = (RwaEmitter *)&D_0040E780;
        M2C_FIELD(input,void **,0)=D_0040E780;
        M2C_FIELD(D_0040E780, void **, 4) = input;
        D_0040E780 = input;
        D_0040E1BC -= 1;
        D_0040E1C0 -= input->channels;
        /* Preserve the reset scope and its matching loop-label setting. */
        do {
            input->channels = 0;
            flags = input->flags & 0xFC;
            input->level = 0;
            input->position_bytes = input->start_bytes;
        } while (0);
        input->flags = flags;
        return;
    }
    return;
}
