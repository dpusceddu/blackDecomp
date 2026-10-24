#include "auto/prelude.h"

#ifdef NONMATCHING_RWA_316C38
// Unmatched: 28 instructions in allocation failure layout and request store scheduling.
typedef struct AudioDescriptor { u8 prefix[0x14]; u16 rows, columns; } AudioDescriptor;
typedef struct AudioBuildRequest {
    s32 mode, reserved4, reserved8;
    void *(*allocate)(u32, void *);
    void *state;
    void *user;
} AudioBuildRequest;
typedef struct AudioChannelOptions { s32 count; s32 **items; } AudioChannelOptions;
extern u8 D_00409610[16], D_00409400[16];
extern AudioDescriptor *func_00311DB8(void *);
extern void *func_00312C48(s32,s32);
extern void *func_003176D0(u32,void *);
extern s32 *func_00310338(void *,AudioDescriptor *,AudioBuildRequest *);
extern void func_00312C70(void *);
extern void func_00310478(s32 *,s32);
extern s32 *D_0040E1B0;
extern s32 **D_0040E790;
extern s32 D_0040E1B8,D_0040E1AC;
extern s32 func_00310698(void *,s32,s32,void *);
extern void *D_0040E1B4;
extern void *func_00310870(void *,s32,s32,void *);
static inline s32 AudioObjectBytes(AudioDescriptor *d,s32 prefix) { return d->rows*8+(d->columns*8+prefix); }
static inline void AudioBuildRequestInit(AudioBuildRequest *p,u8 **c,u8 *memory) {
    p->reserved8=0; p->mode=2; p->reserved4=0;
    p->allocate=func_003176D0;
    p->state=c;
    p->user=memory;
    *c=memory+24;
}
s32 func_00316C38(void *input,void **inputs,s32 length) {
    AudioChannelOptions options;
    AudioBuildRequest request __attribute__((aligned(16)));
    u8 *cursor;
    AudioDescriptor *first,*second;
    u8 *memory;
    u32 index;
    first=func_00311DB8(D_00409610);
    second=func_00311DB8(D_00409400);
    memory=func_00312C48((length+1)*24 + AudioObjectBytes(first,28)+AudioObjectBytes(second,40) + length*4,0x3080E);
    if (memory==NULL) return 0;
    AudioBuildRequestInit(&request,&cursor,memory);
    D_0040E1B0=func_00310338(input,first,&request);
    if (D_0040E1B0==NULL) {func_00312C70(memory);return 0;}
    memory=cursor;
    D_0040E790=(s32 **)memory;
    memory+=length*4;
    index=0;
    if (length!=0) {
        do {
            cursor=memory+24;
            request.user=memory;
            D_0040E790[index]=func_00310338(inputs[index],second,&request);
            if (D_0040E790[index]==NULL) {
                while (index-- != 0) func_00310478(D_0040E790[index],0);
                func_00310478(D_0040E1B0,0);
                D_0040E1B8=0;
                D_0040E1B0=NULL;
                return 0;
            }
            ++index;
            memory=cursor;
        } while(index<(u32)length);
    }
    options.count=length;
    options.items=D_0040E790;
    D_0040E1AC=1;
    D_0040E1B8=length;
    func_00310698(D_0040E1B0,5,1,&options);
    D_0040E1B4=func_00310870(D_0040E1B0,1,2,NULL);
    return 1;
}
#endif



#ifdef NONMATCHING_RWA_3174F0
// Unmatched: 14 instructions in integer allocation around unsigned-to-float conversions.
extern u32 func_0031D510(void),func_0031D520(void);
extern u32 D_0040E1C8,D_0040E1C4;
void func_003174F0(void) {
    u32 now=func_0031D510();
    u32 frequency=func_0031D520();
    u32 elapsed;
    if(now<D_0040E1C8) {elapsed=now-1;elapsed-=D_0040E1C8;}
    else elapsed=now-D_0040E1C8;
    D_0040E1C4=(s32)(((f32)elapsed/(f32)frequency)*1000.0f)+D_0040E1C4;
    D_0040E1C8=now;
}
#endif

