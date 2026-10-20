// Shared mod context; accessed PS2 prefixes only. Original identities and full allocations remain qualified.
// Partial actor view. Semantic class identities and full sizes remain unverified.
#ifndef BLACK_CAMPAIGN_ACTOR_CAMERA_HPP
#define BLACK_CAMPAIGN_ACTOR_CAMERA_HPP
#include "game/ai_action.hpp"
#include "mod/camera/aim.hpp"

namespace CampaignActor {
// The non-virtual base puts the GCC 2.95 vptr at the verified PS2 offset 0x4C.
struct ChildData {
    char pad[0x48];
    unsigned char active;
    char tail[3];
};
struct Child : ChildData {
    virtual void V0();
    virtual void V1();
    virtual void Update();
    virtual int V3();
    virtual void V4(BlackGame::PositionArg, BlackGame::PositionArg, float,
            unsigned char, signed char, float, long);
    virtual void Target(BlackGame::PositionArg, BlackGame::PositionArg, float, long);
    virtual bool Available();
    virtual void Activate();
    virtual void Deactivate();
};
class CameraController {
public:
    inline void *&Owner() { return *(void **)((char *)this + 0x7C); }
    inline int &Current() { return *(int *)((char *)this + 0x4B4); }
    inline Child *&ChildAt(int n) { return *(Child **)((char *)this + n * 4 + 0x490); }
    inline unsigned char &B(int n) { return *(unsigned char *)((char *)this + n); }
    inline int &I(int n) { return *(int *)((char *)this + n); }
    Child *GetChild() __asm__("func_001412C0");
    bool Ready() __asm__("func_00141308");
    void Tick() __asm__("func_00140E48");
    void Update();
    int Choose(int);
    void SetTarget(BlackGame::PositionArg, BlackGame::PositionArg, float, long);
    int Enable();
    int Clear();
    void Configure(BlackGame::PositionArg, BlackGame::PositionArg, float,
            unsigned char, signed char, float, long);
};
}
#endif
