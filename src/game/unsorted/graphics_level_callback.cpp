#include "include_asm.h"

#include "game/graphics/level_callbacks.hpp"
extern "C" {
extern Graphics::GameState* D_0040F0E0;
int func_0035E750(const char*);
void func_00217408();
int func_0020F268(const char*);
}

int Graphics::LevelCallbacks::SetDifficulty(const char* command) {
    D_0040F0E0->difficulty = func_0035E750(command);
    func_00217408();
    return func_0020F268(command);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020F5E8);
