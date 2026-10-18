/* Medium-confidence playback/voice TU from shared data and call edges. */
#ifdef NONMATCHING_RWA_PLAYBACK
#include "rwa_ee/voice.h"
extern s32 func_0031C968(RwaPlaybackState *);
extern s32 func_00316190(RwaVoice *);
extern s32 func_00324F98(void);
extern void func_0031D528(RwaVoice *,u32,void *);
extern u32 func_00313098(void);
extern void *func_0031CCE8(RwaPlaybackState *,void *);
extern void *func_0031CD10(RwaPlaybackState *,void *);
extern RwaVoice *func_0031CDE8(RwaVoice *,const s32 *);
extern RwaVoice *func_0031CE30(RwaVoice *,const s32 *);
// Unmatched: channel loop scheduling and saved-register allocation differ.
s32 func_0031BD20(RwaPlaybackState *state) {
    RwaRequest *request;u32 write,index,offset,result=0; s32 fallback=0;
    if(state->status.bits&((u64)0x9000<<21))return 0;
    request=state->request;
    if(request){
        write=state->read_index;
        if(request->flags&8){state->saved_read=write;state->status.words.high|=1;}
        if(state->status.words.high&4)state->status.words.high&=~4;
    }else{
        fallback=1;request=&state->fallback;
        if(func_0031C968(state)&&!(state->status.words.high&0x40))write=state->read_index;else write=state->write_index;
        {u32 end=write?write:state->ring_count;state->fallback.tag=(RwaIdBytes *)&state->ring[end-1];state->active_ring=end-1;}
        if(!(state->status.words.high&4)||state->filled_channels==state->voice_count)state->filled_channels=0;
        state->status.words.high|=4;
    }
    offset=write*state->frame_bytes;index=state->next_voice;
    while(index<state->voice_count){
        RwaVoice *voice=state->voices+index;
        s32 busy=(state->status.words.high&0x20)?func_00316190(voice):func_00324F98();
        if(busy)break;
        func_0031D528(voice,offset,request->data+index*state->frame_bytes);
        if(state->filled_channels>=state->voice_count)break;
        ++state->filled_channels;++index;
    }
    if(index==state->voice_count)index=0;
    if(state->filled_channels==state->voice_count){
        *(RwaIdBytes *)&state->ring[write]=*request->tag;
        if(++write==state->ring_count)write=0;
        state->write_index=write;
        if(fallback){
            if(!func_0031C968(state)||(state->status.words.high&0x40)){state->next_voice=index;return 0;}
            state->ring[state->active_ring].ready=1;state->status.words.high|=0x40;result=1;
        }else{
            state->ring[state->active_ring].ready=1;state->queued_bytes+=state->output_chunk;state->read_index=state->write_index;result=1;
        }
    }
    state->next_voice=index;return result;
}
// Unmatched: callback stack records and list traversal scheduling differ.
s32 func_0031BFE8(RwaDriverContext *context) {
    RwaPlaybackState *state=context->state;u32 mode=state->voices->channel.playback->mode,index;RwaLink *node,*sentinel;u32 status;struct {u32 first,second,third,fourth,extra,one;} settings;
    settings.one=1;
    if(mode==3||mode==1||(state->status.words.high&8)){
        if(state->epoch<func_00313098()){
            sentinel=state->owners;node=sentinel->previous;
            while(node!=sentinel){if(!func_0031CCE8((RwaPlaybackState *)((char *)node-0xc4),&settings.extra))break;node=node->previous;}
            sentinel=state->owners;node=sentinel->previous;
            while(node!=sentinel){if(!func_0031CD10((RwaPlaybackState *)((char *)node-0xc4),&settings))break;node=node->previous;}
        }
        if(state->advance){
            RwaVoice *voice=state->voices;
            for(index=0;index<state->voice_count;++index,++voice)if(!func_0031CDE8(voice,(s32 *)&state->position))break;
            voice=state->voices;
            for(index=0;index<state->voice_count;++index,++voice)if(!func_0031CE30(voice,(s32 *)&settings.one))break;
            state->status.words.high&=~8;status=6;
        }else status=4;
    }else status=6;
    context->status=status;return status;
}

