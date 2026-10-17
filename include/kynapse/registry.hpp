// Ported from the companion project (an unpublished companion project).
#ifndef BLACK_KYNAPSE_REGISTRY_HPP
#include "kynapse/compat.hpp"
#define BLACK_KYNAPSE_REGISTRY_HPP

// Recovered fixed-capacity class registry used by lazy singleton accessors.
namespace Kaim {

template <class T, int Capacity>
struct Registry {
    T* slots[Capacity];
    int count;
    static bool resetPending;
    Registry()
    {
        if (resetPending)
            count = 0;
        resetPending = false;
    }
    ~Registry() {}
};
template <class T, int Capacity> bool Registry<T, Capacity>::resetPending = true;

}  // namespace Kaim

#endif
