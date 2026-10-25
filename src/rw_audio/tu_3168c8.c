#include "rw_audio/emitter.h"
typedef struct AudioListHead{void *next,*previous;}AudioListHead;

#include "ps2/prototypes.h"
/* Active/idle emitter heads, channel table and listener-list head. */
void *D_0040E780 __attribute__((section(".sbss")));
void *D_0040E784 __attribute__((section(".sbss")));
RwaEmitter *D_0040E788 __attribute__((section(".sbss")));
RwaEmitter *D_0040E78C __attribute__((section(".sbss")));
s32 **D_0040E790 __attribute__((section(".sbss")));
AudioListHead D_0040E798 __attribute__((section(".sbss")));
void *D_0040E7A0 __attribute__((section(".sbss")));
void *D_0040E7A4 __attribute__((section(".sbss")));
void *D_0040E7A8 __attribute__((section(".sbss")));
void *D_0040E7AC __attribute__((section(".sbss")));
AudioListHead D_0040E7B0 __attribute__((section(".sbss")));

#include "rw_audio/io_cache.h"
extern AudioIoCache D_00456480;

extern s32 *D_0040E1B0;
extern RwaEmitter *D_0040E788;
extern s32 D_0040E1C0;
extern s32 D_0040E1B8;
extern void func_003175C8(RwaEmitter *);
extern s32 func_003107E0(void *, s32, s32, void *);
extern s32 func_003105E8(void *, s32, s32, s32);
extern s32 func_00310698(void *, s32, s32, void *);
extern s32 D_0040E1C4;
extern s32 func_00314F08(RwaFormat *, s32);
extern void *func_00310870(void *, s32, s32, void *);
extern s32 func_003106F0(void *, s32, s32, f32);
extern s32 func_00310640(void *, s32, s32, s32);
extern s32 func_00310590(void *, s32, s32, void *);
s32 func_003168C8(void)
{
    RwaEmitter *next;
    RwaEmitter *entry;
    f32 elapsedFloat;
    s32 cursor;
    s32 result;
    u32 elapsedTicks;
    s32 length;
    s32 count;
    u32 wrappedCursor;
    u32 updatedCursor;
    u8 flags;
    u8 currentFlags;
    void *handle;
    void *newHandle;
    RwaSound *asset;
    result = (s32) D_0040E1B0;
    if (result != 0)
    {
        entry = D_0040E788;
        count = 0;
        if (entry != ((RwaEmitter *)&D_0040E788))
        {
            do
            {
                handle = entry->handle;
                next = entry->next;
                if (count < (D_0040E1C0 - D_0040E1B8))
                {
                    flags = entry->flags;
                    if (flags & 0x10)
                    {
                        func_003175C8(entry);
                    }
                    else if (handle != NULL)
                    {
                        if (flags & 8)
                        {
                            cursor = entry->start_bytes;
                        }
                        else
                        {
                            cursor = func_003107E0(handle, 9, 2, NULL);
                        }
                        entry->position_bytes = cursor;
                        func_003105E8(handle, 8, 1, 0);
                        /* Keep this one-shot scope for the original SN store scheduling. */
                        do
                        {
                            func_00310698(handle, 0xB, 1, NULL);
                            func_00310698(entry->handle, 0xE, 1, NULL);
                            entry->last_tick = (s32) D_0040E1C4;
                            entry->handle = NULL;
                        }
                        while (0);
                    }
                    currentFlags = entry->flags;
                    if ((currentFlags & 1) && (!(currentFlags & 8)))
                    {
                        asset = entry->sound;
                        length = func_00314F08(&asset->source_format, (s32)asset->source_format.extent);
                        elapsedTicks = D_0040E1C4 - (entry->last_tick);
                        elapsedFloat = (f32) elapsedTicks;
                        updatedCursor = (entry->position_bytes) + ((s32) ((elapsedFloat * (entry->pitch)) / 1000.0f));
                        entry->position_bytes = (s32) updatedCursor;
                        if (updatedCursor >= ((u32) length))
                        {
                            if ((entry->flags) & 4)
                            {
                                do
                                {
                                    wrappedCursor = (entry->position_bytes) - length;
                                    entry->position_bytes = (s32) wrappedCursor;
                                }
                                while (wrappedCursor >= ((u32) length));
                            }
                            else
                            {
                                func_003175C8(entry);
                                entry->handle = NULL;
                            }
                        }
                        entry->last_tick = (s32) D_0040E1C4;
                    }
                }
                else if (handle == NULL)
                {
                    newHandle = func_00310870(D_0040E1B0, 4, 2, NULL);
                    entry->handle = newHandle;
                    if (newHandle != NULL)
                    {
                        func_00310698(newHandle, 0xB, 1, entry->sound);
                        func_003106F0(newHandle, 6, 1, entry->pitch);
                        func_003106F0(newHandle, 7, 1, ((f32) (entry->gain)) / 255.0f);
                        func_003105E8(newHandle, 0xA, 1, (((u8) (entry->flags)) >> 2) & 1);
                        if (!((entry->flags) & 8))
                        {
                            func_00310640(newHandle, 9, 1, entry->position_bytes);
                        }
                        func_003106F0(newHandle, 0xC, 1, (f32) (entry->pan));
                        func_00310590(newHandle, 0, 1, entry->position);
                        func_00310590(newHandle, 1, 1, entry->velocity);
                        func_003106F0(newHandle, 4, 1, entry->min_distance);
                        func_003106F0(newHandle, 5, 1, entry->max_distance);
                        func_003106F0(newHandle, 0xD, 1, ((f32) (entry->field5e)) / 255.0f);
                        func_003105E8(newHandle, 8, 1, 1);
                        func_00310698(newHandle, 0xE, 1, entry->user);
                    }
                }
                result = entry->channels;
                entry = next;
                count += result;
            }
            while (entry != ((RwaEmitter *)&D_0040E788));
        }
    }
    return result;
}

extern s32 func_00310768(void *, s32, s32, void *);
extern void * D_0040E780;
extern s32 D_0040E1BC;
extern void func_00317030(RwaEmitter *);
extern u8 D_0040A0F0[];

void func_00316E90(RwaEmitter *input) {
    u8 channels;
    void *handle;
    RwaSound *sound;

    if (input->flags & 1) {
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
        M2C_FIELD(input,void **,0) = D_0040E780;
        M2C_FIELD(D_0040E780, void **, 4) = input;
        D_0040E780 = input;
        D_0040E1BC -= 1;
        D_0040E1C0 -= input->channels;
        /* Preserve the reset scope for SN store scheduling. */
        do {
            input->level = 0;
            input->channels = 0U;
            input->position_bytes = input->start_bytes;
            input->flags &= 0xFC;
        } while (0);
    }
    func_00317030(input);
    input->channels = 1U;
    sound = input->sound;
    input->flags = (u8) (input->flags | 2);
    input->start_bytes = 0;
    input->channels = sound->source_format.channels;
    if ((sound->flags & 2) && (func_00310768(D_0040E1B0, 3, 2, NULL) == 4) && ((void *)*M2C_FIELD(*D_0040E1B0, s32 **, 0) == D_0040A0F0)) {
        input->channels = 2U;
    }
    channels = input->channels;
    D_0040E1C0 += channels;
    D_0040E1BC += 1;
    return;
}

extern s32 func_003178F0(void *, void *, void *, void *, s32, s32);
extern void *D_0040E1B4;
inline static void RwaUnlink(RwaEmitter *input)
{
  input->previous->next = input->next;
  input->next->previous = input->previous;
}

inline static void RwaInsertBefore(void *before, RwaEmitter *input)
{
  input->previous = *((void **) (((s8 *) before) + 4));
  input->next = before;
  *(*((void ***) (((s8 *) before) + 4))) = input;
  *((void **) (((s8 *) before) + 4)) = input;
}

