// Unmatched: 0x1ab1c0: fallback branch layout and register lifetimes.
#ifdef NONMATCHING
#include "ps2/prelude.h"
extern int func_00360838(const char *, const char *);
extern char *D_003BD13C, *D_003BD140, *D_003BD144;
extern char *func_001AB338(void *, char *, const char *, const char *, const char *, void *);
extern char *func_0035CBC0(char *, const char *);
extern char *func_0035C7A4(char *, const char *);
char *func_001AB1C0(void *actor, char *name, const char *prefix, const char *variant, const char *suffix, void *context) {
    int defaultPrefix = func_00360838(D_003BD13C, prefix) == 0;
    int defaultVariant = func_00360838(defaultPrefix ? D_003BD140 : D_003BD144, variant) == 0;
    char *result = func_001AB338(actor, name, prefix, variant, suffix, context);
    if (result) return result;
    if (!defaultVariant) {
        result = func_001AB338(actor, name, prefix, defaultPrefix ? D_003BD140 : D_003BD144, suffix, context);
        if (result) return result;
    }
    if (!defaultPrefix) {
        result = func_001AB338(actor, name, D_003BD13C, variant, suffix, context);
        if (result) return result;
    }
    func_0035CBC0(name, D_003BD13C);
    func_0035C7A4(name, D_003BD140);
    return func_0035C7A4(name, suffix);
}

#endif