#endif

#ifdef NONMATCHING_RWA_VOICE_CREATE
#include "rwa_ee/voice.h"
typedef struct RwaFormatList {u32 field00;RwaFormat **formats;u32 count;} RwaFormatList;
typedef struct RwaPluginRecord {u8 fields00[0x54];RwaFormatList *format_list;} RwaPluginRecord;
typedef struct RwaDescription {u8 fields00[0x14];RwaFormat *format;u32 field18;u16 mode;} RwaDescription;
typedef struct RwaVoiceBuildArgs {u8 fields00[0x1c];RwaDescription *description;u8 fields20[0x10];u32 enabled;void *user;} RwaVoiceBuildArgs;
extern RwaPluginRecord *func_0031DEB8(s32,const void *,void *);
extern RwaFormatId D_00409F20,D_0040A260;
extern s32 func_003150D0(RwaFormat *,RwaFormat *);
extern void *func_00312C48(u32,u32);
extern s32 func_00311248(void *);
extern u32 func_00314F08(RwaFormat *,u32);
extern RwaVoice *func_00328C08(void *,RwaFormat *,RwaFormat *,void *,RwaVoice *);
extern void *func_00327F20(void *,void *,s32,void *,void *);
extern s32 func_0031C4E8(s32,void *,s32,s32);
extern void func_00328140(RwaChannel *,RwaVoice *);
extern void func_003281B0(RwaChannel *,f32);
extern void func_00328180(RwaChannel *,f32);
// Unmatched: format search, stack callback lifetimes and channel allocation differ.
u32 func_0031C1C8(RwaDriverContext *context,void *driver,RwaVoiceBuildArgs *args,u32 callback0,u32 callback1) {
    RwaPlaybackState *state=context->state;
    RwaDescription *description=args->description;
    RwaFormat local=*description->format,*selected=&local;
    RwaFormatList *list=func_0031DEB8(0,&D_00409F20,0)->format_list;
    RwaFormat **format=list->formats;
    u32 index,channels=1,created,offset; s32 plugin;
    struct {u32 first,second;RwaChannel *channel;} callback;
    do {
        for(index=0;index<list->count;++index,++format)if(func_003150D0(*format,&local))goto found;
        if(--local.channels==0){selected=0;break;}
    }while(1);
found:
    if(!selected)return 0;
    if(description->mode==1){local.channels=1;channels=description->format->channels;}
    state->voices=func_00312C48(channels*0x130,0x30809);
    plugin=func_00311248(func_0031DEB8(0,&D_0040A260,0));
    callback.first=callback0;callback.second=callback1;
    state->frame_bytes=state->chunk_size/channels;
    local.extent=state->frame_bytes*state->ring_count;local.field19=1;
    state->source_channels=description->format->channels;
    state->ring_size=func_00314F08(&local,(u32)local.extent);state->output_chunk=func_00314F08(&local,state->chunk_size);state->voice_bytes=state->output_chunk/channels;
    for(created=0,offset=0;created<channels;++created,offset+=0x130){
        RwaVoice *voice=(RwaVoice *)((u8 *)state->voices+offset);
        RwaSound *sound=(RwaSound *)voice;u32 flags;
        if(!func_00328C08(driver,&local,&local,args->user,voice))return 0;
        flags=sound->flags;sound->flags=flags|0x20;sound->flags=args->enabled?(flags|0x60):((flags|0x20)&~0x40);
        callback.channel=&voice->channel;
        if(!func_00327F20(driver,0,plugin,(void *)func_0031C4E8,&callback))return 0;
        func_00328140(callback.channel,voice);func_003281B0(callback.channel,0.0f);
    }
    if(channels==2){func_00328180(&state->voices[0].channel,-1.0f);func_00328180(&state->voices[1].channel,1.0f);}
    else if(channels==1)func_00328180(&state->voices[0].channel,0.0f);
    state->voice_count=channels;return channels;
}

#endif
