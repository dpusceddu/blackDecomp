#include "campaign/actor/views.hpp"
namespace BlackPS2Campaign {
template<class T> inline T &At(void *p,int o) { return *(T *)((char *)p+o); }

}
extern "C" {
int func_001484C8(void *);
void *func_001AFDA8(void *);
void func_00149BE8(void *,int,void *);
bool func_0014C5C8(void *,int);
void func_0025DBA8(void *);
void func_00129108(void *,void *,int,int,int);
void func_0014C3E0(void *);
extern char *D_0040F4D0;
}
namespace BlackPS2Campaign {
inline bool ActorEntries::GetCommandState() {
    if (At<unsigned char>(this,0x13a)) return 0;
    char *table=(char *)Field_0010();
    return !(*(int (**)(void *))(table+0xcc))((char *)this+*(short *)(table+0xc8));
}
void ActorEntries::Command(unsigned int message) {
    switch(message) {
    case 0: {int index=func_001484C8(this);void *item=func_001AFDA8((char *)Field_01A0()+index*12);func_00149BE8(this,index,item);break;}
    case 1: if(func_0014C5C8(this,6)) func_0025DBA8(Field_00B4());break;
    case 2: {
        int state=GetCommandState();
        func_00129108(D_0040F4D0,this,state,0,-1);break;
    }
    case 3: func_0014C3E0(this);break;
    case 4: At<unsigned char>(this,0x13f)=0;break;
    }
}
}

// Unmatched: 001448C8 initialization still differs in aggregate copies and allocation.
// Unmatched: 00145558 masks need original iterator, bitset and VU metadata helper lifetimes.
// Unmatched: 00145A50 attachment update differs in matrix copy and component setter ordering.
// Unmatched: 00145B98 behavior transition differs in predicate lifetimes and rigid inverse spills.
// Unmatched: 00146000 effect update differs in helper evaluation and VU temporary allocation.
// Unmatched: 001463D0 nearby notification has matching VU arithmetic but different scalar allocation.
// Unmatched: 00146CE0 any-hit trace needs complete query filtering and rigid inverse context.
// Unmatched: 001471E0 closest trace differs in matrix inverse and output aggregate lifetimes.
// Unmatched: 001475F0 floor query differs in local handle/matrix storage and allocation.
// Unmatched: 00149798 reset flags has a saved-register allocation swap.
