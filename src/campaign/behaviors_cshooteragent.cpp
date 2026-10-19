#include "campaign/behaviors/shooter.hpp"
namespace Kaim {
inline bool BaseConfigure(ChildBuffers* entry) {
    if (entry) {
        if (entry->GetSecond()) {
            if (*entry->GetSecond() == '_') return true;
        }
    }
    return false;
}
bool ShooterAgent::Configure(ChildBuffers* entry)
{
    if (!entry)
        return false;
    const char* key = entry->GetSecond();
    if (!_stricmp(key, "DangerousConeAngle")) {
        const char* value = entry->GetValue();
        if (value) {
            dangerousConeAngle = func_00291C68(func_0035E730(value));
            return true;
        }
    } else if (!_stricmp(key, "TargetBot")) {
        const char* value = entry->GetValue();
        if (value) {
            target = gEngine->FindByName(value);
            return target ? true : false;
        }
    } else if (!_stricmp(key, "GunRange")) {
        const char* value = entry->GetValue();
        if (value) {
            long parsed=func_0035E730(value);
            Engine* engine = gEngine;
            gunRange = func_00291C68(parsed) * engine->unit;
            return true;
        }
    } else if (!_stricmp(key, "MaxInaccuracy")) {
        const char* value = entry->GetValue();
        if (value) {
            maxInaccuracy = func_00291C68(func_0035E730(value));
            return true;
        }
    } else if (!_stricmp(key, "AimAtTargetInterval")) {
        const char* value = entry->GetValue();
        if (value) {
            interval = func_00291C68(func_0035E730(value));
            return true;
        }
    }
    return BaseConfigure(entry);
}
bool ShooterAgent::Prepare()
{
    if (!target)
        return false;
    targetDistance = perception->GetRecord(target)->distance;
    if (targetDistance == kDefaultFloat)
        return false;
    if (gunRange <= kDefaultFloat)
        return false;
    aimOrigin = context->actor->position;
    if (propertyB) {
        Vec3 position(*(const Vec3*)&propertyB->x);
        aimOrigin = position;
    }
    return true;
}
// Unmatched: IsClear code matches; its mask shares ownership with a following RTTI name.
// Unmatched: Init retains different validation-result scheduling.
// Unmatched: Update needs the controller and virtual-call context.
// Unmatched: Aim needs the original scalar/vector temporary lifetimes.
}
