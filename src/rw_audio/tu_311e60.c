#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "rw_audio/property.h"
#endif

extern s32 func_00312AD0();
extern M2C_UNK D_00455FD0;
extern s32 func_00312510(M2C_UNK *, M2C_UNK);
extern M2C_UNK D_003CEA88;
extern s32 func_00317C20(M2C_UNK *, void *);
extern M2C_UNK D_00455FE0;

/* Provisional property-value TU from call and shared-data joins. */





#ifdef NON_MATCHING
extern void func_00312C70(void *);
extern void *func_00312C48(u32,u32);
extern void *func_0035C6EC(void *,s32,u32);
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
RwaPropertyClass *func_00311E60(RwaPropertyClass *type,RwaProperty *input,u32 inputs,RwaProperty *output,u32 outputs){
    u32 i,bytes;
    RwaProperty *property;
    if(type->input && type->output){
        if(!(type->flags&1))func_00312C70(type->input);
        type->input=0;type->output=0;
    }
    if(input && output){
        i=0;property=input;
        if(inputs)do{property->state=0;if(!func_00312880(property->descriptor))return 0;++i;++property;}while(i<inputs);
        i=0;property=output;
        if(outputs)do{property->state=0;if(!func_00312880(property->descriptor))return 0;++i;++property;}while(i<outputs);
        type->input=input;type->output=output;type->input_count=inputs;type->output_count=outputs;type->flags|=1;
    }else{
        bytes=(inputs+outputs)*sizeof(RwaProperty);
        input=(RwaProperty *)func_00312C48(bytes,0x3080b);
        type->input=input;
        if(!input)return 0;
        type->output=input+inputs;
        func_0035C6EC(input,0,bytes);
        type->flags&=~1u;
    }
    return type;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_00311E60);
#endif
#ifdef NON_MATCHING
extern u32 func_00312DB8(u32);
extern void *func_00317A78(RwaPool *,u32);
extern RwaValuePool D_003CEA60[5];
extern void *func_0035C544(void *,const void *,u32);
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
RwaValue *func_00312000(u32 type,const void *input,const void *output,RwaValue *value,u8 *storage){
    u32 size=func_00312DB8(type),key,i;
    if(!value){value=(RwaValue *)func_00317A78(&D_00455FE0,0x30803);value->flags=0;}else value->flags=1;
    if(!value)return 0;
    value->input=0;value->output=0;
    if(storage){
        value->flags|=2;
        if(input){value->input=storage;if(output)value->output=storage+func_00312DB8(type);}
        else if(output)value->output=storage;
    }else{
        if(input){key=func_00312DB8(type);for(i=0;i<5;++i)if(D_003CEA60[i].size==key)break;
            value->input=i<5?func_00317A78(D_003CEA60[i].pool,0x30803):0;
            if(!value->input)func_00312938(value);
        }
        if(output){key=func_00312DB8(type);for(i=0;i<5;++i)if(D_003CEA60[i].size==key)break;
            value->output=i<5?func_00317A78(D_003CEA60[i].pool,0x30803):0;
            if(!value->output){func_00312900(value);func_00312938(value);}
        }
    }
    if(input)func_0035C544(value->input,input,size);
    if(output)func_0035C544(value->output,output,size);
    func_00316758(value);value->type=type;value->parent=0;
    func_00312A40(D_00455FD0,value);
    return value;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_00312000);
#endif
#ifdef NON_MATCHING
extern RwaValue *func_00312B40(void *,RwaValue *);
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
void func_00312228(RwaValue *value,s32 recursive){
    RwaValue *child;
    void *data;
    u32 key,i;
    while((child=func_00312B40(D_00455FD0,value))!=0)if(recursive==1)func_00312228(child,1);
    if(!(value->type&0x1000)){}else{}
    if(!(value->flags&1))func_00317C20(&D_00455FE0,value);
    func_00312A80(D_00455FD0,value);func_00316668(value);
    if(!(value->flags&2)){
        data=value->input;
        if(data){key=func_00312DB8(value->type);for(i=0;i<5;++i)if(D_003CEA60[i].size==key){func_00317C20(D_003CEA60[i].pool,data);break;}}
        data=value->output;
        if(data){key=func_00312DB8(value->type);for(i=0;i<5;++i)if(D_003CEA60[i].size==key){func_00317C20(D_003CEA60[i].pool,data);break;}}
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_00312228);
#endif
#ifdef NON_MATCHING
extern void func_00312A10(void *),func_00317FC0(RwaPool *);
extern RwaPool *func_00317E40(u32,u32,u32,u32,RwaPool *,u32);
extern u32 D_0040E738,D_0040E0F8;
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
s32 func_003123B8(void){
    u32 i=0,j;
    func_00312A10(D_00455FD0);
    do{
        if(!func_00317E40(D_003CEA60[i].size,8,0x40,0,D_003CEA60[i].pool,0x40803) && i){j=i;do{--j;i=j;func_00317FC0(D_003CEA60[j].pool);}while(i);}
        ++i;
    }while(i<5);
    D_0040E738=0;D_0040E0F8=1;
    if(func_00317E40(0x28,0x10,0x40,0,&D_00455FE0,0x40803)){
        if(func_003128D8()==1)return 1;
        func_00317FC0(&D_00455FE0);
    }
    if(i)do{--i;func_00317FC0(D_003CEA60[i].pool);}while(i);
    D_0040E0F8=0;return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_003123B8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_00312510);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_00311FF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_003127B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_003127E0);

s32 func_00312880(s32 arg0) {
    s32 temp_2;

    if (M2C_FIELD(arg0, s32 *, 4) != 1) {
        goto block_6;
    }
    temp_2 = func_00312AD0((s32) &D_00455FD0, M2C_FIELD(arg0, s32 *, 0));
    if (temp_2 == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s32 *, 0) = temp_2;
    goto block_5;
block_3:
    return 0;
block_5:
    M2C_FIELD(arg0, s32 *, 4) = 0;
block_6:
    return arg0;
}

s32 func_003128D8(void) {
    return func_00312510(&D_003CEA88, 0xF) != 0;
}

void func_00312900(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 1)) {
        func_00317C20(&D_00455FE0, arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_311e60", func_00312938);
