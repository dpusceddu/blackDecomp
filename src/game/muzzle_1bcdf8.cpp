#include "game/effects/mod_muzzle.hpp"
#include "game/effects/mod_random.hpp"
extern "C" {extern ModEffects::RandomState D_00418590;}
void ModEffects::MuzzleMethods::Advance() {
 if(phase<3) {
  if(!resource->config->quantized) {
   rotation=resource->config->extent*D_00418590.Fraction();
   if(D_00418590.Fraction()<0.5f)rotation=-rotation;
  }
  ++phase;
 }
}
