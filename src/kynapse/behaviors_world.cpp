#include "include_asm.h"

#include "kynapse/agents/world.hpp"
namespace KaimWorld {

void Engine::Reset() {
 for(ListIterator<Entity*> it(entities->head);it.node;it.node=it.node->next)it.node->value->Reset();
 for(unsigned int i=0;i<serviceCount;++i)((Service*)services[i])->Reset();
}

Entity* Engine::Find(const char* name) {
 for(ListIterator<Entity*> it(entities->head);it.node;it.node=it.node->next)
  {Entity* entity=it.node->value;if(!func_00360838(*(const char**)((char*)entity+4),name))return entity;}
 return 0;
}

void Engine::RemoveFirst(EntityCallback callback,void* context) {
 for(int i=0;i<(int)gFirstCount;++i)if(gFirstFunctions[i]==callback && gFirstContexts[i]==context) {
  --gFirstCount;for(;i<(int)gFirstCount;++i){gFirstFunctions[i]=gFirstFunctions[i+1];gFirstContexts[i]=gFirstContexts[i+1];}break;
 }
}

void Engine::RemoveSecond(EntityCallback callback,void* context) {
 for(int i=0;i<(int)gSecondCount;++i)if(gSecondFunctions[i]==callback && gSecondContexts[i]==context) {
  --gSecondCount;for(;i<(int)gSecondCount;++i){gSecondFunctions[i]=gSecondFunctions[i+1];gSecondContexts[i]=gSecondContexts[i+1];}break;
 }
}

static inline bool IsA(ClassInfo* wanted,ClassInfo* c) {
 do { if(wanted==c)return true; c=c->base; } while(c);return false;
}

Service* Engine::FindService(ClassInfo* wanted) {
 for(unsigned int i=0;i<serviceCount;++i)
  if(IsA(wanted,((Service*)services[i])->GetClassInfo()))return (Service*)services[i];
 return 0;
}

Service* Engine::FindExactService(ClassInfo* wanted) {
 for(unsigned int i=0;i<serviceCount;++i)if(wanted==((Service*)services[i])->GetClassInfo())return (Service*)services[i];return 0;
}

void Engine::RegisterFirst(EntityCallback callback,void* context) {
 if(gFirstCapacity==0) {
  gFirstCapacity=16;gFirstFunctions=(EntityCallback*)KaimAllocate(64);gFirstContexts=(void**)KaimAllocate(gFirstCapacity*4);
 }else if(gFirstCapacity==gFirstCount) {
  gFirstCapacity*=2;
  EntityCallback* functions=(EntityCallback*)KaimAllocate(gFirstCapacity*4);
  void** contexts=(void**)KaimAllocate(gFirstCapacity*4);
  for(int i=0;i<(int)gFirstCount;++i){functions[i]=gFirstFunctions[i];contexts[i]=gFirstContexts[i];}
  memoryRelease(gFirstFunctions);memoryRelease(gFirstContexts);gFirstFunctions=functions;gFirstContexts=contexts;
 }
 gFirstFunctions[gFirstCount]=callback;gFirstContexts[gFirstCount]=context;++gFirstCount;
}

void Engine::RegisterSecond(EntityCallback callback,void* context) {
 if(gSecondCapacity==0) {
  gSecondCapacity=16;gSecondFunctions=(EntityCallback*)KaimAllocate(64);gSecondContexts=(void**)KaimAllocate(gSecondCapacity*4);
 }else if(gSecondCapacity==gSecondCount) {
  gSecondCapacity*=2;
  EntityCallback* functions=(EntityCallback*)KaimAllocate(gSecondCapacity*4);
  void** contexts=(void**)KaimAllocate(gSecondCapacity*4);
  for(int i=0;i<(int)gSecondCount;++i){functions[i]=gSecondFunctions[i];contexts[i]=gSecondContexts[i];}
  memoryRelease(gSecondFunctions);memoryRelease(gSecondContexts);gSecondFunctions=functions;gSecondContexts=contexts;
 }
 gSecondFunctions[gSecondCount]=callback;gSecondContexts[gSecondCount]=context;++gSecondCount;
}
// Unmatched: Update retains iterator-return lifetimes and register allocation differences.
// Unmatched: Register and Unregister retain iterator-copy/destructor scheduling differences.
// Unmatched: World destructor retains callback-table address scheduling differences.
// Unmatched: Configure retains original array cleanup, temporary lifetimes and string/data ownership differences.
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_world", func_002EA898);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_world", func_002EABB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_world", func_002EAD58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_world", func_002EAF30);
