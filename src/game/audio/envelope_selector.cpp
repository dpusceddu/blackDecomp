// Accessed selector prefix; original identity and fields beyond the flag remain UNVERIFIED.
#include "game/graphics/timed_envelope.hpp"
using Graphics::EnvelopeInterface;
struct EnvelopeSelector {
    EnvelopeInterface* choices[4];
    EnvelopeInterface* current;
    unsigned char forced;
};
extern "C" int func_001ED6B0(EnvelopeSelector* selector) {
    if (selector->current) {
        selector->current->Unregister();
        selector->current = selector->choices[0];
        selector->current->Begin(0.0f, 0);
    }
    return 1;
}

extern "C" void func_001ED718(EnvelopeSelector* selector, int choice, unsigned forced) {
    EnvelopeInterface* target = selector->choices[choice];
    if (target == selector->current) {
        if (selector->forced == forced) return;
        if (!forced) {
            target->Release();
            selector->forced = 0;
            return;
        }
    } else if (selector->current && choice < (int)selector->current->kind) {
        if (selector->current->state != 0) return;
    } else if (!forced) {
        return;
    }
    selector->forced = forced;
    float level;
    if (selector->current) {
        level = selector->current->level;
        selector->current->Unregister();
    } else {
        level = 24000.0f;
    }
    selector->current = target;
    target->Begin(level, 1);
}
