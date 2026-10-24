// PS2 pathway and script-waypoint storage. Unnamed virtual behavior remains unverified.
#ifndef BLACK_CONTEXT_BEHAVIORS_PATHWAY_HPP
#define BLACK_CONTEXT_BEHAVIORS_PATHWAY_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
extern "C" {
char* func_0035CBC0(char*,const char*);
unsigned int func_0035CCD8(const char*);
int func_00360838(const char*,const char*);
int func_0035CA74(const char*,const char*);
void* func_0035C544(void*,const void*,unsigned int);
void* func_0035C5F0(void*,const void*,unsigned int);
int func_0035D728(char*,const char*,...);
int func_0035D7B0(const char*,const char*,...);
}
extern const char* D_003C71F4;extern const char* D_003C71F8;extern const char* D_003C71FC;extern const char* D_003C7200;extern const char* D_003C7204;extern const char* D_003C7208;extern const char* D_003C720C;
namespace KaimPathData {
struct Vec3 {
 float x,y,z;
 Vec3(){}
 Vec3(float a,float b,float c):x(a),y(b),z(c){}
 Vec3(const Vec3& v):x(v.x),y(v.y),z(v.z){}
 Vec3& operator=(const Vec3& v){x=v.x;y=v.y;z=v.z;return *this;}
 Vec3& operator+=(const Vec3& v){x+=v.x;y+=v.y;z+=v.z;return *this;}
 Vec3 operator-(const Vec3& v)const{return Vec3(x-v.x,y-v.y,z-v.z);}
 float LengthSquared()const{return x*x+y*y+z*z;}
};
extern Vec3 gOrigin;
struct ObjectRoot {
 virtual ~ObjectRoot(){}
 static void* operator new[](unsigned int size){return KaimAllocate(size);}
 static void operator delete[](void* p){memoryRelease(p);}
 static void operator delete(void* p){memoryRelease(p);}
};
struct ScriptWP:ObjectRoot {
 Vec3 position;char mode[8];char action[64];
 #ifdef BLACK_PATHWAY_OUTLINE_WP
 ScriptWP() __asm__("func_002DF198");
#else
 ScriptWP():position(gOrigin){func_0035CBC0(mode,D_003C71F8);func_0035CBC0(action,D_003C7208);}
#endif
 virtual ~ScriptWP(){}
 void Reset(){position.z=0;position.x=0;position.y=0;func_0035CBC0(mode,D_003C71F4);func_0035CBC0(action,D_003C7208);}
};
struct FileService {
 virtual void Slot0();virtual void Slot1();virtual int Exists(const void*);
 virtual int Read(const void*,void*,unsigned int);virtual void Close(const void*);
};
struct Engine {void* vtable;FileService* files;int unknown08;float unit;};
extern Engine* gEngine;
struct PathWay:ObjectRoot {
 ScriptWP* records;unsigned int count;unsigned char closed;char name[0x103];unsigned int capacity;
 PathWay() __asm__("func_002DF230");
 PathWay(const PathWay&) __asm__("func_002DF380");
 virtual ~PathWay();
 virtual void Moved(unsigned int,unsigned int);
 virtual void SetChanged(char);
 PathWay& operator=(const PathWay&) __asm__("func_002DD548");
 int Load(const void*) __asm__("func_002DD778");
 int LoadFile(const void*) __asm__("func_002DDE28");
 int Save(const void*) __asm__("func_002DE3C0");
 void InsertPosition(const Vec3&,const char*,unsigned int) __asm__("func_002DE8F8");
 int Insert(const ScriptWP&,unsigned int) __asm__("func_002DEA40");
 int Move(unsigned int,unsigned int) __asm__("func_002DEE98");
 void Draw() __asm__("func_002DF060");
 int Remove(unsigned int index) {
  if(index>=count)return 0;
  {func_0035C5F0(records+index,records+index+1,(count-index-1)*sizeof(ScriptWP));--count;
   for(unsigned int i=index+1;i<=count;++i)Moved(i,i-1);
   return 1;
  }return 0;
 }
 int DeletePoint(unsigned int) __asm__("func_002DF3D8");
 int FindNear(const Vec3&,float) __asm__("func_002DF490");
 int Translate(const Vec3&) __asm__("func_002DF540");
 bool TranslateOne(const Vec3&,unsigned int) __asm__("func_002DF5A8");
 bool SetPosition(const Vec3&,unsigned int) __asm__("func_002DF608");
};
struct Hooks {
 char unknown00[0x4c];void (*drawLine)(const Vec3*,const Vec3*,int,int,int);
 void (*drawPoint)(const Vec3*,int,int,int);
 void* (*open)(const void*,const char*);void (*close)(void*);
 char unknown5c[4];char* (*getString)(char*,unsigned int,void*);
 unsigned int (*write)(const void*,unsigned int,unsigned int,void*);
 unsigned int (*read)(void*,unsigned int,unsigned int,void*);
};
extern Hooks hooks;
inline void DrawPoint(const Vec3* position,int a,int b,int c){if(hooks.drawPoint)hooks.drawPoint(position,a,b,c);}
inline void DrawLine(const Vec3* a,const Vec3* b,int c,int d,int e){if(hooks.drawLine)hooks.drawLine(a,b,c,d,e);}
inline ScriptWP* ByteOffset(ScriptWP* base,unsigned int bytes){return (ScriptWP*)(bytes+(unsigned int)base);}
typedef char WaypointSize[sizeof(ScriptWP)==0x58?1:-1];
typedef char PathSize[sizeof(PathWay)==0x114?1:-1];
#define CHECK_OFFSET(T,m,o) typedef char T##m[(unsigned int)&((T*)0)->m==o?1:-1]
CHECK_OFFSET(ScriptWP,position,4);CHECK_OFFSET(ScriptWP,mode,0x10);CHECK_OFFSET(ScriptWP,action,0x18);
CHECK_OFFSET(PathWay,records,4);CHECK_OFFSET(PathWay,count,8);CHECK_OFFSET(PathWay,closed,0xc);CHECK_OFFSET(PathWay,name,0xd);CHECK_OFFSET(PathWay,capacity,0x110);
#undef CHECK_OFFSET
}
#endif
