// Path-way registry views; offsets are checked against PS2 construction and lookup.
#ifndef BLACK_CONTEXT_BEHAVIORS_PATHMANAGER_HPP
#define BLACK_CONTEXT_BEHAVIORS_PATHMANAGER_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
extern "C" int func_00360838(const char*,const char*);
extern "C" char* func_0035CBC0(char*,const char*);
namespace KaimPathRegistry {
struct ObjectRoot {
    virtual ~ObjectRoot() {}
    static void* operator new(unsigned int size) {return KaimAllocate(size);}
    static void operator delete(void* p) {memoryRelease(p);}
};
struct ChildBuffers {
    char unknown00[12];char* first;char unknown10[16];unsigned int count;
    const char* GetSecond() const __asm__("func_002E3920");
    ChildBuffers* FindBySecond(const char*) const __asm__("func_002E31E0");
};
struct PathWay:ObjectRoot {
    char unknown04[0x110];
    PathWay() __asm__("func_002DF230");
    virtual ~PathWay();
    bool Load(ChildBuffers*) __asm__("func_002DD778");
};
struct Record:ObjectRoot {
    char name[128];PathWay* value;
    Record(const char*,PathWay*) __asm__("func_002DABF0");
    virtual ~Record();
};
struct PathManager:ObjectRoot {
    Record** entries;unsigned int count,capacity;
    PathManager() __asm__("func_002DA2A0");
    virtual ~PathManager();
    virtual bool ConfigureAll(ChildBuffers*);
    virtual int Configure(ChildBuffers*) __asm__("func_002DA9B0");
    int Load(const char*,ChildBuffers*) __asm__("func_002DA428");
    int Attach(const char*,PathWay*) __asm__("func_002DA700");
    PathWay* Find(const char* key) {
        for(unsigned int i=0;i<count;++i)
            if(!func_00360838(key,entries[i]->name))return entries[i]->value;
        return 0;
    }
    PathWay* Lookup(const char*) __asm__("func_002DAA70");
    bool Remove(const char*) __asm__("func_002DAB08");
    void Grow() {
        capacity*=2;
        Record** replacement=(Record**)KaimAllocate(capacity*sizeof(Record*));
        for(unsigned int i=0;i<count;++i)replacement[i]=entries[i];
        memoryRelease(entries);entries=replacement;
    }
};
#define CHECK_OFFSET(T,m,o) typedef char T##m[(unsigned int)&((T*)0)->m==o?1:-1]
CHECK_OFFSET(PathManager,entries,4);CHECK_OFFSET(PathManager,count,8);CHECK_OFFSET(PathManager,capacity,12);
CHECK_OFFSET(Record,value,0x84);
#undef CHECK_OFFSET
typedef char RecordSize[sizeof(Record)==0x88?1:-1];
typedef char PathSize[sizeof(PathWay)==0x114?1:-1];
}
#endif
