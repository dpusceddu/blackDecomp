#include "include_asm.h"

#include "game/frontend/movie_stream.hpp"
extern "C" int func_00109308(void*,int,unsigned,const char*,int,void*,int,unsigned,unsigned);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109308);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001093B0);

int FrontendStreamScheduler::Schedule(const char* name,int index,int kind,int callback,void* data,unsigned callbackFlags,unsigned flags) {
    return func_00109308(this,index,flags==0x02000000?1u:2u,name,callback,data,kind,callbackFlags,flags);
}

#include "ps2/prelude.h"
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


#ifdef NON_MATCHING
// Unmatched: timer address construction, unsigned conversion and state scheduling.
#include "ps2/prelude.h"
#include "game/frontend/movie_stream.hpp"
#include "ps2/recovered_types.h"

extern "C" u8 func_00272308(void *);
extern "C" void func_001094C0(void *,const char*,s32,s32);
extern "C" s32 func_00109CF8(void *);
extern "C" s32 func_00109BB0(void *);
extern "C" s32 func_00109588(void *);
extern "C" s32 D_003BD1F0;
extern "C" s32 func_002722C8(void *, f32);
extern "C" char* D_0040F0E0;
extern "C" s32 func_00271F10(void *);

void FrontendMovieState::Update() {
    f32 var_f0;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_7;
    u32 var_2;

    temp_2 = state;
    var_2 = temp_2 - 0x1D;
    if (temp_2 == 0x1C) {
        if (stopRequested == 0) {
            if (func_00272308(decoder) != 0) {
                temp_7 = flags;
                if (temp_7 & 1) {
                    func_001094C0(this, name, fade, temp_7);
                } else {
                    goto block_6;
                }
            }
        } else {
block_6:
            stopRequested = 0U;
            state = 0x1D;
        }
        var_2 = state - 0x1D;
    }
    if (var_2 < 0x1AU) {
        func_00109CF8(this);
    }
    temp_3 = state;
    if (((temp_3 == 0x37) || (temp_3 == 1)) && (requested != 0)) {
        temp_3_2 = pendingFade;
        state = 2;
        requested = 0U;
        fade = temp_3_2;
        pendingFade = 0;
        if (temp_3_2 != 0) {
            flags = (s32) (flags | 2);
        }
    }
    if ((u32) (state - 2) < 0x1AU) {
        func_00109BB0(this);
    }
    if (state == 0x1C) {
        if (!(flags & 0x100)) {
            if (active == 0) {
                func_00109588(this);
                startedAt = (s32) D_003BD1F0;
                goto block_21;
            }
            goto block_22;
        }
block_21:
        if (active != 0) {
block_22:
            if (fade != 0) {
                var_f0 = (f32)((u32)D_003BD1F0-startedAt);
                func_002722C8(decoder, var_f0 * (M2C_FIELD((D_0040F0E0 + 0x20120), f32 *, 0x1C) * 0.5f));
            }
            func_00271F10(decoder);
        }
    }
}
#endif


#ifdef NON_MATCHING
// Unmatched: busy boolean normalization, fallthrough scheduling and saved-register allocation.
#include "game/frontend/movie_stream.hpp"
extern "C" FrontendStreamRequest* D_0040F4C4;
extern "C" int func_0035D728(char*,const char*,...);
extern "C" void func_00109E78(void*,FrontendStreamImage**);
extern "C" int func_001093C0(void*,const char*,int,int,void (*)(void*,FrontendStreamImage**),void*,unsigned char,int);
int FrontendMovieState::Prepare(void* decoderObject,void* renderTarget) {
    char path[64];
    switch(phase) {
    case 1:
        phase=55;
    case 55:
        firstStream=1;
        streamIndex=1;
        phase=2;
        streams[0].name=0;
    case 2:
        if(D_0040F4C4[8].busy || D_0040F4C4[8].loading) return 0;
        func_0035D728(path,"sound\\streams\\%s.ssh",streams[streamIndex].name);
        streams[streamIndex].data=0;
        func_001093C0(D_0040F4C4,path,8,9,func_00109E78,&streams[streamIndex].data,firstStream,0x02000000);
        firstStream=0;
        phase=3;
    case 3:
        if(!streams[streamIndex].data) return 0;
        ++streamIndex;
        if(streamIndex<18) {phase=2;return 0;}
        phase=28;
    case 28:
        decoder=decoderObject;
        target=renderTarget;
        state=1;
        stopRequested=0;
        requested=0;
        return 1;
    }
    return 0;
}
#endif

