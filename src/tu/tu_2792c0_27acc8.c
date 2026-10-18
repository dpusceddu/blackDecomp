/* Translation unit tu_2792c0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002AC628();
extern s32 func_0035C6EC();
extern s32 func_0027BA68();
extern s32 func_0027B688();
extern s32 func_0027BB98();

void func_0027ACC8(void) {

}

/* Assembly between the functions: func_0027ACD0 (1144 bytes), func_0027B148 (280 bytes), func_0027B260 (104 bytes) */

s32 func_0027B2C8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x6C) = -1.0f;
    return 1;
}

void func_0027B2E0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x68) = arg1;
    M2C_FIELD(arg1, void **, 0x30) = arg0;
}

/* Assembly between the functions: func_0027B2F0 (152 bytes) */

void func_0027B388(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x74) = fparg0;
}

s32 func_0027B390(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_5;

    func_002AC628(M2C_FIELD(arg0, s32 *, 0x60), M2C_FIELD(arg1, s32 *, 0x60), arg2);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x64);
    if (temp_5 != 0) {
        func_002AC628(M2C_FIELD(arg0, s32 *, 0x64), temp_5, arg2);
    }
    M2C_FIELD(arg0, s32 *, 0x78) = (s32) M2C_FIELD(arg2, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32) M2C_FIELD(arg2, s32 *, 0xC);
    temp_2 = M2C_FIELD(arg1, s32 *, 0x80);
    M2C_FIELD(arg0, s32 *, 0x80) = temp_2;
    return temp_2;
}

/* Assembly between the functions: func_0027B408 (576 bytes) */

void func_0027B648(void *arg0, s32 arg1, s32 arg2)
{
  M2C_FIELD(arg0, s32 *, 8) = arg1;
  M2C_FIELD(arg0, s32 *, 0xC) = arg2;
  M2C_FIELD(arg0, s32 *, 0) = (M2C_FIELD(arg0, s32 *, 4) = 0);
  func_0035C6EC(arg1, 0, arg2 << 5);
}

/* Assembly between the functions: func_0027B688 (80 bytes) */

s32 func_0027B6D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_18;
    void *temp_4;

    temp_18 = func_0027BA68(arg2, arg3, arg4);
    temp_4 = M2C_FIELD(arg0, s32 *, 8) + (func_0027B688(arg0) << 5);
    M2C_FIELD(temp_4, s32 *, 0xC) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x10) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x14) = arg4;
    M2C_FIELD(temp_4, s32 *, 0x18) = temp_18;
    M2C_FIELD(temp_4, s8 *, 0x1D) = (s8) arg5;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
    return (s32) temp_4;
}

/* Assembly between the functions: func_0027B780 (256 bytes), func_0027B880 (208 bytes), func_0027B950 (272 bytes), func_0027BA60 (8 bytes), func_0027BA68 (128 bytes), func_0027BAE8 (104 bytes), func_0027BB50 (72 bytes), func_0027BB98 (32 bytes), func_0027BBB8 (128 bytes) */

void func_0027BC38(void) {

}

void func_0027BC40(void) {

}

void func_0027BC48(void) {

}

void func_0027BC50(void) {

}

void func_0027BC58(void) {

}

/* Assembly between the functions: func_0027BC60 (160 bytes) */

void func_0027BD00(void) {
    func_0027BB98();
}
