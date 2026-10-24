#include "include_asm.h"

/* Provisional object-allocation TU from call and shared-data joins. */

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310C88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310DE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00310F68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00311008);

#ifdef NONMATCHING_RWA_310978
// Unmatched: typed object/class and property-link hypothesis differs in allocation and scheduling.
#include "rw_audio/object.h"
extern u32 D_0040E0E8;
extern RwaObjectOwner *func_00311430(void);
extern s32 func_0031DF28(RwaClass *,RwaClass *);
extern void *func_00312C48(u32,u32);
extern void func_00312C70(void *);
extern u32 func_003111A8(RwaClass *,u32,u32 *);
extern RwaObject *func_00311048(RwaClass *,u32 *,void *,u32);
extern const RwaIdBytes D_00409160;
extern s32 func_00316400(const void *,const void *);
extern void func_00310C88(RwaObject *,RwaClass *,u32,u32);
extern void func_0031E320(RwaObject *,s32,void *);
extern RwaValueLink *D_0040E720;
RwaObject *func_00310978(RwaClass *type,RwaObjectOwner *owner,u32 flags,void *defaults,RwaObjectAllocator allocate,void *user){
    u8 stack_defaults[512];
    RwaIdBytes tag;
    u32 offset,size,alignment,masked=flags&7;
    RwaObject *object=0,*raw,*aligned;
    void *temporary=0;
    if(D_0040E0E8){
        if(!owner)owner=func_00311430();
        if(!func_0031DF28(owner->type,type))return 0;
    }
    if(!defaults){
        defaults=stack_defaults;
        if(type->defaults_size>512){temporary=func_00312C48(type->defaults_size,0x1080c);defaults=temporary;if(!temporary)return 0;}
        if(type->defaults)type->defaults(0,defaults);else defaults=0;
    }
    size=func_003111A8(type,masked,&offset);
    alignment=1<<(type->extent_alignment>>28);
    if(alignment>64)size=size-64+alignment;
    if(allocate){object=allocate(type,user,defaults,size);if(object)masked|=0x20;}
    if(!object)object=func_00311048(type,&masked,defaults,size);
    tag=D_00409160;
    if(!func_00316400(&tag,type->id) && ((u32)object&(alignment-1))){
        raw=object;aligned=(RwaObject *)(((u32)raw-1+alignment)&~(alignment-1));
        if((u32)aligned-(u32)raw>=4){*(RwaObject **)((u8 *)aligned-4)=raw;masked|=8;}
        else{*(RwaObject **)((u8 *)aligned+size)=raw;masked|=0x10;}
        object=aligned;
    }
    if(!object){if(temporary)func_00312C70(temporary);return 0;}
    object->owner=owner;
    func_00310C88(object,type,masked,offset);
    if(D_0040E0E8){
        object->owner_link.previous=&owner->objects;
        object->owner_link.next=owner->objects.next;
        owner->objects.next->previous=&object->owner_link;
        owner->objects.next=&object->owner_link;
    }
    if(object->type->construct && !object->type->construct(object,owner,defaults,allocate,user)){
        if(temporary)func_00312C70(temporary);
        if(D_0040E0E8){object->owner_link.previous->next=object->owner_link.next;object->owner_link.next->previous=object->owner_link.previous;}
        func_0031E320(object,0,0);return 0;
    }
    if(temporary)func_00312C70(temporary);
    object->global_link.previous=(RwaValueLink *)&D_0040E720;
    object->global_link.next=D_0040E720;
    D_0040E720->previous=&object->global_link;
    D_0040E720=&object->global_link;
    return object;
}

#endif

