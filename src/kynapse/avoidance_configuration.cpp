#include "include_asm.h"

#include "kynapse/avoidance_classes.hpp"

namespace KaimAvoidance {

inline void Avoidance::SetStallDelay(float value)
{
    if (value >= 0)
        stallDelay = value;
}

inline void Avoidance::SetDiagramWidth(float value)
{
    if (value > 0)
        diagramHalfWidth = value * .5f;
}

inline void Avoidance::SetSpacing(float value)
{
    if (value > 0)
        candidateSpacing = value * width;
}

// The runtime parses a software double, then narrows its 64-bit result to float.
extern "C" unsigned long ReadDoubleBits(const char*) __asm__("func_0035E730");
extern "C" float NarrowDoubleBits(unsigned long) __asm__("func_00291C68");

inline float ParseFloat(const char* text)
{
    return NarrowDoubleBits(ReadDoubleBits(text));
}

unsigned char Avoidance::Configure(const Property* p)
{
    if (!_stricmp(p->GetKey(), "TrackingUpdatePeriod")) {
        float value = ParseFloat(p->GetText());
        if (value < 0) return 0;
        if (value >= 0) trackingPeriod = value;
        return 1;
    } else if (!_stricmp(p->GetKey(), "ForcedModeTimerThreshold")) {
        float value = ParseFloat(p->GetText());
        if (value < 0) return 0;
        if (value >= 0) stallThreshold = value;
        return 1;
    } else if (!_stricmp(p->GetKey(), "ForcedModeTimerDelay")) {
        float value = ParseFloat(p->GetText());
        if (value < 0) return 0;
        SetStallDelay(value);
    } else if (!_stricmp(p->GetKey(), "CollisionDiagrammWidth")) {
        float value = ParseFloat(p->GetText());
        if (value <= 0) return 0;
        SetDiagramWidth(value * WorldUnits());
    } else if (!_stricmp(p->GetKey(), "AvoidanceCandidateSpacing")) {
        float value = ParseFloat(p->GetText());
        if (value <= 0) return 0;
        SetSpacing(value);
    } else if (!_stricmp(p->GetKey(), "SlowSpeedFactor")) {
        slowSpeedFactor = ParseFloat(p->GetText());
    } else {
        return 0;
    }
    return 1;
}
}
