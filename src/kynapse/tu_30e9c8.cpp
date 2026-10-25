#include "include_asm.h"

namespace SoundEventViews {
// SoundPool's Reset call and the Xbox counterpart support this identity. The
// PS2 access widths/offsets are verified; Xbox field meanings remain provisional.
struct SoundEventPrefix {
    unsigned int untouched00;
    float x, y, z;
    unsigned int untouched10;
    unsigned int categoryWord;
    unsigned int radiusWord;
    float expiry;
    int next;
};
}
using namespace SoundEventViews;
// Preserve the floating return temporary: direct literals lower to integer stores.

static inline float Zero() { return 0.0f; }
extern "C" {
void func_0030E9C8(SoundEventPrefix* event)
{
    event->categoryWord = 0;
    event->next = -1;
    event->expiry = Zero();
    event->x = Zero();
    event->y = Zero();
    event->z = Zero();
    event->radiusWord = 0;
}
void func_0030E9F0(SoundEventPrefix* event)
{
    event->categoryWord = 0;
    event->next = -1;
    event->z = Zero();
    event->x = Zero();
    event->y = Zero();
    event->radiusWord = 0;
}
int func_0030EA18(const SoundEventPrefix* event) { return (event->categoryWord & 0x27) != 0; }
int func_0030EA28(const SoundEventPrefix* event) { return (event->categoryWord & 0x58) != 0; }
}
