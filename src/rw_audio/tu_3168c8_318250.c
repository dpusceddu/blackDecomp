#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#ifdef NON_MATCHING
#include "rw_audio/request.h"
#endif

extern s32 func_00312C70();
extern s32 func_00317C20(M2C_UNK *, s32 *);
extern M2C_UNK D_00456448;
extern s32 D_00458480;
extern s32 func_00319928();
extern s32 func_00324948();
extern void func_003249E8();
extern s32 func_00318D28();
extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_004584D8;
extern M2C_UNK D_00458500;
extern M2C_UNK D_00458528;
extern s32 func_00310978();
extern M2C_UNK D_00458550;
extern s32 func_00317340(void *, M2C_UNK);
extern s32 func_00310768();
extern s32 func_00317340();
extern s32 func_003106F0(s32, M2C_UNK, M2C_UNK, f32);

volatile unsigned int func_00318250(s32 arg0, s32 arg1)
{
  s32 var_6;
  void *var_3;
  if (arg0)
  {
  }
  var_3 = *((void **) (((s8 *) arg0) + 4));
  var_6 = 0;
  if (var_3 == arg0)
  {
 goto dummy_label_525197; dummy_label_525197: ;
    do
    {
    }
    while (0);
    goto block_7;
  }
  loop_2:
  if ((M2C_FIELD(var_3, s32 *, 8)) == arg1)
  {
    goto block_4;
  }

  var_3 = *((void **) (((s8 *) var_3) + 4));
  goto block_6;
  block_4:
  return var_6;

  block_6:
  var_6 += 1;

  if (var_3 != arg0)
  {
    goto loop_2;
  }
  block_7:
  return -1;

}


s32 func_003183C0(s32 arg0) {
    s32 var_2;
    void *var_3;

    var_3 = M2C_FIELD(arg0, void **, 4);
    var_2 = 0;
    if (var_3 != arg0) {
        do {
            var_3 = M2C_FIELD(var_3, void **, 4);
            var_2 += 1;
        } while (var_3 != arg0);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003183F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318A20);

s32 func_00318A28(void *arg0) {
    return *M2C_FIELD(arg0, s32 **, 8) == M2C_FIELD(arg0, s32 *, 0xC);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318A40);

void func_00318BC0(void) {
    func_00312C70();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318D20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318E80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003192D8);

void func_00319410(void *arg0)
{
  int new_var;
  void *new_var2;
  s32 temp_4;
  func_00319480();
  new_var2 = arg0 + 4;
  temp_4 = new_var2;
  new_var = D_00458480 == temp_4;
  if (new_var)
  {
    func_00319928(temp_4);
  }
  if (((*(*((s32 **) (((s8 *) arg0) + 0)))) == 2) && (func_00324948(M2C_FIELD(arg0, s32 *, 0x5C)) != 0))
  {
    func_003249E8(M2C_FIELD(arg0, s32 *, 0x5C));
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
  }
}

void func_00319480(void) {
    func_00318D28();
}

#include "ps2/recovered_types.h"
extern s32 func_00319828(void *, s32, s32, s32, void *);

s32 func_003194A0(void *arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    M2C_FIELD(arg0, s32 *, 0x44) = 3;
    M2C_FIELD(arg0, s32 *, 0x48) = arg3;
    M2C_FIELD(arg0, void **, 0x4C) = arg4;
    return func_00319828(arg0, arg1, arg2, arg3, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003194D8);

#include "ps2/recovered_types.h"
extern s32 func_00319828(void *, s32, s32, s32, void *);
extern s32 func_00319628(s32, s32, s32, s32, void *);

s32 func_003195D0(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    M2C_FIELD(arg0, void **, 0x4C) = arg3;
    M2C_FIELD(arg0, s32 *, 0x48) = arg2;
    M2C_FIELD(arg0, s32 *, 0x44) = 3;
    return func_00319828(arg0, arg1, 0xC, (s32) func_00319628, arg0);
}

s32 func_00319610(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00319618);
#ifdef NON_MATCHING
// Unmatched: typed PS2 access/control-flow hypothesis still differs in ABI, scheduling or register allocation.
extern s32 func_0032A938(void *);
extern void * func_00324CB0(s32, s32, s32, void *);
extern void * func_00318E80(s32, s32, s32, s32, void *);

void * func_003196D8(s32 input, s32 operation, s32 length, s32 event, RwaAsyncFile *context) {
    M2C_UNK var_5;
    s32 temp_2;
    s32 var_6;
    void *temp_3;
    void *var_4;

    var_6 = length;
    if (var_6 == 4) {
        context->pending = 0;
        M2C_FIELD(context->header, s32 *, 0) = 0;
        M2C_FIELD(context->header, s32 *, 4) = 0;
        M2C_FIELD(context->header, s32 *, 8) = 0;
        var_5 = 0;
        var_6 = 4;
        var_4 = M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC);
        goto block_10;
    }
    if (context->read_header != 0) {
        context->read_header = 0;
        return func_00319828(context, (s32) context->header, 0xC, (s32) func_00319628, context);
    }
    if (M2C_FIELD(context->header, s32 *, 0) == context->target) {
        context->pending = 0;
        var_5 = 0xC;
        var_4 = M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC);
        goto block_11;
    }
    context->read_header = 1;
    temp_2 = func_0032A938(M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC));
    if (temp_2 >= 0) {
        temp_3 = context->header;
        context->position = (s32) (temp_2 + M2C_FIELD(temp_3, s32 *, 4));
        return func_00324CB0(context->handle, temp_2 + M2C_FIELD(temp_3, s32 *, 4), (s32) func_00318E80, context);
    }
    M2C_FIELD(context->header, s32 *, 0) = 0;
    M2C_FIELD(context->header, s32 *, 4) = 0;
    M2C_FIELD(context->header, s32 *, 8) = 0;
    var_5 = 0;
    var_6 = 4;
    var_4 = M2C_FIELD(M2C_FIELD(context, void **, 0), void **, 0xC);
