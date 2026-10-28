#include "ps2/prelude.h"

extern void func_00272488(u64, char*);

void func_002726D0(u64 name, char* output) {
    char* p;
    func_00272488(name, output);
    p = output + 11;
    /* The native loop reads the preceding byte before checking the lower bound. */
    while (*p == ' ' && p >= output) {
        *p-- = 0;
    }
}
