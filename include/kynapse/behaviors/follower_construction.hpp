#ifndef BLACK_FOLLOWER_CONSTRUCTION_HPP
#define BLACK_FOLLOWER_CONSTRUCTION_HPP
#include "kynapse/behaviors/follower.hpp"
#include "kynapse/alloc.hpp"
extern void (*FollowerRelease)(void*) __asm__("D_003C87E0");
namespace FollowerBehavior {
// Constructor view reuses Follower's verified 0x48-byte layout.
struct FollowerConstructible:Follower {
    FollowerConstructible(Context*) __asm__("func_002D3520");
    static void* operator new(unsigned int size) {return KaimAllocate(size);}
    static void operator delete(void* memory) {FollowerRelease(memory);}
};
typedef char FollowerConstructionSize[sizeof(FollowerConstructible)==0x48?1:-1];
}
#endif
