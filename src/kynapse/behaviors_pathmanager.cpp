#include "include_asm.h"

#include "kynapse/agents/pathmanager.hpp"
extern const char D_004059F8[], D_00405A00[];
namespace KaimPathRegistry {

PathManager::PathManager() {
    entries=(Record**)KaimAllocate(8*sizeof(Record*));capacity=8;count=0;
}
PathManager::~PathManager() {
    for(unsigned int i=0;i<count;++i){delete entries[i];entries[i]=0;}
    memoryRelease(entries);entries=0;
}
int PathManager::Load(const char* key,ChildBuffers* data) {
    if(!key)return false;
    if(Find(key))return false;
    PathWay* path=new PathWay;
    if(!path->Load(data)){delete path;return false;}
    if(count==capacity)Grow();
    entries[count]=new Record(key,path);++count;return true;
}
PathWay* PathManager::Lookup(const char* key){return Find(key);}
bool PathManager::Remove(const char* key){
    for(unsigned int i=0;i<count;++i) {
        if(!func_00360838(key,entries[i]->name)) {
            memoryRelease(entries[i]);--count;
            for(;i<count;++i)entries[i]=entries[i+1];
            return true;
        }
    }
    return false;
}
Record::Record(const char* key,PathWay* path):value(path){func_0035CBC0(name,key);}
Record::~Record(){delete value;value=0;}
}

// Unmatched: Attach (544 B) retains branch-shape differences and one short-loop padding difference.
// Unmatched: Configure (192 B) retains success/failure block-order differences.

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/behaviors_pathmanager", func_002DA700);
