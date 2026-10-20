#include "campaign/graph/spatial.hpp"
namespace Kaim {
bool CSpatialGraph::LoadFromPath(const char* path)
{
    char buffer[0x1000];
    Allocator* saved = D_003C87E8;
    ArenaAllocator arena(buffer, 0x1000, 0, 0);
    D_003C87E8 = &arena;
    ConfigBlock* block = new ConfigBlock;
    block->SetSecond("RawData");
    block->SetThird(path);
    D_003C87E8 = saved;
    FileService* previous = D_003C9ED4->files;
    PathFileService service;
    D_003C9ED4->files = &service;
    bool result = Load(block);
    D_003C9ED4->files = previous;
    return result;
}
}

#if 0
#define CONVERT(field) { for(unsigned int word=0;word<sizeof(field)/4;++word){unsigned int *p=(unsigned int*)&(field);p[word]=p[word];} }
namespace Kaim {

// Unmatched: array construction and chunk-copy register lifetimes.
bool CSpatialGraph::LoadOld(FileService* files, const void* resource)
{
    float nodeBuffer[0x320 * 5];
    unsigned int edgeBuffer[0x800 * 2];
    if (files->Read(resource, &coverageDistance, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(coverageDistance);
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
    SpatialNode* block = (SpatialNode*)Allocate(slots * sizeof(SpatialNode));
    if (block) {
        for (unsigned int i = 0; i < slots; ++i) {
            block[i].id = -1;
            block[i].graph = 0;
        }
    }
    nodes = block;
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
    edgeCapacity = 0;
    edgeSlots = edgeCount;
    unsigned int edgeTotal = edgeCount;
    SpatialEdge* edgeBlock = (SpatialEdge*)Allocate(edgeTotal * sizeof(SpatialEdge));
    if (edgeBlock) {
        for (unsigned int i = 0; i < edgeTotal; ++i) {
            edgeBlock[i].index = -1;
            edgeBlock[i].graph = 0;
        }
    }
    edges = edgeBlock;
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
            edges[edgeCapacity].index = edgeCapacity;
            edges[edgeCapacity].graph = (CSpatialGraph*)this;
            edgeEnd[edgeCapacity] = edgeBuffer[i * 2];
            edgeStart[edgeCapacity] = edgeBuffer[i * 2 + 1];
            ++edgeCapacity;
        }
    }
    SetFlags(flags);
    files->Close(resource);
    return true;
}

// Unmatched: inline conversion loops and serialized-field sequencing.
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
if(files->Read(resource,&coverageDistance,4)!=4){files->Close(resource);return false;}CONVERT(coverageDistance);
if(files->Read(resource,&nodeCapacity,4)!=4){files->Close(resource);return false;}CONVERT(nodeCapacity);
if(files->Read(resource,&nodeSlots,4)!=4){files->Close(resource);return false;}CONVERT(nodeSlots);
if(files->Read(resource,&nodeCount,4)!=4){files->Close(resource);return false;}CONVERT(nodeCount);
    unsigned int slots = nodeSlots;
    SpatialNode* block = (SpatialNode*)Allocate(slots * sizeof(SpatialNode));
    if (block) {
        for (unsigned int i = 0; i < slots; ++i) {
            block[i].id = -1;
            block[i].graph = 0;
        }
    }
    nodes = block;
    for (unsigned int i = 0; i < nodeCount; ++i) {
        SpatialNode* node = &nodes[i];
        int junk;
        if (files->Read(resource, &node->id, 4) != 4 || files->Read(resource, &node->x, 4) != 4 ||
            files->Read(resource, &node->y, 4) != 4 || files->Read(resource, &node->z, 4) != 4 ||
            files->Read(resource, &junk, 4) != 4) {
            files->Close(resource);
            return false;
        }
        CONVERT(node->id);
        CONVERT(node->x);
        CONVERT(node->y);
        CONVERT(node->z);
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
    if (files->Read(resource, &edgeCapacity, 4) != 4 || files->Read(resource, &edgeSlots, 4) != 4 ||
        files->Read(resource, &edgeCount, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(edgeCapacity);
    CONVERT(edgeSlots);
    CONVERT(edgeCount);
    unsigned int edgeBlockSlots = edgeSlots;
    SpatialEdge* edgeBlock = (SpatialEdge*)Allocate(edgeBlockSlots * sizeof(SpatialEdge));
    if (edgeBlock) {
        for (unsigned int i = 0; i < edgeBlockSlots; ++i) {
            edgeBlock[i].index = -1;
            edgeBlock[i].graph = 0;
        }
    }
    edges = edgeBlock;
    for (unsigned int i = 0; i < edgeSlots; ++i) {
        SpatialEdge* edge = &edges[i];
        int junk;
        if (files->Read(resource, &edge->index, 4) != 4 || files->Read(resource, &junk, 4) != 4) {
            files->Close(resource);
            return false;
        }
        CONVERT(edge->index);
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

// Unmatched: visitor traversal inlining and scalar-local scheduling (117 differing instructions).
bool CSpatialGraph::SaveOld(const void* path)
{
    void* file = D_00451228.open(path, D_00407BC8);
    if (file) {
        Compact();
        if (D_00451228.write(D_00407C28, 1, 0x15, file) == 0x15) {
            unsigned int word = 1;
            unsigned int converted;
            Word_Convert(&converted, &word, 0);
            if (D_00451228.write(&converted, 4, 1, file) == 1) {
                word = *(unsigned int*)((char*)this + 8);
                Word_Convert(&converted, &word, 0);
                D_00451228.write(&converted, 4, 1, file);
                word = nodeCount;
                Word_Convert(&converted, &word, 0);
                D_00451228.write(&converted, 4, 1, file);
                GraphWriter writer;
                writer.byteOrder = 0;
                writer.file = file;
                writer.VisitNodes(this);
                word = edgeCount;
                Word_Convert(&converted, &word, 0);
                D_00451228.write(&converted, 4, 1, file);
                writer.VisitAll(this);
                D_00451228.close(file);
                return true;
            }
        }
    }
    return false;
}

// Unmatched: serialized scalar lifetimes and allocation of registers (395 differing instructions).
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
#define WRITE_WORD(value) \
    word = (value); \
    if (D_00451228.write(&word, 4, 1, file) != 1) { \
        D_00451228.close(file); \
        return false; \
    }
#define WRITE_VAR(var) \
    if (D_00451228.write(&var, 4, 1, file) != 1) { \
        D_00451228.close(file); \
        return false; \
    }
    if (D_00451228.write(D_00407C28, 1, 0x15, file) != 0x15) {
        D_00451228.close(file);
        return false;
    }
    WRITE_WORD(2)
    WRITE_WORD(saveFlags)
    WRITE_WORD(coverageDistance)
    WRITE_WORD(nodeCount)
    WRITE_WORD(nodeCount)
    WRITE_WORD(nodeCount)
    for (i = 0; i < nodeCount; ++i) {
        SpatialNode* node = &nodes[i];
        if (node->id != -1) {
            int idWord = node->id;
            WRITE_VAR(idWord)
            unsigned int xWord = *(unsigned int*)&node->x;
            WRITE_VAR(xWord)
            unsigned int yWord = *(unsigned int*)&node->y;
            WRITE_VAR(yWord)
            unsigned int zWord = *(unsigned int*)&node->z;
            WRITE_VAR(zWord)
            idWord = 0;
            WRITE_VAR(idWord)
        }
    }
    unsigned int withNodeTable = saveFlags & 1;
    if (withNodeTable != 0) {
        for (i = 0; i < nodeCount; ++i) {
            if (nodes[i].id != -1) {
                WRITE_WORD(0)
            }
        }
    }
    if (saveFlags & 0x10) {
        for (i = 0; i < nodeCount; ++i) {
            if (nodes[i].id != -1) {
                WRITE_WORD(firstEdgeFrom[i])
            }
        }
    }
    if (saveFlags & 8) {
        for (i = 0; i < nodeCount; ++i) {
            if (nodes[i].id != -1) {
                WRITE_WORD(firstEdgeTo[i])
            }
        }
    }
    WRITE_WORD(edgeCount)
    WRITE_WORD(edgeCount)
    WRITE_WORD(edgeCount)
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1) {
            WRITE_WORD(edges[i].index)
            WRITE_WORD(0)
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1) {
            WRITE_WORD(edgeEnd[i])
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1) {
            WRITE_WORD(edgeStart[i])
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1 && (saveFlags & 0x10) != 0) {
            WRITE_WORD(edgeTable40[i])
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1 && (saveFlags & 8) != 0) {
            WRITE_WORD(edgeNext[i])
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if ((saveFlags & 4) != 0) {
            WRITE_WORD(edgeTable48[i])
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (withNodeTable != 0) {
            WRITE_WORD(edgeTable4c[i])
        }
    }
    for (i = 0; i < edgeCount; ++i) {
        if (edges[i].index != -1 && (saveFlags & 2) != 0) {
            WRITE_WORD(0)
        }
    }
    D_00451228.close(file);
    return true;
}

// Unmatched: iterator and endpoint-accessor context.
SpatialEdge* CSpatialGraph::FindEdge(unsigned int endId, unsigned int startId)
{
    if (edgeCount == 0)
        return 0;
    if ((flags & 8) == 0) {
        unsigned int seen = 0;
        if (edgeCount != 0) {
            unsigned int slot = 0;
            do {
                if (slot < edgeCapacity && edges[slot].index != -1 && &edges[slot]) {
                    SpatialEdge* edge = &edges[slot];
                    CSpatialGraph* owner = edge->graph;
                    ++seen;
                    SpatialNode* end;
                    if (edge == &owner->syntheticEdge)
                        end = &owner->syntheticNodes[0];
                    else
                        end = &owner->nodes[owner->edgeEnd[edge->index]];
                    if ((unsigned int)end->id == endId) {
                        SpatialNode* start;
                        if (edge == &owner->syntheticEdge)
                            start = &owner->syntheticNodes[1];
                        else
                            start = &owner->nodes[owner->edgeStart[edge->index]];
                        if ((unsigned int)start->id == startId)
                            return edge;
                    }
                }
                ++slot;
            } while (seen < edgeCount);
        }
        return 0;
    }
    unsigned int index = firstEdgeTo[endId];
    if (index != (unsigned int)-1) {
        while ((unsigned int)edgeStart[index] != startId) {
            index = edgeNext[index];
            if (index == (unsigned int)-1)
                return 0;
        }
        if (index < edgeCapacity)
            return GetEdge(index);
    }
    return 0;
}

// Unmatched: aggregate copy and iterator register allocation.
void CSpatialGraph::Compact()
{
    unsigned int node = 0;
    int* nodeMap = new int[nodeCapacity];
    int* edgeMap = new int[edgeCapacity];
    for (unsigned int i = 0; i < nodeCapacity; ++i)
        nodeMap[i] = -1;
    for (unsigned int i = 0; i < edgeCapacity; ++i)
        edgeMap[i] = -1;
    int liveNodes = 0;
    for (node = 0; node < nodeCapacity; ++node) {
        if (nodes[node].id != -1) {
            nodes[liveNodes] = nodes[node];
            nodes[liveNodes].id = liveNodes;
            nodeMap[node] = liveNodes;
            ++liveNodes;
        }
    }
    int liveEdges = 0;
    for (unsigned int edge = 0; edge < edgeCapacity; ++edge) {
        if (edges[edge].index != -1) {
            edges[liveEdges] = edges[edge];
            edges[liveEdges].index = liveEdges;
            edgeMap[edge] = liveEdges;
            ++liveEdges;
        }
    }
    for (node = 0; node < nodeCapacity; ++node) {
        if (nodeMap[node] != -1) {
            if (firstEdgeFrom) {
                int target = firstEdgeFrom[node];
                firstEdgeFrom[nodeMap[node]] = target == -1 ? -1 : edgeMap[target];
            }
            if (firstEdgeTo) {
                int target = firstEdgeTo[node];
                firstEdgeTo[nodeMap[node]] = target == -1 ? -1 : edgeMap[target];
            }
        }
    }
    for (unsigned int edge = 0; edge < edgeCapacity; ++edge) {
        if (edgeMap[edge] != -1) {
            if (edgeEnd)
                edgeEnd[edgeMap[edge]] = nodeMap[edgeEnd[edge]];
            if (edgeStart)
                edgeStart[edgeMap[edge]] = nodeMap[edgeStart[edge]];
            if (edgeTable40)
                edgeTable40[edgeMap[edge]] = edgeTable40[edge] == -1 ? -1 : edgeMap[edgeTable40[edge]];
            if (edgeNext)
                edgeNext[edgeMap[edge]] = edgeNext[edge] == -1 ? -1 : edgeMap[edgeNext[edge]];
            if (edgeTable48)
                edgeTable48[edgeMap[edge]] = edgeTable48[edge];
        }
    }
    nodeCount = liveNodes;
    nodeCapacity = liveNodes;
    edgeCount = liveEdges;
    edgeCapacity = liveEdges;
    D_003C87E0(nodeMap);
    D_003C87E0(edgeMap);
}

// Unmatched: flag predicates, edge helpers and float-distance scheduling (197 differing instructions).
void CSpatialGraph::SetFlags(unsigned int newFlags)
{
    flags = newFlags;
    if (HasFlag(1)) {
        if (!nodeTable1c)
            nodeTable1c = (int*)Allocate(nodeSlots << 2);
        if (!edgeTable4c)
            edgeTable4c = (int*)Allocate(edgeSlots << 2);
    } else {
        if (nodeTable1c) {
            D_003C87E0(nodeTable1c);
            nodeTable1c = 0;
        }
        if (edgeTable4c) {
            D_003C87E0(edgeTable4c);
            edgeTable4c = 0;
        }
    }
    if (HasFlag(2)) {
        if (!edgeTable50) {
            edgeTable50 = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeTable50[i] = 0;
        }
    } else {
        if (edgeTable50) {
            D_003C87E0(edgeTable50);
            edgeTable50 = 0;
        }
    }
    if (HasFlag(4)) {
        if (!edgeTable48) {
            edgeTable48 = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < edgeSlots; ++i) {
                if (i < edgeCapacity && edges[i].index != -1 && &edges[i]) {
                    SpatialEdge* edge = &edges[i];
                    SpatialNode* end = edge->EndNode();
                    SpatialNode* start = edge->StartNode();
                    float dz = start->z - end->z;
                    float dx = start->x - end->x;
                    float dy = start->y - end->y;
                    ((float*)edgeTable48)[i] = sqrtf(dz * dz + dx * dx + dy * dy);
                }
            }
        }
    } else {
        if (edgeTable48) {
            D_003C87E0(edgeTable48);
            edgeTable48 = 0;
        }
    }
    if (HasFlag(8)) {
        if (!firstEdgeTo) {
            firstEdgeTo = (int*)Allocate(nodeSlots << 2);
            edgeNext = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < nodeSlots; ++i)
                firstEdgeTo[i] = -1;
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeNext[i] = -1;
            for (unsigned int k = 0; k < edgeSlots; ++k) {
                unsigned int index = edgeSlots - k - 1;
                if (index < edgeCapacity && edges[index].index != -1 && &edges[index]) {
                    SpatialEdge* edge = &edges[index];
                    SpatialNode* end = edge->EndNode();
                    int* head = &firstEdgeTo[end->id];
                    int previous = *head;
                    *head = edge->index;
                    edgeNext[edge->index] = previous;
                }
            }
        }
    } else {
        if (firstEdgeTo) {
            D_003C87E0(firstEdgeTo);
            firstEdgeTo = 0;
        }
        if (edgeNext) {
            D_003C87E0(edgeNext);
            edgeNext = 0;
        }
    }
    if (HasFlag(0x10)) {
        if (!firstEdgeFrom) {
            firstEdgeFrom = (int*)Allocate(nodeSlots << 2);
            edgeTable40 = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < nodeSlots; ++i)
                firstEdgeFrom[i] = -1;
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeTable40[i] = -1;
            for (unsigned int k = 0; k < edgeSlots; ++k) {
                unsigned int index = edgeSlots - k - 1;
                if (index < edgeCapacity && edges[index].index != -1 && &edges[index]) {
                    SpatialEdge* edge = &edges[index];
                    SpatialNode* start = edge->StartNode();
                    int* head = &firstEdgeFrom[start->id];
                    int previous = *head;
                    *head = edge->index;
                    edgeTable40[edge->index] = previous;
                }
            }
        }
    } else {
        if (firstEdgeFrom) {
            D_003C87E0(firstEdgeFrom);
            firstEdgeFrom = 0;
        }
        if (edgeTable40) {
            D_003C87E0(edgeTable40);
            edgeTable40 = 0;
        }
    }
}
}
#undef CONVERT
#endif
