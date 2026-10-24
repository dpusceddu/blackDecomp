/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_TABLEVIEW_H
#define RECOVERED_TABLEVIEW_H
#include "ps2/prelude.h"

typedef struct Recovered_TableView {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
} Recovered_TableView;
typedef char assert_Recovered_TableView_4[(((int)&((Recovered_TableView *)0)->field_4) == 4) ? 1 : -1];
#endif
