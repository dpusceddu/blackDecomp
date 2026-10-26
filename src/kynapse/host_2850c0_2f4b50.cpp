#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/host_2850c0.hpp"
#include "kynapse/array_cleanup.h"
#include "ps2/recovered_types.h"
#ifdef NON_MATCHING
#include "game/classes/UnknownVtable_003DC838.hpp"
#include "game/classes/UnknownVtable_003DC5F8.hpp"
#include "game/classes/UnknownVtable_003DC100.hpp"
#include "game/classes/UnknownVtable_003DB1F8.hpp"
#include "game/classes/UnknownVtable_003DB828.hpp"
#include "game/classes/UnknownVtable_003DC130.hpp"
#include "game/classes/other/UnknownVtable_003E07F8.hpp"
#include "game/classes/other/UnknownVtable_003E06C8.hpp"
#include "game/classes/other/UnknownVtable_003E0688.hpp"
#include "game/classes/other/UnknownVtable_003E0058.hpp"
#include "game/classes/other/UnknownVtable_003E0140.hpp"
#endif

namespace Kaim {
// /SLUS_213.76 0x2f4b50

void Host2850C0::Notify(void* owner)
{
    if (listeners)
        listeners->Notify(this, owner);
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00305FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0030BA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0030BCD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0030BE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0030CF90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0030D038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00311568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00311848);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003119A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00316770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00316838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00316840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031A5B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031A630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031A6D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031A738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031A770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031A7D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AAD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AC10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AC40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AC68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AC98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031ACC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AD20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AD78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031ADF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AE18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AE90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031AEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B7A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B7D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B830);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B8B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031B9B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031BA28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031BA50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031BA78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031BAA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031BAD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031BB08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031CFF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031D178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031D1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031D268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031D2A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031D2E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031D400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0031E5C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003237E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323A08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323A68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323AD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323BB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323C78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323CA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323CE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00323D48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032A578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032A5A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032A600);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032ABD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032AC60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032AD30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032AE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032B3B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032B860);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032B920);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0032E710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00331D70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00332D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00333018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003333A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00333808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003339A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00333B48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00333ED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003343D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003345A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00334B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00335730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00335D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00335DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00335FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00336520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003366F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003367B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00336810);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00336F98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00337110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003372A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00337478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00337988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00337A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00337FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00338150);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00338288);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00338DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003398C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003398D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00339C68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033B8D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033BC28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033C5A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033C6A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033C7C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033C918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033D808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033DAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033DBF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033DD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033DE40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033DF68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033E060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033E220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033EBD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033ECF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033EE08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033EF60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033F328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033FAA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033FB60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033FC38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0033FF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003401A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003404E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003411C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003493F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003494D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00349560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00349960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00349BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00349C38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00349C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0034A000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0034AEA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0034B128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003521F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003527D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003527E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352848);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003528C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003528E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352A90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352B50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352D38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352D48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352D50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00352F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00353110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003560F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00356150);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003561C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00356218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00356220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0035A5C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0035A748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0035A8C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00360838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00360938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00360A00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00360A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00364F50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00365140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00365588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00365BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00365F80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00366090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003660E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003660F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00366188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003661B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003662D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00367400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00367F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00367FF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003680A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003681D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368258);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003682D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368338);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003683A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003684E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003685D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00368738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003688B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036D260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036D3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036D408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036D518);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036D568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036E9B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036E9D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036E9E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036EA90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036EAD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036EB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036EB78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036EBB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036EF80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036F0E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036F140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036F230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0036F310);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00371520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00371598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00371610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003716F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00371848);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003718B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00371928);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00371B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00371C00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003720B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372170);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372B28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372D68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372E30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372F18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00372FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00373378);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00373768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00374488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00374550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003745B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00374608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00374640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00374700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00374F48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00375078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003750B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00375108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00375140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003788C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378A60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378B78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378B98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378CA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00378CD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037BB90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037BC50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037BC58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037BCE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037BE50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037BEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037BF28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037C238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037C4E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037C688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037EC50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037F278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0037F928);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00381AB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003822B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003822D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00382358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00383890);
#ifdef NON_MATCHING
namespace Unnamed {
// Unmatched: exact body, but its section leaves an unexplained zero gap before the next function.
void UnknownVtable_003DC5F8::Function_00383920()
{
    Field_00C4() = 2;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00383920);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00383938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00383978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384708);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003847E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384818);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003848A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003848F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003849F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384AB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384C00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384C38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384C70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384CA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00384E28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00385000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00385078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00385148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003852D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00388D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00388D80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00388D98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00388E10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00388ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00388F48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00389060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00389208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038A490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038A670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038A758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038A838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038A9D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038AAF0);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038B6B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038B840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038BAD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038BBB0);
