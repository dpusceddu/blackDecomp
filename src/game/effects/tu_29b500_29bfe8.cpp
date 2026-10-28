struct ReceiveBuffer {
    int a, b, count;
    unsigned char bytes[128];
    int result;
};
extern char D_004438C0[];
extern ReceiveBuffer D_004439C0;
extern int D_00445D80;
extern "C" int func_003678A0(int);
extern "C" int func_00367880(int);
extern "C" int func_0036B100(void*, unsigned, int, void*, int, void*, int, int, int);
extern "C" void func_0029C110(const char*, ...);
extern "C" int func_0029BFE8(int a, int b, int* count, unsigned char* out) {
    func_003678A0(D_00445D80);
    ReceiveBuffer* buf = &D_004439C0;
    buf->a = a;
    buf->b = b;
    buf->count = *count;
    if (func_0036B100(D_004438C0, 0x8000131a, 0, buf, 0x90, buf, 0x90, 0, 0) < 0) {
        func_0029C110("sceDbcReceiveData: rpc error\n");
        func_00367880(D_00445D80);
        return 0;
    }
    int result = buf->result;
    if (result >= 0) {
        *count = buf->count;
        for (int i = 0; i < buf->count; i++) out[i] = buf->bytes[i];
        result = buf->result;
    }
    func_00367880(D_00445D80);
    return result;
}
