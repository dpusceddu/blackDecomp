// Ported from an unpublished companion project, PS2 branches only.
#ifndef BLACK_GAME_AI_ACTION_HPP
#define BLACK_GAME_AI_ACTION_HPP

// Partial recovered layouts, not complete engine classes. Unknown ranges stay
// explicit. GNU places ActionBase's vptr after its owner-only data base.
//
// The SDK compilers see these declarations unchanged. A host build defines
// BLACK_HOST_ADAPTER (ai_action_host.hpp) to keep the 32-bit
// game layouts and call original table slots; the macros below only name those
// spots.
#define BLACK_REF(T) T*
#define BLACK_VPTR
#define BLACK_VIRTUAL0(ret, name, slot) virtual ret name()
#define BLACK_VIRTUAL1(ret, name, slot, t0, a0) virtual ret name(t0 a0)
#define BLACK_VIRTUAL2(ret, name, slot, t0, a0, t1, a1) virtual ret name(t0 a0, t1 a1)
#define BLACK_GLOBAL_POINTER(T, name) extern T* name
#define BLACK_GLOBAL_OBJECT(T, name) extern const T name
#include "ps2/vector_storage.hpp"
namespace Game {
typedef unsigned char Byte;
struct Brain;
struct RouteRequest;
struct RouteNode;
struct NodeGraph;
struct NavigationAgent;
struct Action;
struct ActionStack;



#define BLACK_STDCALL_BOOL bool
struct SpeedValue { unsigned int unknown00; float speed; };
struct ActorMovement { Byte unknown00[0x60]; BLACK_REF(SpeedValue) value; };
struct ModelInfo { unsigned int unknown00; int kind; };   // kind 0x28: vehicle
struct Actor {
    Byte unknown00[0xa0];
    Vector4 position;
    Byte unknownb0[0x14];
    int kind;                       // 0xc4 on both platforms; 2 marks the larger blocker radius
    Byte unknownc8[0x250];
    float radius;                   // 0x318
    Byte unknown31c[0x30];          // the movement pointer sits at 0x34c (checked against PS2 code)
    BLACK_REF(ActorMovement) movement;
    Byte unknown350[0x60];
    Byte actionFlag;
};
struct MovementRequest {
    Byte unknown00[0x30];
    Byte enabled;
};
struct MovementMode {
    BLACK_VPTR
    BLACK_VIRTUAL0(void, Unknown0, 0);
    BLACK_VIRTUAL0(void, Unknown1, 1);
    BLACK_VIRTUAL1(void, Start, 2, const Vector4*, point);
    BLACK_VIRTUAL0(void, Unknown3, 3);
    BLACK_VIRTUAL0(void, Unknown4, 4);
    BLACK_VIRTUAL0(void, Unknown5, 5);
    BLACK_VIRTUAL0(void, Unknown6, 6);
    BLACK_VIRTUAL0(void, Stop, 7);
    Byte unknown04[0x3c];
    int state;
};
struct Controller {
    Vector4 destination;
    Vector4 pending;                // 0x10: destination a retargeted mode will publish next
    Byte unknown20[8];
    float speed;
    float retryDeadline;
    int state;
    Byte update;
    Byte routeFlag;
    Byte publish;                   // 0x36: set when `pending` has become the destination
    Byte unknown37[2];
    Byte routePending;
    Byte unknown3a[2];
    float elapsed;
    unsigned int active;
    BLACK_REF(MovementMode) modes[4];
    Byte unknown54[0x9c];
    BLACK_REF(NavigationAgent) navigator;   // 0xf0: the owner's graph policies for route searches
    Byte unknownf4[0x21c];
    BLACK_REF(Brain) owner;
    bool IsContinuingState() const;
    void StopActiveMode();
    bool RequestMovement(PositionArg point, unsigned int mode);
    bool RequestRunOrSprint(PositionArg point, Byte alternateMode, Byte forceSprint);
    void SetUpdate(Byte value);
    void SetState(int value);
};
struct Permission {
    Byte unknown00[2];
    Byte allowed;
    void SetAllowed(Byte value);
};
// The payload is inherited by value. Individual action families own its fields.
struct ActionPolicy {
    unsigned int words[34];
    void SetDefaults();
};
struct ActionTimer {
    float deadline;
    bool Enabled() const;
    bool Expired() const;
    void Clear();
    void Start(float interval);
};
// Grace interval after a stall; the timer sits behind 0x20 bytes of owner state.
struct StallGrace {
    Byte unknown00[0x20];
    ActionTimer timer;
    bool Pending() const;
};
// The brain's family number lives in the second word of a reference the speed policy takes.
struct FamilyRef { int unknown; int family; };
// Goal of the formation movement mode (embedded in the brain); `subject` is the member it follows.
struct FormationSubject { Byte unknown00[0x41]; };
struct FormationGoal { Byte unknown00[0x30]; BLACK_REF(FormationSubject) subject; };
struct CompletionRecord {
    float interval;
    ActionTimer timer;
    Byte complete;
    Byte result;
    Byte unknown0a[2];
    ActionPolicy policy;
    void Reset();
};
struct ActionEvent { unsigned int kind; unsigned int payload[5]; };
struct QueuedActionEvent {
    unsigned int kind;
    ActionEvent event;
    void Clear();
};
struct ActionStack {
    unsigned int kinds[8];
    CompletionRecord records[8];
    int count;
    QueuedActionEvent events[21];
    int eventCount;
    BLACK_REF(Brain) owner;
    BLACK_REF(Action) actions[74];
    Action* Resolve(unsigned int kind) const;
    unsigned int TopKind() const;
    Action* Top() const;
    int FindAction(const Action* action) const;
    void NotifyIdentityRemoved(void* identity);
    void Pop();
    void UnwindAbove(int ordinal);
    void UnwindAction(Action* action);
    void RetireFinished();
    void PushAndEnter(unsigned int kind, int argument);
    void RequestSuccessor(Action* action, unsigned int kind, int argument);
    bool Reset();
    void QueueEvent(const ActionEvent* event);
    void DispatchEvent(QueuedActionEvent* event);
    void DeliverEvents();
    void ExpireTimers();
    void Update();
};
// Mode numbers remain native values; their gameplay meanings are not established.
struct Recovered_ModeDescriptor {
    Byte unk_00[0x20];
    int mode;
};
struct Recovered_DispatchedModeData {
    void* sequence;
    Byte unk_04[8];
    Byte enabled;
    Byte unk_0D[3];
};
struct Recovered_DispatchedMode : Recovered_DispatchedModeData {
    // Reset slot; the result is unused by the dispatcher. Its native callbacks return scalar success.
    virtual int Unknown0();
    virtual void Unknown1();
    virtual void Unknown2();
    virtual void Unknown3();
    virtual void Enter(Recovered_ModeDescriptor* descriptor);
    virtual void Leave();
    virtual void Event(QueuedActionEvent* event);
    virtual int Unknown7(void* argument);
    virtual int Unknown8(void* argument);
    virtual int Unknown9(void* argument);
    // Position-valued slot; the meaning depends on the active mode.
    virtual PositionResult Unknown10();
    virtual int Unknown11();
    virtual int Unknown12(void* argument);
    virtual int Unknown13(void* argument);
    virtual int Unknown14(void* argument);
};
struct ModeDispatcher {
    Byte unk_00[8];
    Byte unk_08[12];
    signed char unk_14; // UNVERIFIED: reset writes 1.
    Byte paused;
    Byte unk_16;
    signed char unk_17; // UNVERIFIED: reset clears this byte.
    int unk_18;
    Brain* owner;
    int active;
    Recovered_DispatchedMode* modes[11];
    Byte flags;
    Byte unk_51[3];
    void Event(QueuedActionEvent* event);
};
typedef char ModeDispatcherSize[sizeof(ModeDispatcher) == 0x54 ? 1 : -1];
typedef char ModeDispatcherActive[(unsigned)&((ModeDispatcher*)0)->active == 0x20 ? 1 : -1];
typedef char ModeDispatcherFlags[(unsigned)&((ModeDispatcher*)0)->flags == 0x50 ? 1 : -1];
// Xbox offsets are listed; the PS2 object has a 0x10 smaller prefix and every offset below is
// 0x10 smaller there (checked at the controller 0x810, stall grace 0xcc0, stack 0xec0, formation
// goal 0x1eb0 and generation 0x1fcc against PS2 code).
struct Brain {
    Byte unknown00[0x4c];
    int reaction;
    Byte unknown60[0x2c];
    BLACK_REF(Actor) actor;
    Byte unknown90[0x210];
    Permission permission;
    Byte unknown2a3[0x401];
    BLACK_REF(MovementRequest) movement;
    Byte unknown6a8[0x34];
    Byte movementUnlocked;
    Byte unknown6dd[7];
    Byte sprint;
    Byte unknown6e5[3];
    Byte immobile;                  // 0x6e8: a flagged mover never reports an obstruction
    Byte unknown6e9[0x137];
    Controller controller;
    Byte unknownb34[0x158];
    Byte combatRoute;
    Byte unknownc8d[0x17];
    FamilyRef familyRef;            // 0xca4; the family number is at 0xca8
    Byte unknowncac[0x24];
    StallGrace stallGrace;          // 0xcd0
    Byte unknowncf4[0x2c];
    ModeDispatcher dispatcher;
    Byte unknownd74[0x15c];
    ActionStack stack;
    Byte unknown1710[0x7b0];
    FormationGoal formation;        // 0x1ec0
    Byte unknown1ef4[0xe8];
    unsigned int generation;
};
struct ActionData { BLACK_VPTR BLACK_REF(Brain) brain; };
struct ActionBase : ActionData {
    BLACK_VIRTUAL1(void, BindBrain, 0, Brain*, owner);
    BLACK_VIRTUAL0(void, Reset, 1);
    BLACK_VIRTUAL0(void, Update, 2);
    BLACK_VIRTUAL1(void, Enter, 3, int, argument);
    BLACK_VIRTUAL0(void, Leave, 4);
    BLACK_VIRTUAL2(void, Resume, 5, unsigned int, kind, Byte, result);
    BLACK_VIRTUAL1(bool, Event, 6, void*, event);
    BLACK_VIRTUAL0(void, Timer, 7);
    BLACK_VIRTUAL0(void, Unknown8, 8);
    BLACK_VIRTUAL0(void, Unknown9, 9);
    BLACK_VIRTUAL0(void, Unknown10, 10);
    BLACK_VIRTUAL1(void, IdentityRemoved, 11, void*, identity);
};
struct Action : ActionBase {
    unsigned int phase;
    Byte unknown0c[0x18];
    unsigned int payload;
    void BaseEnter();
    void BaseLeave();
    CompletionRecord* Record() const;
    void RequestSuccessor(unsigned int kind, int argument);
    void Complete(bool result);
    void UnwindAbove();
    bool IsDeadlineReady() const;
    void LeaveIdleGuard();
    void ClearPayload();
    void ClearPhase();
    void LeaveMovementPermission();
    void LeaveReactionWait();
    void LeaveActorFlag();
    void LeaveMovementFlag();
    void LeaveRouteMode();
    void LeaveCombatRouteMode();
};
struct GameClock { Byte unknown00[0x1c]; float frameDelta; float time; };
// The four slots at 0x22974 (Xbox) / 0x22864 (PS2) hold the actors that block a path; the two
// platforms place them differently, so each keeps its own layout (the PS2 generation offset is
// assumed equal to the Xbox one; only the blocker slots are checked against PS2 code).
// Route requests that wait for the navigation service form a singly linked list through
// RouteRequest::next, with the request being searched first.
struct RouteQueue {
    int count;
    int unknown04;
    BLACK_REF(RouteRequest) head;     // the request being searched
    BLACK_REF(RouteRequest) cursor;   // cleared when its request leaves the queue
    void AppendUnique(RouteRequest* request);
    RouteRequest* Head() const;
    bool Contains(const RouteRequest* request) const;
};
// The navigation service's node lookup (candidate collection around a point) that the first two
// search stages of a route request drive. `cursor` is -1 until the candidates were collected.
struct NodeSearch {
    BLACK_REF(RouteNode) result;      // 0x00: the node found, 0 when none
    Byte unknown04[0xc];
    Position4 origin;                 // 0x10
    int cursor;                       // 0x20
    unsigned int candidates[64];      // 0x24: node indices around the origin
    int candidateCount;               // 0x124
    Byte active;                      // 0x128
    Byte unknown129[7];
    void Begin(PositionArg point);
    bool Advance();
    bool TestCandidate(const RouteNode* node) const;
};
// Connectivity data the route stages test node pairs against (opaque here).
struct NodeConnectivity { Byte unknown00[8]; };
// Collision world the local route probes query (embedded in the manager).
struct ProbeWorld { Byte unknown00[0x1b0]; };
// The navigation graphs of the loaded levels (the route searches use entry 1).
struct LevelTable { BLACK_REF(NodeGraph) graphs[4]; };
struct ActionManager {
    Byte unknown00[0x70];
    BLACK_REF(LevelTable) levels;   // 0x70
    Byte unknown74[0xa44 - 0x74];
    unsigned int generation;
    Byte unknowna48[0x558];
    ProbeWorld probeWorld;          // 0xfa0

