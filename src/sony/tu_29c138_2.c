extern int func_0036A038(const char*, ...);
extern unsigned func_0029C628(volatile unsigned*);
void func_0029C138(volatile unsigned* flags) {
    int count = 0x1000000;
    while (*flags & 0x100) {
        if (--count < 0) {
            func_0036A038("libdma: sync timeout\n");
            func_0029C628(flags);
        }
    }
}
