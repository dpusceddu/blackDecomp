// Unmatched: func_00105D48: register allocation and the final configuration store schedule.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
template<class T> struct FrontendRelative {
    unsigned address;
    T* Relocate(void* base) { address+=(unsigned)base; return (T*)address; }
    T* Get() { return (T*)address; }
};
struct FrontendArchive { int reserved0,reserved4,count; void* entries; };
struct FrontendBinding { char opaque[0x24]; };
struct FrontendBindingList { unsigned char count; char reserved[3]; FrontendRelative<FrontendBinding> entries; };
struct FrontendScenePayload { char reserved[0xa0]; FrontendRelative<void> extra; };
struct FrontendScene {
    int reserved0,reserved4;
    FrontendRelative<FrontendScenePayload> payload;
    FrontendRelative<void> dataC,data10,data14,data18;
    int reserved1c;
};
struct FrontendSceneList { unsigned char reserved0,count; char reserved2[2]; FrontendRelative<FrontendScene> entries; };
struct FrontendArchiveConfig { int reserved0,reserved4; FrontendRelative<void> data8,dataC,data10,data14,data18; };
struct FrontendArchivePackage {
    int version;
    FrontendRelative<FrontendArchive> textures,models;
    FrontendRelative<FrontendBindingList> bindings;
    FrontendRelative<FrontendSceneList> scenes;
    FrontendRelative<FrontendArchiveConfig> config;
    FrontendRelative<void> root;
};
extern "C" FrontendArchivePackage* func_001092F8();
extern "C" void func_00272AA8(void*);
extern "C" void* func_003822E0(void*,int);
extern "C" void* func_003822F8(void*,int);
extern "C" void func_0028EED8(void*);
extern "C" void func_001AF930(void*);
extern "C" void func_00382C70(void*);
extern "C" void* func_001282D0(void*);
extern "C" void func_00108540(void*,int,void*,short);
extern "C" void func_0015CC40(void*,void*);
extern "C" void func_0016BE60(void*);
extern "C" void func_001264C8(void*,void*);
extern "C" void func_00155238(void*);
extern void* D_0040F4C4;
extern void* D_0040F4E0;
extern void* D_0040F4E4;
extern void* D_0040F520;
extern char* D_0040F4D0;
extern char* D_0040F0E0;
extern "C" void func_00105D48() {
    FrontendArchivePackage* package=func_001092F8();
    FrontendArchive* textures=(FrontendArchive*)(package->textures.address+(unsigned)package);
    package->bindings.Relocate(package);
    package->textures.address=(unsigned)textures;
    package->config.Relocate(package);
    package->root.Relocate(package);
    package->scenes.Relocate(package);
    package->models.Relocate(package);
    func_00272AA8(textures);
    for(int index=0;index<textures->count;++index) func_0028EED8(func_003822E0(textures,index));
    FrontendBindingList* bindings=package->bindings.Get();
    bindings->entries.Relocate(bindings);
    for(unsigned index=0;index<bindings->count;++index) func_00382C70(&bindings->entries.Get()[index]);
    FrontendSceneList* scenes=package->scenes.Get();
    scenes->entries.Relocate(scenes);
    for(unsigned char index=0;index<scenes->count;++index) {
        FrontendScene* scene=(FrontendScene*)((index<<5)+(unsigned)scenes->entries.Get());
        FrontendScenePayload* payload=(FrontendScenePayload*)(scene->payload.address+(unsigned)scene);
        scene->dataC.Relocate(scene);
        scene->data10.Relocate(scene);
        void* data14=(void*)(scene->data14.address+(unsigned)scene);
        scene->data18.Relocate(scene);
        scene->data14.address=(unsigned)data14;
        scene->payload.address=(unsigned)payload;
        if(payload->extra.address) payload->extra.Relocate(payload);
    }
    FrontendArchiveConfig* config=package->config.Get();
    config->data8.Relocate(config);
    void* dataC=(void*)(config->dataC.address+(unsigned)config);
    void* data10=(void*)(config->data10.address+(unsigned)config);
    void* data14=(void*)(config->data14.address+(unsigned)config);
    config->dataC.address=(unsigned)dataC;
    config->data10.address=(unsigned)data10;
    config->data14.address=(unsigned)data14;
    config->data18.Relocate(config);
    func_001282D0(package->root.Get());
    func_00108540(D_0040F4C4,0,package->textures.Get(),0);
    FrontendArchive* models=package->models.Get();
    func_00272AA8(models);
    for(int index=0;index<models->count;++index) func_001AF930(func_003822F8(models,index));
    func_00108540(D_0040F4C4,1,package->models.Get(),0);
    func_0015CC40(D_0040F4E0,package->scenes.Get());
    func_0016BE60(D_0040F4D0+0x3f0);
    *(void**)(D_0040F0E0+0x2106c)=package->bindings.Get();
    func_001264C8(D_0040F4E4,package->config.Get());
    func_00155238(D_0040F520);
    void** destination=(void**)(D_0040F4D0+0x5ab8);
    *destination=package->root.Get();
}

#endif