typedef struct RwaSpatial
{
  RwaVec3 position;
  RwaVec3 velocity;
  f32 min_distance;
  f32 max_distance;
} RwaSpatial;
void func_00317030(RwaEmitter *input)
{
  RwaSpatial spatial;
  f32 spatialResult[5];
  f32 currentLevel;
  f32 blend;
  s8 *nextLevelAddress;
  f32 previousLevel;
  f32 nextLevel;
  f32 volume;
  u8 flags;
  void *next;
  void *previous;
  void *cursor;
  float zero;
  input->level = 0U;
  if (input->gain != 0)
  {
    zero = 0.0f;
    if ((((s32)input->sound->flags) >> 1) & 1)
    {
      spatial.position = *((RwaVec3 *) input->position);
      spatial.velocity = *((RwaVec3 *) input->velocity);
      spatial.min_distance = input->min_distance;
      spatial.max_distance = input->max_distance;
      func_003178F0(D_0040E1B4, ((u8 *) input) - 0xFA0, &spatial, spatialResult, 0, 1);
      *((RwaVec3 *) input->local_position) = spatial.position;
      *((RwaVec3 *) input->local_velocity) = spatial.velocity;
      volume = spatialResult[0];
      volume = volume * (((f32) input->gain) / 255.0f);
    }
    else
    {
      volume = 1.0f;
    }
    if (volume > zero)
    {
      blend = ((f32) input->blend) / 255.0f;
      volume *= 255.0f;
      input->level = (u8) ((s32) ((volume * (1.0f - blend)) + (((((f32) input->priority) / 255.0f) * 255.0f) * blend)));
    }
  }
  if (input->flags & 1)
  {
    cursor = input;
    nextLevel = 255.0f;
    previousLevel = (f32) input->level;
    currentLevel = previousLevel;
    currentLevel = currentLevel / nextLevel;
    while (1)
    {
      next = *((void **) (0 + ((s8 *) cursor)));
      previous = *((void **) (((s8 *) cursor) + 4));
      if (next == (&D_0040E788))
      {
        nextLevel = 2.0f;
      }
      else
      {
        nextLevelAddress = (s8 *)&((RwaEmitter *)next)->level;
        nextLevel = ((f32) (*((u8 *) nextLevelAddress))) / 255.0f;
      }
      if (previous == (&D_0040E788))
      {
        previousLevel = -1.0f;
      }
      else
      {
        previousLevel = ((f32) (M2C_FIELD(previous, u8 *, 0x60))) / 255.0f;
      }
      if (nextLevel < currentLevel)
      {
        cursor = *((void **) (((s8 *) cursor) + 0));
        continue;
      }
      if (currentLevel < previousLevel)
      {
        cursor = *((void **) (((s8 *) cursor) + 4));
        continue;
      }
      break;
    }

    if (cursor != input)
    {
      RwaUnlink(input);
 /* Preserve the insertion scopes for SN block placement. */
      do { RwaInsertBefore(cursor, input); } while (0);
    }
  }
  else
  {
    void *head = &D_0040E788;
    RwaUnlink(input);
    cursor = *((M2C_UNK **) (((s8 *) head) + 0));
    while ((cursor != head) && (input->level >= (M2C_FIELD(cursor, u8 *, 0x60))))
    {
      cursor = *((void **) (((s8 *) cursor) + 0));
    }

    if (cursor == head)
    {
      do { RwaInsertBefore(head,input); } while(0);
    }
    else
    {
      RwaInsertBefore(cursor, input);
    }
  }
  flags = input->flags | 1;
  input->flags = flags;
  return;
}

extern RwaEmitter *D_0040E78C;
extern void *D_0040E784;
extern s32 D_0040E1A8;
typedef struct PlaybackClass PlaybackClass;
extern PlaybackClass *func_00319CE8(void);
s32 func_00317490(void) {
    D_0040E1A8=1;
    D_0040E784=(D_0040E780=&D_0040E780);
    D_0040E78C=(D_0040E788=(RwaEmitter *)&D_0040E788);
    func_00319CE8();
    return 1;
}

extern AudioListHead D_0040E798;
extern RwaListener *D_0040E1D4;
void func_003178C0(RwaListener *listener) {
    void *entry=D_0040E798.next;
    void *head=&D_0040E798;
    while(entry!=head) {
        if(entry==(u8 *)listener+0x40) {D_0040E1D4=listener;return;}
        entry=*(void **)entry;
    }
}

extern void *func_00312C48(s32, s32);
extern void *func_0035C6EC(void *, s32, u32);

static inline void PoolInsertAfter(RwaPoolBlock *block, RwaPoolBlock *head)
{
    RwaPoolBlock *next = head->next;
    block->previous = head;
    *(void **)block = next;
    head->next->previous = block;
    head->next = block;
}

static inline u32 PoolPayloadAddress(RwaPoolBlock *block, u32 bitmapBytes, u32 alignment)
{
    return ((u32)((u8 *)block + (bitmapBytes + 8)) + alignment - 1) & -alignment;
}

static inline u32 PoolAddBitmapBytes(u32 bitmapBytes, u32 payloadBytes)
{
    return bitmapBytes + payloadBytes;
}

void *func_00317A78(RwaPool *pool, s32 tag)
{
    RwaPoolBlock *sentinel = &pool->blocks;
    RwaPoolBlock *block = pool->blocks.next;
    u32 bitmapBytes = pool->bitmap_bytes;
    u8 *result = NULL;

    for (; block != sentinel && result == NULL; block = block->next) {
        u32 bitmapOffset = bitmapBytes + 8;
        u8 *bitmap = block->bits;
        u32 remaining = pool->count;
        u32 payloadBase;
        u32 byte;
        for (byte = 0; byte < bitmapBytes; ++byte) {
            u8 *bits = bitmap + byte;
            u8 value = *bits;
            u32 full = 0xff;
            payloadBase = (u32)block + bitmapOffset;
            if (value != full) {
                u32 bit;
                bit = 0;
                if (remaining) do {
                    u8 mask = 0x80 >> bit;
                    if (!(value & mask)) {
                        *bits |= mask;
                        result = (u8 *)(((payloadBase + pool->alignment - 1) & -pool->alignment)
                                      + (byte * 8 + bit) * pool->stride);
                        break;
                    }
                    ++bit;
                    --remaining;
                } while (bit < 8 && remaining);
            } else {
                remaining -= 8;
            }
            if (result) break;
        }
    }

    if (result == NULL) {
        RwaPoolBlock *newBlock;
        u32 bytes = pool->count * pool->stride;
        bytes += 8;
        bytes = PoolAddBitmapBytes(bitmapBytes, bytes);
        bytes += pool->alignment;
        newBlock = func_00312C48(bytes, tag);
        if (newBlock == NULL) return NULL;
        func_0035C6EC(newBlock->bits, 0, bitmapBytes);
        PoolInsertAfter(newBlock, &pool->blocks);
        newBlock->bits[0] = 0x80;
        result = (u8 *)PoolPayloadAddress(newBlock, bitmapBytes, pool->alignment);
    }
    return result;
}

typedef struct AudioPoolLink {struct AudioPoolLink *next,*previous;} AudioPoolLink;
// Accessed full layout; the initializer allocates 0x24 bytes. Names are inferred.
typedef struct AudioPoolObject {u32 stride,count,bitmap_bytes,alignment;AudioPoolLink blocks;u32 flags;AudioPoolLink registry;} AudioPoolObject;
typedef char AudioPoolObjectIs36[sizeof(AudioPoolObject) == 0x24 ? 1 : -1];
typedef char AudioPoolFlagsAt24[((int)&((AudioPoolObject*)0)->flags == 0x18) ? 1 : -1];
typedef char AudioPoolRegistryAt28[((int)&((AudioPoolObject*)0)->registry == 0x1c) ? 1 : -1];
/* Voice/channel lifecycle, clock state and listener-selection defaults. */
s32 D_0040E1A8 __attribute__((section(".sdata")))=0;
s32 D_0040E1AC __attribute__((section(".sdata")))=0;
s32 *D_0040E1B0 __attribute__((section(".sdata")))=NULL;
void *D_0040E1B4 __attribute__((section(".sdata")))=NULL;
s32 D_0040E1B8 __attribute__((section(".sdata")))=0;
s32 D_0040E1BC __attribute__((section(".sdata")))=0;
s32 D_0040E1C0 __attribute__((section(".sdata")))=0;
s32 D_0040E1C4 __attribute__((section(".sdata")))=0;
u32 D_0040E1C8 __attribute__((section(".sdata")))=0;
s32 D_0040E1CC __attribute__((section(".sdata")))=0;
u32 D_0040E1D0 __attribute__((section(".sdata")))=1;
RwaListener *D_0040E1D4 __attribute__((section(".sdata")))=NULL;
f32 (*D_0040E1D8)(void *,RwaListener *) __attribute__((section(".sdata")))=NULL;
f32 D_0040E1DC __attribute__((section(".sdata")))=3.40282346638528859812e38F;
u32 D_0040E1E0 __attribute__((section(".sdata"))) = 0;
AudioPoolObject *D_0040E1E4 __attribute__((section(".sdata"))) = NULL;
u32 D_0040E1E8 __attribute__((section(".sdata"))) = 0;
u32 D_0040E1EC __attribute__((section(".sdata"))) = 0;
s32 D_0040E1F0 __attribute__((section(".sdata")))=0;
extern AudioPoolObject *D_0040E1E4;

extern void func_00312C70(void *);
extern void func_00317C20(AudioPoolObject *, void *);
static inline void PoolRemoveLink(AudioPoolLink *node) {
    node->previous->next=node->next;
    node->next->previous=node->previous;
}
static inline void PoolReleaseStorage(AudioPoolObject *pool,s32 unregister) {
    AudioPoolLink *sentinel=&pool->blocks;
    AudioPoolLink *block;
    if(unregister) {
        pool->registry.previous->next=pool->registry.next;
        pool->registry.next->previous=pool->registry.previous;
    }
    while((block=pool->blocks.next)!=sentinel) {
        PoolRemoveLink(block);
        func_00312C70(block);
    }
    if(!(pool->flags&1)) {
        if(D_0040E1E4==pool || D_0040E1E4==NULL) func_00312C70(pool);
        else func_00317C20(D_0040E1E4,pool);
    }
}
void func_00317FC0(AudioPoolObject *pool) {PoolReleaseStorage(pool,1);}
void func_00318080(AudioPoolObject *pool) {PoolReleaseStorage(pool,0);}

