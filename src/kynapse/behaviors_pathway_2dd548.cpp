#include "include_asm.h"

#include "kynapse/agents/pathway.hpp"

namespace KaimPathData {

PathWay& PathWay::operator=(const PathWay& other){
 if(this!=&other){closed=other.closed;func_0035CBC0(name,other.name);count=other.count;capacity=count;
  if(count){records=new ScriptWP[count];func_0035C544(records,other.records,capacity*sizeof(ScriptWP));}else records=0;
 }return *this;
}

PathWay::PathWay(){closed=0;func_0035CBC0(name,D_003C720C);count=0;capacity=0;records=0;}

PathWay::PathWay(const PathWay& other){*this=other;}

PathWay::~PathWay(){func_0035CBC0(name,D_003C720C);closed=0;if(records){delete[]records;records=0;}}

int PathWay::Insert(const ScriptWP& record,unsigned int index){
 if(index==0xfffffffe)index=count;
 if(index>count)return 0;
 if(count==capacity){capacity+=5;ScriptWP* grown=new ScriptWP[capacity];
  func_0035C544(grown,records,index*sizeof(ScriptWP));grown[index]=record;
  func_0035C544(ByteOffset(grown,index*sizeof(ScriptWP))+1,ByteOffset(records,index*sizeof(ScriptWP)),(count-index)*sizeof(ScriptWP));
  delete[]records;records=grown;
 }else{func_0035C5F0(records+index+1,records+index,(count-index)*sizeof(ScriptWP));records[index]=record;}
 for(unsigned int i=count;i>index;--i)Moved(i-1,i);
 ++count;return 1;
}

int PathWay::DeletePoint(unsigned int index){return Remove(index);}

void PathWay::Draw(){
 for(int i=0;i<(int)count-1;++i){DrawPoint(&records[i].position,0,255,255);DrawLine(&records[i].position,&records[i+1].position,255,255,255);}
 if(count){DrawPoint(&records[count-1].position,0,255,255);if(closed==1)DrawLine(&records[count-1].position,&records[0].position,255,255,255);}
}

int PathWay::FindNear(const Vec3& position,float range){range=range*range*gEngine->unit*gEngine->unit;for(unsigned int i=0;i<count;++i){if((records[i].position-position).LengthSquared()<range)return i;}return -1;}

int PathWay::Translate(const Vec3& v){for(unsigned int i=0;i<count;++i)records[i].position+=v;return 1;}

// Unmatched: Load (1712 B), LoadFile (1428 B), and Save (1336 B) retain stream/temporary lifetime and branch-order differences.
// Unmatched: InsertPosition (328 B) and Move (452 B) retain exception cleanup scheduling differences.
// Unmatched: TranslateOne (96 B) and SetPosition (72 B) retain branch-layout differences.
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DD778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DDE28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DE3C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DE8F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DEE98);
