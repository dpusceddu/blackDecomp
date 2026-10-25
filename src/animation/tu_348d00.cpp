#include "include_asm.h"

#include "animation/channel_state.h"
#include "animation/instance.h"
#include "ps2/ee_fpu.h"
// A scoped view adds methods without asserting historical inheritance.
struct AnimationChannelView : AnimationChannelState {
    float FadeWeight(float) __asm__("func_00348D00") __attribute__((section(".text.func_00348D00")));
    static AnimationChannelState* Lookup(AnimationChannelState*, int) __attribute__((section(".text.Lookup__20AnimationChannelViewP21AnimationChannelStatei")));
};
extern "C" f32 func_003527E8(f32);
extern "C" void func_003492E0(AnimationChannelState*);

f32 AnimationChannelView::FadeWeight(f32 fade_out_duration) {
    AnimationChannelState* state=this;
    f32 weight = 0.0f;
    if (state->fade_direction != 0) {
        if (state->fade_direction > 0) {
            weight = BkEeDividePipelineGuardedValue(state->fade_time, state->fade_duration);
            if (weight < 1.0f) weight = func_003527E8(weight * 3.1415927f * 0.5f);
            if (weight >= 1.0f) state->fade_direction = 0;
        } else {
            if (fade_out_duration > 0.0f) {
                weight = 1.0f - state->fade_time / fade_out_duration;
                if (weight > 0.0f) weight = func_003527E8(weight * 3.1415927f * 0.5f);
            }
            if (weight <= 0.0f) func_003492E0(state);
        }
    }
    return weight;
}

AnimationChannelState *AnimationChannelView::Lookup(AnimationChannelState *state, s32 index) {
    s32 position;
    if (state == 0 || index < 0) return 0;
    state = state->next;
    for (position = 0; position < index; ++position) {
        state = state->next;
        if (state == 0) break;
    }
    return state;
}

namespace Fragment348E78 {


s32 func_00348E78(void *arg0) __asm__("func_00348E78") __attribute__((section(".text.func_00348E78")));
s32 func_00348E78(void *arg0) {
    return BkAnimationHasNextPS2((const BkAnimationInstancePS2*)arg0);
}
}

namespace Fragment348E88 {
extern AnimationChannelState *func_00348E30(AnimationChannelState *, s32) __asm__("func_00348E30");
extern void func_00350570(AnimationChannelState *, s32, f32, s32) __asm__("func_00350570");

s32 func_00348E88(f32 time, AnimationChannelState *state, s32 clip, s32 flags, s32 index) __asm__("func_00348E88") __attribute__((section(".text.func_00348E88")));
s32 func_00348E88(f32 time, AnimationChannelState *state, s32 clip, s32 flags, s32 index) {
    s32 result = 0;
    if (clip != -1) {
        func_00350570(func_00348E30(state, index), clip, time, flags);
        result = 1;
        state->flags &= 0xffdfffff;
    }
    state->flags &= 0xedfffffe;
    return result;
}
}

namespace Fragment348F28 {
typedef struct ChannelTransition {
    u8 unknown_000[0x20];
    f32 duration_frames;
    u8 unknown_024[4];
    s32 mode;
} ChannelTransition;
extern AnimationChannelState *func_00348E30(AnimationChannelState *, s32) __asm__("func_00348E30");
extern void func_00350570(AnimationChannelState *, s32, s32, f32) __asm__("func_00350570");
extern ChannelTransition *func_003507C0(AnimationChannelState *, s32) __asm__("func_003507C0");


s32 func_00348F28(f32 time, AnimationChannelState *state, s32 clip, s32 fade, s32 flags, s32 index) __asm__("func_00348F28") __attribute__((section(".text.func_00348F28")));
s32 func_00348F28(f32 time, AnimationChannelState *state, s32 clip, s32 fade, s32 flags, s32 index) {
    s32 result = 0;
    state = func_00348E30(state, index);
    if (state != NULL) {
        if (clip != -1) {
            func_00350570(state, clip, flags, time);
            result = 1;
            state->flags &= ~0x80;
            state->playback_time = -1.0f;
            if (fade != 0) {
                s32 old_direction = state->fade_direction;
                f32 old_time = state->fade_time;
                ChannelTransition *transition;
                state->fade_direction = 1;
                transition = func_003507C0(state, clip);
                if (transition != NULL) {
                    state->fade_duration = transition->duration_frames / 59.94f;
                    state->fade_mode = transition->mode;
                } else {
                    state->fade_mode = 0;
                    state->fade_duration = 0.3f;
                }
                if (clip == state->clip && old_direction < 0) {
                    state->fade_time = state->fade_duration * (1.0f - old_time / 0.3f);
                    if (state->fade_time < 0.0f) state->fade_time = 0.0f;
                } else {
                    state->fade_time = 0.0f;
                }
            }
            state->flags &= 0xffdfffff;
        }
        state->flags &= 0xedfffffe;
    }
    return result;
}
}

