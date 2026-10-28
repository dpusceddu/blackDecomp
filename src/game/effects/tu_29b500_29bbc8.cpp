struct Status {
    int entry[16];
};
extern Status D_00445CC0, D_00445D40;
extern "C" void func_003680A0(void*, void*);
extern "C" int func_0036D518();
extern "C" int func_0036D568();
extern "C" int func_0029BBC8(int index) {
    func_003680A0(&D_00445CC0, (char*)&D_00445CC0 + 0x80);
    func_0036D518();
    D_00445D40 = D_00445CC0;
    func_0036D568();
    return D_00445D40.entry[index] == 1 ? 1 : 3;
}
