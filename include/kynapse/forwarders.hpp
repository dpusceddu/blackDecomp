// Declarations of the Kynapse source module "forwarders" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_FORWARDERS_HPP
#define BLACK_KYNAPSE_MODULE_FORWARDERS_HPP
#include "kynapse/compat.hpp"

// Public wrappers that forward to entity methods.

struct EntityObject {
    int ApplyA(int first, int second);
    int ApplyB(int first, int second);
    int ApplyC(int first, int second);
    int ApplyD(int first, int second);
    bool Query(int argument);
};


int Entity_ApplyA(EntityObject* entity, int first, int second);



int Entity_ApplyB(EntityObject* entity, int first, int second);



int Entity_ApplyC(EntityObject* entity, int first, int second);



int Entity_ApplyD(EntityObject* entity, int first, int second);



bool Entity_Query(EntityObject* entity, int argument);


#endif
