/* Provisional property-value TU from call and shared-data joins. */

#ifdef NONMATCHING_RWA_311E60
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
#include "rwa_ee/property.h"
extern void func_00312C70(void *);
extern void *func_00312880(void *);
extern void *func_00312C48(u32,u32);
extern void *func_0035C6EC(void *,s32,u32);
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

#endif

#ifdef NONMATCHING_RWA_312000
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
#include "rwa_ee/property.h"
extern u32 func_00312DB8(u32);
extern void *func_00317A78(RwaPool *,u32);
extern RwaPool D_00455FE0;
extern RwaValuePool D_003CEA60[5];
extern void func_00312938(RwaValue *),func_00312900(RwaValue *),func_00316758(RwaValue *),func_00312A40(void *,RwaValue *);
extern u8 D_00455FD0[];
extern void *func_0035C544(void *,const void *,u32);
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

#endif

#ifdef NONMATCHING_RWA_312228
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
#include "rwa_ee/property.h"
extern RwaValue *func_00312B40(void *,RwaValue *);
extern void func_00317C20(RwaPool *,void *),func_00312A80(void *,RwaValue *),func_00316668(RwaValue *);
extern u8 D_00455FD0[];
extern RwaPool D_00455FE0;
extern RwaValuePool D_003CEA60[5];
extern u32 func_00312DB8(u32);
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

#endif

#ifdef NONMATCHING_RWA_3123B8
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
#include "rwa_ee/property.h"
extern void func_00312A10(void *),func_00317FC0(RwaPool *);
extern RwaPool *func_00317E40(u32,u32,u32,u32,RwaPool *,u32);
extern RwaValuePool D_003CEA60[5];
extern RwaPool D_00455FE0;
extern u8 D_00455FD0[];
extern u32 D_0040E738,D_0040E0F8;
extern s32 func_003128D8(void);
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

#endif

#ifdef NONMATCHING_RWA_312510
// Unmatched: typed property/value ownership and allocation hypothesis differs in scheduling and register allocation.
#include "rwa_ee/property.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 * func_00312AD0(void *, s8 *);
extern M2C_UNK D_00455FD0;
extern void * func_00312000(s32, void *, void *, s32, s32);
extern s32 func_00312DB8(s32);
extern void * func_00316618(s32, s32);
extern void * func_003165C8(s32, s32);
extern s32 * func_00312228(s32 *, s32);

s32 func_00312510(s32 arg0, s32 arg1) {
    u8 sp[32] __attribute__((aligned(16)));
    s32 *temp_16;
    s32 *temp_2_2;
    s32 *var_16;
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_8;
    s32 var_19;
    s32 var_2;
    s32 var_30;
    s32 var_7;
    s8 **var_16_2;
    s8 *temp_5_2;
    s8 *temp_5_3;
    u32 var_17_2;
    u32 var_20;
    RwaValueSpec *temp_18;
    void *temp_2;
    void *temp_2_3;
    void *temp_2_4;
    void *temp_5;
    void *var_17;
    void *var_3;
    void *var_4;
    void *var_6;

    var_20 = 0;
    if (arg1 != 0) {
        var_30 = -0x10;
        var_2 = 0 << 5;
loop_2:
        temp_18 = (RwaValueSpec *)(arg0 + var_2);
        temp_4 = temp_18->type;
        switch (temp_4) {                           /* irregular */
        case 0x2000:
            var_19 = 0x2000;
            temp_16 = func_00312AD0(&D_00455FD0, temp_18->parent);
            *(s32 *)(sp + 4) = temp_18->size;
            *(s32 *)(sp + 0) = 0;
            temp_2 = func_00312000(0x2000, sp, (sp + 4), temp_18->object, temp_18->storage);
            var_17 = NULL;
            if (temp_2 != NULL) {
                if (temp_16 != NULL) {
                    M2C_FIELD(temp_2, s32 **, 0x18) = temp_16;
                    var_19 = M2C_FIELD(temp_16, s32 *, 0x14) | 0x4000;
                }
                var_17 = temp_2;
                M2C_FIELD(temp_2, s32 *, 0x14) = (s32) (M2C_FIELD(temp_2, s32 *, 0x14) | var_19);
            }
            break;
        case 0x4000:
            temp_2_2 = func_00312AD0(&D_00455FD0, temp_18->parent);
            var_3 = temp_18->data;
            temp_2_3 = var_3 + func_00312DB8(M2C_FIELD(temp_2_2, s32 *, 0x14));
            var_7 = temp_18->object;
            var_6 = temp_2_3;
            if ((var_3 == NULL) && (var_7 != 0)) {
                var_3 = M2C_FIELD(temp_2_2, void **, 0xC);
                var_7 = M2C_FIELD(temp_2_2, s32 *, 0x18);
loop_11:
                if (var_3 == NULL) {
                    if (var_7 != 0) {
                        goto loop_11;
                    }
                }
            }
            if ((temp_2_3 == NULL) && (var_7 != 0)) {
                var_6 = M2C_FIELD(temp_2_2, void **, 0x10);
                var_7 = M2C_FIELD(temp_2_2, s32 *, 0x18);
loop_16:
                if (var_6 == NULL) {
                    if (var_7 != 0) {
                        goto loop_16;
                    }
                }
            }
            temp_2_4 = func_00312000(M2C_FIELD(temp_2_2, s32 *, 0x14), var_3, var_6, var_7, temp_18->storage);
            var_17 = temp_2_4;
            if (temp_2_4 != NULL) {
                M2C_FIELD(temp_2_4, s32 **, 0x18) = temp_2_2;
                M2C_FIELD(temp_2_4, s32 *, 0x14) = (s32) (M2C_FIELD(temp_2_4, s32 *, 0x14) | 0x4000);
            } else {
block_29:
                var_17 = NULL;
            }
            break;
        default:
            temp_5 = temp_18->data;
            var_17 = func_00312000(temp_4, temp_5, temp_5 + temp_18->size, temp_18->object, temp_18->storage);
            break;
        case 0x1000:
            temp_5_2 = temp_18->parent;
            var_16 = NULL;
            if (temp_5_2 != NULL) {
                var_16 = func_00312AD0(&D_00455FD0, temp_5_2);
            }
            temp_4_2 = temp_18->object;
            temp_8 = temp_18->storage;
            if (var_16 != NULL) {
                var_4 = func_00312000(0x1000, M2C_FIELD(var_16, void **, 0xC), M2C_FIELD(var_16, void **, 0x10), temp_4_2, temp_8);
                if (var_4 != NULL) {
                    M2C_FIELD(var_4, s32 **, 0x18) = var_16;
                    goto block_31;
                }
                goto block_29;
            }
            var_4 = func_00312000(0x1000, NULL, NULL, temp_4_2, temp_8);
block_31:
            var_17 = var_4;
            break;
        }
        if (var_17 != NULL) {
            var_20 += 1;
            var_30 += 0x20;
            func_00316618((s32) var_17, temp_18->id);
            func_003165C8((s32) var_17, temp_18->name);
            var_2 = var_20 << 5;
            if (var_20 >= (u32) arg1) {
                goto block_41;
            }
            goto loop_2;
        }
        var_17_2 = var_20;
        if (var_20 != 0) {
            var_16_2 = var_30 + arg0;
            do {
                temp_5_3 = *var_16_2;
                var_16_2 = (s8 **)((u8 *)var_16_2 - 0x20);
                var_17_2 -= 1;
                func_00312228(func_00312AD0(&D_00455FD0, temp_5_3), 1);
            } while (var_17_2 != 0);
        }
        return 0;
    }
block_41:
    return arg0;
}

#endif