typedef struct AudioValueNode {struct AudioValueNode *next,*previous;void *value;} AudioValueNode;

static inline void ValueInsertAfter(AudioValueNode *head,AudioValueNode *node) {
    AudioValueNode *next=head->next;
    node->previous=head;
    *(void**)node=next;
    head->next->previous=node;
    head->next=node;
}
AudioValueNode *func_00318120(AudioValueNode *head,void *value) {
    AudioValueNode *node=func_00312C48(12,0x30804);
    if(!node) return NULL;
    node->value=value;
    ValueInsertAfter(head,node);
    return node;
}
static inline void ValueRemoveMember(AudioValueNode *head,AudioValueNode *node) {
    AudioValueNode *cursor=head->previous;
    while(cursor!=node && cursor!=head) cursor=cursor->previous;
    node->next->previous=node->previous;
    node->previous->next=node->next;
    func_00312C70(node);
}
void func_003181E8(AudioValueNode *head,AudioValueNode *node) {ValueRemoveMember(head,node);}
AudioValueNode *func_00318188(AudioValueNode *head,void *value) {
    AudioValueNode *node=head->previous;
    while(value!=node->value) {
        if(node==head) return NULL;
        node=node->previous;
    }
    func_003181E8(head,node);
    return head;
}

extern void *D_0040E7A0,*D_0040E7A4;
extern u32 D_0040E1E0;
extern AudioPoolObject D_004563F8;
extern AudioPoolObject *func_00317E40(u32,u32,u32,s32,AudioPoolObject*,s32);
s32 func_00317D68(void) {
    AudioPoolObject *pool;
    D_0040E7A0=&D_0040E7A0;
    D_0040E7A4=&D_0040E7A0;
    D_0040E1E0=1;
    pool=func_00317E40(36,16,64,0,&D_004563F8,0x40800);
    D_0040E1E4=pool;
    if(!pool) {D_0040E1E0=0;return 0;}
    {
        *(void**)pool->registry.previous=pool->registry.next;
        D_0040E1E4->registry.next->previous=D_0040E1E4->registry.previous;
        return 1;
    }
}
void func_00317DF0(void) {
    void *head=&D_0040E7A0;
    void *node=D_0040E7A0;
    while(node!=head) {
        func_00317FC0((AudioPoolObject*)((u8*)node-0x1c));
        node=D_0040E7A0;
    }
    func_00317FC0(D_0040E1E4);
    D_0040E1E4=NULL;
    D_0040E1E0=0;
}

static inline u8 PoolSlotMask(u32 bit) {
    return 0x80 >> bit;
}

static inline AudioPoolLink *PoolBlockHeader(AudioPoolObject *pool) {
    return &pool->blocks;
}

void func_00317C20(AudioPoolObject *pool, void *allocation) {
    AudioPoolLink *head = &pool->blocks;
    AudioPoolLink *block = pool->blocks.next;
    u32 bitmapBytes = pool->bitmap_bytes;

    while (block != head) {
        u8 *payload = (u8 *)block + (bitmapBytes + 8);
        if ((u32)allocation < (u32)payload) {
            block = block->next;
            continue;
        }
        if ((u32)allocation <= (u32)(payload + pool->count * pool->stride)) {
            AudioPoolLink *next;
            u32 slot = ((u32)allocation - (u32)payload) / pool->stride;
            u32 byte = slot >> 3;
            u8 mask = PoolSlotMask(slot - (byte << 3));
            u8 *bitmap = (u8 *)block + 8;
            bitmap[byte] &= ~mask;
            PoolRemoveLink(block);
            next = pool->blocks.next;
            if (next == PoolBlockHeader(pool) || !(pool->flags & 2)) {
                *(void **)block = next;
                block->previous = PoolBlockHeader(pool);
            } else {
                s32 sum = 0;
                u32 i = 0;
                while (i < bitmapBytes) {
                    sum += bitmap[i];
                    ++i;
                }
                if (sum == 0) {
                    func_00312C70(block);
                    return;
                }
                next = pool->blocks.next;
                block->previous = PoolBlockHeader(pool);
                *(void **)block = next;
            }
            pool->blocks.next->previous = block;
            pool->blocks.next = block;
            return;
        }
        block = block->next;
    }
}

static inline AudioValueNode *ValueNodeAt(AudioValueNode *head, u32 index) {
    u32 i = 0;
    AudioValueNode *node = head->previous;
    for (; i != index; ++i) {
        node = node->previous;
        if (node == head) {
            return NULL;
        }
    }
    return node;
}

void *func_00318288(AudioValueNode *head, u32 index) {
    AudioValueNode *node = ValueNodeAt(head, index);
    if (node != NULL) {
        return node->value;
    }
    return NULL;
}

typedef struct AudioEndianWriter {u8 *cursor;} AudioEndianWriter;
typedef struct AudioEndianVector {f32 x,y,z;} AudioEndianVector;
extern void func_00318600(AudioEndianWriter *, const void *, u32);

void func_003182C8(AudioEndianVector *input) {
    AudioEndianVector result;
    AudioEndianWriter writer;
    writer.cursor = (u8 *)&result;
    func_00318600(&writer, &input->x, 4);
    func_00318600(&writer, &input->y, 4);
    func_00318600(&writer, &input->z, 4);
    *input = result;
}

void func_00318600(AudioEndianWriter *writer, const void *source, u32 size) {
    switch (size) {
    case 1: {
        u8 *cursor = writer->cursor;
        *cursor = *(const u8 *)source;
        writer->cursor = cursor + 1;
        break;
    }
    case 2: {
        u16 value = *(const u16 *)source;
        u16 *cursor = (u16 *)writer->cursor;
        *cursor = ((value & 0xff) << 8) | (value >> 8);
        ++cursor;
        writer->cursor = (u8 *)cursor;
        break;
    }
    case 4: {
        u32 value = *(const u32 *)source;
        u32 *cursor = (u32 *)writer->cursor;
        *cursor = (value << 24) | ((value & 0xff00) << 8) |
                  ((value >> 8) & 0xff00) | (value >> 24);
        ++cursor;
        writer->cursor = (u8 *)cursor;
        break;
    }
    }
}

extern AudioPoolObject D_00456420;

void func_00318340(AudioValueNode *head) {
    AudioValueNode *node = head->previous;
    while (node != head) {
        ValueRemoveMember(head, node);
        node = head->previous;
    }
}

s32 func_00318400(void) {
    if (func_00317E40(12, 32, 0, 0, &D_00456420, 0x40804)) {
        D_0040E1E8 = 1;
        return 1;
    }
    return 0;
}

void func_00318450(void) {
    func_00317FC0(&D_00456420);
    D_0040E1E8 = 0;
}

typedef struct AudioArenaLink {struct AudioArenaLink *next,*previous;} AudioArenaLink;
typedef struct AudioArenaChunk {struct AudioArenaChunk *next,*previous;u32 bytes;} AudioArenaChunk;
typedef struct AudioArenaBlock {AudioArenaLink link;AudioArenaChunk *first;u8 *end;} AudioArenaBlock;
typedef struct AudioArena {u32 flags,block_bytes,alignment;AudioArenaLink blocks,registry;} AudioArena;
typedef char AudioArenaIs28[sizeof(AudioArena) == 28 ? 1 : -1];
typedef char AudioArenaBlockIs16[sizeof(AudioArenaBlock) == 16 ? 1 : -1];
typedef char AudioArenaChunkIs12[sizeof(AudioArenaChunk) == 12 ? 1 : -1];
extern AudioPoolObject D_00456448;
extern void func_003187F8(AudioArena *);

u8 func_003186B0(u32 mask) {
    u8 index = 0;
    while (index < 32 && !(mask & (1u << index))) {
        ++index;
    }
    return index;
}

AudioArenaBlock *func_00318B60(u32 bytes) {
    AudioArenaBlock *block = func_00312C48(bytes, 0x30800);
    if (block != NULL) {
        block->end = (u8 *)block + bytes;
        block->first = (AudioArenaChunk *)(block + 1);
        block->first->bytes = 0;
        block->first->previous = NULL;
        block->first->next = (AudioArenaChunk *)block->end;
    }
    return block;
}

void func_00318C40(void) {
    void *head = &D_0040E7A8;
    void *node = D_0040E7A8;
    while (node != head) {
        func_003187F8((AudioArena *)((u8 *)node - 20));
        node = D_0040E7A8;
    }
    func_00317FC0(&D_00456448);
    D_0040E1EC = 0;
}

void func_00318CE8(AudioArena *arena) {
    if (!(arena->flags & 1)) {
        func_00317C20(&D_00456448, arena);
    }
}

extern void func_00318BC0(void *);
extern AudioArenaBlock *func_00318C90(AudioArena *);

static inline void ArenaRemoveLink(AudioArenaLink *node) {
    node->previous->next = node->next;
    node->next->previous = node->previous;
}

