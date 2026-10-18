#include "rwa_ee/voice.h"

typedef struct RwaConstructCallback {
    void *(*create)(void **,void *);
    void *user,*memory;
} RwaConstructCallback;
extern void *func_0031DEB8(s32,const void *,void *);
extern RwaFormatId D_0040A260;
extern void *func_0031E320(void **,void *,void *);
extern void *func_0035C6EC(void *,s32,u32);

void *func_0031C578(void **object, RwaConstructCallback *callback) {
    if (callback->create) return callback->create(object,callback->user);
    if (*object != func_0031DEB8(0,&D_0040A260,0))
        return func_0031E320(object,(void *)callback->create,callback->user);
    return func_0035C6EC(callback->memory,0xcd,0xd0);
}
