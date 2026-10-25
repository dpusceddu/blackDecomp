#include "include_asm.h"

#include "kynapse/graph/tables.hpp"
extern const char D_00407950[],D_00407F08[];
extern const int D_00407968,D_00407F1C;

int Kaim::CPathCostData::Save(const void *path) {
 if (table && size > 0) {
  void *file = D_00451228.open(path,"wb");
  if (!file) return 0;
  {
   float savedScale=scale; int version=D_00407968;
   if(D_00451228.write(D_00407950,1,func_0035CCD8(D_00407950),file)==func_0035CCD8(D_00407950)) {
    int wrote=D_00451228.write(&version,4,1,file);
    if(wrote==1 && D_00451228.write(&savedScale,4,1,file)==wrote) {
     if(D_00451228.write(table,1,size*size,file)==size*size) { D_00451228.close(file); return 1; }
     D_00451228.close(file);
    }
   }
   return 0;
  }
 }
 return 0;
}

