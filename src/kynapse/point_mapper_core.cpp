#include "include_asm.h"

#include "kynapse/point_mapper.hpp"

extern unsigned int D_003E6438[], D_003E0040, D_003E6428;
extern unsigned int D_00450FD8, D_003E5E40;
extern unsigned int *D_004510E8;
extern "C" void func_002E7610(void *, const char *, PointMapper *(*)(), int, int, int);
extern "C" PointMapper *func_002DAD10();

extern "C" PointMapper *func_002DADA8(PointMapper *self) {
    self->count = 0;
    *(void **) self = D_003E6438;
    self->pointCounts = 0;
    self->names = 0;
    self->cells = 0;
    return self;
}
extern "C" void func_002DC7E0(int initialize, int priority) {
    if (priority == 0xffff) {
        if (initialize) {
            func_002E7610(&D_00450FD8, "CPointMapper", func_002DAD10, 0, 0, 0);
            return;
        }
        D_004510E8 = &D_003E5E40;
    }
}
extern "C" void func_002DC840(PointMapper *self, int flags) {
    *(void **) self = D_003E6438;
    func_002DADD0(self);
    *(void **) self = &D_003E0040;
    if (flags&1) D_003C87E0(self);
}
extern "C" int func_002DC8A0(PointMapper *self, const char *name, unsigned int *index) {
    *index = 0;
    while (*index<self->count) {
        if (!func_00360838(name, self->names[*index])) return 1;
        ++*index;
    }
    return 0;
}
extern "C" void func_002DC9F0() {
    D_003E6428 = 0;
}
extern "C" void func_002DCA00() {
    func_002DC7E0(1, 0xffff);
}
extern "C" void func_002DCA20() {
    func_002DC7E0(0, 0xffff);
}







INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/point_mapper_core", func_002DADD0);
