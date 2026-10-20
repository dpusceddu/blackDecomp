#ifndef BLACK_CAMPAIGN_SOUND_ENVELOPES_HPP
#define BLACK_CAMPAIGN_SOUND_ENVELOPES_HPP
#include "campaign/graphics/timed_envelope.hpp"
namespace CampaignGraphics {
// Access layouts are shared with the matched Tinnitus methods. These names
// describe behavior and strings; original class identities remain unverified.
struct SoundEnvelope : EnvelopeInterface {
    void Register(const char *name, int includeHold);
    int ActivateChannels();
    void Release();
};
struct DestructionEnvelope : SoundEnvelope {
    int Begin(float value, unsigned useEndpoint);
    void Update();
    int Unregister();
};
struct LowHealthEnvelope : SoundEnvelope {
    void Reset();
    int Begin(float value, unsigned useEndpoint);
    void Update();
    float Blend() const { return blend; }
};
}
extern "C" {
extern unsigned char *D_0040F510, *D_0040F4D0, *D_003C09E8;
extern const char *D_003BDA08, *D_003BDA14, *D_003BDA18;
extern const char D_003F8A88[], D_003F8A98[], D_003F8AA8[], D_003F8AB8[];
extern const char D_003F8AC0[], D_003F8AD0[], D_003F8AE0[];
void func_001E1690(void *, unsigned, int);
void func_001E2C68(void *, unsigned, int);
void func_001D7198(void *, unsigned, int);
void func_001DC498(void *, unsigned, int);
void func_001EC9F0(void *, unsigned, int);
void func_001E4260(void *, unsigned, int);
void func_001E6208(void *, unsigned, int);
void func_0027B950(float,float,void *,void *,const char *,const char *,const char *,int,int);
// This source parameter order is verified by the envelope registration caller.
// The zero-valued control widths and original API spelling remain unverified.
void RegisterEnvelopeParameter(void *,void *,const char *,const char *,const char *,int,float,float,int)
    __asm__("func_0027B950");
void func_001ED9C8(void *,const char *,int);
int func_001EDB80(void *);
// Scoped caller view: Begin preserves its FP/selector arguments; the matched
// callee itself ignores them. This does not establish semantic parameters.
int ActivateEnvelopeWithArguments(void *,float,unsigned) __asm__("func_001EDB80");
void func_001EFE70(void *,int);
void func_001EDDB8(void *);
float func_0029E688(float,float);
void func_00286120(float,float,void *);
void func_001D7238(float,float,float,void *);
void func_001D7258(float,void *);
void func_002860D0(float,void *);
}
namespace CampaignGraphics {
static inline void **SoundObjects() { return *(void ***)(D_0040F510+0xcbd8); }
static inline void *SoundFilter() { return *(void **)(D_0040F510+0xcbe0); }
static inline float SoundClock() { return *(float *)(D_0040F4D0+0x20); }
}
#endif
