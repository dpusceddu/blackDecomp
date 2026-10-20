#include "campaign/graph/spatial.hpp"

#define CONVERT(field) { for(unsigned int word=0;word<sizeof(field)/4;++word){unsigned int *p=(unsigned int*)&(field);p[word]=p[word];} }
namespace Kaim {
// Unmatched: chunk-copy aggregate and conversion-loop register allocation.
#if 0
bool CSpatialGraph::LoadOld(FileService* files, const void* resource)
{
    float nodeBuffer[0x320 * 5];
    unsigned int edgeBuffer[0x800 * 2];
    if (files->Read(resource, &field08, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(field08);
    if (files->Read(resource, &nodeCount, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(nodeCount);
    if (nodeCount == 0) {
        files->Close(resource);
        return true;
    }
    nodeCapacity = 0;
    nodeSlots = nodeCount;
    unsigned int slots = nodeCount;
    nodes = new SpatialNode[slots];
    unsigned int remaining = nodeCount;
    while (remaining != 0) {
        unsigned int chunk = remaining > 0x320 ? 0x320 : remaining;
        if (files->Read(resource, nodeBuffer, chunk * sizeof(SpatialNode)) != (int)(chunk * sizeof(SpatialNode))) {
            files->Close(resource);
            return false;
        }
        remaining -= chunk;
        for (unsigned int i = 0; i < chunk; ++i) {
            nodes[nodeCapacity].id = nodeCapacity;
            nodes[nodeCapacity].graph = (CSpatialGraph*)this;
            nodes[nodeCapacity].x = nodeBuffer[i * 5];
            nodes[nodeCapacity].y = nodeBuffer[i * 5 + 1];
            nodes[nodeCapacity].z = nodeBuffer[i * 5 + 2];
            ++nodeCapacity;
        }
    }
    if (files->Read(resource, &edgeCount, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(edgeCount);
    if (edgeCount == 0) {
        files->Close(resource);
        return true;
    }
    field28 = 0;
    edgeSlots = edgeCount;
    unsigned int edgeTotal = edgeCount;
    edges = new SpatialEdge[edgeTotal];
    edgeEnd = (int*)Allocate(edgeTotal << 2);
    edgeStart = (int*)Allocate(edgeTotal << 2);
    remaining = edgeCount;
    while (remaining != 0) {
        unsigned int chunk = remaining > 0x800 ? 0x800 : remaining;
        if (files->Read(resource, edgeBuffer, chunk * 8) != (int)(chunk * 8)) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < chunk * 2; ++i)
            CONVERT(edgeBuffer[i]);
        remaining -= chunk;
        for (unsigned int i = 0; i < chunk; ++i) {
            edges[field28].index = field28;
            edges[field28].graph = (CSpatialGraph*)this;
            edgeEnd[field28] = edgeBuffer[i * 2];
            edgeStart[field28] = edgeBuffer[i * 2 + 1];
            ++field28;
        }
    }
    SetFlags(flags);
    files->Close(resource);
    return true;
}
#endif

// Unmatched: field conversion helpers and error cleanup block ordering.
#if 0
bool CSpatialGraph::Load(const void* resource)
{
    Reset();
    FileService* files = D_003C9ED4->files;
    if (!files->Exists(resource))
        return false;
    char header[0x40];
    unsigned int version;
    int headerRead = files->Read(resource, header, strlen(D_00407C28));
    int versionRead = files->Read(resource, &version, 4);
    if (headerRead != strlen(D_00407C28) || versionRead != 4) {
        files->Close(resource);
        return false;
    }
    header[headerRead] = 0;
    if (_stricmp(header, D_00407C28) != 0) {
        files->Close(resource);
        return false;
    }
    if (version == 1) {
        if (!LoadOld(files, resource))
            return false;
        files->Close(resource);
        return true;
    }
    if (version != 2) {
        files->Close(resource);
        return false;
    }
    if(files->Read(resource,&flags,4)!=4){files->Close(resource);return false;}CONVERT(flags);
if(files->Read(resource,&field08,4)!=4){files->Close(resource);return false;}CONVERT(field08);
if(files->Read(resource,&nodeCapacity,4)!=4){files->Close(resource);return false;}CONVERT(nodeCapacity);
if(files->Read(resource,&nodeSlots,4)!=4){files->Close(resource);return false;}CONVERT(nodeSlots);
if(files->Read(resource,&nodeCount,4)!=4){files->Close(resource);return false;}CONVERT(nodeCount);
    unsigned int slots = nodeSlots;
    nodes = new SpatialNode[slots];
    for (unsigned int i = 0; i < nodeCount; ++i) {
        SpatialNode* node = &nodes[i];
        int junk;
        if(files->Read(resource,&node->id,4)!=4){files->Close(resource);return false;}CONVERT(node->id);
        if(files->Read(resource,&node->x,4)!=4){files->Close(resource);return false;}CONVERT(node->x);
        if(files->Read(resource,&node->y,4)!=4){files->Close(resource);return false;}CONVERT(node->y);
        if(files->Read(resource,&node->z,4)!=4){files->Close(resource);return false;}CONVERT(node->z);
        if(files->Read(resource,&junk,4)!=4){files->Close(resource);return false;}
        node->graph = (CSpatialGraph*)this;
    }
    if (flags & 1) {
        unsigned int bytes = nodeSlots << 2;
        nodeTable1c = (int*)Allocate(bytes);
        if (files->Read(resource, nodeTable1c, bytes) != (int)bytes) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < nodeSlots; ++i)
            CONVERT(nodeTable1c[i]);
        for (unsigned int i = 0; i < nodeCount; ++i)
            nodeTable1c[i] = 0;
    }
    if (flags & 0x10) {
        unsigned int bytes = nodeSlots << 2;
        firstEdgeFrom = (int*)Allocate(bytes);
        if (files->Read(resource, firstEdgeFrom, bytes) != (int)bytes) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < nodeSlots; ++i)
            CONVERT(firstEdgeFrom[i]);
    }
    if (flags & 8) {
        unsigned int bytes = nodeSlots << 2;
        firstEdgeTo = (int*)Allocate(bytes);
        if (files->Read(resource, firstEdgeTo, bytes) != (int)bytes) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < nodeSlots; ++i)
            CONVERT(firstEdgeTo[i]);
    }
    if(files->Read(resource,&field28,4)!=4){files->Close(resource);return false;}CONVERT(field28);
    if(files->Read(resource,&edgeSlots,4)!=4){files->Close(resource);return false;}CONVERT(edgeSlots);
    if(files->Read(resource,&edgeCount,4)!=4){files->Close(resource);return false;}CONVERT(edgeCount);

    unsigned int edgeBlockSlots = edgeSlots;
    edges = new SpatialEdge[edgeBlockSlots];
    for (unsigned int i = 0; i < edgeSlots; ++i) {
        SpatialEdge* edge = &edges[i];
        int junk;
        if(files->Read(resource,&edge->index,4)!=4){files->Close(resource);return false;}CONVERT(edge->index);
        if(files->Read(resource,&junk,4)!=4){files->Close(resource);return false;}
        edge->graph = (CSpatialGraph*)this;
    }
    // The per-edge tables hold edgeCount values each.
#define READ_EDGE_TABLE(table) \
    table = (int*)Allocate(edgeSlots << 2); \
    if (files->Read(resource, table, edgeCount << 2) != (int)(edgeCount << 2)) { \
        files->Close(resource); \
        return false; \
    } \
    for (unsigned int i = 0; i < edgeCount; ++i) \
        CONVERT(table[i]);
    READ_EDGE_TABLE(edgeEnd)
    READ_EDGE_TABLE(edgeStart)
    if (flags & 0x10) {
        READ_EDGE_TABLE(edgeTable40)
    }
    if (flags & 8) {
        READ_EDGE_TABLE(edgeNext)
    }
    if (flags & 4) {
        READ_EDGE_TABLE(edgeTable48)
    }
    if (flags & 1) {
        READ_EDGE_TABLE(edgeTable4c)
    }
    if (flags & 2) {
        READ_EDGE_TABLE(edgeTable50)
        for (unsigned int i = 0; i < edgeCount; ++i)
            edgeTable50[i] = 0;
    }
    files->Close(resource);
    return true;
}
#endif

// Unmatched: index helper and pointer address register allocation.
#if 0
bool CSpatialGraph::SaveOld(const void *path) {
    void *file=D_00451228.open(path,D_00407BC8);
    if(file) {
        Compact();
        if(D_00451228.write(D_00407C28,1,strlen(D_00407C28),file)==strlen(D_00407C28)) {
            unsigned int version=1;
            if(D_00451228.write(&version,4,1,file)==1) {
                unsigned int distance=field08;
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
#endif

template<class T> inline bool SpatialWriteScalar(const T &value,void *file){unsigned int converted=*(const unsigned int*)&value;return D_00451228.write(&converted,4,1,file)==1;}
// Unmatched: scalar serialization temporary lifetimes and register allocation.
#if 0
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
    if(!SpatialWriteScalar(field08,file)){D_00451228.close(file);return false;}
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
#endif
}
