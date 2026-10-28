#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0020DF68();
extern M2C_UNK D_003FBA80;
extern s32 func_00214B90();
extern M2C_UNK D_003FBA98;
extern s32 func_002145E0();
extern M2C_UNK D_003FBAB8;
extern s32 func_00214A20();
extern s32 func_0020DCB0();
extern M2C_UNK D_00492420;
extern M2C_UNK D_00492430;
extern M2C_UNK D_00492440;
extern M2C_UNK D_00492450;
extern s32 func_0020DCF8();
extern M2C_UNK D_003FB980;
extern s32 func_0020DD48();
extern s32 func_0020DF30();
extern s32 func_0020DF90();
extern s32 D_003BE858;
extern void * D_0040F0E0;
extern void func_00105258();
extern void *D_0040F0E0;
extern s32 func_0010B1C8();
extern s32 D_0040F4F0;
extern s32 D_003BE84C;
extern s32 func_0010B270();
extern s32 func_0010B2C0();
extern s32 func_0010B608(s32, s32);
extern s32 D_003BE850;
extern s32 func_0010B530(s32, M2C_UNK);
extern s32 func_00275260();
extern s32 func_0020DE78();
extern M2C_UNK D_004924B0;
extern s32 func_00215BE8();
extern s32 func_0020DE28();
extern s32 D_004924B0;
extern s32 func_0035D1A0(M2C_UNK *, s32, M2C_UNK);
extern M2C_UNK D_003BE860;

s32 func_00214408(s32 arg0) {
    func_0020DF68(arg0, (s32) &D_003FBA80, (s32) func_00214B90);
    func_0020DF68(arg0, (s32) &D_003FBA98, (s32) func_002145E0);
    func_0020DF68(arg0, (s32) &D_003FBAB8, (s32) func_00214A20);
    func_0020DCB0((s32) &D_00492420);
    func_0020DCB0((s32) &D_00492430);
    func_0020DCB0((s32) &D_00492440);
    func_0020DCB0((s32) &D_00492450);
    func_0020DCF8((s32) &D_00492420, (s32) "FE_MEDALAWARDED");
    func_0020DCF8((s32) &D_00492430, (s32) "FE_CHALLENGERESULTS");
    func_0020DCF8((s32) &D_00492440, (s32) &D_003FB980);
    func_0020DCF8((s32) &D_00492450, (s32) "FE_CHALLENGERESULT");
    return 1;
}

s32 func_00214508(s32 arg0) {
    func_0020DD48((s32) &D_00492420);
    func_0020DD48((s32) &D_00492430);
    func_0020DD48((s32) &D_00492440);
    func_0020DD48((s32) &D_00492450);
    func_0020DF30((s32) &D_00492420);
    func_0020DF30((s32) &D_00492430);
    func_0020DF30((s32) &D_00492440);
    func_0020DF30((s32) &D_00492450);
    func_0020DF90(arg0, (s32) &D_003FBA80);
    func_0020DF90(arg0, (s32) &D_003FBA98);
    func_0020DF90(arg0, (s32) &D_003FBAB8);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_214408", func_002145E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_214408", func_00214A20);
extern void* func_00103358(void*, s32);
extern s32 func_001034B0(void*, void*);
s32 func_00214B90(void) {
    void* group = func_00103358(D_0040F0E0, M2C_FIELD(D_0040F0E0, u8*, 0x2020C));
    u8 i = 0;
    s32 result;
    if (M2C_FIELD(group, u8*, 0x21)) {
        do {
            u8* item = (u8*)((i * 0x60) + M2C_FIELD(group, s32*, 0x18));
            if (M2C_FIELD(item, u8*, 0x58) == M2C_FIELD(D_0040F0E0, u8*, 0x2020E)) {
                result = func_001034B0(D_0040F0E0, (u8*)D_0040F0E0 + 0x20FA0);
                goto done;
            }
            i++;
        } while (i < M2C_FIELD(group, u8*, 0x21));
    }
    result = func_001034B0(D_0040F0E0, (u8*)D_0040F0E0 + 0x20FD8);
done:
    return result;
}
s32 func_00214C48(const s8* text) {
    s32 i = 0;
    do {
        s8 c = *text;
        if (!c) return 0;
        if (c != '-' && (i == 4 || i == 9 || i == 14)) return 0;
        if (i != 4 && i != 9 && i != 14) {
            u8 c2 = *text;
            if ((u32)(c2 - 'A') >= 26 && (u32)(c2 - 'a') >= 26 && (u32)(c2 - '0') >= 10) return 0;
        }
        i++;
        text++;
    } while (i < 19);
    return 1;
}

void func_00215028(void) {
    u8 temp_2;

    D_003BE858 = 0;
    temp_2 = M2C_FIELD(D_0040F0E0, u8 *, 0x20164);
    if (temp_2 == 1) {
        D_003BE858 = (s32) temp_2;
    }
}

#include "ps2/recovered_types.h"
extern s32 func_00209760(void *, s32);
extern void * D_0040F544;
extern M2C_UNK D_003FBC50;
extern M2C_UNK D_003FBC60;
extern M2C_UNK D_003FBC78;
extern M2C_UNK D_003FBC90;
extern M2C_UNK D_003FBCA8;
extern M2C_UNK D_003FBCC0;
extern M2C_UNK D_003FBCD8;
extern M2C_UNK D_003FBCF0;
extern M2C_UNK D_003FBD08;
extern M2C_UNK D_003FBD20;
extern M2C_UNK D_003FBD30;
extern M2C_UNK D_003FBD40;
extern M2C_UNK D_003FBD50;
extern s32 func_0020E0C8(s32, s32);
extern M2C_UNK D_003FBB80;
extern M2C_UNK D_003FBBA0;
extern M2C_UNK D_003FBBB8;
extern M2C_UNK D_003FBBD0;
extern s32 func_0020E020(s32, s32);
extern M2C_UNK D_003FBBE8;
extern s32 func_0020DD48(void *);
extern s32 D_00492460;
extern s32 func_0020DF30(s32 *);
extern s32 D_00492470;
extern s32 D_004924A0;
extern s32 D_004924B0;

