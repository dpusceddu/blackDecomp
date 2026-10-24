#include "include_asm.h"

#include "game/frontend/profile_snapshot.hpp"

void FrontendProfileSnapshot::Remember() {
    int nextCount=data.count;
    int nextChecksum=storedChecksum;
    float now=currentTime;
    unsigned char flag=data.valid;
    count=nextCount;
    valid=flag;
    checksum=nextChecksum;
    previousTime=now;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010F648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010F680);
