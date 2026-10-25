#include "include_asm.h"

#ifdef NON_MATCHING
// Partial PS2 views retained for subsequent reconstruction. Enable one candidate
// only after re-scoring its complete class context. No full object sizes are known.

// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
// Unmatched: vector-copy alignment, inline helpers and temporary lifetimes; best aligned candidate 333 differences.
#include "game/classes/other/UnknownVtable_003E0A40.hpp"
#include "game/ai_vector.hpp"
namespace Graphics {
struct __attribute__((aligned(16))) Vec4 {float x,y,z,w;};
struct Tween {
    Vec4 from,to,fromColor,toColor;
    char unknown40[0x20];
    char* text;
    char unknown64[12];
    float rate,duration,alpha,targetAlpha;
    unsigned short output;
    char unknown82[14];
    inline bool Finished()const {return alpha<=0.0000152587890625f;}
};
typedef char Tween_stride[(sizeof(Tween)==0x90)?1:-1];
struct Notification {
char unknown00[0x20];Tween first,second;
char unknown140[0x800];Vec4 positions[8];void* resources[8];
char title[0x304],description[0x200],output[0x200],messages[0x800],unknown18E4[0x80];
unsigned short index;char unknown1966[2];unsigned short pending;unsigned char unknown196A,initialized;
float elapsed,duration,idle;char unknown1978[8];Vec4 hiddenPosition,currentPosition;int phase;unsigned char request;
void Update(float);
};
typedef char Notification_first[((int)&((Notification*)0)->first==0x20)?1:-1];
typedef char Notification_positions[((int)&((Notification*)0)->positions==0x940)?1:-1];
typedef char Notification_index[((int)&((Notification*)0)->index==0x1964)?1:-1];
typedef char Notification_request[((int)&((Notification*)0)->request==0x19a4)?1:-1];
template<class T> inline T& At(void* p,int o){return *(T*)((char*)p+o);}
inline void SetAlpha(Vec4& v,float alpha){
    Game::Vec value=Game::Load(*(Game::Position4*)&v),scalar;
    asm("qmtc2.ni alphaf,alphav":"=j alphav"(scalar):"r alphaf"(alpha));
    asm("vmulx.w colorv,vf0,alphav":"+j colorv"(value):"j alphav"(scalar));
    Game::Store(*(Game::Position4*)&v,value);
}
}
using namespace Graphics;
extern "C" {
extern char *D_0040F0E0,*D_0040F510,*D_0040F518;
extern void *D_0040F4DC;
extern Vec4 D_0042BEA0;
void func_001F5770(Notification*);
int func_001F5850(Notification*);
int func_00122660(void*);
void func_00201108(Tween*,float);
void func_00201010(Tween*);
void func_00275260(char*,char*,int);
int func_00275340(char*);
void func_001EED98(float,void*,void*);
unsigned short func_001089B0(float,float,char*,char*,void*);
}
void Notification::Update(float delta){
    unsigned short& pending=this->pending;
    unsigned char& request=this->request;
    float& idle=this->idle;
    if(!pending){
        idle+=delta;
        if(request){func_001F5770(this);request=0;}
        else if(idle>1.0f){int current=func_00122660(D_0040F4DC);int available=func_001F5850(this);if(current!=At<int>(this,0xbe0)&&available>=current)func_001F5770(this);}
    }else {request=0;idle=0.0f;}
    if(!pending)return;
    unsigned char& initialized=this->initialized;
    if(!initialized){initialized=1;return;}
    Tween& first=this->first;Tween& second=this->second;
    func_00201108(&first,delta);func_00201108(&second,delta);
    float& elapsed=this->elapsed;elapsed+=At<float>(D_0040F0E0,0x2013c);
    int& phase=this->phase;
    if(first.Finished()&&second.Finished()){
        Vec4 empty={0,0,0,0};
        Vec4 color=At<Vec4>(D_0040F518,0x180);SetAlpha(color,0.0f);
        unsigned short& index=this->index;
        Vec4& currentPosition=this->currentPosition;
        Vec4& hiddenPosition=this->hiddenPosition;
        switch(phase){
        case 0:{
            char* title=(char*)this+0x9e0;char* description=(char*)this+0xce4;
            func_00275260((char*)this+0x10e4+index*0x100,title,0x100);
            func_00275260((char*)this+0x1164+index*0x100,description,0x100);
            float duration=func_00275340(description)*0.05f;
            this->duration=duration;if(duration>2.5f)this->duration=2.5f;
            Vec4& target=this->positions[index];
            hiddenPosition=target;SetAlpha(hiddenPosition,0.0f);currentPosition=target;
            first.toColor=D_0042BEA0;first.fromColor=first.toColor;
            first.to=currentPosition;first.from=first.to;
            first.text=title;first.duration=15.0f;first.rate=15.0f;At<float>(this,0x8c)=0.0f;
            func_00201010(&first);first.targetAlpha=0.3f;first.alpha=0.3f;first.duration=15.0f;
            first.to=currentPosition;
            second.to=empty;
            second.text=description;second.duration=20.0f;second.rate=20.0f;At<float>(this,0x11c)=0.0f;
            func_00201010(&second);second.to=color;second.duration=20.0f;second.targetAlpha=0.4f;second.alpha=0.4f;
            elapsed=0.0f;phase=1;break;
        }
        case 1:
            func_001EED98(this->duration,At<void*>(At<void*>(D_0040F510,0xcbd8),0x30),this->resources[index]);
            first.to=currentPosition;first.from=first.to;first.duration=15.0f;first.rate=15.0f;
            func_00201010(&first);first.duration=15.0f;first.to=currentPosition;first.targetAlpha=0.25f;first.alpha=0.25f;
            second.to=color;second.from=second.to;second.duration=20.0f;second.rate=20.0f;
            func_00201010(&second);second.to=color;second.duration=20.0f;second.targetAlpha=0.25f;second.alpha=0.25f;
            phase=2;break;
        case 2:
            first.to=currentPosition;first.from=first.to;first.duration=15.0f;first.rate=15.0f;
            func_00201010(&first);second.to=color;second.from=second.to;second.rate=20.0f;second.duration=20.0f;
            func_00201010(&second);
            if(elapsed>4.0f){elapsed=0.0f;phase=3;first.targetAlpha=0.3f;first.alpha=0.3f;first.to=hiddenPosition;second.targetAlpha=0.3f;second.to=empty;second.alpha=0.3f;}
            break;
        case 3:
            phase=0;--pending;initialized=0;++index;if(index>=8)index=0;break;
        }
    }
    if(phase!=3)second.output=func_001089B0(elapsed,this->duration,(char*)this+0xee4,(char*)this+0xce4,this);
}

