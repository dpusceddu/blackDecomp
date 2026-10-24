#include "include_asm.h"

// Virtual slot names describe observed use; original class names are unknown.
class BkRenderDispatchPS2 {
public:
    virtual void Unknown0();
    virtual void Unknown1();
    virtual void Unknown2();
    virtual int Begin(void *record);
    virtual int Load(void *record, void *objects);
    virtual int End(void *record);
};
extern "C" BkRenderDispatchPS2 *func_001AFF88(void *, int);

extern "C" int func_001AFF98(void *context, signed char *record) {
    return func_001AFF88(context, *record)->Begin(record);
}
extern "C" int func_001AFFD8(void *context, signed char *record, void *objects) {
    return func_001AFF88(context, *record)->Load(record, objects);
}
extern "C" int func_001B0028(void *context, signed char *record) {
    return func_001AFF88(context, *record)->End(record);
}
