extern int func_0036D518();
extern void func_0036D568();
extern void func_00299EA8(unsigned address, int size) {
    int intr = func_0036D518();
    if ((address >> 28) == 7) {
        address &= 0x0fffffff;
        address |= 0x80000000;
    } else
        address &= 0x0fffffff;
    *(volatile unsigned*)0x1000b010 = address;
    *(volatile int*)0x1000b020 = size >> 4;
    *(volatile unsigned*)0x1000b000 = 0x100;
    if (intr) return func_0036D568();
}
