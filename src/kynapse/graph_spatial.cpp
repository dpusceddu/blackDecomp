#include "include_asm.h"

#include "kynapse/graph/spatial.hpp"

#define CONVERT(field) { for(unsigned int word=0;word<sizeof(field)/4;++word){unsigned int *p=(unsigned int*)&(field);p[word]=p[word];} }
namespace Kaim {
// Unmatched: chunk-copy aggregate and conversion-loop register allocation.



bool CSpatialGraph::SaveOld(const void *path) {
    void *file=D_00451228.open(path,D_00407BC8);
    if(file) {
        Compact();
        if(D_00451228.write(D_00407C28,1,strlen(D_00407C28),file)==strlen(D_00407C28)) {
            unsigned int version=1;
            if(D_00451228.write(&version,4,1,file)==1) {
                unsigned int distance=*(const unsigned int*)&coverageDistance;
                D_00451228.write(&distance,4,1,file);
                unsigned int count=nodeCount;
                D_00451228.write(&count,4,1,file);
                GraphWriter writer;writer.file=file;writer.byteOrder=0;
                writer.VisitNodes(this);
                unsigned int edgesCount=edgeCount;
                D_00451228.write(&edgesCount,4,1,file);
                writer.VisitAll(this);
                D_00451228.close(file);return true;
            }
        }
    }
    return false;
}

template<class T> inline bool SpatialWriteScalar(const T &value,void *file){unsigned int converted=*(const unsigned int*)&value;return D_00451228.write(&converted,4,1,file)==1;}
}

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: scalar serialization temporary lifetimes and register allocation.
bool CSpatialGraph::Write(const void* path, unsigned int saveFlags)
{
    if (nodeSlots != 0 && (saveFlags & 1) != 0 && nodeTable1c == 0)
        return false;
    if (edgeSlots != 0 && (saveFlags & 2) != 0 && edgeTable50 == 0)
        return false;
    if (edgeSlots != 0 && (saveFlags & 4) != 0 && edgeTable48 == 0)
        return false;
    if (nodeSlots != 0 && (saveFlags & 8) != 0 && firstEdgeTo == 0)
        return false;
    if (edgeSlots != 0 && (saveFlags & 8) != 0 && edgeNext == 0)
        return false;
    if (nodeSlots != 0 && (saveFlags & 0x10) != 0 && firstEdgeFrom == 0)
        return false;
    if (edgeSlots != 0 && (saveFlags & 0x10) != 0 && edgeTable40 == 0)
        return false;
    Compact();
    void* file = D_00451228.open(path, D_00407BC8);
    if (!file)
        return false;
    unsigned int word;
    unsigned int i;
    if (D_00451228.write(D_00407C28,1,strlen(D_00407C28),file)!=strlen(D_00407C28)) {
        D_00451228.close(file);
        return false;
    }
    if(!SpatialWriteScalar(2,file)){D_00451228.close(file);return false;}
    if(!SpatialWriteScalar(saveFlags,file)){D_00451228.close(file);return false;}
    if(!SpatialWriteScalar(coverageDistance,file)){D_00451228.close(file);return false;}
    if(!SpatialWriteScalar(nodeCount,file)){D_00451228.close(file);return false;}
    if(!SpatialWriteScalar(nodeCount,file)){D_00451228.close(file);return false;}
    if(!SpatialWriteScalar(nodeCount,file)){D_00451228.close(file);return false;}
    for (i = 0; i < nodeCount; ++i) {
        SpatialNode* node = &nodes[i];
        if (node->id != -1) {
            int idWord = node->id;
            if(!SpatialWriteScalar(idWord,file)){D_00451228.close(file);return false;}
            unsigned int xWord = *(unsigned int*)&node->x;
            if(!SpatialWriteScalar(xWord,file)){D_00451228.close(file);return false;}
            unsigned int yWord = *(unsigned int*)&node->y;
            if(!SpatialWriteScalar(yWord,file)){D_00451228.close(file);return false;}
            unsigned int zWord = *(unsigned int*)&node->z;
            if(!SpatialWriteScalar(zWord,file)){D_00451228.close(file);return false;}
            idWord = 0;
            if(!SpatialWriteScalar(idWord,file)){D_00451228.close(file);return false;}
        }
    }
    unsigned int withNodeTable = saveFlags & 1;
    if (withNodeTable != 0) {
        for (i = 0; i < nodeCount; ++i) {
            if (nodes[i].id != -1) {
                if(!SpatialWriteScalar(0,file)){D_00451228.close(file);return false;}
            }
        }
    }
    if (saveFlags & 0x10) {
        for (i = 0; i < nodeCount; ++i) {
            if (nodes[i].id != -1) {
                if(!SpatialWriteScalar(firstEdgeFrom[i],file)){D_00451228.close(file);return false;}
            }
        }
    }
    if (saveFlags & 8) {
        for (i = 0; i < nodeCount; ++i) {
            if (nodes[i].id != -1) {
                if(!SpatialWriteScalar(firstEdgeTo[i],file)){D_00451228.close(file);return false;}
            }
        }
    }
    if(!SpatialWriteScalar(edgeCount,file)){D_00451228.close(file);return false;}
    if(!SpatialWriteScalar(edgeCount,file)){D_00451228.close(file);return false;}
    if(!SpatialWriteScalar(edgeCount,file)){D_00451228.close(file);return false;}
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1) {
            if(!SpatialWriteScalar(edges[i].index,file)){D_00451228.close(file);return false;}
            if(!SpatialWriteScalar(0,file)){D_00451228.close(file);return false;}
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1) {
            if(!SpatialWriteScalar(edgeEnd[i],file)){D_00451228.close(file);return false;}
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1) {
            if(!SpatialWriteScalar(edgeStart[i],file)){D_00451228.close(file);return false;}
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1 && (saveFlags & 0x10) != 0) {
            if(!SpatialWriteScalar(edgeTable40[i],file)){D_00451228.close(file);return false;}
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1 && (saveFlags & 8) != 0) {
            if(!SpatialWriteScalar(edgeNext[i],file)){D_00451228.close(file);return false;}
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if ((saveFlags & 4) != 0) {
            if(!SpatialWriteScalar(edgeTable48[i],file)){D_00451228.close(file);return false;}
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (withNodeTable != 0) {
            if(!SpatialWriteScalar(edgeTable4c[i],file)){D_00451228.close(file);return false;}
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1 && (saveFlags & 2) != 0) {
            if(!SpatialWriteScalar(0,file)){D_00451228.close(file);return false;}
        }
    }
    D_00451228.close(file);
    return true;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_spatial", func_002F8238);
#endif
