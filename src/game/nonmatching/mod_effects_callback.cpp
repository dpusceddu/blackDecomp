// Unmatched: VU operator load order and seven remaining allocation differences.
#ifdef NONMATCHING
// Layouts are accessed prefixes, not assertions about the original class names.
#include "mod/effects/vu_math.h"
namespace EffectCallbackProposal {
typedef s128 Value;
struct Matrix { Value row[4]; };
struct Pair { Value first,second; };
struct Actor {
    unsigned char unknown00[0x70];
    Matrix world;
    unsigned char unknownb0[0x14];
    int kind;
};
struct Hit {
    Value position;
    unsigned char unknown10[0x14];
    Actor* actor;
    unsigned char unknown28[4];
    unsigned char bone;
};
extern const Pair* BonePair(Actor*,unsigned char) __asm__("func_00148498");
extern const Matrix* BoneMatrix(Actor*,unsigned char) __asm__("func_00147988");
extern const Pair* DefaultPair(Actor*) __asm__("func_001528B8");
extern void* gRecipient __asm__("D_0040F4D4");
extern void Notify(void*,Value,void*) __asm__("func_0016E250");
class Callback {
public:
    void Emit(const Hit*,void*) __asm__("func_001BC428");
    // The two floats occupy F12/F13 independently of the four GPR arguments.
    void Spawn(Value,Value,int,float,float) __asm__("func_001BC548");
};
static inline Value Transform(const Matrix* m,Value direction)
{
    Value result;
    asm("vmulax.xyz ACC, matrixx, dirvx\n\t"
        "vmadday.xyz ACC, matrixy, dirvy\n\t"
        "vmaddaz.xyz ACC, matrixz, dirvz\n\t"
        "vmaddw.xyz answer, basevec, vf0w"
        : "=j answer"(result)
        : "j matrixy"(m->row[1]),"j matrixx"(m->row[0]),
          "j matrixz"(m->row[2]),"j basevec"(m->row[3]),"j dirv"(direction));
    return result;
}
void Callback::Emit(const Hit* hit,void* context)
{
    Actor* actor=hit->actor;
    if(actor && (unsigned)(actor->kind-3)<2) {
        Value position=hit->position;
        const Pair* pair;
        const Matrix* world;
        if(actor->kind==4) {
            pair=BonePair(actor,hit->bone);
            world=BoneMatrix(hit->actor,hit->bone);
        } else {
            pair=DefaultPair(actor);
            world=&hit->actor->world;
        }
        Value direction=BkEffectSubPS2(pair->first,pair->second);
        Value displaced=Transform(world,direction);
        displaced=BkEffectSubPS2(displaced,world->row[3]);
        Value scaled=BkEffectScalePS2(displaced,0.5f);
        Spawn(position,scaled,4,1.5f,1.0f);
        Notify(gRecipient,position,context);
    }
}
}
#endif
