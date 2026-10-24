#include "game/actor/views.hpp"
#include "game/ai_vector.hpp"
namespace BlackPS2Campaign {
template<class T> inline T &At(void *base,int offset) { return *(T *)((char *)base+offset); }
struct CollisionEvent { BlackGame::Position4 first,second; };
struct Matrix { BlackGame::Position4 rows[4]; };
}
extern "C" {
void *func_001AFD80(void *,void *);
float func_001AFDB0(void *);
char *func_00147988(void *,int);
void func_0014C120(void *);
void func_001ECF80(void *,void *,void *);
void func_0025CB08(void *,void *);
void func_00149828(void *,int,int);
void func_001B1728(BlackGame::Vec,BlackGame::Vec,BlackPS2Campaign::Matrix *);
void func_001B7A00(void *,BlackPS2Campaign::Matrix *,long,int);
extern char *D_0040F510;
extern void *D_0040F4CC;
extern char *D_0040F4D8;
}
namespace BlackPS2Campaign {
int ActorEntries::Collision(void *raw) {
    CollisionEvent *event=(CollisionEvent *)raw;
    int result=0;
    if (At<unsigned char>(this,0x1ec) || BlackGame::Y(BlackGame::Load(event->second))<0.9f) return 0;
    if (Field_01F0()) func_0025CB08(D_0040F4CC,Field_00B4());
    for (int i=0;i<Field_01F5();++i) {
        void *item=func_001AFD80((char *)Field_01A0()+i*12,Field_0118());
        if (item) {
            unsigned short flags=At<unsigned short>(item,0x5a);
            if (flags&4) func_00149828(this,i,1);
            else if (flags&8) func_00149828(this,i,0);
            if (At<unsigned short>(item,0x5a)&0x1000) result=1;
            if (At<long>(item,0x20)) {
                Matrix transform;
                func_001B1728(BlackGame::Load(event->first),BlackGame::Load(event->second),&transform);
                func_001B7A00(D_0040F4D8+0x696f0,&transform,At<long>(item,0x20),1);
            }
        }
    }
    At<unsigned char>(this,0x1ec)=1;
    return result;
}
}