s32 func_00215058(s32 arg0) {
    s32 *var_16;

    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC50);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC60);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC78);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC90);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCA8);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCC0);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCD8);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCF0);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD08);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD20);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD30);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD40);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD50);
    func_0020E0C8(arg0, (s32) &D_003FBB80);
    func_0020E0C8(arg0, (s32) &D_003FBBA0);
    func_0020E0C8(arg0, (s32) &D_003FBBB8);
    func_0020E0C8(arg0, (s32) &D_003FBBD0);
    func_0020E020(arg0, (s32) &D_003FBBE8);
    func_0020DD48(&D_00492460);
    func_0020DF30(&D_00492460);
    var_16 = &D_00492470;
    do {
        func_0020DD48(var_16);
        func_0020DF30(var_16);
        var_16 = (s32 *) (((s8 *) var_16) + 0xC);
    } while ((s32) var_16 < (s32) ((s32 *) (((s8 *) &D_00492470) + 0x30)));
    func_0020DD48(&D_004924A0);
    func_0020DF30(&D_004924A0);
    func_0020DD48(&D_004924B0);
    func_0020DF30(&D_004924B0);
    return 1;
}


void func_002156B0(void)
{
  func_00105258(0x20220 + D_0040F0E0);
  func_0010B1C8(D_0040F4F0);
  D_003BE84C = 1;
}

void func_002156F8(void)
{
  func_00105258(D_0040F0E0 + 0x20220);
  func_0010B270(D_0040F4F0);
  D_003BE84C = 3;
}

extern void func_0010B238(s32);
extern void func_0010B2A8(s32);
void func_00215740(void) {
    func_00105258((u8*)D_0040F0E0 + 0x20220);
    func_0010B238(D_0040F4F0);
    D_003BE84C = 2;
}
void func_00215788(void) {
    func_00105258((u8*)D_0040F0E0 + 0x20220);
    func_0010B2A8(D_0040F4F0);
    D_003BE84C = 0;
}
void func_002157C8(void) {
    func_00105258((u8*)D_0040F0E0 + 0x20220);
    func_0010B2C0(D_0040F4F0, 0);
    D_003BE84C = 4;
}

void func_00215810(void)
{
  void *new_var;
  void *new_var2;
  new_var2 = D_0040F0E0;
  new_var = new_var2 + 0x20220;
  func_00105258(new_var);
  func_0010B2C0(D_0040F4F0, 0);
  D_003BE84C = 5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_214408", func_00215858);
extern s32 func_0035E750(s32);
extern void func_0010B2F0(s32);
extern void func_0010B308(s32);
void func_00215980(s32 arg0) {
    s32 value = func_0035E750(arg0) != 0;
    if (value != M2C_FIELD(D_0040F0E0, u8*, 0x20164)) {
        func_00105258((u8*)D_0040F0E0 + 0x20220);
        if (value) func_0010B2F0(D_0040F4F0);
        else func_0010B308(D_0040F4F0);
        D_003BE84C = 7;
    }
}

void func_00215A00(void) {
    func_0010B608(D_0040F4F0, D_003BE850);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_214408", func_00215A30);

void func_00215BB0(void) {
    func_0010B530(D_0040F4F0, 0);
    func_0010B608(D_0040F4F0, 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_214408", func_00215BE8);

void func_00215D20(s32 arg0) {
    u8 sp[56];
    func_00275260(arg0 + 0x78, sp, 0x20);
    func_0020DE78(&D_004924B0, sp);
    func_00215BE8(arg0);
}

void func_00215D68(s32 arg0, s32 arg1) {
    func_0020DE28(&D_004924B0);
    func_0035D1A0(&D_003BE860, arg1, 0x3C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_214408", func_00215DA8);

#include "ps2/recovered_types.h"
extern s32 D_004924E0;
extern s32 func_0020DD48(void *);
extern s32 func_0020DF30(s32 *);
extern s32 D_004924C0;
extern s32 D_004924D0;
extern s32 func_0020DF90(s32, s32);
extern M2C_UNK D_003FBE10;
extern M2C_UNK D_003FBE20;

s32 func_00215EC8(s32 arg0) {
    s32 *var_16;

    var_16 = &D_004924E0;
    do {
        func_0020DD48(var_16);
        func_0020DF30(var_16);
        var_16 = (s32 *) (((s8 *) var_16) + 0xC);
    } while ((s32) var_16 < (s32) ((s32 *) (((s8 *) &D_004924E0) + 0x18)));
    func_0020DD48(&D_004924C0);
    func_0020DF30(&D_004924C0);
    func_0020DD48(&D_004924D0);
    func_0020DF30(&D_004924D0);
    func_0020DF90(arg0, (s32) &D_003FBE10);
    func_0020DF90(arg0, (s32) &D_003FBE20);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_214408", func_00215F80);
extern s32 func_0020B988(void*, s32);
extern void func_001F2838(s32, s8, s32);
extern s32 D_0040F51C;
extern void* D_0040F510;
extern void* D_0040F0E4;
extern void func_001D8DF0(void*);
extern void func_00103818(void*);
extern void func_001005A0(void*);
void func_00216258(void) {
    func_0020B988(D_0040F544, 4);
    func_001F2838(D_0040F51C, 0, 6);
    func_001D8DF0(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x34));
    func_00103818(D_0040F0E0);
    func_001005A0(D_0040F0E4);
}
