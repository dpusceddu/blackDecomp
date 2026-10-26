#ifndef KYNAPSE_CALLBACK_OBJECT_HPP
#define KYNAPSE_CALLBACK_OBJECT_HPP

// Partial callback object; the object identity and two callback signatures are UNVERIFIED.
struct Recovered_CallbackObject {
    unsigned int unk_00, unk_04, unk_08;
    unsigned short flags;
    short index;
    unsigned int unk_10, unk_14, unk_18;
    Recovered_CallbackObject* self;
    void (*callback_20)();
    int (*callback_24)(void*, void*, int);
    void (*callback_28)();
    void (*callback_2c)(void*);
    char unk_30[0x24];
    void* context;
};

// Partial owning object; the meaning of the counts is UNVERIFIED.
struct Recovered_CallbackFamily {
    char unk_00[0x38];
    int count;
    int (*callback)(int);
    char unk_40[0x198];
    int unk_1d8;
    int object_count;
    Recovered_CallbackObject* objects;
    Recovered_CallbackObject object[3];
};

extern "C" void func_00366090(Recovered_CallbackObject*, int, int, void*);

#endif
