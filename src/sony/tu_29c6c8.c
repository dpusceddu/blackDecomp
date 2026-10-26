#include "include_asm.h"
#include "sony/pad2.h"

extern s32 gPad2Initialized;
extern Recovered_Pad2Slot gPad2Slots[16];
extern s32 func_0029B868(Recovered_Pad2OpenRequest* request, void* first, void* second);
extern s32 func_0029B998(s32 index);
extern s32 func_0029BA58(s32 index);
extern s32 func_0036A038(const char* format, ...);
extern void* func_0035C544(void* dest, const void* source, u32 size);
extern void* memset(void* dest, s32 value, u32 size);
extern void func_003680A0(void* start, void* end);

s32 Pad2_Initialize(s32 unused) {
    Recovered_Pad2Slot* current;
    gPad2Initialized = 1;
    current = gPad2Slots;
    do {
        current->opened = 0;
        current->ready = 0;
        current->lastFrame = 0;
        current->lastResult = 0;
        ++current;
    } while ((s32)current < (s32)(gPad2Slots + 16));
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: slot-address setup and state stores are reordered.
s32 Pad2_Open(const Recovered_Pad2OpenOptions* options, Recovered_Pad2Packet* packets) {
    Recovered_Pad2OpenRequest request;
    s32 index;
    if ((u32)packets & 63) {
        func_0036A038("libpad2: buffer addr is not 64 byte align. %08x\n", packets);
        return -1;
    }
    if (options) {
        request.flags = options->flags;
        request.port = options->port;
        request.slot = options->slot;
        request.unk_10 = options->unk_0C;
        request.extra = options->extra;
    } else {
        request.flags = 0;
        request.port = 0;
        request.slot = 0;
        request.unk_10 = 0;
        request.extra.bytes[0] = 0;
    }
    request.mode = 1;
    request.flags |= 1;
    index = func_0029B868(&request, packets, packets + 1);
    if (index >= 0) {
        gPad2Slots[index].packets = packets;
        gPad2Slots[index].opened = 1;
        Pad2_ClearPackets(index);
    }
    return index;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c6c8", func_0029C708);
#endif

s32 Pad2_Close(s32 index) {
    s32 result = func_0029B998(index);
    if (result < 0) return result;
    gPad2Slots[index].opened = 0;
    gPad2Slots[index].ready = 0;
    gPad2Slots[index].lastResult = 0;
    return 1;
}

s32 Pad2_ReadPayload(s32 index, u8* output) {
    Recovered_Pad2Packet* packet;
    if (!gPad2Slots[index].opened) return -1;
    if (!gPad2Slots[index].ready && Pad2_UpdateReady(index) < 0) return -1;
    packet = Pad2_LatestPayloadPacket(index);
    {
        s32 count = packet->payloadSize;
        if (count) {
            u8* data = packet->data;
            if (data) {
                func_0035C544(output, data, count);
                Pad2_BuildFieldMap(packet->data + packet->payloadSize, gPad2Slots[index].fields);
            }
        }
    }
    if (!packet->available) return -1;
    return packet->payloadSize;
}

s32 Pad2_ReadFormat(s32 index, u8* output) {
    Recovered_Pad2Packet* packet;
    func_0029CA10(index);
    if (!gPad2Slots[index].ready) {
        s32 result = Pad2_UpdateReady(index);
        if (result < 0) return -1;
    }
    packet = Pad2_LatestFormatPacket(index);
    {
        s32 count = packet->formatSize;
        if (count && packet->data) {
            /* Preserve the native offset-first 32-bit address calculation. */
            u32 payloadEnd = (u32)packet->payloadSize + (u32)packet;
            func_0035C544(output, (u8*)(payloadEnd + 0x1C), count);
            Pad2_BuildFieldMap(packet->data + packet->payloadSize, gPad2Slots[index].fields);
        }
    }
    if (!packet->available) return -1;
    return packet->formatSize;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c6c8", func_0029CA10);

#ifdef NON_MATCHING
// Unmatched: the one-bit result uses the opposite conditional-move form.
s32 Pad2_DecodeField(s32 index, const u8* data, s32 field) {
    Recovered_Pad2Field description = gPad2Slots[index].fields[field];
    if (description.present) {
        switch (description.width) {
            case 1: {
                u8 bits = data[description.byteOffset] >> description.bitOffset;
                s32 value;
                if (!(bits & 1))
                    value = description.width;
                else
                    value = 0;
                return value;
            }
            case 8: {
                u8 value = data[description.byteOffset] >> description.bitOffset;
                if (description.bitOffset) {
                    ++description.byteOffset;
                    value |= data[description.byteOffset] << (description.width - description.bitOffset);
                }
                return value;
            }
            default: return -1;
        }
    }
    return -1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c6c8", func_0029CB50);
#endif

void Pad2_ClearPackets(s32 index) {
    Recovered_Pad2Packet* packet = gPad2Slots[index].packets;
    s32 count = 1;
    do {
        packet->status = 0;
        packet->frame = 0;
        packet->unk_01 = 0;
        packet->formatSize = 0;
        packet->payloadSize = 0;
        packet->available = 0;
        memset(packet->data, 255, 32);
        ++packet;
    } while (--count >= 0);
}

s32 Pad2_UpdateReady(s32 index) {
    s32 result = func_0029BA58(index);
    if (result < 0) return result;
    gPad2Slots[index].lastResult = result;
    gPad2Slots[index].ready = 1;
    return result;
}

Recovered_Pad2Packet* Pad2_LatestPayloadPacket(s32 index) {
    Recovered_Pad2Packet* packets[2];
    packets[0] = gPad2Slots[index].packets;
    packets[1] = packets[0] + 1;
    func_003680A0(packets[0], (u8*)packets[0] + 255);
    return packets[packets[0]->frame < packets[1]->frame];
}
Recovered_Pad2Packet* Pad2_LatestFormatPacket(s32 index) {
    Recovered_Pad2Packet* packets[2];
    packets[0] = gPad2Slots[index].packets;
    packets[1] = packets[0] + 1;
    func_003680A0(packets[0], (u8*)packets[0] + 256);
    return packets[packets[0]->frame < packets[1]->frame];
}
s32 Pad2_HasNewFrame(s32 index) {
    s32 frame = Pad2_LatestPayloadPacket(index)->frame;
    if (!frame || frame == gPad2Slots[index].lastFrame) return 0;
    gPad2Slots[index].lastFrame = frame;
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: format index and packed-bit cursor use opposite registers.
s32 Pad2_BuildFieldMap(const u8* presence, Recovered_Pad2Field* fields) {
    s32 presenceBit = 0;
    s32 byteOffset = 0;
    s32 bitOffset = 0;
    s32 index;
    for (index = 0; index < 40; ++index) {
        if ((*presence >> presenceBit) & 1) {
            fields->present = 1;
            fields->byteOffset = byteOffset;
            fields->bitOffset = bitOffset;
            if ((u32)(index - 16) < 16 || (u32)(index - 35) < 4) {
                fields->width = 8;
                ++byteOffset;
            } else {
                fields->width = 1;
                if ((++bitOffset & 7) == 0) {
                    ++byteOffset;
                    bitOffset = 0;
                }
            }
        } else {
            fields->present = 0;
            fields->byteOffset = 0;
            fields->bitOffset = 0;
        }
        if ((++presenceBit & 7) == 0) {
            ++presence;
            presenceBit = 0;
        }
        ++fields;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c6c8", func_0029CE30);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c6c8", func_0029CEE0);