#ifdef NONMATCHING_RWA_3176E0
// Unmatched: 69 scalar FP allocation/scheduling differences across point and velocity transforms.
#include "rw_audio/emitter.h"
extern void func_002A75F0(RwaVec3 *,const RwaVec3 *);
void func_003176E0(RwaVec3 *value,const RwaListener *listener,void *driver) {
    RwaVec3 forward __attribute__((aligned(16)));
    RwaVec3 right __attribute__((aligned(16)));
    RwaVec3 up __attribute__((aligned(16)));
    RwaVec3 velocity;
    f32 x,y,z;
    func_002A75F0(&forward,&listener->forward);
    func_002A75F0(&right,&listener->right);
    func_002A75F0(&up,&listener->up);
    x=value[0].x-listener->position.x;
    y=value[0].y-listener->position.y;
    z=value[0].z-listener->position.z;
    value[0].x=forward.x*x+forward.y*y+forward.z*z;
    value[0].z=up.x*x+up.y*y+up.z*z;
    value[0].y=right.x*x+right.y*y+right.z*z;
    x=value[1].x-listener->velocity.x;
    y=value[1].y-listener->velocity.y;
    z=value[1].z-listener->velocity.z;
    velocity.x=x;velocity.y=y;velocity.z=z;
    value[1].z=up.x*velocity.x+up.y*velocity.y+up.z*velocity.z;
    value[1].x=forward.x*velocity.x+forward.y*velocity.y+forward.z*velocity.z;
    value[1].y=right.x*velocity.x+right.y*velocity.y+right.z*velocity.z;
}
#endif

#ifdef NONMATCHING_RWA_3178F0
// Unmatched: two nearest-listener load positions with -malign-loops=2.
#include "rw_audio/emitter.h"
extern u32 D_0040E1D0;
extern RwaListener *D_0040E1D4;
extern void *D_0040E798;
extern f32 D_0040E1DC[];
extern f32 (*D_0040E1D8)(void *,RwaListener *);
extern void func_003176E0(void *,const RwaListener *,void *);
extern s32 func_0031B030(void *,void *,void *,s32,s32);
s32 func_003178F0(void *driver,void *owner,RwaVec3 *value,void *result,s32 context,s32 flags) {
    RwaVec3 delta;
    void *entry;
    RwaListener *listener,*selected;
    f32 distance,bestDistance;
    switch(D_0040E1D0) {
    case 0:break;
    case 2: func_003176E0(value,D_0040E1D4,driver);break;
    case 3:
        entry=D_0040E798;
        bestDistance=D_0040E1DC[0];
        selected=NULL;
        if(entry!=&D_0040E798) {
            listener=(RwaListener *)((u8 *)entry-0x40);
            do {
                do {delta.x=listener->position.x-value[0].x;
                delta.y=listener->position.y-value[0].y;
                delta.z=listener->position.z-value[0].z;
                } while(0);
                distance=delta.x*delta.x+delta.y*delta.y+delta.z*delta.z;
                if(D_0040E1D8!=NULL) distance+=D_0040E1D8(owner,listener);
                entry=*(void **)entry;
                if(distance<bestDistance) {selected=listener;bestDistance=distance;}
                listener=(RwaListener *)((u8 *)entry-0x40);
            } while(entry!=&D_0040E798);
        }
        func_003176E0(value,selected,driver);
        break;
    }
    return func_0031B030(driver,value,result,context,flags);
}
#endif

