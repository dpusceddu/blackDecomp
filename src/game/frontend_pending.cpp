// Unmatched: func_00106068: store scheduling in the load-state initializer.
// Unmatched: func_001077B8: register allocation of the indexed threshold address.
// Unmatched: func_001065D0: switch layout and jump-table ownership.
#ifdef NONMATCHING
struct FrontendLoadState {
    int state, error;
    char reserved[16];
    long request;
    char reserved20[16];
    void* resource;
    void Reset() __asm__("func_00106068");
};
void FrontendLoadState::Reset() {
    request=0;
    state=1;
    error=0;
    resource=0;
}

struct FrontendControllerThresholds {
    char reserved[0x77c];
    unsigned char enabled[2];
    char reserved77e[14];
    float thresholds[2];
    void Raise(signed char index,int mask,float value) __asm__("func_001077B8");
};
void FrontendControllerThresholds::Raise(signed char index,int mask,float value) {
    if (enabled[index] && (mask&1)) {
        float* threshold=&thresholds[index];
        if (*threshold<value) *threshold=value;
    }
}
extern "C" int func_00129DE8(void*);
extern "C" int func_001E8900(int);
extern "C" void func_0020B0C0(void*);
extern void* D_0040F4D0;
extern char* D_0040F510;
extern void* D_0040F544;
extern int* D_0040F504;
struct FrontendLoadExit {
    int state;
    int Step() __asm__("func_001065D0");
};
int FrontendLoadExit::Step() {
    switch(state) {
    case 2: case 3: case 4: case 28:
        state=29;
    case 29:
        break;
    case 30:
        goto waitForAudio;
    case 32:
        goto finish;
    default:
        return 1;
    }
    if (!func_00129DE8(D_0040F4D0)) return 0;
    *D_0040F504=1;
    state=30;
waitForAudio:
    if (!func_001E8900(*(int*)(D_0040F510+0xcbd8))) return 0;
    state=32;
finish:
    func_0020B0C0(D_0040F544);
    state=55;
    return 1;
}

#endif
// Unmatched: func_00105BC0: small-data access selection.
// Unmatched: func_00105CF0: argument spill and call scheduling.
// Unmatched: func_00105D48: relative-pointer archive types.
// Unmatched: func_00106080: switch layout and jump-table ownership.
// Unmatched: func_00106200: mixed 64-bit and 128-bit decompiler model.
// Unmatched: func_001063F8: callee and load-spec return types.
// Unmatched: func_001064D8: callee return and object aliasing.
// Unmatched: func_00106550: callee and member-pointer signatures.
// Unmatched: func_001066D0: callee and load-spec return types.
// Unmatched: func_00106868: switch layout and jump-table ownership.
// Unmatched: func_001069F8: mixed 64-bit and 128-bit decompiler model.
// Unmatched: func_00106BF8: callee and load-spec return types.
// Unmatched: func_00106CD8: typed status-field register allocation.
// Unmatched: func_00106D70: callee and member-pointer signatures.
// Unmatched: func_00106DF0: switch layout and jump-table ownership.
// Unmatched: func_00107020: floating-point callee arguments and stack objects.
// Unmatched: func_00107228: controller-interface and state object types.
// Unmatched: func_00107470: controller-interface and float argument types.
// Unmatched: func_00107730: float argument forwarding in dispatch wrapper.
// Unmatched: func_00107800: float argument forwarding and threshold layout.
// Unmatched: func_00107880: signed-byte loop induction register allocation.
// Unmatched: func_00107928: callback dispatch and constant ownership.
// Unmatched: func_00107B18: resource-slot callee signatures.
// Unmatched: func_00107E30: I/O thread and semaphore callee signatures.
// Unmatched: func_00108120: archive record and callee signatures.
// Unmatched: func_00108218: archive record and callee signatures.
// Unmatched: func_00108328: archive record and string lookup types.
// Unmatched: func_00108540: archive dispatch and cache record types.
// Unmatched: func_00108668: cache cursor and return-register liveness.
// Unmatched: func_001087C8: small-data flags and callee signatures.
// Unmatched: func_00108818: small-data flags and archive lookup signatures.
// Unmatched: func_00108890: stack pathname aggregate and callback signatures.
