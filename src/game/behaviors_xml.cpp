#include "include_asm.h"

#include "kynapse/agents/xml.hpp"
extern const char D_0040C418[];
namespace KaimXmlReader {

int XmlDataReader::ReadAll(void* file,void* context){
 if(!file)return 0;
 char chunk[1024];char* contents=0;unsigned int size=0,read;
 do{
  read=hooks.read(chunk,1,1024,file);
  if(read){unsigned int nextSize=size+read;char* next=(char*)KaimAllocate(nextSize);
   if(contents){func_0035D1A0(next,contents,size);memoryRelease(contents);}
   func_0035D1A0(next+size,chunk,read);contents=next;size=nextSize;
  }
 }while(read==1024);
 if(!contents)return 0;
 Parser parser;int result=parser.Parse(contents,size,context);memoryRelease(contents);return result;
}
unsigned int XmlDataReader::Size(Resource* resource){
 void* file=resource->file;unsigned int result;
 if(file){unsigned int position=hooks.tell(file);hooks.seek(file,0,2);
  result=hooks.tell(file);hooks.seek(file,position,0);
 }else{
  const char* name=resource->GetValue();if(!name)return 0;
  void* opened=hooks.open(name,D_0040C418);if(!opened)return 0;
  hooks.seek(opened,0,2);result=hooks.tell(opened);hooks.close(opened);
 }
 return result;
}
unsigned int XmlDataReader::Read(Resource* resource,void* buffer,unsigned int size){
 if(!resource->file)return 0;
 return hooks.read(buffer,1,size,resource->file);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00373250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00373268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003732A0);
