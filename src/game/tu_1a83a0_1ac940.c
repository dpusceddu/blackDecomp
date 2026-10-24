#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001AE088();
extern s32 func_001AE078();
extern s32 func_001AE0F0();

void func_001AC940(s32 arg0) {
    func_001AE088(arg0 + 0x8F0);
}

#ifdef NON_MATCHING
// Unmatched: 0x1ac960: layer indexing and 64-bit-key ABI scheduling.
#include "ps2/prelude.h"
typedef struct { s64 key; void *value; int pad; } BkAnimationEntryPS2;
typedef struct { int a,b,count; BkAnimationEntryPS2 *entries; } BkAnimationMapPS2;
typedef struct { char pad[0x20]; BkAnimationMapPS2 *map; int unknown; void *first,*second,*third,*fourth,*fifth; } BkAnimationAssetPS2;
extern void *func_003843C0(void *,int), *func_003843D8(void *,int);
extern void func_001A8300(void *),func_001A8168(void *,void *,void *,void *),func_001ADC30(void *,signed char,char *),func_001ADD58(void *,char *),func_001A8350(void *,void *);
extern int func_001A51C8(void *,int,void *);
extern char D_0040D9C8,D_003F7060;
void func_001AC960(char *actor,int index,BkAnimationAssetPS2 *asset,int id,int flag,s64 key) {
 void *record=func_003843C0(asset->first,0);
 void *state=func_003843D8(asset->fourth,0);
 void *transition=func_003843D8(asset->second,0);
 void *value=0; int n; char *layer=actor+0x398+index*0x6c;
 func_001A8300(transition);
 for(n=0;n<asset->map->count;) {
  BkAnimationEntryPS2 *entry=&asset->map->entries[n++];
  if(entry->key==key) { value=entry->value; break; }
 }
 func_001A8168(layer,state,value,M2C_FIELD(actor,void **,0x940));
 func_001ADC30(layer,(signed char)flag,&D_0040D9C8);
 func_001ADD58(layer,&D_003F7060);
 if(transition)func_001A8350(layer,transition);
 while(!func_001A51C8(actor+0x470+index*0x240,id,layer)) {}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC960);
#endif

#ifdef NON_MATCHING
// Unmatched: 0x1acac8: map traversal pointer lifetimes and fallback control flow.
#include "ps2/prelude.h"
typedef struct {s64 key;void *value;int pad;} BkAssetEntryPS2;
typedef struct {int a,b,count;BkAssetEntryPS2 *entries;} BkAssetMapPS2;
typedef struct {char pad[0x28];BkAssetMapPS2 *transition,*secondary,*parameters,*primary;} BkAnimationAssetPS2;
typedef struct {s64 primary,secondary;u8 skip;} BkTransitionPS2;
extern char *D_0040F514;extern void *D_0040F50C;
extern void *func_003843C0(void *,int),*func_003843D8(void *,int);
extern void func_001A8300(void *),func_001A8168(void *,void *,void *,void *),func_001A8350(void *,void *),func_001AC940(void *,int);
extern void *func_001ACEB0(void *,s64,BkAnimationAssetPS2 *);
extern int func_001ACF88(void *,s64);
static inline void *find(BkAssetMapPS2 *map,s64 key) {
 int i=0;BkAssetEntryPS2 *entry=map->entries;
 while(i<map->count){if(entry->key==key)return entry->value;++i;++entry;}
 return 0;
}
void func_001ACAC8(char *actor,BkAnimationAssetPS2 *asset,int own) {
 BkAnimationAssetPS2 *fallback;int i;void *primary,*secondary,*frame;BkTransitionPS2 *transition;s64 key;int slot;char *layer;
 fallback=own?asset:M2C_FIELD(D_0040F514,BkAnimationAssetPS2 **,0x8518);
 if(own)for(i=0;i<fallback->parameters->count;i++)func_001A8300(func_003843D8(fallback->parameters,i));
 for(i=0;i<asset->transition->count;i++) {
  transition=func_003843C0(asset->transition,i);
  if(transition->skip)continue;
  key=asset->transition->entries[i].key;
  if(!own && find(fallback->transition,key))continue;
  primary=find(asset->primary,transition->primary);
  if(!primary && !own)primary=find(fallback->primary,transition->primary);
  secondary=0;
  if(transition->secondary) {
   secondary=find(asset->secondary,transition->secondary);
   if(!secondary && !own)secondary=find(fallback->secondary,transition->secondary);
   if(secondary)func_001A8300(secondary);
  }
  frame=func_001ACEB0(actor,key,asset);
  if(!own && !frame)frame=func_001ACEB0(actor,key,fallback);
  if(!frame)continue;
  slot=func_001ACF88(actor,key);
  if(slot==-1)continue;
  layer=actor+0xf8+slot*0x60;
  func_001A8168(layer,primary,frame,M2C_FIELD(actor,void **,0x944));
  if(secondary){func_001AC940(D_0040F50C,2);func_001A8350(layer,secondary);}
  for(slot=0;slot<fallback->parameters->count;slot++)func_001A8350(layer,func_003843D8(fallback->parameters,slot));
  func_001AC940(D_0040F50C,0);
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ACAC8);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ACEB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ACF88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ACFC0);

void func_001AD030(s32 arg0) {
    func_001AE078(arg0 + 0x8F0);
}

void func_001AD050(s32 arg0) {
    func_001AE0F0(arg0 + 0x8F0);
}
