#include "rw_audio/emitter.h"

#include "ps2/prototypes.h"

#include "rw_audio/io_cache.h"
AudioIoCache D_00456480 __attribute__((section(".bss")));

void func_00319928(void)
{
 D_00456480.position=0xffffffffu;
 D_00456480.owner=NULL;
 D_00456480.file=0;
 D_00456480.bytes=0;
}
