#include "game/actor/views.hpp"
namespace BlackPS2Campaign {
template<class T> inline T &At(void *p,int o) { return *(T *)((char *)p+o); }

}
extern "C" {
void func_0014C140(void *);
void *func_001AFD80(void *,void *);
void func_00149828(void *,int,int);
float func_001AFDB0(void *);
void func_00146578(void *,int,int,int,float);
}
namespace BlackPS2Campaign {
void ActorEntries::ResetEntries(int reason) {
    Field_0124()=0;
    for (int i=0;i<Field_01F5();++i)
        if (func_001AFDB0((char *)Field_01A0()+i*12)>0.0f) func_00146578(this,i,1,0,1e9f);
    char *table=(char *)Field_0010();
    (*(void (**)(void *,int))(table+0x14))((char *)this+*(short *)(table+0x10),reason);
}
}
