// Unmatched: 0x1acac8: map traversal pointer lifetimes and fallback control flow.
#ifdef NONMATCHING
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

#endif
