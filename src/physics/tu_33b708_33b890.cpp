// Relocation fixup and the TU's guarded static initialization.
#include "physics/relocation.hpp"
#include "physics/scene.hpp"
#ifdef BLACK_NONMATCHING
// Unmatched: static vector temporary lifetimes and gp-relative opaque object addresses.
// Only addresses of these opaque objects are used; this view does not establish their allocation size.
extern "C" {extern char D_0040E938,D_0040E940;extern PhysicsVec D_0045E860,D_0045E870,D_0045E880,D_0045E890;void* func_00100228(void*);void* func_00100258(void*);void func_00100260(void*,int);void func_00100230(void*,int);}
static inline PhysicsVec ConstantVector(float x,float y,float z){struct Storage{float x,y,z,w;} __attribute__((aligned(16)));Storage v;v.x=x;v.y=y;v.z=z;return *(PhysicsVec*)&v;}
extern "C" void func_0033B708(int initialize,int priority){
 if(priority==65535){if(initialize){
 func_00100228(&D_0040E938);func_00100258(&D_0040E940);
 struct Storage{float x,y,z,w;} __attribute__((aligned(16)));
 Storage a;a.x=1.5707963705062866f;a.y=-0.15915493667125702f;a.z=12582912.0f;PhysicsVec qa=*(PhysicsVec*)&a;
 Storage b;b.x=-0.15915493667125702f;b.y=0.5f;b.z=0.25f;PhysicsVec qb=*(PhysicsVec*)&b;
 Storage c;c.x=-76.57495880126953f;c.y=-41.3416748046875f;c.z=81.60222625732422f;PhysicsVec qc=*(PhysicsVec*)&c;
 Storage d;d.x=39.71065902709961f;d.y=6.283185005187988f;d.z=0.0f;PhysicsVec qd=*(PhysicsVec*)&d;
 D_0045E860=qa;D_0045E870=qb;D_0045E880=qc;D_0045E890=qd;
 }else{func_00100260(&D_0040E940,2);func_00100230(&D_0040E938,2);}}
}

#endif
int PhysicsRelocatedHandle::Relocate(const PhysicsRelocationContext* context){
 data+=(unsigned)this-(unsigned)context->originalBase;
 func_00341B48((char*)this+0x10,context);
 return 1;
}

extern "C" void func_0033B708(int,int);
extern "C" void func_0033B890(){func_0033B708(1,65535);}
extern "C" void func_0033B8B0(){func_0033B708(0,65535);}
