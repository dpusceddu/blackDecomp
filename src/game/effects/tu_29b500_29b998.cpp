extern int D_003C1570, D_00445D80;
extern char D_004438C0[];
extern int D_004439C0[];
extern "C" int func_0036B100(void*, unsigned, int, void*, int, void*, int, int, int);
extern "C" int func_003678A0(int);
extern "C" int func_00367880(int);
extern "C" void func_0029C110(const char*, ...);
extern "C" int func_0029B998(int value) {
    if (!D_003C1570) return 0;
    func_003678A0(D_00445D80);
    D_004439C0[0] = value;
    if (func_0036B100(D_004438C0, 0x80001302, 0, D_004439C0, 0x90, D_004439C0, 0x90, 0, 0) < 0) {
        func_0029C110("sceDbcDeleteSocket: rpc error\n");
        func_00367880(D_00445D80);
        return 0;
    }
    int result = D_004439C0[1];
    func_00367880(D_00445D80);
    return result;
}
