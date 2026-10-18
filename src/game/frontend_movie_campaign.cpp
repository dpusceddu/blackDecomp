#include "game/frontend/movie_stream.hpp"
extern "C" int func_00109308(void*,int,unsigned,const char*,int,void*,int,unsigned,unsigned);
int FrontendStreamScheduler::Schedule(const char* name,int index,int kind,int callback,void* data,unsigned callbackFlags,unsigned flags) {
    return func_00109308(this,index,flags==0x02000000?1u:2u,name,callback,data,kind,callbackFlags,flags);
}

#include "auto/prelude.h"
#include "game/frontend/movie_stream.hpp"

extern "C" s32 func_00109BB0(void *);
extern "C" s32 func_00109550(void *);
extern "C" s32 func_00109578(void *);
extern "C" s32 func_00109CF8(void *);
int FrontendMovieState::Stop()
{
  s32 temp_3;
  s32 var_2=0;
  temp_3 = phase;
  switch (temp_3)
  {
    case 28:
      if ((((u32) ((state) - 2)) >= 0x1AU) || ((var_2 = 0, func_00109BB0(this) != 0)))
    {
      func_00109550(this);
      stopRequested = 0;
      if (func_00109578(this) != 0)
      {
        state = 0x1D;
      }
      phase = 0x1D;
      case 29:
        var_2=0x37;
        if (func_00109CF8(this) == 0)
      {
        return 0;
      }

      phase = var_2;
      var_2 = 1;
      return var_2;
    }
      return var_2;

    default:
      return 1;

  }

}

#include "game/frontend/movie_stream.hpp"
extern "C" int func_00109F68(void*,int);
extern "C" unsigned D_0040EAE4;
int FrontendStreamScheduler::ErrorCode(int kind) {
    if(func_00109F68(this,kind)==0) {
        switch(D_0040EAE4) {
        case 0:return 5;
        case 1:return 6;
        case 2:return 3;
        case 3:return 1;
        case 5:return 4;
        case 6:return 2;
        case 4:case 7:case 8:case 9:case 10:case 11:case 12:case 13:
        default:return 0;
        }
    }
    return 0;
}
