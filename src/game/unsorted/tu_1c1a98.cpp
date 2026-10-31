#include "game/draft_views.hpp"
#include "ps2/prelude.h"

namespace Game {
namespace DraftViews {

void RefreshAtCoordinates(void* object, const int* coordinates) {
    PrepareCoordinates(object, coordinates);
    void* context = M2C_FIELD(M2C_FIELD(effects, void**, 0xd540), void**, 0x58);
    void* position = M2C_FIELD(context, void**, 0x60);
    int previousX = M2C_FIELD(position, int*, 0xc);
    M2C_FIELD(position, int*, 0xc) = coordinates[0];
    int previousY = M2C_FIELD(position, int*, 0x10);
    M2C_FIELD(M2C_FIELD(context, void**, 0x60), int*, 0x10) = coordinates[1];
    PublishCoordinates(effects + 0xcfd0, context);
    SetEffectMode(effects + 0x14, 3);
    M2C_FIELD(M2C_FIELD(context, void**, 0x60), int*, 0xc) = previousX;
    M2C_FIELD(M2C_FIELD(context, void**, 0x60), int*, 0x10) = previousY;
    PublishCoordinates(effects + 0xcfd0, context);
    FinishCoordinates(object);
}

} // namespace DraftViews
} // namespace Game
