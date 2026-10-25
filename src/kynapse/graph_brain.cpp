#include "include_asm.h"

#include "kynapse/graph/brain.hpp"
using namespace Kaim;



bool CBrain::Configure(GraphConfig *config)
{
    unsigned int i;
    if (!handler)
        return false;
    if (!config)
        return true;
    for (i = 0; i < config->count; ++i) {
        GraphConfig *child = config->GetChild(i);
        if (child->GetSecond()) {
            if (!_stricmp(child->GetSecond(), "Service")) {
                const char *name = child->FindThirdBySecond("Class");
                if (name) {
                    BrainComponentClass *entry = func_0038C438(name);
                    if (entry && entry->create) {
                        BrainComponent *object = entry->create(this);
                        if (!object->Configure(child)) {
                            delete object;
                        } else {
                            services[serviceCount] = object;
                            ++serviceCount;
                        }
                    }
                }
            } else if (!_stricmp(child->GetSecond(), "Agent")) {
                const char *name = child->FindThirdBySecond("Class");
                if (name) {
                    BrainComponentClass *entry = func_0038C4D8(name);
                    if (entry && entry->create) {
                        BrainComponent *object = entry->create(this);
                        if (!object->Configure(child)) {
                            delete object;
                        } else {
                            agents[agentCount] = object;
                            ++agentCount;
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < config->count; ++i) {
        if (_stricmp(config->GetChild(i)->GetSecond(), "Class") &&
            _stricmp(config->GetChild(i)->GetSecond(), "Service") &&
            _stricmp(config->GetChild(i)->GetSecond(), "Agent")) {
            if (!ConfigureChild(config->GetChild(i)))
                return false;
        }
    }
    return true;
}

BrainComponent *CBrain::GetAgent(PathClassInfo *wanted)
{
    for (int i = 0; i < agentCount; ++i) {
        if (agents[i]->GetClassInfo() == wanted)
            return agents[i];
    }
    return 0;
}

BrainComponent *CBrain::GetService(PathClassInfo *wanted)
{
    for (int i = 0; i < serviceCount; ++i) {
        if (wanted == services[i]->GetClassInfo())
            return services[i];
    }
    return 0;
}

BrainComponent *CBrain::FindService(PathClassInfo *wanted)
{
    for (int i = 0; i < serviceCount; ++i) {
        if (BrainIsA(wanted, services[i]->GetClassInfo()))
            return services[i];
    }
    return 0;
}

bool CBrain::ConfigureChild(GraphConfig *config)
{
    if (config) {
        if (!config->GetSecond())
            return false;
        if (*config->GetSecond() == '_')
            return true;
    }
    return false;
}

