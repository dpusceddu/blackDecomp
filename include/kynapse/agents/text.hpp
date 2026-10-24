// CScript byte-buffer view; text/size offsets and file slots follow the PS2 consumers.
#ifndef BLACK_CONTEXT_BEHAVIORS_TEXT_HPP
#define BLACK_CONTEXT_BEHAVIORS_TEXT_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
namespace KaimText {
struct ObjectRoot {virtual ~ObjectRoot() {}static void operator delete(void*p){memoryRelease(p);}};
struct FileService {
 virtual void Slot0();virtual void Slot1();virtual bool Open(const char*);virtual unsigned int Read(const char*,void*,unsigned int);virtual void Close(const char*);virtual unsigned int GetSize(const char*);
};
struct Engine {char unknown00[4];FileService*files;};extern Engine*gEngine;
struct Hooks {char unknown00[0x54];void*(*open)(const char*,const char*);void(*close)(void*);char unknown5c[8];unsigned int(*write)(const void*,unsigned int,unsigned int,void*);unsigned int(*read)(void*,unsigned int,unsigned int,void*);unsigned int(*seek)(void*,int,int);};extern Hooks hooks;
struct Script:ObjectRoot {
 char*text;unsigned int size;
 Script(const Script&) __asm__("func_002DF960");virtual ~Script();
 Script&operator=(const Script&);
 bool Load(const char*) __asm__("func_002DF658");bool LoadFile(const char*) __asm__("func_002DF7A8");bool SaveFile(const char*) __asm__("func_002DFA68");
};
typedef char ScriptSize[sizeof(Script)==12?1:-1];typedef char ScriptText[(unsigned int)&((Script*)0)->text==4?1:-1];typedef char ScriptLength[(unsigned int)&((Script*)0)->size==8?1:-1];
}
#endif
