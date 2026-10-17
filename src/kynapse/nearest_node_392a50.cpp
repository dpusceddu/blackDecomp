// Ported from the companion project (an unpublished companion project).
#include "kynapse/nearest_node.hpp"

// /SLUS_213.76 0x392a50
void NearestNodeVisitor::Begin(NodeGraph*)
{
    best = -1.0;
    result = 0;
    unknown14 = 0;
}
