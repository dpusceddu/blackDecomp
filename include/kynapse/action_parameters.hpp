#ifndef BLACK_KYNAPSE_ACTION_PARAMETERS_HPP
#define BLACK_KYNAPSE_ACTION_PARAMETERS_HPP

#include "kynapse/parameter_assign.hpp"

// Partial action-assignment views; authored values share a changed flag.
// UNVERIFIED: complete interfaces, uncalled slots, scalar units, and request conventions.
struct AuthoredActionParameter : ParameterRoot {
    unsigned char changed;
};

struct AccelerationAction : AuthoredActionParameter {
    float acceleration;
    void SetAcceleration(float value) { acceleration = value; changed = true; }
    AccelerationAction& operator=(const ParameterRoot&) __asm__("func_002D7A38");
};

struct CrouchAction : AuthoredActionParameter {
    unsigned char requested;
    void SetRequested(unsigned char value) { requested = value; changed = true; }
    CrouchAction& operator=(const ParameterRoot&) __asm__("func_002D7BC0");
};

struct JumpAction : AuthoredActionParameter {
    unsigned char requested;
    void SetRequested(unsigned char value) { requested = value; changed = true; }
    JumpAction& operator=(const ParameterRoot&) __asm__("func_002D7D48");
};

struct RotateAction : AuthoredActionParameter {
    float rotation;
    void SetRotation(float value) { rotation = value; changed = true; }
    RotateAction& operator=(const ParameterRoot&) __asm__("func_002D7ED0");
};

struct SteeringAction : AuthoredActionParameter {
    float steering;
    void SetSteering(float value) { steering = value; changed = true; }
    SteeringAction& operator=(const ParameterRoot&) __asm__("func_002D8388");
};

struct ActivateAction : AuthoredActionParameter {
    unsigned char requested;
    void SetRequested(unsigned char value) { requested = value; changed = true; }
    ActivateAction& operator=(const ParameterRoot&) __asm__("func_002D9C60");
};

struct TorsoRotateAction : AuthoredActionParameter {
    // UNVERIFIED: which controls the two rotation values represent.
    float primary, secondary;
    void SetPrimary(float value) { primary = value; changed = true; }
    void SetSecondary(float value) { secondary = value; changed = true; }
    TorsoRotateAction& operator=(const ParameterRoot&) __asm__("func_002D9F78");
};

struct VerticalSpeedAction : AuthoredActionParameter {
    float speed;
    void SetSpeed(float value) { speed = value; changed = true; }
    VerticalSpeedAction& operator=(const ParameterRoot&) __asm__("func_002DA108");
};

#endif
