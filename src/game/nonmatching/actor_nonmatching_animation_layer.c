// Unmatched: 0x1ac960: layer indexing and 64-bit-key ABI scheduling.
#ifdef NONMATCHING
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

#endif
