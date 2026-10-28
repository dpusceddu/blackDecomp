extern char D_004438C0[];
extern int D_004439C0[];
extern "C" int func_0036B100(void*, unsigned, int, void*, int, void*, int, int, int);
extern "C" void func_0029C110(const char*, ...);
extern "C" int func_0029B7F8(int value) {
    D_004439C0[1] = value;
    int result = func_0036B100(D_004438C0, 0x80001304, 0, D_004439C0, 0x90, D_004439C0, 0x90, 0, 0);
    if (result < 0) {
        func_0029C110("sceDbcSetWorkAddr: rpc error\n");
        return 0;
    }
    return D_004439C0[0];
}
