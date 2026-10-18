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
