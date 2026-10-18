// Unmatched: func_00108328: nested lookup control flow and register allocation.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
struct FrontendNamedResource { char reserved[0xa8]; char name[1]; };
struct FrontendNamedArchiveEntry { int reserved0,reserved4; FrontendNamedResource* resource; int reservedc; };
struct FrontendNamedArchive { int reserved0,reserved4,count; FrontendNamedArchiveEntry* entries; };
struct FrontendNamedArchiveManager {
    char reserved[0xc8c];
    FrontendNamedArchive* archives[11];
    FrontendNamedResource* Find(const char* name) __asm__("func_00108328");
};
extern FrontendResourceTable D_0040F0F0;
extern "C" int func_001080F0();
extern "C" int func_00360838(const char*,const char*);
FrontendNamedResource* FrontendNamedArchiveManager::Find(const char* name) {
    int worker=func_001080F0();
    int current=D_0040F0F0.selectedIndex;
    int all=(unsigned)(current-13)<2;
    FrontendNamedArchive** archive=archives;
    for(int index=0;index<11;++index,++archive) {
        if(*archive) {
            int bank=D_0040F0F0.Find(*archive);
            if(all || bank==1 || (worker && current==bank)) {
                FrontendNamedArchive* currentArchive=*archive;
                FrontendNamedResource* found=0;
                for(int resource=0;resource<currentArchive->count;++resource) {
                    FrontendNamedResource* object=currentArchive->entries[resource].resource;
                    if(!func_00360838(object->name,name)) { found=object; break; }
                }
                if(found) return found;
            }
        }
    }
    return 0;
}

#endif