namespace Fragment3490A8 {

extern s32 * func_00345F28(s8 *, s32 *, s32 *) __asm__("func_00345F28");
extern s32 func_00348E88(s32 *, s32, s32, s32, f32) __asm__("func_00348E88");


s32 func_003490A8(s32 *arg0, s8 *arg1, s32 arg2) __asm__("func_003490A8") __attribute__((section(".text.func_003490A8")));
s32 func_003490A8(s32 *arg0, s8 *arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 var_18;

    var_18 = 0;
    if ((arg0 != NULL) && (arg1 != NULL)) {
        *(s32 *)(sp + 0) = -1;
        if (func_00345F28(arg1, arg0, (s32*)sp) != NULL) {
            var_18 = func_00348E88(arg0, *(s32 *)(sp + 0), 0, arg2, 0.0f);
        }
    }
    return var_18;
}
}

namespace Fragment349128 {

extern s32 func_00348E88(AnimationChannelState *, s32, s32, s32, f32) __asm__("func_00348E88");
extern s32 func_00348F28(AnimationChannelState *, s32, s32, s32, s32, f32) __asm__("func_00348F28");




s32 func_00349128(AnimationChannelState *state, s32 clip, s32 index) __asm__("func_00349128") __attribute__((section(".text.func_00349128")));
s32 func_00349128(AnimationChannelState *state, s32 clip, s32 index) {
    if (state != NULL) return func_00348E88(state, clip, 0, index, 0.0f);
    return 0;
}
}

namespace Fragment349158 {

extern s32 * func_00345F28(s8 *, s32 *, s32 *) __asm__("func_00345F28");
extern s32 func_00348F28(s32 *, s32, s32, s32, s32, f32) __asm__("func_00348F28");


s32 func_00349158(s32 *arg0, s8 *arg1, s32 arg2, s32 arg3) __asm__("func_00349158") __attribute__((section(".text.func_00349158")));
s32 func_00349158(s32 *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 var_18;

    var_18 = 0;
    if ((arg0 != NULL) && (arg1 != NULL)) {
        *(s32 *)(sp + 0) = -1;
        if (func_00345F28(arg1, arg0, (s32*)sp) != NULL) {
            var_18 = func_00348F28(arg0, *(s32 *)(sp + 0), arg3, 0, arg2, 0.0f);
        }
    }
    return var_18;
}
}

namespace Fragment3491E8 {

extern s32 func_00348E88(AnimationChannelState *, s32, s32, s32, f32) __asm__("func_00348E88");
extern s32 func_00348F28(AnimationChannelState *, s32, s32, s32, s32, f32) __asm__("func_00348F28");




s32 func_003491E8(AnimationChannelState *state, s32 clip, s32 index, s32 unused, s32 flags) __asm__("func_003491E8") __attribute__((section(".text.func_003491E8")));
s32 func_003491E8(AnimationChannelState *state, s32 clip, s32 index, s32 unused, s32 flags) {
    if (state != NULL) return func_00348F28(state, clip, flags, 0, index, 0.0f);
    return 0;
}
}

