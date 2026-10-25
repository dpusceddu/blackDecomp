#ifndef BLACK_GRAPHICS_LEVEL_CALLBACKS_HPP
#define BLACK_GRAPHICS_LEVEL_CALLBACKS_HPP
namespace Graphics {
// Partial PS2 views; original class identity and complete sizes remain unknown.
struct GameState {
    unsigned char unknown00[0x2014c];
    int difficulty;
};
typedef char GameState_difficulty_offset[((int)&((GameState*)0)->difficulty == 0x2014c) ? 1 : -1];
struct LevelCallbacks { static int SetDifficulty(const char* command); };
}
#endif
