#include "campaign/graphics/level_callbacks.hpp"
extern "C" {
extern CampaignGraphics::GameState* D_0040F0E0;
int func_0035E750(const char*);
void func_00217408();
int func_0020F268(const char*);
}

int CampaignGraphics::LevelCallbacks::SetDifficulty(const char* command) {
    D_0040F0E0->difficulty = func_0035E750(command);
    func_00217408();
    return func_0020F268(command);
}
