#include "game/effects/runtime.hpp"
extern "C" {void func_001B1110(void *,void *);int func_001B1138(void *);void func_001B1648(void *,void *);}
int ModEffects::Entry::Release(){for(unsigned short i=0;i<8;++i){Child *child=children[i];if(child){if(child!=(Child*)1)func_001B1110(child,this);children[i]=0;}}resource=0;return 1;}
