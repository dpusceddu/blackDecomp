#ifndef BLACK_CAMPAIGN_MOVEMENT_CORE_HPP
#define BLACK_CAMPAIGN_MOVEMENT_CORE_HPP
#include "ps2/vu0.hpp"
namespace CampaignGraphics {
using BlackGame::Vec;
// Access view only. Exact consumers verify selected offsets; total class size is unknown.
struct BrainView {
    template<class T> T& Field(unsigned offset) {return *(T *)((unsigned char *)this+offset);}
    void *Part(unsigned offset){return (unsigned char *)this+offset;}
    Vec& Position(){return *(Vec *)((unsigned char *)Field<void *>(0x7c)+0xa0);}
};
struct MovementFields { unsigned char *parameters; BrainView *brain; int behavior;unsigned unknown0c; };
struct MovementInterface : MovementFields {
    virtual void Slot0();virtual void Update();virtual void Slot2();virtual void Slot3();virtual void Slot4();virtual void Slot5();
    virtual long Event(unsigned*);virtual void Slot7();virtual void Slot8();virtual void Slot9();
    virtual Vec Target();virtual void Slot11();virtual void Slot12();virtual void Slot13();virtual long Allowed(long);
    virtual int Choose(int);virtual void Slot16();virtual void Slot17();virtual Vec Direction();virtual Vec Nearest(Vec);virtual void Slot20();
};
struct MovementCore : MovementInterface {
    unsigned char signaled,actorMode,unknown16[2];float radius;
    long Event(unsigned*);long Allowed(long);Vec Direction();Vec Nearest(Vec);void Update();Vec Target();int Choose(int);
    Vec AlternateTarget();int AlternateChoose(int);bool IsNear(Vec);long Priority();void UpdateProximity();
};
struct ActionWeight { void *value;float Score(unsigned char *event); };
struct MovementPolicy { BrainView *brain;void Update(); };
struct GoalRecord {unsigned unknown00; BlackGame::Point3 point;};
}
#endif