static inline void ArenaInsertAfter(AudioArenaLink *head, AudioArenaLink *node) {
    AudioArenaLink *next = head->next;
    node->previous = head;
    *(void **)node = next;
    head->next->previous = node;
    head->next = node;
}

static inline u32 ArenaBlockPrefixBytes(u32 alignment) {
    return alignment + sizeof(AudioArena);
}

static inline void ArenaRegister(AudioArena *arena, AudioArenaLink *head) {
    AudioArenaLink *next = head->next;
    arena->registry.previous = head;
    *(void **)&arena->registry = next;
    head->next->previous = &arena->registry;
    head->next = &arena->registry;
}

AudioArena *func_003186F0(u32 bytes, u32 count, u32 alignment,
                         s32 initialBlocks, AudioArena *arena) {
    if (arena == NULL) {
        arena = func_00317A78((RwaPool *)&D_00456448, 0x30800);
        if (arena == NULL) {
            return NULL;
        }
        arena->flags = 0;
    } else {
        arena->flags = 1;
    }
    arena->block_bytes = (bytes + sizeof(AudioArenaChunk)) * count + ArenaBlockPrefixBytes(alignment);
    arena->blocks.next = &arena->blocks;
    arena->blocks.previous = &arena->blocks;
    arena->alignment = alignment;
    ArenaRegister(arena, (AudioArenaLink *)&D_0040E7A8);
    while (initialBlocks--) {
        if (func_00318C90(arena) == NULL) {
            func_003187F8(arena);
            return NULL;
        }
    }
    return arena;
}

void func_003187F8(AudioArena *arena) {
    AudioArenaLink *head = &arena->blocks;
    AudioArenaLink *node = arena->blocks.next;
    while (node != head) {
        ArenaRemoveLink(node);
        func_00318BC0(node);
        node = arena->blocks.next;
    }
    arena->registry.previous->next = arena->registry.next;
    arena->registry.next->previous = arena->registry.previous;
    func_00318CE8(arena);
}

s32 func_00318BE0(void) {
    D_0040E7A8 = &D_0040E7A8;
    D_0040E7AC = &D_0040E7A8;
    if (func_00317E40(28, 8, 64, 0, &D_00456448, 0x40800)) {
        D_0040E1EC = 1;
        return 1;
    }
    return 0;
}

AudioArenaBlock *func_00318C90(AudioArena *arena) {
    AudioArenaBlock *block = func_00318B60(arena->block_bytes);
    if (block == NULL) {
        return NULL;
    }
    ArenaInsertAfter(&arena->blocks, &block->link);
    return block;
}

void func_00318B08(AudioArenaBlock *block,void *allocation) {
    AudioArenaChunk *chunk=block->first;
    do {
        if(chunk+1==allocation) {
            if(chunk->previous!=(AudioArenaChunk *)block->end) chunk->previous->next=chunk->next;
            if(chunk->next!=(AudioArenaChunk *)block->end) chunk->next->previous=chunk->previous;
            return;
        }
        chunk=chunk->next;
    } while(chunk!=(AudioArenaChunk *)block->end);
}

static inline AudioArenaBlock *ArenaNewBlock(AudioArena *arena) {
    AudioArenaBlock *block=func_00318B60(arena->block_bytes);
    if(block==NULL)return NULL;
    ArenaInsertAfter(&arena->blocks,&block->link);
    return block;
}
void *func_00318880(AudioArena *arena, u32 bytes) {
    void *result = NULL;
    AudioArenaBlock *block;
    AudioArenaLink *head = &arena->blocks;
    AudioArenaLink *entry = arena->blocks.next;
    while (entry != head) {
        block = (AudioArenaBlock *)entry;
        result = func_00318A40(block, bytes, arena->alignment);
        entry = entry->next;
        if (result != NULL) {
            break;
        }
    }
    if (result == NULL) {
        block = ArenaNewBlock(arena);
        if (block != NULL) {
            result = func_00318A40(block, bytes, arena->alignment);
        }
    }
    return result;
}

/* Retain the legacy 32-bit carry accumulator and its final high-bit truncation. */
void func_00318478(u32 left,u32 right,u32 *highResult,u32 *lowResult) {
    u32 low = 0;
    u32 high = 0;
    u32 carry = 0;
    while(left&0xfffffffeu) {
        carry<<=1;
        if(right&0x80000000u) {
            carry|=1;
            right&=0x7fffffffu;
        }
        if(left&1) {
            low+=right;
            high+=carry;
            if(low&0x80000000u) {
                ++high;
                low&=0x7fffffffu;
            }
        }
        left>>=1;
        right<<=1;
    }
    carry<<=1;
    if(right&0x80000000u) {
        carry|=1;
        right&=0x7fffffffu;
    }
    if(left&1) {
        low+=right;
        high+=carry;
        if(low&0x80000000u) {
            ++high;
            low&=0x7fffffffu;
        }
    }
    low |= high << 31;
    high >>= 1;
    *highResult = high;
    *lowResult = low;
}

typedef char PlaybackEmitterAt28[((int)&((AudioPlayback*)0)->emitter == 0x28)?1:-1];
extern void func_00317340(RwaEmitter*,u32);
extern s32 D_0040E1C4;
extern s32 func_00310698(void*,s32,s32,void*);
void func_00319DE0(AudioPlayback *playback,s32 pause) {
    if(pause) {
        func_00317340(&playback->emitter,0);
        playback->emitter.last_tick=D_0040E1C4;
    } else {
        func_00317340(&playback->emitter,1);
    }
}
void func_00319E28(AudioPlayback *playback,RwaSound *sound) {
    if(playback->emitter.sound!=NULL) {
        playback->emitter.sound=NULL;
    }
    if(sound!=NULL) {
        playback->emitter.sound=sound;
        if(!(playback->emitter.flags&0x20))playback->emitter.pitch=(f32)sound->output_format.rate;
    }
    if(playback->emitter.handle!=NULL) {
        func_00310698(playback->emitter.handle,11,1,playback->emitter.sound);
    }
}

AudioPlayback *func_0031A108(AudioPlayback *playback,u32 selector,const RwaVec3 *value) {
    *(RwaVec3 *)playback->emitter.position=*value;
    if(playback->emitter.handle!=NULL)func_00310590(playback->emitter.handle,0,1,(void*)value);
    return playback;
}
AudioPlayback *func_0031A188(AudioPlayback *playback,u32 selector,const RwaVec3 *value) {
    *(RwaVec3 *)playback->emitter.velocity=*value;
    if(playback->emitter.handle!=NULL)func_00310590(playback->emitter.handle,1,1,(void*)value);
    return playback;
}
AudioPlayback *func_0031A208(AudioPlayback *playback,u32 selector,const RwaVec3 *value) {
    *(RwaVec3 *)playback->emitter.local_position=*value;
    if(playback->emitter.handle!=NULL)func_00310590(playback->emitter.handle,2,1,(void*)value);
    return playback;
}
AudioPlayback *func_0031A288(AudioPlayback *playback,u32 selector,const RwaVec3 *value) {
    *(RwaVec3 *)playback->emitter.local_velocity=*value;
    if(playback->emitter.handle!=NULL)func_00310590(playback->emitter.handle,3,1,(void*)value);
    return playback;
}

extern s32 func_00317300(AudioPlayback*);
typedef char PlaybackEmitterStorageIs100[sizeof(RwaEmitter)==100?1:-1];
AudioPlayback *func_00319ED0(AudioPlayback *playback,u32 selector,const u8 *flags) {
    RwaEmitter *emitter=&playback->emitter;
    func_0035C6EC(emitter,0,sizeof(*emitter));
    emitter->previous=NULL;
    emitter->next=NULL;
    func_00317300(playback);
    emitter->flags=*flags&0x18;
    emitter->pitch=22050.0f;
    emitter->gain=0xff;
    emitter->min_distance=1.0f;
    emitter->max_distance=10000.0f;
    emitter->pan=0;
    emitter->last_tick=0;
    emitter->position_bytes=0;
    emitter->start_bytes=0;
    emitter->priority=0x7f;
    emitter->blend=0x7f;
    emitter->level=0x7f;
    emitter->handle=NULL;
    return playback;
}

