#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_MovementModeBase.h"
#include "game/layouts/Recovered_RouteMode.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_00191C20(Recovered_RouteMode *, void *);
extern void func_00191568(Recovered_MovementModeBase *, void *);

void func_00181FF0(void *arg0, void *arg1) {
    Recovered_MovementModeBase *temp_18;
    Recovered_MovementModeBase *temp_19;
    Recovered_RouteMode *temp_20;

    temp_19 = (Recovered_MovementModeBase *) (((s8 *) arg0) + 0x1F0);
    temp_20 = (Recovered_RouteMode *) (((s8 *) arg0) + 0x60);
    M2C_FIELD(arg0, void **, 0x310) = arg1;
    temp_18 = (Recovered_MovementModeBase *) (((s8 *) arg0) + 0x280);
    func_00191C20(temp_20, arg1);
    func_00191568(temp_19, arg1);
    func_00191568(temp_18, arg1);
    M2C_FIELD(arg0, Recovered_MovementModeBase **, 0x50) = temp_18;
    M2C_FIELD(arg0, Recovered_MovementModeBase **, 0x4C) = temp_19;
    M2C_FIELD(arg0, Recovered_RouteMode **, 0x48) = temp_20;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
}
