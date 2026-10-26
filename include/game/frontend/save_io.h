#ifndef GAME_FRONTEND_SAVE_IO_H
#define GAME_FRONTEND_SAVE_IO_H
#include "ps2/prelude.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Native asynchronous save-I/O view. The two information buffers have distinct
 * roles; only the directory entry's size and attribute accesses are identified.
 * UNVERIFIED: fields used only by drafts are not yet confirmed by exact source. */
typedef union {
    s32 word;
    u8 lowByte; // UNVERIFIED: the read permission check remains a draft.
} SaveIoOpenFlags;

typedef struct {
    u8 unk_00[0x10];
    s32 size;
    u16 attributes;
    u8 unk_16[0x22];
} Recovered_SaveEntry;

typedef struct {
    s32 reportedStatus;
    char path[72]; // UNVERIFIED: buffer extent follows the open-flags boundary.
    SaveIoOpenFlags openFlags;
    s32 operation;
    s32 handle;
    s32 error;
    u8 information[0x38];
    Recovered_SaveEntry entry;
    s32 entryCount;
    s32 deviceType;
    s32 formatted;
    s32 freeBlocks;
} Recovered_SaveIo;

/* UNVERIFIED parameter prefix: the consumer reads these four words. The
 * initializer leaves the fourth untouched; its complete local extent is open. */
typedef struct {
    s32 unk_00, unk_04, unk_08, unk_0C;
} Recovered_SaveIoParameters;
typedef char SaveIoPrefixSize[sizeof(Recovered_SaveIo) == 0xDC ? 1 : -1];
typedef char SaveIoEntryOffset[(u32) & ((Recovered_SaveIo*)0)->entry == 0x94 ? 1 : -1];
typedef char SaveEntrySize[sizeof(Recovered_SaveEntry) == 0x38 ? 1 : -1];

/* Names are descriptive. Numeric commands and raw error codes belong to the
 * native socket protocol; its complete SDK interface has not been recovered. */
s32 SaveIo_GetStatus(s32* status);
void SaveIo_SetStatus(s32* status, s32 value);
s32 SaveIo_GetError(void* io);
void SaveIo_SetError(void* io, s32 error);
s32 SaveIo_QueryEntry(Recovered_SaveIo* io, const char* path);
s32 SaveIo_GetFreeBytes(void* io);

s32 SaveIo_Initialize(Recovered_SaveIo* io);
s32 SaveIo_SubmitPathInfo(Recovered_SaveIo* io, const char* path);
s32 SaveIo_CloseFile(Recovered_SaveIo* io);
s32 SaveIo_Read(Recovered_SaveIo* io, void* buffer, s32 size, s32 offset);
s32 SaveIo_Write(Recovered_SaveIo* io, void* buffer, s32 size, s32 offset);
s32 SaveIo_RequestFormat(Recovered_SaveIo* io);
s32 SaveIo_SubmitPathCommand(Recovered_SaveIo* io, const char* path);
s32 SaveIo_Poll(Recovered_SaveIo* io, s32 mode, s32* output);
s32 SaveIo_MapPendingCommand(Recovered_SaveIo* io, s32 command);
s32 SaveIo_MapAuxiliaryResult(Recovered_SaveIo* io, s32 status);
s32 SaveIo_MapDeviceResult(Recovered_SaveIo* io, s32 status);
s32 SaveIo_MapEntryResult(Recovered_SaveIo* io, s32 status, s32* output);
s32 SaveIo_DispatchResult(Recovered_SaveIo* io, s32 command, s32 status, s32* output);
s32 SaveIo_RefreshDevice(Recovered_SaveIo* io);
#ifdef __cplusplus
}
#endif
#endif
