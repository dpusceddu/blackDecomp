#include "game/effects/mod_emitter_methods.hpp"
extern "C" int func_001B1080(void *);

int ModEffects::EmitterRecord::Reset() {
    owner = 0;
    func_001B1080(this);
    return 1;
}
