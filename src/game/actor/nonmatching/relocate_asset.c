// Unmatched: 0x1af930: asset relocation loop scheduling and register lifetimes.
#ifdef NONMATCHING
#include "auto/prelude.h"
#include "game/actor/asset.h"
extern void func_001C64E8(void *),func_0027E760(void *),func_001AFFD8(void *,void *,void *);
extern char *D_0040F4C0;
#define RELOCATE(member) if(asset->member) asset->member=(__typeof__(asset->member))((unsigned int)asset->member+(unsigned int)asset)
void func_001AF930(BkActorAssetPS2 *asset) {
 int i,offset;void **entry;BkActorAssetRecordPS2 *record;int recordOffset;
 RELOCATE(unknown64);RELOCATE(renderData);RELOCATE(unknown54);RELOCATE(unknown58);RELOCATE(links);
 RELOCATE(linkIndices);RELOCATE(strings);RELOCATE(unknown40);RELOCATE(objects);RELOCATE(records);
 i=0;offset=0;
 if(asset->renderCount>0)do {++i;func_001C64E8(asset->renderData+offset);offset+=0x30;}while(i<asset->renderCount);
 for(i=0;i<asset->objectCount;i++) {
  entry=(void **)(i*4+(unsigned int)asset->objects);
  if(*entry)*entry=(void *)((unsigned int)*entry+(unsigned int)asset);
 }
 for(i=0;i<asset->linkCount;i++) {
  entry=(void **)(i*4+(unsigned int)asset->links);
  if(*entry)*entry=(void *)((unsigned int)*entry+(unsigned int)asset);
 }
 for(i=0,offset=0;i<asset->recordCount;i++,offset+=0xd0) {
  record=(BkActorAssetRecordPS2 *)((char *)asset->records+offset);
  if(record->object)record->object=(void *)((unsigned int)record->object+(unsigned int)asset);
  record=(BkActorAssetRecordPS2 *)((char *)asset->records+offset);
  if(record->auxiliary)record->auxiliary=(void *)((unsigned int)record->auxiliary+(unsigned int)asset);
  recordOffset=i*0xd0;record=(BkActorAssetRecordPS2 *)((char *)asset->records+recordOffset);
  if(record->object)func_0027E760(record->object);
  record=(BkActorAssetRecordPS2 *)((char *)asset->records+recordOffset);
  if(record->links)record->links=(void *)((unsigned int)record->links+(unsigned int)asset);
 }
 i=0;offset=0;
 if(asset->renderCount>0)do {
  short stringOffset;
  ++i;stringOffset=*(short *)(asset->linkIndices+offset);offset+=6;
  func_001AFFD8(D_0040F4C0+0xcd70,asset->strings+stringOffset,asset->objects);
 }while(i<asset->renderCount);
}
#undef RELOCATE

#endif
