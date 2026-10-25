#ifndef BLACK_APT_PAIR_HPP
#define BLACK_APT_PAIR_HPP
#include "apt/apt_function.hpp"
namespace AptPS2 {
extern "C" {
 extern Token D_003BFAF8;
 void func_00250198(void*,Token*,int);
 void func_0024C6D0(Value*,void*);
 void func_00253058(void*,void*);
 int func_0035CA74(const char*,const char*);
 extern char D_003FE460,D_003FE468,D_003FD8A8;
 extern NativeFunction* D_003BF044;
 void func_00247560();
 void func_002486D8(void*,int);
 void func_00387020(void*,int);
 void func_0024FA98(void*,void*,int);
 extern char D_003E1320,D_003E1E78;
}
struct TextHandle {
 Token* token;
 TextHandle():token(&D_003BFAF8) {++token->refs;}
 ~TextHandle() {if(!--token->refs)func_00250198(D_0043DEE0,token,*(unsigned short*)((char*)token+4)+9);}
 inline const char* Text()const{return token->text;}
};
struct TextPair:Value {
 char unknown08[0x18];TextHandle first,second;
 Value*Read(int,Token**);
 int Write(int,Token**,Value*);
 void Destroy(int);
};
typedef char FirstAt20[(unsigned int)&((TextPair*)0)->first==0x20?1:-1];
}
#endif
