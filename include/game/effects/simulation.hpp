#ifndef BLACK_MOD_EFFECT_SIMULATION_HPP
#define BLACK_MOD_EFFECT_SIMULATION_HPP
#include "game/effects/geometry.h"
namespace ModEffects {
// Descriptive PS2 access views, not recovered original class identities.
class GeometryNodes {
public:
    BkEffectGeometryBucketPS2 nodes[8];
    void *materials[12];
    BkEffectGeometryBucketPS2 *heads[12];
    void Clear() __asm__("func_001B8138");
};
class Simulation {
public:
    int count;
    unsigned char unknown04[12];
    BkEffectGeometryPS2 records[255];
    void *pending[32], *batches[32];
    float scales[32];
    short indices[32];
    float timeout[32];
    unsigned char kinds[32], next;
    void Render() __asm__("func_001B86F8");
    int Clear() __asm__("func_001B90D0");
};
typedef char GeometryNodesSize[sizeof(GeometryNodes)==0x4a0?1:-1];
typedef char SimulationNext[(unsigned)&((Simulation*)0)->next==0x11160?1:-1];
}
#endif
