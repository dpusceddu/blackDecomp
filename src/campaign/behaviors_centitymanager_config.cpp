#include "ps2/kynapse/property.hpp"
#include "campaign/behaviors/entities.hpp"
extern "C" int _stricmp(const char*,const char*);
extern "C" long func_0035E730(const char*);
extern "C" float func_00291C68(long);

bool Perception::Configure(ChildBuffers* entry) {
    if(!_stricmp(entry->GetSecond(),"ComputeInfoDelay")) {
        const char* value=entry->GetValue();if(value) {recordInterval=func_00291C68(func_0035E730(value));return true;}return false;
    }
    if(!_stricmp(entry->GetSecond(),"ComputeCommonInfoDelay")) {
        const char* value=entry->GetValue();if(value) {pairInterval=func_00291C68(func_0035E730(value));return true;}return false;
    }
    return BlackPS2::Kynapse::IsPrivateProperty(entry);
}
