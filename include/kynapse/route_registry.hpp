#ifndef BLACK_ROUTE_REGISTRY_HPP
#define BLACK_ROUTE_REGISTRY_HPP
#include "kynapse/compat.hpp"
// Guarded model: complete type not verified by a linked matching function.
// PS2 callback descriptor: virtual word,256-byte name,callback and ordinal.
struct RouteCallbackDescriptor { void* vtable; char name[256]; void* callback; int ordinal; unsigned int unresolved10c; };
struct RouteCallbackRegistry { RouteCallbackDescriptor* entries[16]; int count; unsigned char overflowed; };
#endif
