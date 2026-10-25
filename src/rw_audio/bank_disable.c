#include "include_asm.h"

#include "rw_audio/sound.h"
#ifdef NON_MATCHING
#include "ps2/prelude.h"
#endif

extern void func_00315EE8(RwaSound *, s32);

RwaSound *func_00313F90(RwaSound *sound, s32 argument) {
    sound->driver->enable(sound, argument, 0);
    func_00315EE8(sound, 0);
    return sound;
}

#ifdef NON_MATCHING
extern s32 func_00313EA8(s32);
extern void func_00313650(RwaDiskHeader *);
extern void *func_00312CC8(u32,u32);
extern void *func_0035C544(void *,const void *,u32);
extern void func_00312D08(void *);
extern void func_00324BA0(s32,void *,u32,s32,s32,void *);
extern void func_003137D8(RwaBank *,s32,s32);
extern s32 func_00316400(void *,const char *);
extern void *D_0040E15C;
extern void func_003143D8(RwaBank *,void *,void *);
extern void func_00313F00(void *,void *);
extern void *func_00313C90(RwaBank *,u32);
extern RwaStream *func_003134E0(RwaStream *);
extern RwaBank *D_0040E178,*D_0040E174;
extern RwaLink D_0040E778;
extern void func_00313DC8(RwaBank *);
extern void func_00315F28(void *);
extern void *func_00314440(RwaBank *,void *);
extern void func_00318340(void *);
extern void func_003145D0(RwaBank *);
// Unmatched: shared-bank list traversal scheduling and register allocation differ.
void func_00313FD0(RwaBank *bank) {
    RwaLink *link,*owner,*sentinel=(RwaLink *)&bank->list_previous;
    *bank->previous=bank->next;bank->next->previous=bank->previous;
    if(bank==D_0040E178)D_0040E178=D_0040E174;
    if((bank->flags1b&0x40)&&(bank->data||(bank->flags1a&1)))func_00313DC8(bank);
    if(!(bank->flags1b&0x20)) {
        if(bank->flags1b&0x10)func_00312D08(bank->allocation);
        else {
            link=bank->first;
            if(link!=sentinel){
                owner=D_0040E778.previous;
                do {
                    s32 retained=0;void *sound=link->object;
                    if(owner==&D_0040E778)func_00315F28(sound);
                    while(owner!=&D_0040E778){if(func_00314440((RwaBank *)((char *)owner-0x1c),sound)){retained=1;break;}owner=owner->previous;}
                    if(!retained)func_00315F28(sound);
                    link=link->next;owner=D_0040E778.previous;
                }while(link!=sentinel);
            }
            func_00318340(sentinel);func_003145D0(bank);
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313FD0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003141E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314370);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003143C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003144C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314530);
