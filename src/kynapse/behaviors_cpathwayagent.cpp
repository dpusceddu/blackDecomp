#include "kynapse/behaviors/pathway.hpp"
// Unmatched: the remaining C++ member context is still being recovered.

#include "kynapse/behaviors/pathway.hpp"
namespace Kaim {
PathWayAgent* PathWayAgent::Create(Context* context) { return new PathWayAgent(context); }
}

namespace Kaim {
void PathWayAgent::SetPathWay(PathWay* path) {
    if(pathWay==path)return;
    pathWay=path;
    if(pointIndex==0 || pointIndex>=path->count) {
        if(reverse)pointIndex=path->count-1;else pointIndex=0;
    }
    waiting=false;finished=false;paused=false;rotating=false;orienting=false;
}
}
