// Declarations of the Kynapse source module "parameter_assign" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_PARAMETER_ASSIGN_HPP
#define BLACK_KYNAPSE_MODULE_PARAMETER_ASSIGN_HPP
#include "kynapse/compat.hpp"

// Assignment operators of Kynapse parameter objects. A parameter copies its fields only from an
// object of the same runtime class (compared through the class-info getter in vtable slot 2);
// setters that mark the parameter as authored write a changed flag at 0x04.

struct ParameterRoot {
    virtual ~ParameterRoot();
    virtual void Slot1();
    virtual const void* GetClassInfo() const;
};

struct Triple {
    int a, b, c;
    Triple& operator=(const Triple& o) { a = o.a; b = o.b; c = o.c; return *this; }
};

#define PARAMETER_CLASS(Name) \
    struct Name : ParameterRoot { \
        Name& operator=(const ParameterRoot& other);

PARAMETER_CLASS(ParamInts3)
    int a;
    int b;
    int c;
};

PARAMETER_CLASS(ParamInt)
    int a;
};

PARAMETER_CLASS(ParamFlag)
    bool a;
};

PARAMETER_CLASS(ParamChangedMixed)
    bool changed;
    Triple triple;
    char d;
    void SetTriple(const Triple& value);

    void SetD(char v);

};

PARAMETER_CLASS(ParamChangedInt)
    bool changed;
    // Provisional class name; the matching PS2 operator copies a float payload.
    float a;
    void SetA(float v) { a = v; changed = true; }

};

PARAMETER_CLASS(ParamClamped)
    float a;
    float b;
    void SetA(float v);

    void SetB(float v);

};

PARAMETER_CLASS(ParamClampedOne)
    float a;
    void SetA(float v);

};

PARAMETER_CLASS(ParamChangedByte)
    bool changed;
    unsigned char unknown05[3];
    char a;
    void SetA(char v);

};

PARAMETER_CLASS(ParamChangedPair)
    bool changed;
    float a;
    float b;
    void SetA(float v) { a = v; changed = true; }

    void SetB(float v) { b = v; changed = true; }

};




























#endif