#ifdef NONMATCHING_RWA_318550
// Unmatched: fifteen initial FP allocation/scheduling and parity-join alignment differences.
typedef struct AudioLengthVector {f32 x,y,z;} AudioLengthVector;
typedef union AudioLengthWord {f32 number;u32 word;u16 halves[2];} AudioLengthWord;
extern s16 D_003CED80[];
void func_00318550(AudioLengthWord *result, const AudioLengthVector *input) {
    result->number = (input->x * input->x + input->y * input->y) + input->z * input->z;
    if (result->number != 0.0f) {
        u32 bits = result->word;
        s16 exponent = (bits >> 23) - 127;
        result->word = bits & 0x7fffff;
        if (exponent & 1) {
            result->word |= 0x800000;
        }
        result->word = (D_003CED80[result->halves[1]] << 16) |
                       (((exponent >> 1) + 127) << 23);
    }
}
#endif

#ifdef NONMATCHING_RWA_318950
// Unmatched: five entry/head-copy instructions differ; all remaining release instructions match.
typedef struct AudioArenaLink {struct AudioArenaLink *next,*previous;} AudioArenaLink;
typedef struct AudioArenaChunk {struct AudioArenaChunk *next,*previous;u32 bytes;} AudioArenaChunk;
typedef struct AudioArenaBlock {AudioArenaLink link;AudioArenaChunk *first;u8 *end;} AudioArenaBlock;
typedef struct AudioArena {u32 flags,block_bytes,alignment;AudioArenaLink blocks,registry;} AudioArena;
extern void *func_00318A40(AudioArenaBlock*,u32,u32);
extern void func_00318B08(AudioArenaBlock*,void*);
extern s32 func_00318A28(AudioArenaBlock*);
extern void func_00318BC0(void*);
extern AudioArenaBlock *func_00318B60(u32);
static inline void ArenaRemoveLink(AudioArenaLink *node) {
    node->previous->next=node->next;
    node->next->previous=node->previous;
}
static inline void ArenaInsertAfter(AudioArenaLink *head,AudioArenaLink *node) {
    AudioArenaLink *next=head->next;
    node->previous=head;
    *(void **)node=next;
    head->next->previous=node;
    head->next=node;
}
static inline AudioArenaBlock *ArenaNewBlock(AudioArena *arena) {
    AudioArenaBlock *block=func_00318B60(arena->block_bytes);
    if(block==NULL)return NULL;
    ArenaInsertAfter(&arena->blocks,&block->link);
    return block;
}
static inline AudioArenaLink *ArenaHead(AudioArena *arena){return &arena->blocks;}
void func_00318950(AudioArena *arena,void *allocation) {
    AudioArenaLink *head=&arena->blocks;
    AudioArenaBlock *block=(AudioArenaBlock*)arena->blocks.next;
    while(&block->link!=ArenaHead(arena)) {
        if((u32)block<(u32)allocation && (u32)allocation<(u32)block+arena->block_bytes) {
            func_00318B08(block,allocation);
            if(func_00318A28(block)) {
                ArenaRemoveLink(&block->link);
                {AudioArenaLink *next=arena->blocks.next;if(next==head){block->link.next=next;block->link.previous=next;arena->blocks.next->previous=&block->link;arena->blocks.next=&block->link;}else func_00318BC0(block);}

            }
            break;
        }
        block=(AudioArenaBlock*)block->link.next;
    }
}
#endif

