#ifndef BLACK_CAMPAIGN_TIMED_MATRIX_HPP
#define BLACK_CAMPAIGN_TIMED_MATRIX_HPP
#include "ps2/matrix.hpp"

namespace CampaignGraphics {
// Access view of vtable 003DB1F8. The semantic class name and fields 14/18
// remain inferred; the offsets below come from PS2 accesses, not Xbox packing.
class TimedMatrixInterface {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual int Reset();
    virtual int Kind();
    virtual void Update(float step, void *output);
};
class TimedMatrix : public TimedMatrixInterface {
public:
    int Reset();
    void Update(float step, void *output);
    float elapsed, duration, amplitude;
    int kind;
    unsigned owner, token, unknown1c;
    BlackPS2::VU0::Value curvePoints[4];
};
}
#endif
