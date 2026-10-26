#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/frontend/save_io.h"

extern s32 func_00355B40();

extern void SaveIo_SetError(void* io, s32 error);
extern s32 SaveIo_GetError(void* io);
extern s32 func_00355278(s32 flags);
extern s32 func_003554F8(Recovered_SaveIoParameters* parameters, void* context);
extern s32 func_00355708(s32 handle, const char* path, void* information);
extern s32 func_00355808(s32 handle, const char* path, void* buffer, s32 offset, s32 size);
extern s32 func_00355928(s32 handle, const char* path, void* buffer, s32 offset, s32 size);
extern s32 func_00355598(s32 handle);
extern s32 func_00355C70(s32 handle, const char* path);
extern s32 func_00356030(s32* command, s32* value);
extern s32 func_00356058(s32* command, s32* value);
extern s32 func_00355648(s32 handle, s32* deviceType);
extern u8 D_004405C0[];

#ifdef NON_MATCHING
// Unmatched: scalar instructions agree, but the native frame is 16 bytes larger.
s32 SaveIo_Initialize(Recovered_SaveIo* io) {
    s32 handle;
    s32 zero;
    s32* handleResult;
    Recovered_SaveIoParameters parameters;
    u8 failed;
    io->reportedStatus = 0;
    SaveIo_SetError(io, 0);
    if (func_00355278(0) != 0) return 0;
    parameters.unk_00 = 2;
    parameters.unk_04 = 2;
    zero = 0;
    parameters.unk_08 = zero;
    handleResult = &io->handle;
    io->handle = func_003554F8(&parameters, D_004405C0);
    handle = *handleResult;
    failed = handle < zero;
    return failed ^ 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_26f440", func_0026F440);
#endif

s32 SaveIo_GetStatus(s32 *arg0) {
    return *arg0;
}

void SaveIo_SetStatus(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

s32 SaveIo_GetError(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x58);
}

s32 SaveIo_SubmitPathInfo(Recovered_SaveIo* io, const char* path) {
    s32 success;
    if (func_00355708(io->handle, path, io->information) == 0)
        success = 1;
    else {
        SaveIo_SetError(io, 13);
        success = 0;
    }
    return success;
}

s32 SaveIo_QueryEntry(Recovered_SaveIo* io, const char* path) {
    s32 success;
    if (func_00355B40(io->handle, path, 0, 1, &io->entry, &io->entryCount) == 0)
        success = 1;
    else {
        SaveIo_SetError(io, 13);
        success = 0;
    }
    return success;
}

s32 SaveIo_GetFreeBytes(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xD8);
    if (temp_2 < 0) {
        return -1;
    }
    return temp_2 << 0xA;
}

