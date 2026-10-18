#ifndef BLACK_ACTOR_ASSET_H
#define BLACK_ACTOR_ASSET_H
/* Accessed prefixes inferred from PS2 relocation and timer callbacks. */
typedef struct BkActorAssetRecordPS2 {
    char opaque[0x28];
    float duration;
    char unknown2c[0x94];
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
    void *unknown64;
    unsigned char recordCount;
} BkActorAssetPS2;

typedef struct BkActorTimerPS2 {
    float remaining;
    int index;
    unsigned char repeat;
} BkActorTimerPS2;
#endif