#ifdef NONMATCHING_RWA_318A40
// Unmatched: 22 chunk arithmetic/lifetime differences with -fno-expensive-optimizations; 32 with the primary recipe.
typedef struct AudioArenaLink {struct AudioArenaLink *next,*previous;} AudioArenaLink;
typedef struct AudioArenaChunk {struct AudioArenaChunk *next,*previous;u32 bytes;} AudioArenaChunk;
typedef struct AudioArenaBlock {AudioArenaLink link;AudioArenaChunk *first;u8 *end;} AudioArenaBlock;
static inline u8 *ArenaRound(u8 *address,u32 alignment){return (u8*)(((u32)(address+alignment-1))&-alignment);}
void *func_00318A40(AudioArenaBlock *block,u32 bytes,u32 alignment) {
    AudioArenaChunk *chunk=block->first;
    u32 required=bytes+sizeof(AudioArenaChunk);
    u32 inverseAlignment=-alignment;
    void *result=NULL;
    AudioArenaChunk *selected=NULL;
    do {
        AudioArenaChunk *next=chunk->next;
        u32 used=chunk->bytes;
        if((u32)next-(u32)chunk-sizeof(AudioArenaChunk)-used>=required) {
            selected=(AudioArenaChunk *)((u8 *)(chunk+1)+used);
            selected=(AudioArenaChunk *)(ArenaRound((u8*)(selected+1),alignment)-sizeof(AudioArenaChunk));
            if((u32)next<(u32)selected+required)selected=NULL;
            else if((u32)selected<(u32)chunk+used+sizeof(AudioArenaChunk))selected=NULL;
            else break;
        }
        chunk=next;
    } while(chunk!=(AudioArenaChunk *)block->end);
    if(selected!=NULL) {
        AudioArenaChunk *next=chunk->next;
        selected->previous=chunk;
        selected->next=next;
        if(next!=(AudioArenaChunk *)block->end)next->previous=selected;
        if(selected->previous!=(AudioArenaChunk *)block->end)selected->previous->next=selected;
        selected->bytes=bytes;
        result=selected+1;
    }
    return result;
}
#endif

#ifdef NONMATCHING_RWA_QUEUE
// Unmatched: request/constant allocation, repeated address materialization and immediate-dispatch scheduling; no recorded states.
#include "auto/prelude.h"
typedef struct AudioIoOperation AudioIoOperation;
typedef struct AudioIoOwner {u32 mode,parameter,status;void*stream;}AudioIoOwner;
typedef void (*AudioIoCallback)(s32,s32,s32,s32,void*);
struct AudioIoOperation {
 AudioIoOperation *next,*previous;
 u32 state,offset,total,remaining;
 void *destination;
 s32 file;
 u32 field20,result,block_position,block_bytes;
 void *buffer;
 void *context;
 AudioIoCallback callback;
 void *user;
};
typedef struct AudioIoRequest {AudioIoOwner *owner;AudioIoOperation operation;}AudioIoRequest;
typedef struct AudioIoQueue {s32 semaphore,signal;AudioIoOperation*next,*previous,*active;}AudioIoQueue;
extern AudioIoQueue D_004584C0;
extern s32 D_004584C4[];
extern volatile s32 D_0040E214;
extern s32 func_003678A0(s32),func_00367880(s32),func_0031D2A8(s32*);
extern void func_00318E80(s32,s32,s32,s32,void*);
void func_00319828(AudioIoRequest *request,void *destination,u32 bytes,AudioIoCallback callback,void *user)
{
 volatile AudioIoOperation *operation=&request->operation;
 AudioIoQueue *queue;
 s32 file;
 operation->state=3;
 file=(s32)request->owner->stream;
 operation->remaining=bytes;
 operation->file=file;
 operation->destination=destination;
 operation->callback=callback;
 operation->user=user;
 operation->total=bytes;
 if(D_0040E214==2)func_003678A0(D_004584C4[0]);
 queue=&D_004584C0;
 if(func_0031D2A8(&queue->semaphore)!=0){
  queue->active=(AudioIoOperation*)operation;
  if(D_0040E214==2)func_00367880(queue->signal);
  func_00318E80(operation->file,operation->total,0,1,request);
 }else{
  operation->next=queue->next;
  operation->previous=(AudioIoOperation*)&queue->next;
  queue->next->previous=(AudioIoOperation*)operation;
  queue->next=(AudioIoOperation*)operation;
  operation->state=2;
  if(D_0040E214==2)func_00367880(queue->signal);
 }
}
#endif

