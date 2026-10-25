#include "include_asm.h"

#include "kynapse/agents/goto.hpp"
namespace KaimGoto {

extern "C" GotoAgent* func_002D38C8(ClassRegistry* context){return new GotoAgent(context);}
int GotoAgent::Init(ChildBuffers* config){
 if(!ConfigureAll(config))return 0;
 target=context->FindByClass(&targetClass);destination=origin;active=false;field14=0;
 return Prepare()?true:false;
}
void GotoAgent::Stop(){target->Stop();}
// Unmatched: Update (160 B) retains twelve branch-layout differences after PS2 virtual-slot correction.
// Unmatched: SetDestination (120 B) retains seven temporary-register differences.
}