block_10:
block_11:
    return M2C_FIELD(context, void *(**)(void *, M2C_UNK, s32, s32, s32), 0x48)(var_4, var_5, var_6, event, M2C_FIELD(context, s32 *, 0x4C));
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003196D8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00319828);

void func_003199C0(void) {
    func_00311CA0(&D_004584D8);
}


void func_00319A50(void) {
    func_00311CA0(&D_00458500);
}


void func_00319AE0(void) {
    func_00311CA0(&D_00458528);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00319B00);

s32 func_00319C70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_00310978((s32) &D_00458550, arg0, arg2, arg1, arg3, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00319DA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00319EB0);

void func_00319F80(void *arg0) {
    void *temp_3;

    func_00317340(arg0 + 0x28, 1);
    temp_3 = M2C_FIELD(arg0, void **, 0x28);
    if (temp_3 != NULL) {
        *M2C_FIELD(arg0, void ***, 0x2C) = temp_3;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x2C);
    }
}

s32 func_00319FD0(s32 arg0) {
    M2C_UNK var_17;
    s32 temp_4;
    void *temp_16;

    temp_16 = arg0 + 0x28;
    if (M2C_FIELD(temp_16, u8 *, 0x62) & 2) {
        temp_4 = M2C_FIELD(temp_16, s32 *, 0x38);
        var_17 = 2;
        if (temp_4 != 0) {
            var_17 = (func_00310768(temp_4, 8, 2, 0) == 0) ? 1 : 2;
        }
        func_00317340(temp_16, var_17);
    }
    M2C_FIELD(temp_16, u8 *, 0x62) = (u8) (M2C_FIELD(temp_16, u8 *, 0x62) & 0xDF);
    return arg0;
}

s32 func_0031A058(s32 arg0, s32 *arg1) {
    *arg1 = 0;
    return arg0;
}


void * func_0031A308(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 4, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A350(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
    return arg0;
}

void * func_0031A360(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x80) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 5, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A3A8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
    return arg0;
}

void * func_0031A3B8(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 6, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A400(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0031A410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0031A498);