#ifdef NONMATCHING_RWA_SHUTDOWN
// Unmatched: Seven scheduling/branch differences; first Wait/Delete transition and nested conditional load duplication.
#include "auto/prelude.h"
extern s32 D_0040E214;
extern s32 D_00458490[];
extern s32 D_004584C4[];
typedef struct Queue {s32 semaphore,signal;void *pending[2],*active;}Queue;extern Queue D_004584C0;
extern s32 func_003678A0(s32);
extern s32 func_00367870(s32);
void func_003192D8(void){s32 mode;if(D_0040E214==2)func_003678A0(D_00458490[0]);func_00367870(D_00458490[0]);mode=D_0040E214;if(mode==2){func_003678A0(D_004584C4[0]);if(D_0040E214==mode)func_003678A0(D_004584C0.semaphore);}func_00367870(D_004584C4[0]);func_00367870(D_004584C4[-1]);}

#endif

#ifdef NONMATCHING_RWA_SEEK
// Unmatched: Seventeen allocation/scheduling differences; requested offset and aligned block use opposite temporary roles.
#include "auto/prelude.h"
typedef void(*Callback)(s32,u32,s32,s32,void*);
typedef struct Request{u8 prefix[0x10];u32 position;u8 unknown14[12];s32 operationFile;u8 unknown24[32];u32 phase;Callback completion;void*user;u32 target;void*record;u32 pending;s32 file;u32 block;}Request;
typedef struct Cache{u8 bytes[8192];void*owner;s32 file;u32 position,count;}Cache;
extern Cache D_00456480;
extern void func_00318E80(s32,u32,s32,s32,void*);
extern s32 func_00324CB0(s32,u32,Callback,void*);
void func_003194D8(Request*request,u32 offset,Callback completion,void*user){u32 block;request->position=offset;block=(offset>>13)<<13;request->completion=completion;request->user=user;request->phase=3;request->block=block;if(D_00456480.file==request->operationFile && offset>=D_00456480.position && offset<D_00456480.position+D_00456480.count){func_00318E80(D_00456480.file,offset,0,4,request);}else{func_00324CB0(request->file,block,func_00318E80,request);}}

#endif

#ifdef NONMATCHING_RWA_RECORD_COMPLETE
// Unmatched: 22 instructions in shared error cleanup and completion arguments; no recorded states.
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
typedef struct RwaIoRecordHeader{u32 id,next_offset,size;}RwaIoRecordHeader;
extern void func_00319628(void*,u32,s32,s32,void*);
extern void func_00319828(RwaIoRequest*,u32,u32,RwaIoCallback,void*);
extern void func_00318E80(void*,u32,s32,s32,void*);
extern s32 func_0032A938(void*);
extern s32 func_00324CB0(s32,u32,RwaIoCallback,void*);
#define Record(r) ((RwaIoRecordHeader*)((r)->record))
void func_003196D8(void *file,u32 bytes,s32 status,s32 reason,RwaIoRequest *request) {
    s32 position;
    if(status==4) {
        request->phase=0;
        Record(request)->id=0;
        Record(request)->size=0;
        Record(request)->next_offset=0;
        request->completion(request->owner->stream,0,4,reason,request->user);
        return;
    }
    if(request->scan_pending) {
        request->scan_pending=0;
        func_00319828(request,(u32)request->record,12,func_00319628,request);
        return;
    }
    if(Record(request)->id==request->target_id) {
        request->phase=0;
        request->completion(request->owner->stream,12,status,reason,request->user);
        return;
    }
    request->scan_pending=1;
    position=func_0032A938(request->owner->stream);
    if(position<0) {
        Record(request)->next_offset=0;
        Record(request)->size=0;
        Record(request)->id=0;
        request->completion(request->owner->stream,0,4,reason,request->user);
        return;
    }
    request->field60=position+Record(request)->next_offset;
    func_00324CB0(request->file,position+Record(request)->next_offset,func_00318E80,request);
}

#endif

