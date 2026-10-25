#include "include_asm.h"

#include "kynapse/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {

void CPathObject::Replay()
{
    unsigned int i; PathTypeRegistry* registry = (PathTypeRegistry*)func_002EC058(D_003C9ED4,&D_00452158);
    if (registry) {
        for(i = 0; i < registry->count; ++i) {
            int id = registry->entries[i]->typeId;
            if (registry->HasId(id)) {
                if (registry->entries[i]->mirrored)
                    OnType(id);
            }
        }
        for(i = 0; i < elementCount; ++i) {
            CLinkedEdge* record = &elements[i];
            if (registry->HasId(record->id))
                Release(record->id, record->slot);
        }
        elementCount = 0;
    }
}
}
#include "kynapse/graph/path_object.hpp"
extern const unsigned char D_00452158,D_004524A0,D_004525B8;
namespace Kaim {
CPathObject::~CPathObject()
{
    delete[] elements;
}
}


unsigned int Kaim::CPathObject::Slot5(unsigned int a, unsigned int b, PathCallback *callback, unsigned int c)
{
    return callback->Filter(a, b, c);
}
void Kaim::CPathObject::OnType(int)
{
    Notify(0);
}