s32 SaveIo_CloseFile(Recovered_SaveIo* io) {
    s32 success;
    if (io->openFlags.word) {
        io->openFlags.word = 0;
        io->operation = 5;
        success = 1;
    } else {
        SaveIo_SetError(io, 13);
        success = 0;
    }
    return success;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_26f440", func_0026F680);
#ifdef NON_MATCHING
// Unmatched: the error join retains an extra owner-argument copy.
s32 SaveIo_Read(Recovered_SaveIo* io, void* buffer, s32 size, s32 offset) {
    s32 success;
    if (((io->openFlags.lowByte ^ 1) & 1) == 0) {
        if (func_00355808(io->handle, io->path, buffer, offset, size) == 0)
            success = 1;
        else {
            SaveIo_SetError(io, 13);
            success = 0;
        }
    } else {
        SaveIo_SetError(io, 13);
        success = 0;
    }
    return success;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_26f440", func_0026F688);
#endif
#ifdef NON_MATCHING
// Unmatched: the error join retains an extra owner-argument copy.
s32 SaveIo_Write(Recovered_SaveIo* io, void* buffer, s32 size, s32 offset) {
    s32 success;
    if (io->openFlags.word & 2) {
        if (func_00355928(io->handle, io->path, buffer, offset, size) == 0)
            success = 1;
        else {
            SaveIo_SetError(io, 13);
            success = 0;
        }
    } else {
        SaveIo_SetError(io, 13);
        success = 0;
    }
    return success;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_26f440", func_0026F6E8);
#endif
#ifdef NON_MATCHING
// Unmatched: the initial guard fills a native empty delay slot.
s32 SaveIo_RequestFormat(Recovered_SaveIo* io) {
    s32 success;
    if (!io->formatted) {
        if (func_00355598(io->handle) == 0)
            success = 1;
        else {
            SaveIo_SetError(io, 13);
            success = 0;
        }
    } else {
        SaveIo_SetError(io, 13);
        success = 0;
    }
    return success;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_26f440", func_0026F748);
#endif
s32 SaveIo_SubmitPathCommand(Recovered_SaveIo* io, const char* path) {
    s32 success;
    if (func_00355C70(io->handle, path) == 0)
        success = 1;
    else {
        SaveIo_SetError(io, 13);
        success = 0;
    }
    return success;
}
#ifdef NON_MATCHING
// Unmatched: status publication has different argument setup and exit joins.
s32 SaveIo_Poll(Recovered_SaveIo* io, s32 mode, s32* output) {
    s32 command, value, status;
    if (io->operation == 5) {
        io->operation = 14;
        SaveIo_SetStatus((s32*)io, 0);
    } else {
        switch (mode) {
            case 0: status = func_00356030(&command, &value); break;
            case 1: status = func_00356058(&command, &value); break;
            default: goto error;
        }
        switch (status) {
            case 0: SaveIo_SetStatus((s32*)io, SaveIo_MapPendingCommand(io, command)); break;
            case 1: SaveIo_SetStatus((s32*)io, SaveIo_DispatchResult(io, command, value, output)); break;
            case -1:
                if (SaveIo_RefreshDevice(io))
                    SaveIo_SetStatus((s32*)io, 1);
                else
                    goto error;
                break;
            default: goto error;
        }
    }
    return SaveIo_GetStatus((s32*)io);
error:
    SaveIo_SetError(io, 13);
    SaveIo_SetStatus((s32*)io, 13);
    return SaveIo_GetStatus((s32*)io);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_26f440", func_0026F7E0);
#endif

void SaveIo_SetError(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0xE;
    M2C_FIELD(arg0, s32 *, 0xD8) = -1;
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = arg1;
    M2C_FIELD(arg0, s32 *, 0xD0) = 0;
    if (arg1 == 3) {
        M2C_FIELD(arg0, s32 *, 0xD4) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0xD4) = 1;
}

s32 SaveIo_MapPendingCommand(Recovered_SaveIo* io, s32 command) {
    switch (command) {
        case 7: return 4;
        case 5: return 7;
        case 6: return 8;
        case 11: return 10;
        case 8: return 6;
        case 3: return 9;
        case 10: return io->operation == 4 ? 4 : 11;
        case 14: return 12;
        case 2:
        default: return 1;
    }
}

s32 func_0026F9D0(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x6F:
    case 0x13:
        SaveIo_SetError(arg0, 1);
block_13:
        return 0xD;
    case 0x1C:
        SaveIo_SetError(arg0, 0xB);
        goto block_13;
    case 0x17:
        SaveIo_SetError(arg0, 0xC);
        goto block_13;
    default:
        SaveIo_SetError(arg0, 0xD);
        goto block_13;
    }
}

s32 func_0026FA70(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_5;

    if (arg1 >= 0) {
        if (arg2 != 0) {
            M2C_FIELD(arg2, s32 *, 0) = arg1;
        }
        return 0;
    }
    temp_5 = arg1 & 0xFFFF;
    if ((temp_5 == 0x13) || (temp_5 == 0x6F)) {
        SaveIo_SetError(arg0, 1);
    } else {
        SaveIo_SetError(arg0, 0xD);
    }
    return 0xD;
}

s32 func_0026FAD0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_5;

    if (arg1 >= 0) {
        if (arg2 != 0) {
            M2C_FIELD(arg2, s32 *, 0) = arg1;
        }
        return 0;
    }
    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x1C:
        SaveIo_SetError(arg0, 0xB);
        break;
    case 0x6F:
    case 0x13:
        SaveIo_SetError(arg0, 1);
        break;
    default:
        SaveIo_SetError(arg0, 0xD);
        break;
    }
    return 0xD;
}

s32 func_0026FB60(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 var_2;

    temp_5 = arg1 & 0xFFFF;
    if (temp_5 == 0x13) {
        goto block_5;
    }
    if (temp_5 >= 0x14) {
        goto block_4;
    }
    var_2 = 0;
    if (temp_5 == 0) {
        goto block_8;
    }
    goto block_6;
block_4:
    if (temp_5 != 0x6F) {
        goto block_6;
    }
block_5:
    SaveIo_SetError(arg0, 1);
    goto block_7;
block_6:
    SaveIo_SetError(arg0, 0xD);
block_7:
    var_2 = 0xD;
block_8:
    return var_2;
}

s32 SaveIo_MapAuxiliaryResult(Recovered_SaveIo* io, s32 status) {
    switch (status & 0xFFFF) {
        case 0: return 0;
        case 0x1C: SaveIo_SetError(io, 11); break;
        case 0x13:
        case 0x6F: SaveIo_SetError(io, 1); break;
        default: SaveIo_SetError(io, 13); break;
    }
    return 13;
}
s32 SaveIo_MapDeviceResult(Recovered_SaveIo* io, s32 status) {
    switch (status & 0xFFFF) {
        case 0:
            if (io->deviceType == 2) {
                if (io->formatted) {
                    if (SaveIo_GetError(io) == 3 || SaveIo_GetError(io) == 1) SaveIo_SetError(io, 0);
                    return 0;
                } else
                    goto uninitialized;
            } else
                goto absent;
        case 0x9003: SaveIo_SetError(io, 2); break;
        case 0x13:
        case 0x6F:
        absent:
            SaveIo_SetError(io, 1);
            break;
        case 0x9001: SaveIo_SetError(io, 6); break;
        case 0x2F:
        uninitialized:
            SaveIo_SetError(io, 3);
            break;
        default: SaveIo_SetError(io, 13); break;
    }
    return 13;
}
s32 SaveIo_MapEntryResult(Recovered_SaveIo* io, s32 status, s32* output) {
    switch (status & 0xFFFF) {
        case 0:
            if (io->entryCount != 1) { goto missingEntry; }
            if (io->operation == 4)
                io->operation = 14;
            else if (output) {
                if (io->entry.attributes & 0x20)
                    *output = 0;
                else
                    *output = io->entry.size;
            }
            return 0;
        case 0x9002: SaveIo_SetError(io, 10); break;
        case 2:
        case 0x14:
        missingEntry:
            SaveIo_SetError(io, 9);
            break;
        case 0x13:
        case 0x6F: SaveIo_SetError(io, 1); break;
        default: SaveIo_SetError(io, 13); break;
    }
    return 13;
}

s32 func_0026FE80(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x14:
    case 0x16:
        SaveIo_SetError(arg0, 9);
block_12:
        return 0xD;
    case 0x6F:
    case 0x13:
        SaveIo_SetError(arg0, 1);
        goto block_12;
    default:
        SaveIo_SetError(arg0, 0xD);
        goto block_12;
    }
}

s32 func_0026FF10(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 & 0xFFFF;
    switch (temp_5) {                               /* irregular */
    case 0x0:
        return 0;
    case 0x16:
    case 0x14:
    case 0x2:
        SaveIo_SetError(arg0, 9);
block_15:
        return 0xD;
    case 0x13:
    case 0x6F:
        SaveIo_SetError(arg0, 1);
        goto block_15;
    default:
        SaveIo_SetError(arg0, 0xD);
        goto block_15;
    }
}

s32 SaveIo_DispatchResult(Recovered_SaveIo* io, s32 command, s32 status, s32* output) {
    if (output) *output = -1;
    switch (command) {
        case 7: return func_0026F9D0((s32)io, status);
        case 5: return func_0026FA70((s32)io, status, (s32)output);
        case 6: return func_0026FAD0((s32)io, status, (s32)output);
        case 11: return SaveIo_MapAuxiliaryResult(io, status);
        case 8: return func_0026FE80((s32)io, status);
        case 3: return func_0026FB60((s32)io, status);
        case 10: return SaveIo_MapEntryResult(io, status, output);
        case 2: return SaveIo_MapDeviceResult(io, status);
        case 14: return func_0026FF10((s32)io, status);
        default: SaveIo_SetError(io, 13); return 13;
    }
}
s32 SaveIo_RefreshDevice(Recovered_SaveIo* io) {
    u32 status = func_00355648(io->handle, &io->deviceType) & 0xFFFF;
    switch (status) {
        case 0: return 1;
        case 0x13:
        case 0x6F: SaveIo_SetError(io, 1); return 0;
        default: SaveIo_SetError(io, 13); return 0;
    }
}
