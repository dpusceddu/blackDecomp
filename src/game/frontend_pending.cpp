// Unmatched: func_00106068: store scheduling in the load-state initializer.
// Unmatched: func_001077B8: register allocation of the indexed threshold address.
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

#endif
// Unmatched: func_00105BC0: small-data access selection.
// Unmatched: func_00105CF0: argument spill and call scheduling.
// Unmatched: func_001063F8: callee and load-spec return types.
// Unmatched: func_001064D8: callee return and object aliasing.
// Unmatched: func_00106550: unexplained outgoing stack area.
// Unmatched: func_001066D0: callee and load-spec return types.
// Unmatched: func_00106BF8: callee and load-spec return types.
// Unmatched: func_00106CD8: typed status-field register allocation.
// Unmatched: func_00106D70: unexplained outgoing stack area.
// Unmatched: func_00107800: float argument forwarding and threshold layout.
// Unmatched: func_00107880: signed-byte loop induction register allocation.
// Unmatched: func_00107928: callback dispatch and constant ownership.
// Unmatched: func_00107B18: assembler padding of the short wait loop.
// Unmatched: func_00107E30: I/O thread and semaphore callee signatures.
// Unmatched: func_00108120: archive record and callee signatures.
// Unmatched: func_00108218: archive record and callee signatures.
// Unmatched: func_00108540: archive dispatch and cache record types.
// Unmatched: func_00108668: cache cursor and return-register liveness.
// Unmatched: func_001087C8: conditional-return block layout under -G1.
