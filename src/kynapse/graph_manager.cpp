#include "include_asm.h"

#include "kynapse/graph/manager.hpp"
namespace Kaim {

CGraphManager::CGraphManager()
{
    items = new CGraphMap*[8];
    capacity = 8;
    count = 0;
}

CGraphManager::CGraphMap::CGraphMap(const char *source, CSpatialGraph *newGraph, unsigned char newUpdate)
    : graph(newGraph), update(newUpdate), additionalCount(0)
{
    func_0035D1A0(name, source, 0x80);
    name[0x7f] = 0;
}

bool CGraphManager::RemoveGraph(const char *name)
{
    for (unsigned int i = 0; i < count; ++i) {
        if (!_stricmp(name, items[i]->name)) {
            delete items[i]->graph;
            --count;
            for (; i < count; ++i)
                items[i] = items[i + 1];
            return true;
        }
    }
    return false;
}

bool CGraphManager::Setup(GraphConfig *config)
{
    if (!config)
        return false;
    searchConfigured = false;
    if (!ConfigureAll(config))
        return false;
    if (!searchConfigured) {
        unsigned int largest = 0;
        for (unsigned int i = 0; i < count; ++i) {
            if (items[i]->graph->HasFlag(1) == true) {
                unsigned int size = items[i]->graph->NodeCount();
                if (size > largest)
                    largest = size;
            }
        }
        if (largest > 0 && !func_002ECB80(largest))
            return false;
    }
    return true;
}

CGraphManager::CGraphMap *CGraphManager::LoadGraph(const char *name, GraphConfig *raw, unsigned char update)
{
    if (!name)
        return 0;
    if (FindGraph(name))
        return 0;
    CSpatialGraph *graph = new CSpatialGraph;
    if (!graph->Load(raw)) {
        delete graph;
        return 0;
    }
    if (count == capacity) {
        capacity += capacity;
        CGraphMap **grown = new CGraphMap*[capacity];
        for (unsigned int i = 0; i < count; ++i)
            grown[i] = items[i];
        D_003C87E0(items);
        items = grown;
    }
    items[count] = new CGraphMap(name, graph, update);
    ++count;
    return items[count - 1];
}
}

namespace Kaim {
bool CGraphManager::Configure(GraphConfig *config)
{
    if (!config)
        return false;
    if (!_stricmp(config->GetSecond(), "Graph")) {
        const char *name = config->first;
        if (!name)
            return false;
        bool update = false;
        const char *flag = config->FindThirdBySecond("UpdateWithPathObjects");
        if (flag)
            update = func_0035E750(flag) != 0;
        GraphConfig *raw = config->FindBySecond("RawData");
        if (!raw)
            return false;
        CGraphMap *record = LoadGraph(name, raw, update);
        if (!record)
            return false;
        const char *coverage = config->FindThirdBySecond("CoverageDistance");
        if (coverage) {
            float distance = (float)(GraphAtof(coverage) * (double)D_003C9ED4->unit);
            record->graph->coverageDistance = distance;
        }
        for (unsigned int i = 0; i < config->count; ++i) {
            GraphConfig *child = config->GetChild(i);
            if (!_stricmp(child->GetSecond(), "AdditionalData")) {
                GraphConfig *type = child->FindBySecond("Class");
                if (type) {
                    AdditionalEntry *entry = func_00390CF8(type->GetValue());
                    if (entry) {
                        CGraphData *object = entry->create(record->graph);
                        if (!object->Init((ChildBuffers*)child))
                            delete object;
                        else {
                            record->additional[record->additionalCount] = object;
                            ++record->additionalCount;
                        }
                    }
                }
            }
        }
        return true;
    }
    if (!_stricmp(config->GetSecond(), "AstarMemory")) {
        func_002ECB80(func_0035E750(config->GetValue()));
        searchConfigured = true;
    } else {
        return BlackPS2::Kynapse::IsPrivateProperty(config);
    }
    return true;
}
}

#if 0
namespace Kaim {
// Unmatched: lookup branch placement and allocation-loop scheduling.
bool CGraphManager::AddGraph(const char*name,CSpatialGraph *graph,unsigned char update){
 if(!name||!graph)return 0;
 if(!FindGraph(name)){
 if(count==capacity){capacity+=capacity;CGraphMap **grown=new CGraphMap*[capacity];for(unsigned int i=0;i<count;++i)grown[i]=items[i];D_003C87E0(items);items=grown;}
 items[count]=new CGraphMap(name,graph,update);++count;return true;}return false;
}


}
#endif

