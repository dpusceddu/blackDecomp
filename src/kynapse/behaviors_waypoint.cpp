#include "include_asm.h"

#define BLACK_PATHWAY_OUTLINE_WP
#include "kynapse/agents/pathway.hpp"
namespace KaimPathData {

ScriptWP::ScriptWP():position(gOrigin){func_0035CBC0(mode,D_003C71F8);func_0035CBC0(action,D_003C7208);}
}

namespace KaimPathData {
bool PathWay::TranslateOne(const Vec3& delta, unsigned int index) {
    if (index >= count) return false;
    records[index].position += delta;
    return true;
}

bool PathWay::SetPosition(const Vec3& position, unsigned int index) {
    if (index >= count) return false;
    records[index].position = position;
    return true;
}
}
