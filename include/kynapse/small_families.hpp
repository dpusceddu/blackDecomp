// Declarations of the Kynapse source module "small_families" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_SMALL_FAMILIES_HPP
#define BLACK_KYNAPSE_MODULE_SMALL_FAMILIES_HPP
#include "kynapse/compat.hpp"

// Small table, search and list routines that appear in several near-identical copies.
#include "kynapse/kynapse.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);

// Parameter tables addressed by index; counts and arrays live at fixed offsets.
struct ParameterTables {
    unsigned char unknown00[4];
    unsigned int countA;
    unsigned int countB;
    unsigned int countC;
    unsigned char unknown10[0x10];
    float* floatsC;
    int* intsB;
    float* floatsB;
    float* floatsA;
    float* floatsC2;

    void SetFloatB(int index, float value);
    void SetFloatC(int index, float value);
    void SetIntB(int index, int value);
    void SetFloatA(int index, float value);
    void SetFloatC2(int index, float value);
};







// Name tables searched case-insensitively.
#define KAIM_NAME_TABLE(Type, CountOffset, NamesOffset)                    \
    struct Type {                                                          \
        unsigned char padding[CountOffset];                                \
        unsigned int count;                                                \
        unsigned char gap[NamesOffset - CountOffset - 4];                  \
        const char** names;                                                \
        int FindName(const char* name) const;                              \
    };                                                                     \
    int Type::FindName(const char* name) const                             \
    {                                                                      \
        for (unsigned int i = 0; i < count; ++i) {                         \
            if (_stricmp(name, names[i]) == 0)                             \
                return i;                                                  \
        }                                                                  \
        return -1;                                                         \
    }

KAIM_NAME_TABLE(NameTable8, 8, 0x14)    
KAIM_NAME_TABLE(NameTable4, 4, 0x10)    
KAIM_NAME_TABLE(NameTableC, 0xc, 0x18)  



float Degrees_WrapSigned(float degrees);



// Wraps an angle in degrees into [0, 360].
float Degrees_WrapUnsigned(float degrees);


namespace Kaim {
struct ListPayload24 { unsigned char bytes[0x24]; };
struct ListPayload18 { unsigned char bytes[0x18]; };
template struct List<ListPayload24>;  // Clear at 0x64070
template struct List<ListPayload18>;  // Clear at 0x672b0
}  // namespace Kaim

#endif
