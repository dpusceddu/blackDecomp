/* Binding collision storage uses a three-argument work initializer. */
#include "auto/prelude.h"

extern s32 func_0032FAF0(s32);
extern s32 func_0037CE60(void *, s32, s32, s32);
extern s32 func_0032E710(void *, s32, s32);

void func_0032E120(void *scene, void *definitions) {
    u8 storage[8] __attribute__((aligned(16)));
    s32 work;
    s32 oldWork;
    void *solver;

    M2C_FIELD(scene, void **, 0x14) = definitions;
    oldWork = M2C_FIELD(scene, s32 *, 0x1C);
    if (oldWork != 0) {
        func_0032FAF0(oldWork);
        M2C_FIELD(scene, s32 *, 0x1C) = 0;
    }
    solver = M2C_FIELD(scene, void **, 0x18);
    if (definitions != NULL) {
        func_0037CE60(solver, M2C_FIELD(definitions, s32 *, 0x10), M2C_FIELD(definitions, s32 *, 8), M2C_FIELD(definitions, s32 *, 4));
        *(s32*)(storage+0)=M2C_FIELD(definitions,s32*,0x14);
        work = func_0032E710(storage, M2C_FIELD(definitions, s32 *, 0), (s32) M2C_FIELD(scene, void **, 0x18));
        M2C_FIELD(scene, s32 *, 0x1C) = work;
        return;
    }
    func_0037CE60(solver, 0, 0, 0);
}
