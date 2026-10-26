#ifndef GAME_AI_POINT_HISTORY_H
#define GAME_AI_POINT_HISTORY_H
#include "ps2/prelude.h"

/* Three retained full-quad point samples and their last update time. The exact
 * initializer confirms these fields; the complete component extent is unknown. */
typedef struct {
    s128 samples[3];
    f32 lastSampleTime;
} Recovered_PointHistory;

typedef char PointHistoryTimeOffset[(u32)&((Recovered_PointHistory*)0)->lastSampleTime == 0x30 ? 1 : -1];
#endif