namespace Fragment349220 {

extern s32 *func_00348E30(...) __asm__("func_00348E30");




s32 func_00349220(void) __asm__("func_00349220") __attribute__((section(".text.func_00349220")));
s32 func_00349220(void) {
    s32 *temp_2;
    s32 var_16;

    var_16 = 0;
    temp_2 = func_00348E30();
    if (M2C_FIELD(temp_2, f32 *, 0x1C) <= 1.0f) {
        var_16 = 1;
    }
    return !(M2C_FIELD(temp_2, s32 *, 0) & 0x02000001) ? var_16 : 1;
}
}

namespace Fragment349278 {

extern s32 *func_00348E30(...) __asm__("func_00348E30");




void func_00349278(s32 *arg0) __asm__("func_00349278") __attribute__((section(".text.func_00349278")));
void func_00349278(s32 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x9A0) = 0;
    M2C_FIELD(arg0, s32 *, 0x99C) = -1;
}
}

namespace Fragment349288 {

extern s32 *func_00348E30(...) __asm__("func_00348E30");
extern s32 func_00349278(...) __asm__("func_00349278");


void func_00349288(void *arg0) __asm__("func_00349288") __attribute__((section(".text.func_00349288")));
void func_00349288(void *arg0)
{
  int var_16;
  void *temp_2;
  var_16 = 0;
 do { loop_1: temp_2 = func_00348E30(arg0, var_16); } while (0);
  if (temp_2 != NULL)
  {
    var_16 += 1;
    func_00349278(temp_2);
    goto loop_1;
  }
}
}

namespace Fragment3492E0 {


void func_003492E0(s32 *arg0) __asm__("func_003492E0") __attribute__((section(".text.func_003492E0")));
void func_003492E0(s32 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x99C) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = -1;
}
}

namespace Fragment3492F0 {

extern s32 *func_00348E30(...) __asm__("func_00348E30");
extern s32 func_003492E0(...) __asm__("func_003492E0");


void func_003492F0(void *arg0) __asm__("func_003492F0") __attribute__((section(".text.func_003492F0")));
void func_003492F0(void *arg0)
{
  int var_16;
  void *temp_2;
  var_16 = 0;
 do { loop_1: temp_2 = func_00348E30(arg0, var_16); } while (0);
  if (temp_2 != NULL)
  {
    var_16 += 1;
    func_003492E0(temp_2);
    goto loop_1;
  }
}
}

namespace Fragment349348 {

extern s32 *func_00348E30(...) __asm__("func_00348E30");
extern void func_00349278(s32 *arg0) __asm__("func_00349278");






s32 func_00349348(void) __asm__("func_00349348") __attribute__((section(".text.func_00349348")));
s32 func_00349348(void) {
    s32 *temp_2;
    s32 var_16;

    var_16 = -1;
    temp_2 = func_00348E30();
    if (temp_2 != NULL) {
        var_16 = M2C_FIELD(temp_2, s32 *, 0x10);
    }
    return var_16;
}
}

namespace Fragment349378 {

extern s32 *func_00348E30(...) __asm__("func_00348E30");
extern void func_00349278(s32 *arg0) __asm__("func_00349278");






void func_00349378(void) __asm__("func_00349378") __attribute__((section(".text.func_00349378")));
void func_00349378(void) {
    s32 *temp_2;

    temp_2 = func_00348E30();
    if (temp_2 != NULL) {
        func_00349278(temp_2);
    }
}
}

namespace Fragment3493A8 {

extern s32 *func_00348E30(...) __asm__("func_00348E30");
extern void func_00349278(s32 *arg0) __asm__("func_00349278");






s32 func_003493A8(void) __asm__("func_003493A8") __attribute__((section(".text.func_003493A8")));
s32 func_003493A8(void) {
    s32 *temp_2;
    s32 var_16;

    var_16 = 0;
    temp_2 = func_00348E30();
    if (temp_2 != NULL) {
        var_16 = 1;
        *temp_2 |= 0x10000000;
    }
    return var_16;
}
}
