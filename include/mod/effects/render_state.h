// Shared mod context; accessed PS2 prefixes only. Original identities and full allocations remain qualified.
#ifndef BLACK_ACTOR_RENDER_STATE_H
#define BLACK_ACTOR_RENDER_STATE_H
/* Accessed PS2 prefixes; field names describe their uses in the matched callbacks. */
typedef struct BkRenderResourcePS2 {
    char opaque[0x58];
    void *geometry;
} BkRenderResourcePS2;

typedef struct BkRenderBufferPS2 {
    char opaque[0x58];
    void *geometry;
    char trailing[0x44];
} BkRenderBufferPS2;

typedef struct BkActorRenderPS2 {
    char opaque[0xd360];
    BkRenderBufferPS2 buffers[3];
    BkRenderResourcePS2 *resource;
} BkActorRenderPS2;
#endif
