#include "game/effects/mod_muzzle.hpp"
#include "game/effects/random.hpp"
extern "C" {extern ModEffects::RandomState D_00418590;}
void ModEffects::MuzzleMethods::Start(MuzzleResource *record) {
 if(phase>2) {
  unsigned sample=D_00418590.Next();
  resource=record;
  variant=sample%3;
  if(record->config->quantized) {
   unsigned slots=(unsigned short)(int)(360.0f/record->config->extent);
   unsigned sample2=D_00418590.Next();
   unsigned slot=sample2%slots;
   rotation=(float)slot*resource->config->extent;
  }
  phase=0;
 }
}
