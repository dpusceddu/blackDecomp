#include "kynapse/pair_owner.hpp"

#ifdef NONMATCHING
// Unmatched: final name-prefix branch and register allocation differ.
bool PairOwner::Configure(ChildBuffers* config)
{
    if (!_stricmp(config->GetSecond(), "ComputeInfoDelay")) {
        const char* text = config->GetValue();
        if (text) {
            low = (float)atof(text);
            return true;
        }
        return false;
    }
    if (!_stricmp(config->GetSecond(), "ComputeCommonInfoDelay")) {
        const char* text = config->GetValue();
        if (text) {
            high = (float)atof(text);
            return true;
        }
        return false;
    }
    if (config && config->GetSecond() && *config->GetSecond() == '_')
        return true;
    return false;
}
#endif
