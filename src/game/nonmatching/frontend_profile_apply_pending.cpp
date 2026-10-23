// Unmatched: global setting address reuse and aggregate-copy scheduling.
#if 0
#include "game/frontend/profile_snapshot.hpp"
extern "C" FrontendProfileGlobal* D_0040F0E0;
extern "C" FrontendProfileData** D_0040F53C;
extern "C" void func_00108BB8(FrontendProfileSettings*);
extern "C" void func_00122B10(FrontendProfileData*);
extern "C" void func_00122B60(FrontendProfileData*);
void FrontendProfileSnapshot::Apply() {
    D_0040F0E0->settings.option24=settings.option24;
    D_0040F0E0->settings.option19=settings.option19;
    D_0040F0E0->settings.option1b=settings.option1b;
    for(int i=0;i<37;++i) D_0040F0E0->settings.progress[i]=settings.progress[i];
    D_0040F0E0->settings.option1c=settings.option1c;
    D_0040F0E0->settings.sound=settings.sound;
    D_0040F0E0->settings.music=settings.music;
    D_0040F0E0->settings.sensitivity=settings.sensitivity;
    func_00108BB8(&D_0040F0E0->settings);
    D_0040F0E0->settings.control=settings.control;
    D_0040F0E0->settings.vertical=settings.vertical;
    D_0040F0E0->settings.horizontal=settings.horizontal;
    D_0040F0E0->settings.enabled=settings.enabled;
    FrontendProfileData* destination=*D_0040F53C;
    func_00122B10(destination);
    *destination=data;
    func_00122B60(destination);
    Remember();
}
#endif
