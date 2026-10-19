#include "kynapse/point_mapper.hpp"

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
