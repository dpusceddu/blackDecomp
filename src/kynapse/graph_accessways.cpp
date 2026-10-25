#include "include_asm.h"

#include "kynapse/graph/accessways.hpp"
using namespace Kaim;

extern "C" CAccessWaysData *func_002FCAA8(SearchGraph *graph)
{
    return new CAccessWaysData(graph);
}

int CAccessWaysData::Get(int node, short **out)
{
    if (node >= nodeCount || node < 0) {
        *out = 0;
        return 0;
    }
    *out = lists[node];
    return counts[node];
}

int CAccessWaysData::Build()
{
    int total = graph->liveNodes;
    if (total == 0)
        return false;
    if (graph->edgeCount == 0)
        return false;
    nodeCount = (short)total;
    counts = new short[nodeCount];
    memset(counts, 0, nodeCount << 1);
    lists = new short*[nodeCount];
    memset(lists, 0, nodeCount << 2);
    ComputeAccessWaysTraversal visitor;
    visitor.owner = this;
    visitor.VisitNodes((CSpatialGraph*)graph);
    return true;
}

#if 0


// Unmatched: serializer cleanup branches and callback-base/local register lifetimes.
extern char D_00407D50[];
int CAccessWaysData::Save(const void* path)
{
    void* file = AccessFile.open(path, D_00407D50);
    if (file) {
        int version = D_00407DD0;
        int i;
        if (AccessFile.write(D_00407DB8, 1, strlen(D_00407DB8), file) == strlen(D_00407DB8) && AccessFile.write(&version, 4, 1, file) == 1) {
            unsigned short words = (unsigned short)nodeCount;
            if (AccessFile.write(&words, 2, 1, file) == 1) {
                short* buffer = (short*)Allocate(nodeCount << 1);
                for (i = 0; i < nodeCount; ++i)
                    buffer[i] = counts[i];
                int total = AccessFile.write(buffer, 2, nodeCount, file);
                if (total != nodeCount) {
                    D_003C87E0(buffer);
                    AccessFile.close(file);
                    return false;
                }
                int node = 0;
                if (total > 0) do {
                    for (i = 0; i < counts[node]; ++i)
                        buffer[i] = lists[node][i];
                    if (AccessFile.write(buffer, 2, counts[node], file) != counts[node]) {
                        D_003C87E0(buffer);
                        AccessFile.close(file);
                        return false;
                    }
                    ++node;
                } while (node < nodeCount);
                D_003C87E0(buffer);
                AccessFile.close(file);
                return true;
            }
        }
        AccessFile.close(file);
    }
    return false;
}

// Unmatched: header/read guards and native short-conversion helpers differ.
int CAccessWaysData::Load(const void* resource)
{
    char header[64];
    __builtin_strcpy(header,"none");
    unsigned int version=0;
    FileService* files = D_003C9ED4->files;
    if (!files)
        return false;
    if (files->Exists(resource)) {
        int signatureLength=strlen(D_00407DB8);
        int headerRead=files->Read(resource,header,signatureLength);
        if (headerRead==signatureLength && files->Read(resource,&version,4)==4){
            header[headerRead] = 0;
            if (_stricmp(D_00407DB8, (char*)&header) == 0 && version == 1) {
                if (files->Read(resource, &nodeCount, 2) == 2) {
                    short n = nodeCount;
                    nodeCount = n;
                    if (n == (short)graph->liveNodes) {
                        counts = (short*)Allocate(nodeCount << 1);
                        lists = (short**)Allocate(nodeCount << 2);
                        int bytes = nodeCount;
                        if (files->Read(resource, counts, nodeCount << 1) == bytes * 2) {
                            for (int i = 0; i < nodeCount; ++i) {
                                volatile short* p = &counts[i];
                                *p = *p;
                            }
                            for (int node = 0; node < nodeCount; ++node) {
                                lists[node] = (short*)Allocate(counts[node] << 1);
                                int words = counts[node];
                                if (files->Read(resource, lists[node], counts[node] << 1) != words * 2) {
                                    files->Close(resource);
                                    return false;
                                }
                                for (int j = 0; j < counts[node]; ++j) {
                                    volatile short* q = &lists[node][j];
                                    *q = *q;
                                }
                            }
                            files->Close(resource);
                            return true;
                        }
                    }
                }
            }
        }
        files->Close(resource);
    }
    return false;
}

// Unmatched: native short conversion and read-count lifetimes differ.
int CAccessWaysData::LoadFile(const void *resource){
 void *file=AccessFile.open(resource,"rb");if(!file)return false;
 char header[64];unsigned int version;
 int headerRead=AccessFile.read(header,1,strlen(D_00407DB8),file);
 if(headerRead!=(int)strlen(D_00407DB8)){AccessFile.close(file);return false;}
 if(AccessFile.read(&version,4,1,file)!=1){AccessFile.close(file);return false;}
 header[headerRead]=0;
 if(_stricmp(D_00407DB8,header)){AccessFile.close(file);return false;}
 if(AccessFile.read(&nodeCount,2,1,file)!=1){AccessFile.close(file);return false;}
 if(nodeCount!=(short)graph->liveNodes)return false;
 counts=new short[nodeCount];lists=new short*[nodeCount];
 int total=nodeCount;
 if(AccessFile.read(counts,2,nodeCount,file)!=(unsigned int)total){AccessFile.close(file);return false;}
 for(int i=0;i<nodeCount;++i){volatile short *p=counts+i;*p=*p;}
 for(int node=0;node<nodeCount;++node){
  lists[node]=new short[counts[node]];int words=counts[node];
  if(AccessFile.read(lists[node],2,counts[node],file)!=(unsigned int)words){AccessFile.close(file);return false;}
  for(int i=0;i<counts[node];++i){volatile short *p=lists[node]+i;*p=*p;}
 }
 AccessFile.close(file);return true;
}

// Unmatched: vertex/edge iterator and grid lifetime context differs.
bool ComputeAccessWaysTraversal::Consider(SpatialNode *node){
 ComputeVisibilityTraversal grid;grid.origin.x=node->x;grid.origin.y=node->y;grid.origin.z=node->z;grid.owner=owner;
 grid.VisitNodes(graph);grid.VisitAll(graph);short n=grid.count;owner->counts[node->id]=n;int bytes=n<<1;short *block=new short[n];owner->lists[node->id]=block;memcpy(owner->lists[node->id],grid.values,bytes);
 if(owner->progress)owner->progress((unsigned int)(node->id*100)/graph->nodeCount);return true;
}

#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FCB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FCEC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FD4A0);
