#include "include_asm.h"

#include "kynapse/point_mapper.hpp"
#ifdef NON_MATCHING
#include "kynapse/classes/Kaim_CPointMapper.hpp"
#include "kynapse/graph/tables.hpp"
#endif

extern const char D_00405AE8[16] __attribute__((aligned(8))) = "MaxDeltaUp";
extern const char D_00405AF8[16] __attribute__((aligned(8))) = "EntityWidth";
extern const char D_00405B08[16] __attribute__((aligned(8))) = "ForceRebuild";
extern const char D_00405B18[8] __attribute__((aligned(8))) = "1";
extern const char D_00405B20[8] __attribute__((aligned(8))) = "yes";
extern const char D_00405B28[8] __attribute__((aligned(8))) = "true";
extern const char D_00405B30[8] __attribute__((aligned(8))) = "RawData";
extern const char D_00405B38[16] __attribute__((aligned(8))) = "OutputFile";

int PointMapper::Configure(ChildBuffers *config) {
    if (!config) return 0;
    float unit = 0.0f;
    if (D_003C9ED4) unit = D_003C9ED4->unit;
    this->maxDeltaUp = unit*1.5f;
    const char *value = func_002E3330(config, D_00405AE8);
    if (value) {
        float parsed = func_00291C68(func_0035E730(value));
        if (!(parsed<0.0f)) this->maxDeltaUp = parsed;
    }
    unit = 0.0f;
    if (D_003C9ED4) unit = D_003C9ED4->unit;
    this->entityWidth = unit*0.6f;
    value = func_002E3330(config, D_00405AF8);
    if (value) {
        float parsed = func_00291C68(func_0035E730(value));
        if (!(parsed<0.0f)) this->entityWidth = parsed;
    }
    const char *force = func_002E3330(config, D_00405B08);
    ChildBuffers *raw;
    if ((force && (!func_00360838(force, D_00405B18) ||
                   !func_00360838(force, D_00405B20) ||
                   !func_00360838(force, D_00405B28))) ||
        !(raw = func_002E31E0(config, D_00405B30)) || !this->Load(raw)) {
        if (!this->Build(config)) return 0;
        const char *output = func_002E3330(config, D_00405B38);
        if (output) {
            char path[0x400];
            func_002E52C8(output, path);
            this->Save(path);
        }
    }
    return 1;
}

#ifdef NON_MATCHING
extern "C" const char *func_002E3920(void *);
struct RegisteredClass { const char *name; PointContainer *(*create)(); };
extern "C" RegisteredClass *func_0038B150(const char *);
extern const char D_00405B48[], D_00405B58[];
extern "C" ChildBuffers *func_002E33E0(ChildBuffers *, unsigned int);
extern const char D_00405B68[], D_00405B98[];
extern const unsigned int D_00405BB4;
extern "C" int LoadSmall(PointMapper *, const void *, int) __asm__("func_002DBCE0");
extern const char D_00405B98[];
// Unmatched: allocator lifetimes and saved-register allocation.
int PointMapper::Build(ChildBuffers *config) {
 unsigned int i,j,k;

    this->count = 0;
    for (i = 0;i<config->count;++i)
        if (!func_00360838(func_002E3920(func_002E33E0(config, i)), D_00405B48))++this->count;
    if (!this->count) return 1;
    this->names = new char *[this->count];
    this->pointCounts = new unsigned int[this->count];
    this->cells = new unsigned int **[this->count];
    for (i = 0;i<this->count;++i) {
        this->pointCounts[i] = 0;
        this->names[i] = 0;
        this->cells[i] = new unsigned int *[this->count];
        for (j = 0;j<this->count;++j) this->cells[i][j] = 0;
    }
    PointContainer **containers = new PointContainer *[this->count];
    unsigned int made = 0;
    for (i = 0;i<config->count;++i) {
        ChildBuffers *child = func_002E33E0(config, i);
        if (func_00360838(func_002E3920(child), D_00405B48)) continue;
        const char *className = func_002E3330(child, D_00405B58);
        if (!className) {
            for (k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        RegisteredClass *factory = func_0038B150(className);
        if (!factory) {
            for (k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        PointContainer *container = factory->create();
        containers[made] = container;
        if (!container->Configure(child)) {
            for (k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        const char *name = child->first;
        this->names[made] = new char[func_0035CCD8(name)+1];
        func_0035CBC0(this->names[made], name);
        ++made;
    }
    for (i = 0;i<this->count;++i) {
        PointContainer *from = containers[i];
        this->pointCounts[i] = from->Count();
        for (j = 0;j<this->count;++j) {
            if (i == j) continue;
            PointContainer *to = containers[j];
            this->cells[i][j] = new unsigned int[from->Count()];
            for (k = 0;k<from->Count();++k) this->cells[i][j][k] = this->FindTarget(from, to, from->Get(k));
        }
    }
    for (i = 0;i<this->count;++i) if (containers[i]) delete containers[i];
    D_003C87E0(containers);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DB140);
#endif
