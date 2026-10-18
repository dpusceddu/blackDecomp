// Collision-definition layout and caller-visible storage requirements.
#include "physics/collision_storage.hpp"


#ifdef BLACK_NONMATCHING
// Unmatched: four instruction load/arithmetic scheduling difference after recovering result-first stack order.
extern "C" PhysicsCollisionDefinitionsLayout func_0032E3D0(const PhysicsSceneSettings* settings){
 PhysicsCollisionDefinitionsLayout layout;
 PhysicsStorageRequirement shapes,work;
 func_0037C190(&shapes,settings->solverJoints,settings->unknown38);func_0032FA70(&work,settings->pairBudget);

 layout.shapeAlignment=shapes.alignment;layout.shapeSize=shapes.size;layout.workAlignment=work.alignment;layout.workSize=work.size;
 unsigned shapeEnd=PhysicsAlignUp(sizeof(PhysicsCollisionDefinitions),shapes.alignment)+shapes.size;
 layout.total=PhysicsAlignUp(shapeEnd,work.alignment)+work.size;return layout;
}

#endif


#ifdef BLACK_NONMATCHING
// Unmatched: static vector temporary lifetimes and gp-relative opaque object addresses.
// Only addresses of these opaque objects are used; this view does not establish their allocation size.
extern "C" {extern char D_0040E858,D_0040E860;extern PhysicsVec D_0045CC70,D_0045CC80,D_0045CC90,D_0045CCA0;void* func_00100228(void*);void* func_00100258(void*);void func_00100260(void*,int);void func_00100230(void*,int);}
static inline PhysicsVec ConstantVector(float x,float y,float z){struct Storage{float x,y,z,w;} __attribute__((aligned(16)));Storage v;v.x=x;v.y=y;v.z=z;return *(PhysicsVec*)&v;}
extern "C" void func_0032E490(int initialize,int priority){
 if(priority==65535){if(initialize){
 func_00100228(&D_0040E858);func_00100258(&D_0040E860);
 struct Storage{float x,y,z,w;} __attribute__((aligned(16)));
 Storage a;a.x=1.5707963705062866f;a.y=-0.15915493667125702f;a.z=12582912.0f;PhysicsVec qa=*(PhysicsVec*)&a;
 Storage b;b.x=-0.15915493667125702f;b.y=0.5f;b.z=0.25f;PhysicsVec qb=*(PhysicsVec*)&b;
 Storage c;c.x=-76.57495880126953f;c.y=-41.3416748046875f;c.z=81.60222625732422f;PhysicsVec qc=*(PhysicsVec*)&c;
 Storage d;d.x=39.71065902709961f;d.y=6.283185005187988f;d.z=0.0f;PhysicsVec qd=*(PhysicsVec*)&d;
 D_0045CC70=qa;D_0045CC80=qb;D_0045CC90=qc;D_0045CCA0=qd;
 }else{func_00100260(&D_0040E860,2);func_00100230(&D_0040E858,2);}}
}

#endif


#ifdef BLACK_NONMATCHING
// Unmatched: temporary storage-wrapper copying and cumulative-offset register allocation.
// This four-byte wrapper is a source hypothesis; its complete type is unverified.
struct PhysicsStorageAddress {void* memory;PhysicsStorageAddress(void* p):memory(p){} PhysicsStorageAddress(const PhysicsStorageAddress& other){memory=other.memory;}};
extern "C" PhysicsCollisionDefinitions* func_0032E618(PhysicsStorageBlock* storage,const PhysicsSceneSettings* settings){
 PhysicsCollisionDefinitionsLayout layout=func_0032E3D0(settings);
 PhysicsCollisionDefinitions* definitions=(PhysicsCollisionDefinitions*)storage->memory;
 unsigned offset=PhysicsAlignUp(sizeof(PhysicsCollisionDefinitions),layout.shapeAlignment);
 PhysicsStorageAddress temporary((char*)definitions+offset);PhysicsStorageAddress shapes(temporary);
 offset+=layout.shapeSize;
 definitions->shapeDefinitions=func_0037C1F0(&shapes,settings->solverJoints,settings->unknown38);
 definitions->workMemory=(char*)definitions+PhysicsAlignUp(offset,layout.workAlignment);
 definitions->pairCapacity=settings->pairBudget;definitions->meshCount=settings->unknown38;definitions->shapeCount=settings->solverJoints;definitions->workSize=layout.workSize;
 return definitions;
}

#endif

extern "C" PhysicsStorageRequirement* func_0032E5D8(PhysicsStorageRequirement* storage,const PhysicsSceneSettings* settings){
 PhysicsCollisionDefinitionsLayout layout=func_0032E3D0(settings);storage->alignment=128;storage->size=layout.total;return storage;
}


extern "C" void func_0032E490(int,int);
extern "C" void func_0032E6D0(){func_0032E490(1,65535);}
extern "C" void func_0032E6F0(){func_0032E490(0,65535);}
