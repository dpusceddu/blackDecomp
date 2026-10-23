// Scoped access views for the differential pilot. Offsets describe observed
// storage, without claiming complete class layouts or original class names.
namespace BlackGame { namespace Pilot {
template<class T> inline T& Field(void* object,int offset) {
    return *reinterpret_cast<T*>(static_cast<char*>(object)+offset);
}

extern char* effects __asm__("D_0040F4C0");
extern int PrepareCoordinates(void*,const int*) __asm__("func_001C1BB8");
extern int PublishCoordinates(void*,void*) __asm__("func_001C88C8");
extern int SetEffectMode(void*,int) __asm__("func_001AF768");
extern int FinishCoordinates(void*) __asm__("func_001C1C10");
extern int ActorVisited(void*,void*,void*) __asm__("func_00128120");
extern int PlaybackScale(void*) __asm__("func_001D9F60");
extern int PlaybackLength(void*) __asm__("func_001D9F40");
extern int WeaponReady(void*) __asm__("func_001580C0");
extern void* PendingWeaponAction(void*) __asm__("func_00158078");
extern int MovementReady(void*) __asm__("func_0017E968");
extern int MovementEnabled(void*) __asm__("func_0017E860");

int RefreshAtCoordinates(void*,const int*) __asm__("func_001C1A98");
unsigned CurrentBuffer(void*) __asm__("func_001C2A98");
float PlaybackInterval(void*) __asm__("func_001DD748");
void UpdateLinkedItems(void*,float) __asm__("func_001F1608");
int VisitWorldActor(void*,int,void*) __asm__("func_0012AE00");
void AdvanceRing(void*) __asm__("func_00176F38");
int IsUnblockedPlayer(void*) __asm__("func_00178F28");
unsigned TableWord(void*,int) __asm__("func_00179668");
unsigned TableFollowingWord(void*,int) __asm__("func_00179680");
int IsWeaponReadyWithoutAction(void*) __asm__("func_0017EA70");
int IsMovementReady(void*) __asm__("func_001A27A8");
unsigned SwapBuffer(void*) __asm__("func_001C2A68");
void* SelectedRecord(void*) __asm__("func_002722D0");
int ContainsAddress(void*,void*) __asm__("func_00274FD8");

int RefreshAtCoordinates(void* object,const int* coordinates) {
    PrepareCoordinates(object,coordinates);
    void* context=Field<void*>(Field<void*>(effects,0xd540),0x58);
    void* position=Field<void*>(context,0x60);
    int previousX=Field<int>(position,0xc);
    Field<int>(position,0xc)=coordinates[0];
    int previousY=Field<int>(position,0x10);
    Field<int>(Field<void*>(context,0x60),0x10)=coordinates[1];
    PublishCoordinates(effects+0xcfd0,context);
    SetEffectMode(effects+0x14,3);
    Field<int>(Field<void*>(context,0x60),0xc)=previousX;
    Field<int>(Field<void*>(context,0x60),0x10)=previousY;
    PublishCoordinates(effects+0xcfd0,context);
    return FinishCoordinates(object);
}

unsigned CurrentBuffer(void* object) {
    return static_cast<unsigned*>(object)[Field<int>(object,8)];
}

float PlaybackInterval(void* object) {
    int divisor=(Field<unsigned short>(object,0x62)<<11)/Field<int>(object,0x48);
    int scaled=static_cast<int>(static_cast<unsigned>(divisor)*PlaybackScale(Field<void*>(object,0x30)));
    return static_cast<float>(PlaybackLength(Field<void*>(object,0x30)))/static_cast<float>(scaled);
}

void UpdateLinkedItems(void* object,float delta) {
    void* item=Field<void*>(object,0xa0);
    while(item) {
        char* table=Field<char*>(item,0x14);
        typedef void (*Update)(void*,float);
        Update update=Field<Update>(table,0x14);
        update(static_cast<char*>(item)+Field<short>(table,0x10),delta);
        item=Field<void*>(item,4);
    }
}

int VisitWorldActor(void* node,int,void* hit) {
    void* actor=Field<void*>(node,0x34);
    if(actor && Field<int>(actor,0xc4)==0) {
        void* owner=Field<void*>(hit,0x24);
        ActorVisited(actor,hit,owner?Field<void*>(owner,0x2a4):0);
    }
    return 1;
}

void AdvanceRing(void* object) {
    int count=Field<int>(object,0);
    if(count>0) {
        int next=static_cast<int>(static_cast<unsigned>(Field<int>(object,4))+1);
        Field<int>(object,4)=next%count;
    }
}

int IsUnblockedPlayer(void* object) {
    return Field<int>(object,4)==0 && Field<int>(Field<void*>(object,8),0xc4)==2;
}

unsigned TableWord(void* object,int index) {
    return Field<unsigned*>(object,0x70)[index];
}

unsigned TableFollowingWord(void* object,int index) {
    return Field<unsigned*>(object,0x70)[index+2];
}

int IsWeaponReadyWithoutAction(void* object) {
    void* actor=Field<void*>(Field<void*>(object,0x44),0x7c);
    if(!WeaponReady(Field<void*>(actor,0x2a4)))return 0;
    actor=Field<void*>(Field<void*>(object,0x44),0x7c);
    return PendingWeaponAction(Field<void*>(actor,0x2a4))==0;
}

int IsMovementReady(void* object) {
    if(!MovementReady(Field<char*>(object,0x38)+0x650))return 0;
    return MovementEnabled(Field<char*>(object,0x38)+0x650)!=0;
}

unsigned SwapBuffer(void* object) {
    int next=static_cast<int>(static_cast<unsigned>(Field<int>(object,8))+1)%2;
    Field<int>(object,8)=next;
    return static_cast<unsigned*>(object)[next];
}

void* SelectedRecord(void* object) {
    if(Field<int>(object,0x120)!=0x1c)return 0;
    int index=Field<signed char>(object,0x11d);
    return index<0?0:static_cast<char*>(object)+index*0x18;
}

int ContainsAddress(void* object,void* address) {
    unsigned value=reinterpret_cast<unsigned>(address);
    return value>=Field<unsigned>(object,8) && value<Field<unsigned>(object,0xc);
}
} }
