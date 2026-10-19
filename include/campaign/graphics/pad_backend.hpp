#ifndef CAMPAIGN_GRAPHICS_PAD_BACKEND_HPP
#define CAMPAIGN_GRAPHICS_PAD_BACKEND_HPP
#include "campaign/graphics/controller.hpp"
namespace CampaignGraphics {
// PS2 access prefix. Interface identity, unused fields and full allocation are unverified.
struct PadBackend {
    EeU8 unknown00[0x40];
    EeU8 buffers[2][0x100];
    Controller *controllers[2];
    int count;
    EeU8 feedback;
    EeU8 reserved24d[3];
    int state[2];
    EeU8 packets[2][0x20];
    int handles[2];
    EeU8 singlePort;
    EeU8 reserved2a1[3];
    int lastMode;
    void Initialize(bool single);
    void Poll(); void SetFeedback(int); bool Attach(unsigned,Controller*); void Detach(unsigned,Controller*);
    void PollPort(int port);
    int GetState(unsigned int port);
    int GetHandle(unsigned int port);
};
typedef char PadStateAt250[(int)&((PadBackend*)0)->state==0x250?1:-1];
typedef char PadHandlesAt298[(int)&((PadBackend*)0)->handles==0x298?1:-1];
}
#endif
