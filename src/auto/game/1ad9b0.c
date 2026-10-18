#include "auto/prelude.h"

typedef struct { char opaque[0x60]; char animationVariant[1]; } BkActorNamePS2;
extern char *func_001AB1C0(BkActorNamePS2 *, char *, const char *, const char *, const char *, void *);
extern const char *D_003BD190;
extern const char D_003F6E00[];

char *func_001AD9B0(BkActorNamePS2 *actor, char *name, void *context) {
    return func_001AB1C0(actor, name, D_003BD190, actor->animationVariant, "S_300", context);
}

char *func_001AD9E0(BkActorNamePS2 *actor, char *name, void *context) {
    return func_001AB1C0(actor, name, D_003BD190, actor->animationVariant, D_003F6E00, context);
}

char *func_001ADA10(BkActorNamePS2 *actor, char *name, void *context) {
    return func_001AB1C0(actor, name, D_003BD190, actor->animationVariant, "S_106", context);
}

char *func_001ADA40(BkActorNamePS2 *actor, char *name, void *context) {
    return func_001AB1C0(actor, name, D_003BD190, actor->animationVariant, "S_107", context);
}

char *func_001ADA70(BkActorNamePS2 *actor, char *name, void *context) {
    return func_001AB1C0(actor, name, D_003BD190, actor->animationVariant, "???", context);
}
