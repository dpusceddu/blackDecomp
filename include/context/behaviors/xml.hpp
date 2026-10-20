// PS2 XML-reader stream interface. Parsing context and resource internals remain opaque.
#ifndef BLACK_CONTEXT_BEHAVIORS_XML_HPP
#define BLACK_CONTEXT_BEHAVIORS_XML_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
extern "C" void* func_0035D1A0(void*,const void*,unsigned int);
namespace KaimXmlReader {
struct Resource {
 char unknown00[8];void* file;char unknown0c[8];const char* name;
 const char* GetValue() const __asm__("func_002E3918");
};
struct Parser {
 unsigned int opaque;
 Parser(){}~Parser(){}
 int Parse(const char*,unsigned int,void*) __asm__("func_00373768");
};
struct XmlDataReader {
 virtual ~XmlDataReader();
 virtual int ReadAll(void*,void*) __asm__("func_00372FC0");
 virtual int Open(Resource*);
 virtual unsigned int Read(Resource*,void*,unsigned int) __asm__("func_00373300");
 virtual void Close(Resource*);
 virtual unsigned int Size(Resource*) __asm__("func_00373148");
};
struct Hooks {
 char unknown00[0x54];void*(*open)(const char*,const char*);void(*close)(void*);
 char unknown5c[12];unsigned int(*read)(void*,unsigned int,unsigned int,void*);
 int(*seek)(void*,int,int);unsigned int(*tell)(void*);
};
extern Hooks hooks;
typedef char ResourceFileOffset[(unsigned int)&((Resource*)0)->file==8?1:-1];
}
#endif
