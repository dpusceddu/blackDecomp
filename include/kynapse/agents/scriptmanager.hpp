// Path-way registry views; offsets are checked against PS2 construction and lookup.
#ifndef BLACK_CONTEXT_BEHAVIORS_SCRIPTMANAGER_HPP
#define BLACK_CONTEXT_BEHAVIORS_SCRIPTMANAGER_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
extern "C" int func_00360838(const char*,const char*);
extern "C" char* func_0035CBC0(char*,const char*);
namespace KaimScriptRegistry {
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
struct Script:ObjectRoot {
    char unknown04[8];
    Script() __asm__("func_002DF8C8");
    virtual ~Script();
    bool Load(ChildBuffers*) __asm__("func_002DF658");
};
struct Record:ObjectRoot {
    char name[128];Script* value;
    Record(const char*,Script*) __asm__("func_002DD428");
    virtual ~Record();
};
struct ScriptManager:ObjectRoot {
    Record** entries;unsigned int count,capacity;
    ScriptManager() __asm__("func_002DCAD8");
    virtual ~ScriptManager();
    virtual bool ConfigureAll(ChildBuffers*);
    virtual int Configure(ChildBuffers*) __asm__("func_002DD1E8");
    int Load(const char*,ChildBuffers*) __asm__("func_002DCC60");
    int Attach(const char*,Script*) __asm__("func_002DCF38");
    Script* Find(const char* key) {
        for(unsigned int i=0;i<count;++i)
            if(!func_00360838(key,entries[i]->name))return entries[i]->value;
        return 0;
    }
    Script* Lookup(const char*) __asm__("func_002DD2A8");
    bool Remove(const char*) __asm__("func_002DD340");
    void Grow() {
        capacity*=2;
        Record** replacement=(Record**)KaimAllocate(capacity*sizeof(Record*));
        for(unsigned int i=0;i<count;++i)replacement[i]=entries[i];
        memoryRelease(entries);entries=replacement;
    }
};
#define CHECK_OFFSET(T,m,o) typedef char T##m[(unsigned int)&((T*)0)->m==o?1:-1]
CHECK_OFFSET(ScriptManager,entries,4);CHECK_OFFSET(ScriptManager,count,8);CHECK_OFFSET(ScriptManager,capacity,12);
CHECK_OFFSET(Record,value,0x84);
#undef CHECK_OFFSET
typedef char RecordSize[sizeof(Record)==0x88?1:-1];
typedef char PathSize[sizeof(Script)==0xc?1:-1];
}
#endif
