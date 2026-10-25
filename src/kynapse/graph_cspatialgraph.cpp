#include "include_asm.h"

#include "kynapse/graph/spatial.hpp"
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

