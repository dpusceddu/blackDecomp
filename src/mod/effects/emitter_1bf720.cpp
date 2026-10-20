#include "game/effects/mod_emitter_methods.hpp"
extern "C"{int func_001B0FF8(void*),func_001B1080(void*);}
int ModEffects::EmitterRecord::Clear(){owner=0;return func_001B0FF8(this);}