#endif

// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
// Unmatched: teardown loop shape and register scheduling; 45 differences.
#include "game/classes/other/UnknownVtable_003E0AC0.hpp"
struct Sprite;
extern "C" {void func_00278F00(void*,int,Sprite*);extern char* D_0040F518;}
template<class T> inline T& At(void* p,int offset){return *(T*)((char*)p+offset);}
inline void ReleaseSprite(void* self,int group,int offset){func_00278F00(D_0040F518+At<signed char>(self,0x12)*0xa8+0x40,At<short>(self,0x10)+group,At<Sprite*>(self,offset));}
int Unnamed::UnknownVtable_003E0AC0::Function_001FBB48(){
 ReleaseSprite(this,0,0x50);ReleaseSprite(this,0,0x58);ReleaseSprite(this,2,0x18);ReleaseSprite(this,2,0x20);
 for(int i=0;i<3;++i)ReleaseSprite(this,1,0x28+i*4);
 ReleaseSprite(this,2,0x40);ReleaseSprite(this,1,0x48);ReleaseSprite(this,2,0x60);ReleaseSprite(this,2,0x68);
 for(int i=0;i<15;++i)ReleaseSprite(this,2,0x70+i*4);
 for(int i=0;i<8;++i)ReleaseSprite(this,2,0xe8+i*4);
 return 1;
}

#endif

// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
// Unmatched: renderer pointer and player-index load scheduling; 6 differences.
#include "game/classes/other/UnknownVtable_003E0A40.hpp"
struct Sprite;
extern "C" {void func_00278F00(void*,int,Sprite*);extern char* D_0040F518;}
template<class T> inline T& At(void* p,int offset){return *(T*)((char*)p+offset);}
inline void ReleaseSprite(void* self,int group,int offset){func_00278F00(D_0040F518+At<signed char>(self,0x12)*0xa8+0x40,At<short>(self,0x10)+group,At<Sprite*>(self,offset));}
int Unnamed::UnknownVtable_003E0A40::Function_001F4CB0(){
 ReleaseSprite(this,0,0x1c);ReleaseSprite(this,0,0x18);return 1;
}

#endif
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FBB48);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F8208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F8318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F84E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F8528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F8608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F8808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F8FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FAC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FAE18);
