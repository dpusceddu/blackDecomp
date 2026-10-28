// Error strings share the original read-only data group with this wrapper.
extern "C" {
extern const char D_00401D58[] __attribute__((aligned(8))) = "sceDbcGetDepNumber: rpc error\n";
extern const char D_00401D78[] __attribute__((aligned(8))) = "sceDbcInitSocket: rpc error\n";
extern const char D_00401D98[] __attribute__((aligned(8))) = "sceDbcResetSocket: rpc error\n";
extern const char D_00401DB8[] __attribute__((aligned(8))) = "sceDbcGetDeviceStatus: rpc error\n";
extern const char D_00401DE0[] __attribute__((aligned(8))) = "sceDbcSRData: rpc error\n";
extern const char D_00401E00[] __attribute__((aligned(8))) = "sceDbcSendData: rpc error\n";
}
struct Status {
    int entry[16];
};
extern Status D_00445CC0, D_00445D40;
extern char D_004438C0[];
extern int D_004439C0[], D_00445D80;
extern "C" void func_003680A0(void*, void*);
extern "C" int func_0036D518();
extern "C" int func_0036D568();
extern "C" int func_003678A0(int);
extern "C" int func_00367880(int);
extern "C" int func_0036B100(void*, unsigned, int, void*, int, void*, int, int, int);
extern "C" void func_0029C110(const char*, ...);
extern "C" int func_0029BA58(int index) {
    func_003680A0(&D_00445CC0, (char*)&D_00445CC0 + 0x80);
    func_0036D518();
    D_00445D40 = D_00445CC0;
    func_0036D568();
    if (D_00445D40.entry[index] != 1) return -12;
    func_003678A0(D_00445D80);
    D_004439C0[0] = index;
    if (func_0036B100(D_004438C0, 0x80001303, 0, D_004439C0, 0x90, D_004439C0, 0x90, 0, 0) < 0) {
        func_0029C110(D_00401D58);
        func_00367880(D_00445D80);
        return 0;
    }
    int result = D_004439C0[1];
    func_00367880(D_00445D80);
    return result;
}
