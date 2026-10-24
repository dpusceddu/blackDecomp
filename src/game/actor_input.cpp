#include "game/actor/views.hpp"
extern "C" {
void func_0011A890(void *, void *, unsigned int);
void func_001354E0(void *, void *);
void func_00135B80(void *, int);
void func_00103800(void *, int);
extern void *D_0040F530;
extern char *D_0040F0E0;
}
namespace BlackPS2Campaign {
static inline bool ModeTwo(void*owner){return *(int*)((char*)owner+0x38c)==2;}
void ActorStateMachine::Event(int event, int unused, unsigned int flags) {
    if (event == 5) {
        void *owner = Field_007C();
        void *part = (char*)owner+0x620;
        if (Field_0100() > 0) { func_0011A890(D_0040F530, owner, flags); return; }
        func_001354E0(owner, part);
        func_00135B80(Field_007C(), 2);
    }
}
void ActorStateMachine::Leave() {
    if (!ModeTwo(Field_007C())) return;
    {
        func_00103800(D_0040F0E0, 1);
        void *target = *(void **)(D_0040F0E0 + 0x21070);
        char *table = *(char **)((char *)target + 8);
        (*(void (**)(void *, int))(table + 0x34))((char *)target + *(short *)(table + 0x30), 0);
    }
}
}

// Unmatched: 0x13F618 input dispatch vector-copy temporaries, predicate lifetime and branch scheduling.