#ifdef NONMATCHING_RWA_CANCEL
// Unmatched: 20 instructions in queue-address lifetimes and the final conditional signal join; no recorded states.
typedef struct IoOperation IoOperation;
typedef void(*IoCallback)(void*,u32,s32,s32,void*);
struct IoOperation{IoOperation*next,*previous;u32 state,position,length,remaining;u8*destination;s32 file;u32 field20,result,block_position,block_size;u8*buffer;void*owner;IoCallback callback;void*user;};
typedef struct IoRequest{void*owner;IoOperation operation;}IoRequest;
typedef struct IoQueue{s32 semaphore,signal;IoOperation*next,*previous,*active;}IoQueue;
typedef struct IoCache{u8 buffer[8192];IoOperation*operation;s32 file;u32 position,bytes;}IoCache;
typedef char IoOperationIs64[sizeof(IoOperation)==64?1:-1];
extern IoQueue D_004584C0;
extern IoCache D_00456480;
extern s32 D_0040E214,D_00458490[],D_004584C4[];
extern s32 func_003678A0(s32),func_00367880(s32),func_0031D2A8(s32*);
extern void func_00318E80(void*,u32,s32,s32,void*);
void func_00318D28(IoRequest *request) {
    IoOperation *operation=&request->operation;
    s32 mode=D_0040E214;
    s32 complete=0;
    if(mode==2) {
        func_003678A0(D_00458490[0]);
        if(D_0040E214==mode)func_003678A0(D_004584C4[0]);
    }
    if(func_0031D2A8(&D_004584C0.semaphore)==0) {
        if(D_004584C0.active==operation) {
            operation->remaining=0;
            operation->state=3;
            complete=1;
        }
        if(D_00456480.operation==operation) {
            D_00456480.operation=NULL;
            D_00456480.file=0;
        }
    } else if(D_0040E214==2)func_00367880(D_004584C0.semaphore);
    if(operation->next!=NULL) {
        operation->previous->next=operation->next;
        operation->next->previous=operation->previous;
        operation->state=1;
        operation->next=NULL;
    }
    mode=D_0040E214;
    if(mode==2) {
        func_00367880(D_004584C4[0]);
        if(D_0040E214==mode)func_00367880(D_00458490[0]);
    }
    if(complete)func_00318E80((void*)operation->file,0,2,1,request);
}
#endif

#if defined(NONMATCHING_RWA_GAIN) || defined(NONMATCHING_RWA_PAUSE)
#include "rw_audio/emitter.h"
/* Accessed playback prefix; this view does not establish its allocation size. */
typedef struct RwaPlaybackAccess {u8 prefix[0x28];RwaEmitter emitter;} RwaPlaybackAccess;
typedef char PlaybackEmitterAt28[((int)&((RwaPlaybackAccess*)0)->emitter==0x28)?1:-1];
#endif

#ifdef NONMATCHING_RWA_GAIN
// Unmatched: ten FP allocation/scheduling and branch-join alignment differences; no recorded states.
extern s32 func_003106F0(void*,s32,s32,f32);
RwaPlaybackAccess *func_0031A410(RwaPlaybackAccess *playback,u32 selector,const f32 *value) {
    playback->emitter.gain=(u8)(*value*255.0f);
    if(playback->emitter.handle!=NULL)
        func_003106F0(playback->emitter.handle,7,1,*value);
    return playback;
}
#endif

#ifdef NONMATCHING_RWA_PAUSE
// Unmatched: two restore-order differences with -fno-schedule-insns2; three prologue-load differences otherwise.
extern void func_00317340(RwaEmitter*,u32);
extern s32 D_0040E1C4;
static inline void PausePlayback(RwaPlaybackAccess *playback,s32 pause) {
    if(pause) {
        func_00317340(&playback->emitter,0);
        playback->emitter.last_tick=D_0040E1C4;
    } else {
        func_00317340(&playback->emitter,1);
    }
}
RwaPlaybackAccess *func_0031A498(RwaPlaybackAccess *playback,u32 selector,const s32 *value) {
    PausePlayback(playback,*value);
    return playback;
}
#endif
