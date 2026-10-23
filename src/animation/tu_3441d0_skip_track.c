#ifdef NONMATCHING
// Unmatched: switch body folding, loop padding and jump-table layout.
#include "animation/packed_tracks.h"
const u8 *func_00344240(const u8 *bytes) {
    s32 length;
    const u8 *cursor;
    s32 remaining;
    switch (bytes[0]) {
    case 0: length = Track_Count(bytes) * 4; break;
    case 6: length = Track_Count(bytes) * 12; break;
    case 7: length = (Track_Count(bytes) * 3 + 27) & 0xfffffffc; break;
    case 8: length = (Track_Count(bytes) * 6 + 27) & 0xfffffffc; break;
    case 9: case 17: return bytes + 4;
    case 2: case 10: return bytes + 16;
    case 3: case 11: return bytes + 28;
    case 4: case 12: return bytes + 40;
    case 5: case 13: return bytes + 52;
    case 14: length = (((const volatile u8 *)bytes)[1] + (((const volatile u8 *)bytes)[2] << 8)) * 12; break;
    case 15: length = (Track_Count(bytes) * 4 + 27) & 0xfffffffc; break;
    case 16: length = (Track_Count(bytes) * 8 + 27) & 0xfffffffc; break;
    case 1:
        cursor = bytes + 4;
        remaining = Track_Count(bytes);
        if (remaining != 0) {
            do { --remaining; cursor = func_00344240(cursor); } while (remaining != 0);
        }
        return cursor;
    default: return NULL;
    }
    return bytes + length + 4;
}
#endif
