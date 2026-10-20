// Shared mod context; accessed PS2 prefixes only. Original identities and full allocations remain qualified.
#ifndef BLACK_ACTOR_ASSET_H
#define BLACK_ACTOR_ASSET_H
/* Accessed PS2 prefixes; record stride/flags58/5a are exact-backed by
   1AFBA8/1AFC30. Timer remaining/index are exact-backed by 1AFCD8/1AFDA8.
   Other names and unused fields remain qualified instruction evidence. */
typedef struct BkActorAssetRecordPS2 {
    char opaque[0x28];
    float duration;
    char unknown2c[0x2c];
    unsigned short flags58, flags5a;
    char unknown5c[0x64];
    void *object;
    void *auxiliary;
    void *links;
    short next;
    unsigned char repeat;
    unsigned char trailing;
} BkActorAssetRecordPS2;

typedef struct BkActorAssetPS2 {
    char opaque[0x1c];
    char *renderData;
    char *linkIndices;
    int renderCount;
    char unknown28[0x10];
    char *strings;
    int unknown3c;
    void *unknown40;
    int unknown44;
    BkActorAssetRecordPS2 *records;
    void **objects;
    int objectCount;
    void *unknown54;
    void *unknown58;
    int linkCount;
    void **links;
    void *unknown64; /* free-index pointer in 1AFBF0; field name retained for compatibility */
    unsigned char recordCount;
    /* 1AFBF0 PS2 instructions only; promoted after an exact source consumer. */
    unsigned char freeIndexCount;
} BkActorAssetPS2;

typedef struct BkActorTimerPS2 {
    float remaining;
    int index;
    unsigned char repeat;
} BkActorTimerPS2;
#endif
