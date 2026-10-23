#include "campaign/actor/camera.hpp"
#include "ps2/matrix.hpp"

// Unmatched: 0x141008 VU normalization copies and scalar/temporary scheduling.
// Unmatched: 0x140E48 scalar-to-VU scratch-register allocation (two operands).
// Unmatched: 0x140EA8 vector-component accessor lifetime and virtual matrix return.
// Unmatched: 0x141308 queued child-selection loop and success-return control flow.
// Unmatched: 0x141460 small-data byte access and duplicate boolean constant lifetimes.
// Unmatched: 0x1414A0 component-spill reuse and narrow-predicate control flow.