/* Accessed request prefixes; allocation sizes and dormant fields remain unaudited. */
typedef struct RwaIoOwner {u32 mode,parameter,status;void *stream;} RwaIoOwner;
typedef struct RwaIoRequest RwaIoRequest;
typedef void(*RwaIoCallback)(void*,u32,s32,s32,void*);
typedef void (*RwaIoCompletion)(void *,u32,s32,s32,void *);
struct RwaIoRequest {
 RwaIoOwner *owner;
 RwaIoRequest *previous,*next;
 u32 ready,field10;
 u8 unknown14[0x10];
 u32 field24;
 u8 unknown28[0x10];
 void *context38;
 RwaIoCallback callback;
 void *context40;
 u32 phase;
 RwaIoCompletion completion;
 void *user;
 u32 target_id;
 void *record;
 u32 scan_pending;
 s32 file;
 u32 field60;
};
typedef char RwaIoCallbackAt3C[((int)&((RwaIoRequest*)0)->callback==0x3c)?1:-1];
typedef char RwaIoPhaseAt44[((int)&((RwaIoRequest*)0)->phase==0x44)?1:-1];
typedef char RwaIoFileAt5C[((int)&((RwaIoRequest*)0)->file==0x5c)?1:-1];
extern void func_00319628(void*,u32,s32,s32,void*);
extern s32 func_00324990(s8*);
extern void *func_00318E80(s32,s32,s32,s32,void*);
RwaIoOwner *func_00319368(RwaIoOwner *owner,RwaIoRequest *request,u32 mode,u32 parameter,s8 *path,RwaIoCompletion completion,void *user){
 owner->parameter=parameter;
 owner->status=0;
 owner->mode=mode;
 if(mode==2){
  s32 file;
  request->next=NULL;
  request->previous=NULL;
  request->context40=request;
  request->context38=request;
  request->field10=0;
  request->field24=0;
  request->owner=owner;
  request->callback=func_00319628;
  request->completion=completion;
  request->user=user;
  request->ready=1;
  request->phase=1;
  file=func_00324990(path);
  request->field60=0;
  request->file=file;
  func_00318E80(file,0,2,2,request);
 }
 return owner;
}

/* The request scans three-word record headers for its requested identifier. */
typedef struct RwaIoRecordHeader {u32 id,next_offset,size;} RwaIoRecordHeader;
typedef char RwaIoRecordHeaderIs12[sizeof(RwaIoRecordHeader)==12?1:-1];
extern void func_00319828(RwaIoRequest *,u32,u32,RwaIoCallback,void *);
void func_00319578(RwaIoOwner *owner,RwaIoRequest *request,u32 id,
                  RwaIoRecordHeader *record,RwaIoCompletion completion,void *user)
{
    request->owner=owner;
    request->target_id=id;
    request->completion=completion;
    request->user=user;
    request->phase=2;
    request->record=record;
    request->scan_pending=0;
    func_00319828(request,(u32)record,sizeof(*record),func_00319628,request);
}

#include "rw_audio/property.h"
/* Constructor311BF8 initializes the class prefix, field1c and both list links. */
typedef struct AudioPropertyRegistry {RwaPropertyClass type;u32 field1c;RwaValueLink link;}AudioPropertyRegistry;
typedef char AudioPropertyRegistryIs40[sizeof(AudioPropertyRegistry)==40?1:-1];
typedef char AudioRegistryLinksAt32[((int)&((AudioPropertyRegistry*)0)->link==32)?1:-1];
typedef struct AudioIoLink {struct AudioIoLink *next,*previous;}AudioIoLink;
typedef struct AudioIoQueue {s32 semaphore,signal;AudioIoLink pending;void *active;}AudioIoQueue;
typedef char AudioIoQueueIs20[sizeof(AudioIoQueue)==20?1:-1];
typedef char AudioIoPendingAt8[((int)&((AudioIoQueue*)0)->pending==8)?1:-1];
typedef char AudioIoActiveAt16[((int)&((AudioIoQueue*)0)->active==16)?1:-1];
/* Semaphore handles, pending-list sentinel and active request. */
AudioIoQueue D_004584C0 __attribute__((section(".bss")));
AudioPropertyRegistry D_004584D8 __attribute__((section(".bss")));
AudioPropertyRegistry D_00458500 __attribute__((section(".bss")));
AudioPropertyRegistry D_00458528 __attribute__((section(".bss")));

