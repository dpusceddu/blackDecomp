#include "campaign/actor/views.hpp"
extern "C" {
void func_00148550(void *);
void func_00145400(void *);
void func_00147D28(void *, int, void *);
void func_001480E8(void *, int, void *);
void func_00175B60(void *, void *);
void func_0014BE20(void *, float);
void func_0014A8D0(void *);
void func_00129240(void *, void *, int);
extern char *D_0040F4D4;
extern void *D_0040F4D0;
}
namespace BlackPS2Campaign {
void ActorEntries::Update(float delta) {
    if (Field_01F0()) func_00148550(this);
    func_00145400(this);
    int i;
    for (i = Count() - 1; i >= 0; --i) {
        Entry *entry = (Entry *)(i * 6 + (int)Entries());
        if (entry->active && entry->pending) func_00147D28(this, i, entry);
    }
    bool changed = false;
    for (i = Count() - 1; i >= 0; --i) {
        Entry *entry = (Entry *)(i * 6 + (int)Entries());
        if (entry->active) {
            func_001480E8(this, i, entry);
            changed = true;
            Entry &entry = *(Entry *)(i * 6 + (int)Entries());
            entry.active = 0; entry.pending = 0; entry.a = 0; entry.b = 0; entry.c = 0; entry.d = 0;
        }
    }
    for (i = 0; i < Count(); ++i) ((unsigned char *)Field_01AC())[i * 2] = 0;
    if (changed) func_00175B60(D_0040F4D4 + 0xa48, this);
    func_0014BE20(this, delta);
    if (Field_01ED()) {
        --Field_01ED();
        if (!Field_01ED() && Field_013C()) {
            if (Field_01B8()) func_0014A8D0(this);
            func_00129240(D_0040F4D0, this, 0);
        }
        char *table = (char *)Field_0010();
        (*(unsigned char (**)(void *))(table + 0x24))((char *)this + *(short *)(table + 0x20));
    }

}
}
