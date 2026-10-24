#ifndef BLACK_MOD_EFFECTS_RANDOM_METHODS_HPP
#define BLACK_MOD_EFFECTS_RANDOM_METHODS_HPP
#include "game/effects/random_state.h"
namespace ModEffects {
// PS2-verified two-word state and source-shaped inline methods. Original name unknown.
class RandomState {
public:
 unsigned state, accumulator;
 inline unsigned Next() {
  state=(state<<16)+((int)state>>16)+accumulator;
  accumulator+=state;
  return state;
 }
 inline float Fraction() {return (float)Next()*2.3283064365386963e-10f;}
};
}
#endif
