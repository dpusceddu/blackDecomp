#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00360938(const char*, const char*, s32);
extern s32 func_0027C278(const char*);
extern void* func_0020BC00(void*, s32);
extern void* func_00209E80(void*, s32);
extern s32* func_00209C70(void*);
extern f32* func_00209C78(void*);
extern u16* func_00209C60(void*);
extern char* func_00209C68(void*);
extern s32 func_0035E750(const char*);
extern f64 func_0035E730(const char*);
extern s32 func_00275260(const char*, u16*, s32);
extern char* strcpy(char*, const char*);
extern void func_00209CC0(void*);
extern void* D_0040F544;
extern const char D_003FA8E0[];
extern const char D_003FA8E8[];


extern void func_0021AD88();
extern void func_0021AD58();

void func_0020C098(void) {

}

void func_0020C0A0(void) {

}

void func_0020C0A8(void) {
    func_0021AD88();
    func_0021AD58();
}

void func_0020C0D0(void) {

}

s32 func_0020C0D8(void) {
    return 0;
}

s32 func_0020C0E0(void) {
    return 0;
}

void func_0020C0E8(const char* name, const char* text) {
    void* property;
    void* manager;
    s32 key;
    s32 page;
    s32* integer;
    f32* real;
    if (func_00360938(name, D_003FA8E0, 3) == 0) {
        key = func_0027C278(name + 3);
        page = 1;
        manager = D_0040F544;
    } else if (func_00360938(name, D_003FA8E8, 2) == 0) {
        key = func_0027C278(name);
        page = 2;
        manager = D_0040F544;
    } else {
        key = func_0027C278(name);
        page = 0;
        manager = D_0040F544;
    }
    property = func_00209E80(func_0020BC00(manager, page), key);
    switch (M2C_FIELD(property, s32*, 0)) {
        case 3: break;
        case 1:
            integer = func_00209C70(property);
            *integer = func_0035E750(text);
            break;
        case 2:
            real = func_00209C78(property);
            *real = (f32)func_0035E730(text);
            break;
        case 4: func_00275260(text, func_00209C60(property), 31); break;
        case 5: strcpy(func_00209C68(property), text); break;
    }
    func_00209CC0(property);
}

extern void* func_0024F7B0(const char*);
extern void* func_0024F7D0(s32);
extern void* func_0024F898(f32);

static inline void* FrontendPropertyValue(void* property) {
    if (property) {
        func_00209CC0(property);
        switch (M2C_FIELD(property, s32*, 0)) {
            case 1: return func_0024F7D0(*func_00209C70(property));
            case 2: return func_0024F898(*func_00209C78(property));
            case 5: return func_0024F7B0(func_00209C68(property));
            case 3:
            case 4:
            default: return 0;
        }
    }
    return 0;
}
void* func_0020C260(const char* name) {
    void* result = 0;
    s32 key;
    if (func_00360938(name, D_003FA8E0, 3) == 0) {
        key = func_0027C278(name + 3);
        result = FrontendPropertyValue(func_00209E80((u8*)D_0040F544 + 0x1C6C, key));
    } else if (func_00360938(name, D_003FA8E8, 2) == 0) {
        key = func_0027C278(name);
        result = FrontendPropertyValue(func_00209E80((u8*)D_0040F544 + 0x2530, key));
    } else {
        key = func_0027C278(name);
        result = FrontendPropertyValue(func_00209E80((u8*)D_0040F544 + 0x13A8, key));
    }
    if (result) return result;
    return func_0024F7B0(name);
}
