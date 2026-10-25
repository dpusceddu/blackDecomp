// Scoped access views for functions that are still assembly: offsets describe observed storage, without claiming
// complete class layouts or original class names. The readable drafts that use them are in the files of the functions.
#ifndef BLACK_GAME_DRAFT_VIEWS_HPP
#define BLACK_GAME_DRAFT_VIEWS_HPP
namespace Game { namespace DraftViews {
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

} }
#endif
