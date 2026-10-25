#include "include_asm.h"

#include "game/effects/asset_views.hpp"

int Effects::Asset::FindFree() {
 int count=freeIndexCount,index=0;
 if(count) {int *entry=(int *)unknown64;
  do {if(*entry==-1)return index;++index;++entry;}while(index<count);
 }
 return -1;
}