#ifdef NONMATCHING_RWA_310C88
// Unmatched: typed object/class and property-link hypothesis differs in allocation and scheduling.
#include "rw_audio/object.h"
void func_00310C88(RwaObject *object,RwaClass *type,u32 flags,u32 offset){
    RwaObjectProperties *properties;
    RwaObjectProperty *input;
    RwaValueLink *output;
    u8 *data;
    u16 count;
    u32 i;
    object->type=type;object->flags=flags;
    data=(u8 *)object+offset;object->data=data;
    if(flags&1){
        if(data){
            properties=(RwaObjectProperties *)(data+(type->extent_alignment&0x0fffffff));
            if(flags&2)properties=(RwaObjectProperties *)((u8 *)properties+4);
        }else properties=(RwaObjectProperties *)((u8 *)object+((flags&2)?0x2c:0x28));
        input=(RwaObjectProperty *)((u8 *)properties+8);
        properties->input=input;
        properties->output=(RwaValueLink *)(input+type->properties->input);
        count=type->properties->input;i=0;
        if(count)do{
            RwaObjectProperty *p=input+i;
            p->self=p;p->link.next=(RwaValueLink *)p;p->link.previous=(RwaValueLink *)p;
            i=(i+1)&0xffff;
        }while(i<count);
        count=type->properties->output;i=0;
        if(count)do{
            output=properties->output+i;
            output->previous=output;output->next=output;i=(i+1)&0xffff;
        }while(i<count);
    }
    if(object->flags&2){
        if(object->data)data=object->data+(object->type->extent_alignment&0x0fffffff);
        else data=(u8 *)object+0x28;
        *(u32 *)data=0;
    }
    object->owner_link.next=0;
    object->property_link.previous=&object->property_link;
    object->property_link.next=&object->property_link;
    object->owner_link.previous=0;
}

#endif

#ifdef NONMATCHING_RWA_310DE8
// Unmatched: typed object/class and property-link hypothesis differs in allocation and scheduling.
#include "rw_audio/object.h"
extern RwaPool D_00455F80;
extern void func_00317C20(RwaPool *,void *);
RwaObject *func_00310DE8(RwaObject *object,s32 index,s32 direction){
    RwaObjectProperties *properties;
    RwaValueLink *link,*end;
    RwaConnection *connection;
    if(object->data){
        properties=(RwaObjectProperties *)(object->data+(object->type->extent_alignment&0x0fffffff));
        if(object->flags&2)properties=(RwaObjectProperties *)((u8 *)properties+4);
    }else properties=(RwaObjectProperties *)((u8 *)object+((object->flags&2)?0x2c:0x28));
    if(direction==1){
        link=properties->input[index].link.next;end=properties->input[index].link.previous;
        if(link!=end)do{
            connection=(RwaConnection *)((u8 *)link-0x14);link=link->next;
            connection->output_link.previous->next=connection->output_link.next;
            connection->output_link.next->previous=connection->output_link.previous;
            connection->input_link.previous->next=connection->input_link.next;
            connection->input_link.next->previous=connection->input_link.previous;
            func_00317C20(&D_00455F80,connection);
        }while(link!=end);
    }else{
        link=properties->output[index].next;end=properties->output[index].previous;
        if(link!=end)do{
            connection=(RwaConnection *)((u8 *)link-0xc);link=link->next;
            connection->output_link.previous->next=connection->output_link.next;
            connection->output_link.next->previous=connection->output_link.previous;
            connection->input_link.previous->next=connection->input_link.next;
            connection->input_link.next->previous=connection->input_link.previous;
            func_00317C20(&D_00455F80,connection);
        }while(link!=end);
    }
    return object;
}

#endif

#ifdef NONMATCHING_RWA_3111A8
// Unmatched: typed object/class and property-link hypothesis differs in allocation and scheduling.
#include "rw_audio/object.h"
u32 func_003111A8(RwaClass *type,u32 flags,u32 *offset){
    u32 local,size=0x28,alignment,value=type->extent_alignment;
    if(!offset)offset=&local;
    if(value&0x0fffffff){
        alignment=1<<(value>>28);
        *offset=(alignment+0x27)&-alignment;
        size=*offset+(type->extent_alignment&0x0fffffff);
    }else *offset=0;
    if(flags&2)size+=4;
    if(flags&1)size+=8+type->properties->input*12+type->properties->output*8;
    return size;
}

#endif

#include "rw_audio/object.h"
extern s32 func_0031E1F8(RwaClass *,s32,s32);
extern RwaObject *func_0031E2C0(RwaClass *,s32);
RwaObject *func_00311048(RwaClass *type,u32 *flags,void *defaults,s32 size){
    s32 allocation_flags=*flags;
    if(!type->field48){
        if(!func_0031E1F8(type,size,(allocation_flags>>2)&1))return 0;
    }
    return func_0031E2C0(type,size);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003110B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003111A8);