/* A property class is identified by a128-bit GUID, with standard component widths. */
typedef struct AudioPropertyGuid {u32 data1;u16 data2,data3;u8 data4[8];}AudioPropertyGuid;
typedef char AudioPropertyGuidIs16[sizeof(AudioPropertyGuid)==16?1:-1];
extern const AudioPropertyGuid D_00409400,D_00409610;
/* 7eedc799-a006-4fd8-8306-8a06fef30ddf */
const AudioPropertyGuid D_00409400={0x7eedc799,0xa006,0x4fd8,{0x83,0x06,0x8a,0x06,0xfe,0xf3,0x0d,0xdf}};
/* bd6a60e0-d5df-487b-9fb3-38c2370873ab */
const AudioPropertyGuid D_00409410={0xbd6a60e0,0xd5df,0x487b,{0x9f,0xb3,0x38,0xc2,0x37,0x08,0x73,0xab}};
/* e91cbd42-5da6-4b4b-82b4-c92ae95d84b0 */
const AudioPropertyGuid D_00409420={0xe91cbd42,0x5da6,0x4b4b,{0x82,0xb4,0xc9,0x2a,0xe9,0x5d,0x84,0xb0}};
/* 536d681d-33eb-4b5e-bc70-a3d05555f8bc */
const AudioPropertyGuid D_00409430={0x536d681d,0x33eb,0x4b5e,{0xbc,0x70,0xa3,0xd0,0x55,0x55,0xf8,0xbc}};
/* ae425c52-9391-4b3a-9594-7a41bb0ffc53 */
const AudioPropertyGuid D_00409440={0xae425c52,0x9391,0x4b3a,{0x95,0x94,0x7a,0x41,0xbb,0x0f,0xfc,0x53}};
/* ff09bf10-278c-4810-9cb7-50e02629ee84 */
const AudioPropertyGuid D_00409450={0xff09bf10,0x278c,0x4810,{0x9c,0xb7,0x50,0xe0,0x26,0x29,0xee,0x84}};
/* 79de9c19-4879-4646-9b2b-039c08c34d85 */
const AudioPropertyGuid D_00409460={0x79de9c19,0x4879,0x4646,{0x9b,0x2b,0x03,0x9c,0x08,0xc3,0x4d,0x85}};
/* eaabcec0-a3a7-4f5a-b2f0-aacb8387c1c7 */
const AudioPropertyGuid D_00409470={0xeaabcec0,0xa3a7,0x4f5a,{0xb2,0xf0,0xaa,0xcb,0x83,0x87,0xc1,0xc7}};
/* b983cf09-4dab-4a90-8bdf-c41d9a6af3bf */
const AudioPropertyGuid D_00409480={0xb983cf09,0x4dab,0x4a90,{0x8b,0xdf,0xc4,0x1d,0x9a,0x6a,0xf3,0xbf}};
/* 5c3558e8-2e92-41c7-b019-f7edb57a57ee */
const AudioPropertyGuid D_00409490={0x5c3558e8,0x2e92,0x41c7,{0xb0,0x19,0xf7,0xed,0xb5,0x7a,0x57,0xee}};
/* c2b67b25-feed-4fd5-abb1-f7320b1bf90e */
const AudioPropertyGuid D_004094A0={0xc2b67b25,0xfeed,0x4fd5,{0xab,0xb1,0xf7,0x32,0x0b,0x1b,0xf9,0x0e}};
/* 2d816bb6-35e1-46bd-9cec-24e53c287103 */
const AudioPropertyGuid D_004094B0={0x2d816bb6,0x35e1,0x46bd,{0x9c,0xec,0x24,0xe5,0x3c,0x28,0x71,0x03}};
/* 85bfc120-6542-40f9-bd0c-e02362cffb61 */
const AudioPropertyGuid D_004094C0={0x85bfc120,0x6542,0x40f9,{0xbd,0x0c,0xe0,0x23,0x62,0xcf,0xfb,0x61}};
/* 76c4dbd2-31da-4686-b07f-34278311df4f */
const AudioPropertyGuid D_004094D0={0x76c4dbd2,0x31da,0x4686,{0xb0,0x7f,0x34,0x27,0x83,0x11,0xdf,0x4f}};
/* cca31301-f239-4f32-bcf1-c81304ca6603 */
const AudioPropertyGuid D_004094E0={0xcca31301,0xf239,0x4f32,{0xbc,0xf1,0xc8,0x13,0x04,0xca,0x66,0x03}};
/* d2c030c8-e6da-43d1-81f4-c2184254c119 */
const AudioPropertyGuid D_004094F0={0xd2c030c8,0xe6da,0x43d1,{0x81,0xf4,0xc2,0x18,0x42,0x54,0xc1,0x19}};
/* b84e08c7-4dc1-470d-9e4c-78ef056e3c3f */
const AudioPropertyGuid D_00409500={0xb84e08c7,0x4dc1,0x470d,{0x9e,0x4c,0x78,0xef,0x05,0x6e,0x3c,0x3f}};
/* 5a7d6d01-8382-4150-9f68-7a155a7005e9 */
const AudioPropertyGuid D_00409510={0x5a7d6d01,0x8382,0x4150,{0x9f,0x68,0x7a,0x15,0x5a,0x70,0x05,0xe9}};
/* 2f5929be-0ec3-4c72-ac91-f48aade7c300 */
const AudioPropertyGuid D_00409520={0x2f5929be,0x0ec3,0x4c72,{0xac,0x91,0xf4,0x8a,0xad,0xe7,0xc3,0x00}};
/* 67acfdc2-fd80-4781-a988-771986fd36dc */
const AudioPropertyGuid D_00409530={0x67acfdc2,0xfd80,0x4781,{0xa9,0x88,0x77,0x19,0x86,0xfd,0x36,0xdc}};
/* c1a0bb3b-3305-470e-8d80-926d0055a4fd */
const AudioPropertyGuid D_00409540={0xc1a0bb3b,0x3305,0x470e,{0x8d,0x80,0x92,0x6d,0x00,0x55,0xa4,0xfd}};
/* 0c04f898-0aec-4eb8-a6cd-52de42d6e438 */
const AudioPropertyGuid D_00409550={0x0c04f898,0x0aec,0x4eb8,{0xa6,0xcd,0x52,0xde,0x42,0xd6,0xe4,0x38}};
/* 736a5dc2-f6a4-4208-a704-ca5ebb565c96 */
const AudioPropertyGuid D_00409560={0x736a5dc2,0xf6a4,0x4208,{0xa7,0x04,0xca,0x5e,0xbb,0x56,0x5c,0x96}};
/* 676ebde2-8538-4492-a796-8442b80ceffe */
const AudioPropertyGuid D_00409570={0x676ebde2,0x8538,0x4492,{0xa7,0x96,0x84,0x42,0xb8,0x0c,0xef,0xfe}};
/* 882fe847-6385-498b-9257-349c45773872 */
const AudioPropertyGuid D_00409580={0x882fe847,0x6385,0x498b,{0x92,0x57,0x34,0x9c,0x45,0x77,0x38,0x72}};
/* 5820c0a3-b1a5-4b6b-83e9-108a6b9c95f7 */
const AudioPropertyGuid D_00409590={0x5820c0a3,0xb1a5,0x4b6b,{0x83,0xe9,0x10,0x8a,0x6b,0x9c,0x95,0xf7}};
/* 5b232f38-d7bb-4184-aad3-c61ecad0866a */
const AudioPropertyGuid D_004095A0={0x5b232f38,0xd7bb,0x4184,{0xaa,0xd3,0xc6,0x1e,0xca,0xd0,0x86,0x6a}};
/* 2f735bbf-aa49-4246-abc9-3686c038106c */
const AudioPropertyGuid D_004095B0={0x2f735bbf,0xaa49,0x4246,{0xab,0xc9,0x36,0x86,0xc0,0x38,0x10,0x6c}};
/* 2764eed2-c735-4f45-a821-78c98f4efada */
const AudioPropertyGuid D_004095C0={0x2764eed2,0xc735,0x4f45,{0xa8,0x21,0x78,0xc9,0x8f,0x4e,0xfa,0xda}};
/* 7d22cd47-e9a0-4faa-94b1-a5a098b39c9a */
const AudioPropertyGuid D_004095D0={0x7d22cd47,0xe9a0,0x4faa,{0x94,0xb1,0xa5,0xa0,0x98,0xb3,0x9c,0x9a}};
/* 405334f6-da25-4c29-9b1f-6eb361d4bb49 */
const AudioPropertyGuid D_004095E0={0x405334f6,0xda25,0x4c29,{0x9b,0x1f,0x6e,0xb3,0x61,0xd4,0xbb,0x49}};
/* 74662441-6c33-4a8a-af9c-d07dfce0be2d */
const AudioPropertyGuid D_004095F0={0x74662441,0x6c33,0x4a8a,{0xaf,0x9c,0xd0,0x7d,0xfc,0xe0,0xbe,0x2d}};
/* e8c483a3-7471-4e9a-825b-f70d666b19cd */
const AudioPropertyGuid D_00409600={0xe8c483a3,0x7471,0x4e9a,{0x82,0x5b,0xf7,0x0d,0x66,0x6b,0x19,0xcd}};
/* 03c7994d-f302-414f-b36a-74e3514301eb */
const AudioPropertyGuid D_00409610={0x03c7994d,0xf302,0x414f,{0xb3,0x6a,0x74,0xe3,0x51,0x43,0x01,0xeb}};
/* d54ac4a0-5d8f-4d3b-901e-021e8f5d0576 */
const AudioPropertyGuid D_00409620={0xd54ac4a0,0x5d8f,0x4d3b,{0x90,0x1e,0x02,0x1e,0x8f,0x5d,0x05,0x76}};
/* 0da9ccd8-b5a3-4323-917e-27a02cd42d07 */
const AudioPropertyGuid D_00409630={0x0da9ccd8,0xb5a3,0x4323,{0x91,0x7e,0x27,0xa0,0x2c,0xd4,0x2d,0x07}};
/* e26c926f-7d39-4a83-830b-7457f3113d8b */
const AudioPropertyGuid D_00409640={0xe26c926f,0x7d39,0x4a83,{0x83,0x0b,0x74,0x57,0xf3,0x11,0x3d,0x8b}};
/* 84448c49-55e3-44d5-8ce8-66fefe4329bc */
const AudioPropertyGuid D_00409650={0x84448c49,0x55e3,0x44d5,{0x8c,0xe8,0x66,0xfe,0xfe,0x43,0x29,0xbc}};
/* 955a46c4-6d1c-436d-ae39-24d5e397f3d9 */
const AudioPropertyGuid D_00409660={0x955a46c4,0x6d1c,0x436d,{0xae,0x39,0x24,0xd5,0xe3,0x97,0xf3,0xd9}};
/* 64d0bec0-622c-4fca-9862-682c9e389d55 */
const AudioPropertyGuid D_00409670={0x64d0bec0,0x622c,0x4fca,{0x98,0x62,0x68,0x2c,0x9e,0x38,0x9d,0x55}};
/* 1e0342f6-6f95-438d-8fcf-1a80ad5956c8 */
const AudioPropertyGuid D_00409680={0x1e0342f6,0x6f95,0x438d,{0x8f,0xcf,0x1a,0x80,0xad,0x59,0x56,0xc8}};
/* 99983cab-6f41-475f-ad4f-82f52cd11af1 */
const AudioPropertyGuid D_00409690={0x99983cab,0x6f41,0x475f,{0xad,0x4f,0x82,0xf5,0x2c,0xd1,0x1a,0xf1}};
/* ec1c3cf8-7410-4865-8e3a-c61bc3b9e8a4 */
const AudioPropertyGuid D_004096A0={0xec1c3cf8,0x7410,0x4865,{0x8e,0x3a,0xc6,0x1b,0xc3,0xb9,0xe8,0xa4}};
/* fc94f894-672f-4db2-a4b2-ba8be95cab59 */
const AudioPropertyGuid D_004096B0={0xfc94f894,0x672f,0x4db2,{0xa4,0xb2,0xba,0x8b,0xe9,0x5c,0xab,0x59}};
/* 81f44747-b3f3-438f-94e4-7b90202394d4 */
const AudioPropertyGuid D_004096C0={0x81f44747,0xb3f3,0x438f,{0x94,0xe4,0x7b,0x90,0x20,0x23,0x94,0xd4}};
/* 7f2a948f-cabf-4d7d-855c-f1e4a1769ba4 */
const AudioPropertyGuid D_004096D0={0x7f2a948f,0xcabf,0x4d7d,{0x85,0x5c,0xf1,0xe4,0xa1,0x76,0x9b,0xa4}};
/* Typed native storage; the existing registration API uses its legacy20-byte view. */
typedef struct AudioPropertyEntry{const AudioPropertyGuid *id;u32 field4,state;const AudioPropertyGuid *value_type;u32 count;}AudioPropertyEntry;
typedef void*(*AudioPropertyHandler)(void*,u32,void*);
typedef struct AudioClassPropertyEntry{AudioPropertyEntry property;AudioPropertyHandler handler;}AudioClassPropertyEntry;
typedef char AudioPropertyEntryIs20[sizeof(AudioPropertyEntry)==20?1:-1];
typedef char AudioClassPropertyEntryIs24[sizeof(AudioClassPropertyEntry)==24?1:-1];
extern AudioPropertyEntry D_003CF380[15],D_003CF4B0[16],D_003CF5F0[9],D_003CF6A8[10],D_003CF770[6],D_003CF7E8[5];
extern RwaPropertyClass *func_00311BF8(RwaPropertyClass*);
extern RwaPropertyClass *func_00311BB8(RwaPropertyClass*,const AudioPropertyGuid*,const char*);
extern RwaPropertyClass *func_00311E60(RwaPropertyClass*,RwaProperty*,u32,RwaProperty*,u32);
RwaPropertyClass *func_00319950(void){
 RwaPropertyClass *result;
 if(func_00311BF8(&D_004584D8.type)!=NULL){
  func_00311BB8(&D_004584D8.type,&D_00409400,NULL);
  func_00311E60(&D_004584D8.type,(RwaProperty*)D_003CF380,15,(RwaProperty*)D_003CF4B0,16);
  result=&D_004584D8.type;
 }else result=NULL;
 return result;
}
RwaPropertyClass *func_003199E0(void){
 RwaPropertyClass *result;
 if(func_00311BF8(&D_00458500.type)!=NULL){
  func_00311BB8(&D_00458500.type,&D_004094D0,NULL);
  func_00311E60(&D_00458500.type,(RwaProperty*)D_003CF5F0,9,(RwaProperty*)D_003CF6A8,10);
  result=&D_00458500.type;
 }else result=NULL;
 return result;
}
RwaPropertyClass *func_00319A70(void){
 RwaPropertyClass *result;
 if(func_00311BF8(&D_00458528.type)!=NULL){
  func_00311BB8(&D_00458528.type,&D_00409610,NULL);
  func_00311E60(&D_00458528.type,(RwaProperty*)D_003CF770,6,(RwaProperty*)D_003CF7E8,5);
  result=&D_00458528.type;
 }else result=NULL;
 return result;
}

