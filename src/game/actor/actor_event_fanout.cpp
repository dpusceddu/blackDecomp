#include "include_asm.h"

#include "game/actor/event_fanout.hpp"
namespace BlackPS2Campaign {

void ActorFanout3::Dispatch(int event) {
    if (count) {
        for (int i=0; i<count; ++i) {
            EventItem3 *item=items[i];
            if (item) {
                char *table=item->table;
                (*(void (**)(void *,int))(table+0x1c))((char *)item+*(short *)(table+0x18),event);
            }
        }
    }
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00165B98);
