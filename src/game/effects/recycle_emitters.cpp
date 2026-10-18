#include "game/effects/emitter_list.h"
extern "C" void func_001C08D0(BkTimedEmitterNodePS2 *);
extern "C" BkTimedEmitterNodePS2 *func_001C0760(BkEmitterListPS2 *list,BkTimedEmitterNodePS2 *released,f32 now) {
 BkTimedEmitterNodePS2 *previous=0,*node=list->head;
 volatile BkEffectPointPS2 spill;*(s128 *)&spill=*(s128 *)(list->definition+0x60);f32 lifetime=spill.y;
 while(node) {
  BkTimedEmitterNodePS2 *next=node->next;
  bool alive=node->Alive(now,lifetime);
  if(!alive) {
   if(previous)previous->next=next;else list->head=next;
   func_001C08D0(node);node->next=released;released=node;list->count--;
  }else previous=node;
  node=next;
 }
 return released;
}