typedef char AudioIoCacheIs8208[sizeof(AudioIoCache)==8208?1:-1];
typedef char AudioIoCachePositionAt8200[((int)&((AudioIoCache*)0)->position==8200)?1:-1];
typedef char AudioIoOwnerStreamAt12[((int)&((RwaIoOwner*)0)->stream==12)?1:-1];
void func_003196A8(void *file,u32 bytes,s32 status,s32 reason,RwaIoRequest *request)
{
 request->owner->stream=file;
 request->completion(file,bytes,status,reason,request->user);
}

/* Accessed queue prefix; semaphore storage remains in the original BSS. */
extern u8 D_00458490[];
extern void func_00319928(void);
extern void *func_0031D268(void*,s32,s32);
s32 func_00319268(void)
{
 AudioIoLink *head;
 AudioIoQueue *queue;
 func_00319928();
 func_0031D268(D_00458490,1,1);
 queue=&D_004584C0;
 head=&queue->pending;
 queue->active=NULL;
 queue->pending.next=head;
 head->previous=head;
 func_0031D268(&queue->signal,1,1);
 func_0031D268(&queue->semaphore,1,1);
 return 1;
}

extern void func_003196D8(void*,u32,s32,s32,RwaIoRequest*);
/* I/O completion preserves the four operation results and replaces only user. */
void func_00319628(void *file,u32 bytes,s32 status,s32 reason,void *context)
{
    RwaIoRequest *request=(RwaIoRequest*)context;
    switch(request->phase){
    case 1:
        func_003196A8(file,bytes,status,reason,request);
        break;
    case 2:
        func_003196D8(file,bytes,status,reason,request);
        break;
    case 3:
        request->completion(file,bytes,status,reason,request->user);
        break;
    }
}

/* Register the playback class and attach its default property collection. */
extern void*D_0040E7D0;
typedef struct AudioPlaybackProperties {
    AudioPlayback *defaults;
    AudioIoLink values;
    u16 input_count,output_count;
    AudioClassPropertyEntry *input,*output;
} AudioPlaybackProperties;
/* Native class pool uses92bytes; handler signatures remain opaque here. */
struct PlaybackClass {
    const AudioPropertyGuid *identifier;
    const char *name;
    u32 text_flags,flags;
    AudioIoLink derived_classes,parent_link,instances;
    void *construct,*activate,*clone,*destroy,*shutdown,*defaults;
    u32 extent_alignment;
    u16 defaults_size,defaults_alignment;
    void *arena;
    AudioPlaybackProperties *properties;
    AudioIoLink *auxiliary_list;
    void *field54;
    u32 allocation_tag;
};
typedef char PlaybackClassIs92[sizeof(PlaybackClass)==92?1:-1];
typedef char PlaybackClassHandlersAt28[((int)&((PlaybackClass*)0)->construct==0x28)?1:-1];
typedef char PlaybackClassPropertiesAt4C[((int)&((PlaybackClass*)0)->properties==0x4c)?1:-1];
typedef char PlaybackClassTagAt58[((int)&((PlaybackClass*)0)->allocation_tag==0x58)?1:-1];
typedef char AudioPlaybackPropertiesIs24[sizeof(AudioPlaybackProperties)==24?1:-1];
PlaybackClass D_00458550 __attribute__((section(".bss")));
AudioPlaybackProperties D_004585B0 __attribute__((section(".bss")));

extern AudioClassPropertyEntry D_003CF850[17],D_003CF9E8[18];
extern AudioListHead D_0040E7B0;
extern s32 D_0040E1F0;
extern PlaybackClass*func_0031DC40(void*,u32,void*,void*,AudioListHead*,u32);
extern void func_00319B00(PlaybackClass*);
extern PlaybackClass*func_0031D988(PlaybackClass*,void*,u32,void*,u32);
extern void*func_00322A08(void);
extern void func_0031DDD8(PlaybackClass*,void*);
extern void func_0031D7A8(PlaybackClass*);
PlaybackClass *func_00319CE8(void)
{
    PlaybackClass *type;
    void *defaults;
    type=func_0031DC40(D_0040E7D0,12,&D_00458550,&D_004585B0,&D_0040E7B0,0x30811);
    if(type!=NULL){
        func_00319B00(type);
        if(func_0031D988(type,D_003CF850,17,D_003CF9E8,18)!=NULL){
            defaults=func_00322A08();
            if(defaults!=NULL){
                func_0031DDD8(type,defaults);
                D_0040E1F0=1;
                return type;
            }
        }
        func_0031D7A8(type);
        return NULL;
    }
    return NULL;
}

/* Property identifiers, mutable runtime fields, value descriptors and handlers. */
extern const AudioPropertyGuid D_004091B0;
extern const AudioPropertyGuid D_004091C0;
extern const AudioPropertyGuid D_004091F0;
extern const AudioPropertyGuid D_00409210;
extern const AudioPropertyGuid D_00409220;
extern const AudioPropertyGuid D_00409230;
extern const AudioPropertyGuid D_00409410;
extern const AudioPropertyGuid D_00409420;
extern const AudioPropertyGuid D_00409430;
extern const AudioPropertyGuid D_00409440;
extern const AudioPropertyGuid D_00409450;
extern const AudioPropertyGuid D_00409460;
extern const AudioPropertyGuid D_00409470;
extern const AudioPropertyGuid D_00409480;
extern const AudioPropertyGuid D_00409490;
extern const AudioPropertyGuid D_004094A0;
extern const AudioPropertyGuid D_004094B0;
extern const AudioPropertyGuid D_004094C0;
extern const AudioPropertyGuid D_004094E0;
extern const AudioPropertyGuid D_004094F0;
extern const AudioPropertyGuid D_00409500;
extern const AudioPropertyGuid D_00409510;
extern const AudioPropertyGuid D_00409520;
extern const AudioPropertyGuid D_00409530;
extern const AudioPropertyGuid D_00409540;
extern const AudioPropertyGuid D_00409550;
extern const AudioPropertyGuid D_00409560;
extern const AudioPropertyGuid D_00409570;
extern const AudioPropertyGuid D_00409580;
extern const AudioPropertyGuid D_00409590;
extern const AudioPropertyGuid D_004095A0;
extern const AudioPropertyGuid D_004095B0;
extern const AudioPropertyGuid D_004095C0;
extern const AudioPropertyGuid D_004095D0;
extern const AudioPropertyGuid D_004095E0;
extern const AudioPropertyGuid D_004095F0;
extern const AudioPropertyGuid D_00409600;
extern const AudioPropertyGuid D_00409620;
extern const AudioPropertyGuid D_00409630;
extern const AudioPropertyGuid D_00409640;
extern const AudioPropertyGuid D_00409650;
extern const AudioPropertyGuid D_00409660;
extern const AudioPropertyGuid D_00409670;
extern const AudioPropertyGuid D_00409680;
extern const AudioPropertyGuid D_00409690;
extern const AudioPropertyGuid D_004096A0;
extern const AudioPropertyGuid D_004096B0;
extern const AudioPropertyGuid D_004096C0;
extern const AudioPropertyGuid D_00409D00;
extern const AudioPropertyGuid D_00409D10;
extern const AudioPropertyGuid D_00409D20;
extern const AudioPropertyGuid D_00409D30;
extern void*func_0031A068(void*,u32,void*);
extern void*func_0031A090(void*,u32,void*);
extern void*func_0031A0B8(void*,u32,void*);
extern void*func_0031A0E0(void*,u32,void*);
extern void*func_0031A160(void*,u32,void*);
extern void*func_0031A1E0(void*,u32,void*);
extern void*func_0031A260(void*,u32,void*);
extern void*func_0031A2E0(void*,u32,void*);
extern void*func_0031A308(void*,u32,void*);
extern void*func_0031A350(void*,u32,void*);
extern void*func_0031A360(void*,u32,void*);
extern void*func_0031A3A8(void*,u32,void*);
extern void*func_0031A3B8(void*,u32,void*);
extern void*func_0031A400(void*,u32,void*);
extern void*func_0031A410(void*,u32,void*);
extern void*func_0031A470(void*,u32,void*);
extern void*func_0031A498(void*,u32,void*);
extern void*func_0031A4E8(void*,u32,void*);
extern void*func_0031A500(void*,u32,void*);
extern void*func_0031A548(void*,u32,void*);
extern void*func_0031A5B8(void*,u32,void*);
extern void*func_0031A618(void*,u32,void*);
extern void*func_0031A630(void*,u32,void*);
extern void*func_0031A6C8(void*,u32,void*);
extern void*func_0031A6D8(void*,u32,void*);
extern void*func_0031A738(void*,u32,void*);
extern void*func_0031A760(void*,u32,void*);
extern void*func_0031A770(void*,u32,void*);
extern void*func_0031A7D0(void*,u32,void*);
extern void*func_0031A7F8(void*,u32,void*);
extern void*func_0031A840(void*,u32,void*);

