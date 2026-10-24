#include "include_asm.h"

#include "kynapse/behaviors/hide_queries.hpp"
namespace HideRecovery {
    

bool HideAgent::Update()
   {
        bank->ClearActivation();
        allHidden = true;
        unsigned int i = 0;
        while (i < dangerousCount) {
                if (!((Perception*)perception)->GetRecord(dangerous[i])->hidden) {
                    allHidden = false;
                    break;
                }
                ++i;
        }
        float now = gNow;
        if (nextTime < now) {
            ParameterTables* tables = (ParameterTables*)GetNameTables();
            if (tables->Consume(computeName, context->actor)) {
                found = Search();
                tables->Accumulate(computeName, context->actor);
                nextTime = now + 0.1f;
            }
        }
        if (fresh) {
        if (!found) {
            destination = context->actor->position;
            return false;
        }
        // The legacy Xbox names are reversed for the PS2 slots: controller at 6, point at 5.
        bool ok;
        if (graphSlot != -1) {
            HideQueries::Query query(destination, currentId, rank);
            ok = provider->Query(&query);
        }
        else {
            ok = provider->QueryTransform(&destination);
        }
        if (!ok) return false;
        bank->Select(provider->id);
        active = provider->IsActive();
        return true;
        }
        return true;
    }
// Unmatched: Evaluate retains vector/controller lifetime and iterator-register differences.
}
