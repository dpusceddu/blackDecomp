// Ported from an unpublished companion project.
#include "kynapse/nearest_node.hpp"

// /SLUS_213.76 0x3921a0
void NearestSimpleVisitor::Begin(NodeGraph*)
{
    result = 0;
    best = -1.0;
}
