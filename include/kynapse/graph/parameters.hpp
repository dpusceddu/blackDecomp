#ifndef BLACK_GRAPH_PARAMETERS_HPP
#define BLACK_GRAPH_PARAMETERS_HPP
#include "kynapse/parameter_tables.hpp"

// The inherited prefix is verified by the exact PS2 table constructors. The
// additional methods below are scoped views; unused behavior remains provisional.
struct ParameterViews : ParameterTables {
    int FindAperiodicName(const char*)const;
    int FindPeriodicName(const char*)const;
    int FindEstimatedName(const char*)const;
    bool ConsumeGlobal(int);
    bool RaiseIndex(int,IndexUser*);
    void AccumulateIndex(int,IndexUser*);
    void AccumulateGlobal(int);
    void MarkFired();
};
struct ParameterSlotIterator : ObjectBase {
    SlotLink *current;
    ParameterSlotIterator(SlotLink *first):current(first) {}
    ~ParameterSlotIterator() {}
    ParameterSlotIterator &operator++(){current=current->next;return *this;}
    bool IsValid()const{return current!=0;}
    SlotUser *Get()const{return current->user;}
};
extern ParameterTables *ParameterSingleton __asm__("D_003C9588");
inline void *operator new(unsigned int size){return KaimAllocate(size);}
inline bool ParameterHasBudget(float threshold){return 0.0f<threshold;}
#endif