    RouteQueue routeQueue;          // 0x1150 on both platforms
    NodeSearch nodeSearch;          // 0x1160
    Byte unknown1290[0x140];
    NodeConnectivity connectivity;  // 0x13d0
    Byte unknown13d8[0x2148c];
    BLACK_REF(Actor) blockers[4];
};
BLACK_GLOBAL_POINTER(GameClock, gGameClock);
BLACK_GLOBAL_POINTER(ActionManager, gActionManager);
BLACK_GLOBAL_OBJECT(ActionPolicy, gDefaultActionPolicy);
BLACK_STDCALL_BOOL IsMovementObstructed(Controller* controller, PositionArg point, bool force);

inline Action* ActionStack::Top() const { return Resolve(TopKind()); }
// SDK builds enforce the recovered widths without depending on SDK headers.
typedef char CompletionRecordSize[(sizeof(CompletionRecord) == 0x94) ? 1 : -1];
typedef char ActionStackSize[(sizeof(ActionStack) == 0x840) ? 1 : -1];
#define BLACK_OFFSET(T, member) ((unsigned)(&((T*)0)->member))
#define BLACK_BRAIN_SKEW 0x10
#define BLACK_BLOCKER_OFFSET 0x22864
typedef char RouteQueueOffset[(BLACK_OFFSET(ActionManager, routeQueue) == 0x1150) ? 1 : -1];
typedef char BlockerOffset[(BLACK_OFFSET(ActionManager, blockers) == BLACK_BLOCKER_OFFSET) ? 1 : -1];
typedef char ControllerSize[(sizeof(Controller) == 0x314) ? 1 : -1];
typedef char BrainController[(BLACK_OFFSET(Brain, controller) == 0x820 - BLACK_BRAIN_SKEW) ? 1 : -1];
typedef char BrainFamily[(BLACK_OFFSET(Brain, familyRef.family) == 0xca8 - BLACK_BRAIN_SKEW) ? 1 : -1];
typedef char BrainStallGrace[(BLACK_OFFSET(Brain, stallGrace) == 0xcd0 - BLACK_BRAIN_SKEW) ? 1 : -1];
typedef char BrainDispatcher[(BLACK_OFFSET(Brain, dispatcher) == 0xd20 - BLACK_BRAIN_SKEW) ? 1 : -1];
typedef char BrainStack[(BLACK_OFFSET(Brain, stack) == 0xed0 - BLACK_BRAIN_SKEW) ? 1 : -1];
typedef char BrainFormation[(BLACK_OFFSET(Brain, formation) == 0x1ec0 - BLACK_BRAIN_SKEW) ? 1 : -1];
typedef char BrainGeneration[(BLACK_OFFSET(Brain, generation) == 0x1fdc - BLACK_BRAIN_SKEW) ? 1 : -1];
}
#endif
