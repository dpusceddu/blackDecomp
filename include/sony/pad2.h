#ifndef SONY_PAD2_H
#define SONY_PAD2_H
#include "ps2/prelude.h"

/* Partial native libpad2 views. The packet has two variable-length regions at
 * data; concrete device meanings of its status bytes remain unresolved. */
typedef struct {
    s32 present;
    s32 width;
    s32 byteOffset;
    s32 bitOffset;
} Recovered_Pad2Field;

typedef struct {
    u8 status;
    u8 unk_01;
    u8 payloadSize;
    u8 formatSize;
    s32 available;
    u8 unk_08[0x14];
    u8 data[0x60];
    s32 frame;
} Recovered_Pad2Packet;

typedef struct {
    s32 opened;
    s32 ready;
    s32 lastFrame;
    s32 lastResult;
    Recovered_Pad2Packet* packets;
    Recovered_Pad2Field fields[40]; // UNVERIFIED: field decoding remains a draft.
    u8 unk_294[0xA0];
} Recovered_Pad2Slot;

typedef struct {
    u8 bytes[16];
} Pad2Extra;

/* UNVERIFIED: option/request views are currently used only by the open draft. */
typedef struct {
    s32 flags;
    s32 port;
    s32 slot;
    s32 unk_0C;
    Pad2Extra extra;
} Recovered_Pad2OpenOptions;

typedef struct {
    s32 flags;
    s32 mode;
    s32 port;
    s32 slot;
    s32 unk_10;
    Pad2Extra extra;
} Recovered_Pad2OpenRequest;

typedef char Pad2PacketSize[sizeof(Recovered_Pad2Packet) == 0x80 ? 1 : -1];
typedef char Pad2SlotSize[sizeof(Recovered_Pad2Slot) == 0x334 ? 1 : -1];
typedef char Pad2FieldsOffset[(u32) & ((Recovered_Pad2Slot*)0)->fields == 0x14 ? 1 : -1];

s32 Pad2_Initialize(s32 unused);
s32 Pad2_Open(const Recovered_Pad2OpenOptions* options, Recovered_Pad2Packet* packets);
s32 Pad2_Close(s32 index);
s32 Pad2_ReadPayload(s32 index, u8* output);
s32 Pad2_ReadFormat(s32 index, u8* output);
s32 func_0029CA10(s32 index);
s32 Pad2_DecodeField(s32 index, const u8* data, s32 field);
void Pad2_ClearPackets(s32 index);
s32 Pad2_UpdateReady(s32 index);
Recovered_Pad2Packet* Pad2_LatestPayloadPacket(s32 index);
Recovered_Pad2Packet* Pad2_LatestFormatPacket(s32 index);
s32 Pad2_HasNewFrame(s32 index);
s32 Pad2_BuildFieldMap(const u8* presence, Recovered_Pad2Field* fields);
#endif
