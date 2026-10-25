#ifndef BLACK_AUDIO_PROVIDER_HPP
#define BLACK_AUDIO_PROVIDER_HPP
#include "ps2/vu0.hpp"
// Inferred PS2 access fields; no exact consumer verifies this complete view yet.
namespace Graphics {
struct Voice {
    unsigned char unknown00[0x30];
    Game::Point3 position,velocity;
    unsigned char unknown48[0x18];
    void *channel;unsigned active;unsigned unknown68;int playback;
    unsigned char unknown70[0x16];
    unsigned char gain,unknown87[3],flags,pan;
};
// Partial PS2 access view; the vptr position and original class identity are unknown.
struct AudioProvider {
    unsigned char unknown00[12];int savedPlayback;unsigned char unknown10[28];
    unsigned char state,count;unsigned short unknown2e,flags,padding32;
    Voice *voice;
    float Transition();void SetPosition(Game::Vec);void SetVelocity(Game::Vec);
    void SetGain(float);void SetPan(float);void SetPlayback(unsigned);void SetFlag(unsigned);
    bool IsStopped();
};
}
#endif