AudioPropertyEntry D_003CF380[15]={
    {&D_00409410,0,0,&D_00409210,1},
    {&D_00409430,0,0,&D_00409210,1},
    {&D_00409450,0,0,&D_00409210,1},
    {&D_00409470,0,0,&D_00409210,1},
    {&D_00409490,0,0,&D_004091F0,1},
    {&D_004094B0,0,0,&D_004091F0,1},
    {&D_004094E0,0,0,&D_004091F0,1},
    {&D_00409500,0,0,&D_004091F0,1},
    {&D_00409520,0,0,&D_00409220,1},
    {&D_00409540,0,0,&D_004091B0,1},
    {&D_00409560,0,0,&D_00409220,1},
    {&D_00409580,0,0,&D_00409230,1},
    {&D_004095A0,0,0,&D_004091F0,1},
    {&D_004095D0,0,0,&D_004091F0,1},
    {&D_004095F0,0,0,&D_00409230,1},
};

AudioPropertyEntry D_003CF4B0[16]={
    {&D_00409420,0,0,&D_00409210,1},
    {&D_00409440,0,0,&D_00409210,1},
    {&D_00409460,0,0,&D_00409210,1},
    {&D_00409480,0,0,&D_00409210,1},
    {&D_004094A0,0,0,&D_004091F0,1},
    {&D_004094C0,0,0,&D_004091F0,1},
    {&D_004094F0,0,0,&D_004091F0,1},
    {&D_00409510,0,0,&D_004091F0,1},
    {&D_00409530,0,0,&D_00409220,1},
    {&D_00409550,0,0,&D_004091B0,1},
    {&D_00409570,0,0,&D_00409220,1},
    {&D_00409590,0,0,&D_00409230,1},
    {&D_004095B0,0,0,&D_004091F0,1},
    {&D_004095C0,0,0,&D_00409220,1},
    {&D_004095E0,0,0,&D_004091F0,1},
    {&D_00409600,0,0,&D_00409230,1},
};

AudioPropertyEntry D_003CF5F0[9]={
    {&D_004094E0,0,0,&D_004091F0,1},
    {&D_00409500,0,0,&D_004091F0,1},
    {&D_00409520,0,0,&D_00409220,1},
    {&D_00409540,0,0,&D_004091B0,1},
    {&D_00409560,0,0,&D_00409220,1},
    {&D_00409580,0,0,&D_00409230,1},
    {&D_004095A0,0,0,&D_004091F0,1},
    {&D_004095D0,0,0,&D_004091F0,1},
    {&D_004095F0,0,0,&D_00409230,1},
};

AudioPropertyEntry D_003CF6A8[10]={
    {&D_004094F0,0,0,&D_004091F0,1},
    {&D_00409510,0,0,&D_004091F0,1},
    {&D_00409530,0,0,&D_00409220,1},
    {&D_00409550,0,0,&D_004091B0,1},
    {&D_00409570,0,0,&D_00409220,1},
    {&D_00409590,0,0,&D_00409230,1},
    {&D_004095B0,0,0,&D_004091F0,1},
    {&D_004095C0,0,0,&D_00409220,1},
    {&D_004095E0,0,0,&D_004091F0,1},
    {&D_00409600,0,0,&D_00409230,1},
};

AudioPropertyEntry D_003CF770[6]={
    {&D_00409620,0,0,&D_004091F0,1},
    {&D_00409640,0,0,&D_00409230,1},
    {&D_00409660,0,0,&D_00409230,1},
    {&D_00409680,0,0,&D_004091C0,1},
    {&D_004096A0,0,0,&D_00409230,1},
    {&D_004096B0,0,0,&D_00409230,1},
};

AudioPropertyEntry D_003CF7E8[5]={
    {&D_00409630,0,0,&D_004091F0,1},
    {&D_00409650,0,0,&D_00409230,1},
    {&D_00409670,0,0,&D_00409230,1},
    {&D_00409690,0,0,&D_004091C0,1},
    {&D_004096C0,0,0,&D_00409230,1},
};

AudioClassPropertyEntry D_003CF850[17]={
    {{&D_00409D00,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A068},
    {{&D_00409D20,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A0B8},
    {{&D_00409410,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A108},
    {{&D_00409430,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A188},
    {{&D_00409450,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A208},
    {{&D_00409470,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A288},
    {{&D_00409490,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A308},
    {{&D_004094B0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A360},
    {{&D_004094E0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A3B8},
    {{&D_00409500,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A410},
    {{&D_00409520,0,0,&D_00409220,1},(AudioPropertyHandler)func_0031A498},
    {{&D_00409540,0,0,&D_004091B0,1},(AudioPropertyHandler)func_0031A500},
    {{&D_00409560,0,0,&D_00409220,1},(AudioPropertyHandler)func_0031A5B8},
    {{&D_00409580,0,0,&D_00409230,1},(AudioPropertyHandler)func_0031A630},
    {{&D_004095A0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A6D8},
    {{&D_004095D0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A770},
    {{&D_004095F0,0,0,&D_00409230,1},(AudioPropertyHandler)func_0031A7F8},
};

AudioClassPropertyEntry D_003CF9E8[18]={
    {{&D_00409D10,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A090},
    {{&D_00409D30,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A0E0},
    {{&D_00409420,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A160},
    {{&D_00409440,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A1E0},
    {{&D_00409460,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A260},
    {{&D_00409480,0,0,&D_00409210,1},(AudioPropertyHandler)func_0031A2E0},
    {{&D_004094A0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A350},
    {{&D_004094C0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A3A8},
    {{&D_004094F0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A400},
    {{&D_00409510,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A470},
    {{&D_00409530,0,0,&D_00409220,1},(AudioPropertyHandler)func_0031A4E8},
    {{&D_00409550,0,0,&D_004091B0,1},(AudioPropertyHandler)func_0031A548},
    {{&D_00409570,0,0,&D_00409220,1},(AudioPropertyHandler)func_0031A618},
    {{&D_00409590,0,0,&D_00409230,1},(AudioPropertyHandler)func_0031A6C8},
    {{&D_004095B0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A738},
    {{&D_004095C0,0,0,&D_00409220,1},(AudioPropertyHandler)func_0031A760},
    {{&D_004095E0,0,0,&D_004091F0,1},(AudioPropertyHandler)func_0031A7D0},
    {{&D_00409600,0,0,&D_00409230,1},(AudioPropertyHandler)func_0031A840},
};

/* Bit0 retains caller storage; bit1 permits empty-block reuse. */
static inline void PoolConstructLink(AudioPoolLink *node) {
    node->previous=NULL;
    node->next=NULL;
}
static inline void PoolInsertLink(AudioPoolLink *head,AudioPoolLink *node) {
    AudioPoolLink *next=head->next;
    node->previous=head;
    *(void **)node=next;
    head->next->previous=node;
    head->next=node;
}
static inline u32 PoolAlignLastByte(u32 lastByte,u32 alignment) {
    return (lastByte+alignment)&-alignment;
}
AudioPoolObject *func_00317E40(u32 bytes,u32 count,u32 alignment,s32 reserve,AudioPoolObject *storage,s32 tag) {
    AudioPoolObject *pool=storage;
    u32 stride,bitmapBytes,blockBytes;
    alignment=alignment?alignment:1;
    if(pool==NULL) {
        if(D_0040E1E4) pool=func_00317A78((RwaPool *)D_0040E1E4,0x30800);
        else pool=func_00312C48(sizeof(AudioPoolObject),tag);
        if(pool==NULL) return NULL;
        pool->flags=2;
    } else {
        pool->flags=3;
    }
    stride=PoolAlignLastByte(bytes-1,alignment);
    bitmapBytes=(count+7)>>3;
    pool->stride=stride;
    pool->count=count;
    pool->alignment=alignment;
    pool->bitmap_bytes=bitmapBytes;
    pool->blocks.next=&pool->blocks;
    pool->blocks.previous=&pool->blocks;
    if(reserve!=0) {
        u32 payloadBytes=count*stride;
        payloadBytes+=8;
        blockBytes=PoolAddBitmapBytes(bitmapBytes,payloadBytes);
        do {
            AudioPoolLink *block=func_00312C48(blockBytes+alignment,tag);
            if(block==NULL) {func_00318080(pool);return NULL;}
            PoolConstructLink(block);
            PoolInsertLink(&pool->blocks,block);
            func_0035C6EC(block+1,0,bitmapBytes);
            --reserve;
        } while(reserve!=0);
    }
    pool->registry.previous=(AudioPoolLink *)&D_0040E7A0;
    *(void **)&pool->registry.next=D_0040E7A0;
    ((AudioPoolLink *)D_0040E7A0)->previous=&pool->registry;
    D_0040E7A0=&pool->registry;
    return pool;
}
