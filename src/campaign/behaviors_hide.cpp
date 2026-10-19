#include "ps2/kynapse/property.hpp"
#include "campaign/behaviors/hide.hpp"

extern const char D_00404350[], D_00404358[], D_00404368[], D_00404378[];
extern const char D_00404388[], D_00404398[];

const char D_00404350[] __attribute__((aligned(8))) = "Graph";
const char D_00404358[] __attribute__((aligned(8))) = "ResearchType";
const char D_00404368[] __attribute__((aligned(8))) = "FAR_FROM_ENEMY";
const char D_00404378[] __attribute__((aligned(8))) = "CLOSE_TO_ME";
const char D_00404388[] __attribute__((aligned(8))) = "MaxDeltaHeight";
const char D_00404398[] __attribute__((aligned(8))) = "MaxDangerousEntities";

namespace HideRecovery {


    bool HideAgent::Configure(ChildBuffers* entry)
   {
        if (!entry)
        return false;
        const char* key = entry->GetSecond();
        if (!func_00360838(key, D_00404350)) {
            ItemList* list = (ItemList*)((ClassRegistryB*)gEngine)->FindByClass(&gTypeListClass);
            if (!list)
            return false;
            const char* value = entry->GetValue();
            if (value) {
                void* id = list->IdByName(value);
                if (!id)
                return false;
                return SetGraph(id);
            }
        }
        else if (!func_00360838(key, D_00404358)) {
            const char* value = entry->GetValue();
            if (value) {
                if (!func_00360838(value, D_00404368)) {
                    mode = 1;
                    return true;
                }
                if (!func_00360838(value, D_00404378)) {
                    mode = 2;
                    return true;
                }
            }
        }
        else if (!func_00360838(key, D_00404388)) {
            const char* value = entry->GetValue();
            if (value) {
                long parsed = func_0035E730(value);
                Engine* engine = gEngine;
                maxDeltaHeight = func_00291C68(parsed) * engine->unit;
                return true;
            }
        }
        else if (!func_00360838(key, D_00404398)) {
            const char* value = entry->GetValue();
            if (value) {
                maxDangerous = func_0035E750(value);
                return true;
            }
        }
        return BlackPS2::Kynapse::IsPrivateProperty(entry);
    }


// Unmatched: Init retains allocator and validation-result scheduling differences.
// Unmatched: Update needs the original controller and empty-base cleanup context.
// Unmatched: Evaluate needs controller lifetimes, vector temporaries and cleanup reconstruction.
}
