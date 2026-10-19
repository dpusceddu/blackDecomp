#include "ps2/kynapse/property.hpp"
#include "campaign/behaviors/follower.hpp"

extern "C" int func_00360838(const char*, const char*);
extern "C" long func_0035E730(const char*);
extern "C" float func_00291C68(long);

namespace BehaviorCampaign {


bool Follower::Configure(ChildBuffers* entry) {
    if (!entry) return false;
    const char* key=entry->GetSecond();
    if (!func_00360838(key,"DistFromEntity")) {
        const char* value=entry->GetValue();
        if (value) {long parsed=func_0035E730(value);Engine* engine=gEngine;limit=func_00291C68(parsed)*engine->unit;return true;}
    } else if (!func_00360838(key,"AngleFromEntity")) {
        const char* value=entry->GetValue();
        if (value) {angle=func_00291C68(func_0035E730(value));return true;}
    } else if (!func_00360838(key,"EntityToFollow")) {
        const char* value=entry->GetValue();
        if (value) {followed=((Registry*)gEngine)->FindByName(value);return true;}
    }
    return BlackPS2::Kynapse::IsPrivateProperty(entry);
}

bool Follower::IsReady() {
    if (!followed) return false;
    if (limit < 0.0f) return false;
    return true;
}
// Unmatched: Init retains different final virtual-result normalization.
// Unmatched: Refresh needs the original vector temporary and operator lifetimes.
// Unmatched: Update retains different virtual-result branch scheduling.
// Unmatched: ComputeDistance needs property-access helper and local lifetime recovery.
}
