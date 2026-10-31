#include "ps2/prelude.h"
extern void *D_0040F548, *D_0040F510, *D_0040F4C4, *D_0040F0E4, *D_0040F4C0, *D_0040F544, *D_0040F0E8, *D_0040F4E8;
extern s32 D_0040F54C, D_0040F52C;
// Native zero-initialized readiness byte; original variable identity is UNVERIFIED.
u8 D_0040D985 __attribute__((section(".sdata"))) = 0;
extern s32 func_0027F7D0(void*);
extern void func_0027F818(void*);
extern void func_001250C8(void);
extern s32 func_00125178(void*);
extern s32 func_001D59C8(void*);
extern s32 func_00107F60(void*);
extern s32 func_00100518(void*);
extern s32 func_001AE3A8(void*);
extern s32 func_0020A338(void*);
extern s32 func_00216B68(void*);
extern s32 func_00107020(void*);
extern s32 func_0027C110(void*, s32, const s8*);
extern void func_001D84D0(void*);
extern s32 func_0027C128(void*, const s8*, s32, s32, s32);
extern s32 func_001D59E8(void*);
extern s32 func_00107E10(void*);
extern s32 func_00122738(void*);
extern s32 func_0014D910(s32);
// Staged boot access view; original frontend class identity is UNVERIFIED.
s32 func_00102930(void* self) {
    void *frame, *cursor;
    s32 i, enabled;
    switch (M2C_FIELD(self, s32*, 0x21078)) {
        case 1:
            frame = (u8*)self + 0x20120;
            func_0027F7D0(frame);
            func_0027F818(frame);
            func_001250C8();
            if (!func_00125178(D_0040F548)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 2;
        case 2:
            if (!func_001D59C8(D_0040F510)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 3;
        case 3:
            if (!func_00107F60(D_0040F4C4)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 4;
        case 4:
            if (!func_00100518(D_0040F0E4)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 5;
        case 5:
            if (!func_001AE3A8(D_0040F4C0)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 6;
        case 6:
            if (!func_0020A338(D_0040F544)) return 0;
            func_00216B68((u8*)self + 0x210A0);
            M2C_FIELD(self, s32*, 0x21078) = 7;
        case 7:
            if (!func_00107020(D_0040F0E8)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 8;
        case 8:
            if (!func_0027C110(self, M2C_FIELD(D_0040F4C4, s32*, 0xC80), "10.21.92.101")) return 0;
            func_001D84D0(M2C_FIELD(D_0040F510, void**, 0xCBD4));
            M2C_FIELD(self, s32*, 0x21078) = 9;
        case 9:
            if (!func_0027C128(self, "Data/Andy.aku", 0, D_0040F54C, 0x3000)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 10;
        case 10:
            if (!func_001D59E8(D_0040F510)) return 0;
            M2C_FIELD(self, s32*, 0x21078) = 11;
        case 11:
            cursor = (u8*)self + 0x21060;
            i = 0;
            do {
                --i;
                func_00107E10(cursor);
                cursor = (u8*)cursor + 12;
            } while (i >= 0);
            func_00122738(D_0040F4E8);
            func_0014D910(D_0040F52C);
            enabled = 1;
            M2C_FIELD(self, s32*, 0x21078) = 12;
            M2C_FIELD(self, u8*, 0x210CB) = enabled;
            M2C_FIELD(self, s32*, 0x2108C) = 0;
            M2C_FIELD(self, s32*, 0x21088) = 0;
        case 12: M2C_FIELD(self, s32*, 0x21078) = 28;
        case 28: D_0040D985 = 1;
        default: return 1;
    }
}
