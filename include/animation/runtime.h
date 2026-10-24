#ifndef BLACK_MOD_ANIMATION_RUNTIME_H
#define BLACK_MOD_ANIMATION_RUNTIME_H
#include "animation/instance.h"
#include "animation/sampling.h"
#ifdef __cplusplus
#include "animation/instance_state.h"
#endif
#include "animation/playback_state.h"
#include "animation/graph_runtime.h"
/* Existing exact-backed graph/playback helpers retain their own types, mixed
   parameter order and compiler recipes. This entry point does not assert that
   all historical semantic views are interchangeable C++ classes. owner+84 is
   instruction evidence only; original inline matrix/pose operators remain open. */
#endif