// The matched lookups confirm the name and count offsets; the remaining descriptor fields are UNVERIFIED.
extern "C" PS2KaimClassRegistry* func_0038B098();
extern "C" PS2KaimClassRegistry* func_0038E688();
extern "C" PS2KaimClassRegistry* func_00390BC8();
extern "C" PS2KaimClassRegistry* func_0038BD60();
extern "C" PS2KaimClassRegistry* func_0038BDD8();
extern "C" PS2KaimClassRegistry* func_0038B468();
extern "C" PS2KaimClassRegistry* func_0038BE50();
extern "C" PS2KaimClassRegistry* func_0038C3E0();
extern "C" PS2KaimClassRegistry* func_0038BA30();

static inline PS2KaimClassDescriptor* FindClass(PS2KaimClassRegistry* registry, const char* name) {
    int i;
    for (i = 0; i < registry->count; ++i) {
        if (strcmp(registry->slots[i]->name, name) == 0) return registry->slots[i];
    }
    return 0;
}

extern "C" PS2KaimClassDescriptor* func_0038B150(const char* name) {
    if (!name)
        return 0;
    return FindClass(func_0038B098(), name);
}
extern "C" PS2KaimClassDescriptor* func_0038EE80(const char* name) {
    if (!name)
        return 0;
    return FindClass(func_0038E688(), name);
}
extern "C" PS2KaimClassDescriptor* func_00390CF8(const char* name) {
    if (!name)
        return 0;
    return FindClass(func_00390BC8(), name);
}
extern "C" PS2KaimClassDescriptor* func_0038C098(const char* name) {
    if (!name) return 0;
    return FindClass(func_0038BD60(), name);
}
extern "C" PS2KaimClassDescriptor* func_0038C138(const char* name) {
    if (!name) return 0;
    return FindClass(func_0038BDD8(), name);
}
extern "C" PS2KaimClassDescriptor* func_0038C1D8(const char* name) {
    if (!name) return 0;
    return FindClass(func_0038B468(), name);
}
extern "C" PS2KaimClassDescriptor* func_0038C278(const char* name) {
    if (!name) return 0;
    return FindClass(func_0038BE50(), name);
}
extern "C" PS2KaimClassDescriptor* func_0038C438(const char* name) {
    if (!name) return 0;
    return FindClass(func_0038C3E0(), name);
}
extern "C" PS2KaimClassDescriptor* func_0038C4D8(const char* name) {
    if (!name) return 0;
    return FindClass(func_0038BA30(), name);
}





INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038C618);
extern "C" int D_003E8EE8;
extern "C" void func_0038CA50(Recovered_KynapseSmallArrayOwner* self, int flags) {
    KynapseSmallArray_Destroy(self, flags, &D_003E8EE8);
}
extern "C" int D_003E90A8;
extern "C" void func_0038CD28(Recovered_KynapseSmallArrayOwner* self, int flags) {
    KynapseSmallArray_Destroy(self, flags, &D_003E90A8);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038CF20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038D0B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038D2D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038D4C0);
/* Partial owner view; its identity and complete extent are UNVERIFIED. */
typedef struct Recovered_KynapseOffsetChildOwner {
    void* table;
    void* unk_04;
    Recovered_KynapseSmallElement* child;
} Recovered_KynapseOffsetChildOwner;

extern "C" int D_003E9C60;
extern "C" void func_0038D8A8(Recovered_KynapseOffsetChildOwner* self, int flags) {
    self->table = &D_003E9C60;
    if (self->child) {
        Recovered_KynapseSmallElement* child = self->child;
        Recovered_KynapseSmallElementTable* table = child->table;
        table->destroy((char*)child + table->adjustment, 3);
    }
    self->table = &D_003E0040;
    if (flags & 1) D_003C87E0(self);
}
extern "C" int D_003E9A80;
extern "C" void func_0038DD80(Recovered_KynapseSmallArrayOwner* self, int flags) {
    KynapseSmallArray_Destroy(self, flags, &D_003E9A80);
}
extern "C" int D_003E9B40;
extern "C" void func_0038DFB8(Recovered_KynapseSmallArrayOwner* self, int flags) {
    KynapseSmallArray_Destroy(self, flags, &D_003E9B40);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038E108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038E438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038E910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_0038EAA0);


INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00390F40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_00391130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/host_2850c0_2f4b50", func_003912C0);
