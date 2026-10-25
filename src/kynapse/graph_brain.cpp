#include "include_asm.h"

#include "kynapse/graph/brain.hpp"
using namespace Kaim;


#if 0
// Unmatched: handler factory target register differs by four instructions.
CBrain::CBrain(void *ownerValue, BrainHandlerClass *handlerClass)
{
    agentCount = 0;
    serviceCount = 0;
    owner = ownerValue;
    if (func_0038BA30()->count)
        agents = (BrainComponent**)Allocate(func_0038BA30()->count * 4);
    else
        agents = 0;
    if (func_0038C3E0()->count)
        services = (BrainComponent**)Allocate(func_0038C3E0()->count * 4);
    else
        services = 0;
    if (!handlerClass->create)
        handler = 0;
    else
        handler = handlerClass->create();
}

// Unmatched: owned-array cleanup branches and pointer lifetimes differ.
CBrain::~CBrain()
{
    if (handler)
        delete handler;
    if (agents) {
        for (int i = 0; i < agentCount; ++i)
            delete agents[i];
        D_003C87E0(agents);
    }
    if (services) {
        for (int i = 0; i < serviceCount; ++i)
            delete services[i];
        D_003C87E0(services);
    }
}
#endif

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

