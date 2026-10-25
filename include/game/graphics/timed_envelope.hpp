#ifndef BLACK_TIMED_ENVELOPE_HPP
#define BLACK_TIMED_ENVELOPE_HPP
#include "ps2/ee_types.h"
namespace Graphics {
// PS2 access layout. Strings identify a Tinnitus sound effect; original class
// names and the inheritance relationship remain unverified.
struct EnvelopeFields {
    int state;
    float level, endpoint, deadline, ratio, progress;
    unsigned kind, mode;
    float high, low, multiplier, unknown2c, gain;
    float attack, hold, release;
    float blend;
    unsigned char channels[6], unknown4a, unknown4b, enabled, initialized;
    unsigned char padding4e[2];
};
struct EnvelopeInterface : EnvelopeFields {
    virtual void Reset();
    virtual int Begin(float endpoint, unsigned useEndpoint);
    virtual void Update();
    virtual int Unregister();
    virtual void Release();
    virtual void SetMode(int mode);
    virtual unsigned Curve(float input);
};
struct TimedEnvelope : EnvelopeInterface {
    float scale;
    void Reset();
    int Begin(float endpoint, unsigned useEndpoint);
    void Update();
    int Unregister();
    void Release();
};
typedef char EnvelopePrefixSize[sizeof(EnvelopeFields)==0x50?1:-1];
}
#endif
