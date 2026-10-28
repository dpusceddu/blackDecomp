#include "game/graphics/audio_provider.hpp"
extern "C" void func_00310590(void*, int, int, const Game::Point3*);
extern "C" void func_002848A8(Graphics::AudioProvider* self, Game::Vec v) {
    const Game::Position4& p = *(const Game::Position4*)&v;
    Game::Point3 value;
    value.x = p.x;
    value.y = p.y;
    value.z = p.z;
    self->voice->position = value;
    if (self->voice->channel) func_00310590(self->voice->channel, 0, 1, &value);
}
extern "C" void func_00284920(Graphics::AudioProvider* self, Game::Vec v) {
    const Game::Position4& p = *(const Game::Position4*)&v;
    Game::Point3 value;
    value.x = p.x;
    value.y = p.y;
    value.z = p.z;
    self->voice->velocity = value;
    if (self->voice->channel) func_00310590(self->voice->channel, 1, 1, &value);
}
