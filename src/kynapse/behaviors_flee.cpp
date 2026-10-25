#include "include_asm.h"

#include "kynapse/property.hpp"
#include "kynapse/behaviors/flee.hpp"
extern const char D_00404030[], D_00404048[], D_00404058[], D_00404068[];
extern const char D_00404070[], D_00404080[], D_00404088[], D_00404098[];
const char D_00404030[] __attribute__((aligned(8))) = "ComputeDestInterval";
const char D_00404048[] __attribute__((aligned(8))) = "PathLength";
const char D_00404058[] __attribute__((aligned(8))) = "StopWhenHidden";
const char D_00404068[] __attribute__((aligned(8))) = "No";
const char D_00404070[] __attribute__((aligned(8))) = "MaxDeltaHeight";
const char D_00404080[] __attribute__((aligned(8))) = "Graph";
const char D_00404088[] __attribute__((aligned(8))) = "MaxPointsToFlee";
const char D_00404098[] __attribute__((aligned(8))) = "MaxEntitiesToFlee";

namespace FleeViews {

    

bool FleeAgent::Configure(ChildBuffers* entry)
   {
        if (!entry) return false;
            const char* key = entry->GetSecond();
            if (!func_00360838(key, D_00404030)) {
                const char* value = entry->GetValue();
                if (value) {
                    interval = func_00291C68(func_0035E730(value));
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404048)) {
                const char* value = entry->GetValue();
                if (value) {
                    pathLength = func_0035E750(value);
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404058)) {
                const char* value = entry->GetValue();
                if (value) {
                    stopWhenHidden = func_00360838(value, D_00404068) != 0;
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404070)) {
                const char* value = entry->GetValue();
                if (value) {
                    long parsed = func_0035E730(value);
                    Engine* engine = gEngine;
                    maxDeltaHeight = func_00291C68(parsed) * engine->unit;
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404080)) {
                const char* value = entry->GetValue();
                if (value) {
                    ItemList* list = (ItemList*)((ClassRegistryB*)gEngine)->FindByClass(&gTypeListClass);
                    if (!list)
                    return false;
                    void* id = list->IdByName(value);
                    if (!id)
                    return false;
                    return SetGraph(id);
                }
            }
            else if (!func_00360838(key, D_00404088)) {
                const char* value = entry->GetValue();
                if (value) {
                    maxPoints = func_0035E750(value);
                    return true;
                }
            }
            else if (!func_00360838(key, D_00404098)) {
                const char* value = entry->GetValue();
                if (value) {
                    maxEntities = func_0035E750(value);
                    return true;
                }
            }
        return Ps2Math::Kynapse::IsPrivateProperty(entry);
    }
// Unmatched: Init needs the original allocation-cookie and validation lifetimes.
// Unmatched: Update needs visibility-loop and controller cleanup reconstruction.
}
