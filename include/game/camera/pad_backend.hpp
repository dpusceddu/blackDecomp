// Shared mod context; accessed PS2 prefixes only. Original identities and full allocations remain qualified.
#ifndef BLACK_GRAPHICS_PAD_BACKEND_HPP
#define BLACK_GRAPHICS_PAD_BACKEND_HPP
#include "game/camera/pad.hpp"
namespace Graphics {
// The packed 32-byte copy and port offset are confirmed; other field meanings are UNVERIFIED.
struct PadOpenParameters {
    int unknown00;
    int port;
    EeU8 unknown08[24];
} __attribute__((packed));
typedef char PadOpenParametersSize[sizeof(PadOpenParameters) == 32 ? 1 : -1];
typedef char PadOpenParametersPort[(int)&((PadOpenParameters*)0)->port == 4 ? 1 : -1];

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
    void Initialize(unsigned single);
    void Poll(); void SetFeedback(int); bool Attach(Controller*,unsigned); void Detach(Controller*,unsigned);
    void PollPort(int port);
    int GetState(unsigned int port);
    int GetHandle(unsigned int port);
};
typedef char PadStateAt250[(int)&((PadBackend*)0)->state==0x250?1:-1];
typedef char PadHandlesAt298[(int)&((PadBackend*)0)->handles==0x298?1:-1];
}
#endif
