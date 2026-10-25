#include "ps2/prelude.h"

// Class and iterator names of the original; SN supplies their natural eight-byte placement.
const char SteeringClassName[] __asm__("D_00408630") = "CRepulsorDynamicAvoidance";
const char RootTypeName[] __asm__("D_00408650") = "Q24Kaim7CObject";
const char IteratorTypeName[] __asm__("D_00408660") = "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator";
struct SteeringRegistrationState;
struct NativeVirtualTable;
typedef void* (*SteeringFactory)(int);
extern void* func_0030D0E0(void*,const char*,SteeringFactory);
extern struct SteeringRegistrationState D_00455AD0;
extern void* func_00305538(int);
extern const struct NativeVirtualTable* D_00455BE0;
extern const struct NativeVirtualTable D_003F07A0,D_003E0040;
extern void (*D_003C87E0)(void *);

/* Register the factory during initialization, or restore its base class table. */
void func_003063A8(s32 initialize, s32 phase) {
    if (phase == 0xFFFF) {
        if (initialize != 0) {
            func_0030D0E0(&D_00455AD0, SteeringClassName, func_00305538);
            return;
        }
        D_00455BE0 = &D_003F07A0;
    }
}

/* Base destruction resets the vptr and conditionally releases the allocation. */
void func_00306400(void **object, unsigned deleteFlags)
{
    *object = (void*)&D_003E0040;
    if (deleteFlags & 1) D_003C87E0(object);
}

void func_00306438(void) {

}

void func_00306440(void) {

}

/* Assembly between the functions: func_00306448 (240 bytes), func_00306538 (336 bytes), func_00306688 (216 bytes) */

void func_00306760(void) {
    func_003063A8(1, 0xFFFF);
}

void func_00306780(void) {
    func_003063A8(0, 0xFFFF);
}

