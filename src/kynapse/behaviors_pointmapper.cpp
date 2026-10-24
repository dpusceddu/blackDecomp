#include "kynapse/agents/pointmapper.hpp"

int PointMapper::Map(PointLocator* locator,unsigned int container,unsigned int* mapped) {
    unsigned int point,owner;
    if(!locator->Resolve(&point,&owner))return 0;
    if(owner==container) *mapped=point;
    else {
        unsigned int value=cells[owner][container][point];
        *mapped=value;
        if(value==(unsigned int)-1)return 0;
    }
    return 1;
}

// Unmatched: Clear (368 B) differs in loop scheduling and row-base lifetimes.
// Unmatched: Build (1800 B), Save (788 B), LoadSmall (1364 B), and Load (1448 B) differ in allocator and stream-helper lifetimes.
