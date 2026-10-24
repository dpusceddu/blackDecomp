#include "ps2/prelude.h"
extern void *func_002AAF48(const char *,s32,void *,void *);extern void func_002AC128(void);
// Unmatched: exact 48-byte body has a 16-byte original zero tail that natural alignment does not explain.
s32 func_002AC090(const char *name) {s32 found=0;func_002AAF48(name,20,func_002AC128,&found);return found;}
