// Unmatched: aggregate-copy register allocation, absolute-offset symbols and scheduling.
#if 0
#include "game/frontend/profile_snapshot.hpp"
extern "C" FrontendProfileGlobal* D_0040F0E0;
extern "C" FrontendProfileData** D_0040F53C;
extern "C" void func_00123E70(FrontendProfileData*);
extern "C" void func_00122B88(FrontendProfileData*);
extern "C" void func_00124080(FrontendProfileData*,float);
extern "C" void func_00124090(FrontendProfileData*,void*);
extern "C" void func_00124048(FrontendProfileData*);
extern "C" int func_0010F6D8(void*);
void FrontendProfileSnapshot::Capture(void* object,int defaults) {
    version=0x26;
    bytes=0x778;
    settings=D_0040F0E0->settings;
    if(defaults) func_00123E70(&data);
    else {
        func_00122B88(*D_0040F53C);
        data=**D_0040F53C;
        func_00124080(&data,currentTime-previousTime);
    }
    if(object) func_00124090(&data,object);
    func_00124048(&data);
    storedChecksum=func_0010F6D8(&version);
}
#endif
