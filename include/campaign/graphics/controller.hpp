#ifndef CAMPAIGN_GRAPHICS_CONTROLLER_HPP
#define CAMPAIGN_GRAPHICS_CONTROLLER_HPP
#include "ps2/ee_types.h"
// Partial PS2 controller view; complete class identity and allocation size remain unverified.
namespace CampaignGraphics { struct ControllerBase {virtual void Release();}; struct Controller : ControllerBase {

    EeS32 field_4; /* PS2 +0x4 */
    EeU8 opaque_8[4];
    EeU8 connected; /* PS2 +0xC */
    EeU8 initialized; /* PS2 +0xD */
    EeU8 previousStates[28];
    EeU8 button0; /* PS2 +0x2A */
    EeU8 button1; /* PS2 +0x2B */
    EeU8 button2; /* PS2 +0x2C */
    EeU8 button3; /* PS2 +0x2D */
    EeU8 button4; /* PS2 +0x2E */
    EeU8 button5; /* PS2 +0x2F */
    EeU8 button6; /* PS2 +0x30 */
    EeU8 button7; /* PS2 +0x31 */
    EeU8 opaque_32[20];
    EeU8 field_46; /* PS2 +0x46 */
    EeU8 field_47; /* PS2 +0x47 */
    EeU8 field_48; /* PS2 +0x48 */
    EeU8 field_49; /* PS2 +0x49 */
    EeU8 field_4A; /* PS2 +0x4A */
    EeU8 opaque_4B[1];
    float pressure0; /* PS2 +0x4C */
    float pressure1; /* PS2 +0x50 */
    float pressure2; /* PS2 +0x54 */
    float pressure3; /* PS2 +0x58 */
    float pressure4; /* PS2 +0x5C */
    float pressure5; /* PS2 +0x60 */
    float pressure6; /* PS2 +0x64 */
    float pressure7; /* PS2 +0x68 */
    float pressure8; /* PS2 +0x6C */
    float pressure9; /* PS2 +0x70 */
    EeU8 opaque_74[16];
    float pressure14; /* PS2 +0x84 */
    float pressure15; /* PS2 +0x88 */
    float axis1Positive; /* PS2 +0x8C */
    float axis1Negative; /* PS2 +0x90 */
    float axis0Negative; /* PS2 +0x94 */
    float axis0Positive; /* PS2 +0x98 */
    float axis3Positive; /* PS2 +0x9C */
    float axis3Negative; /* PS2 +0xA0 */
    float axis2Negative; /* PS2 +0xA4 */
    float axis2Positive; /* PS2 +0xA8 */
    float rawAxis0; /* PS2 +0xAC */
    float rawAxis1; /* PS2 +0xB0 */
    float rawAxis2; /* PS2 +0xB4 */
    float rawAxis3; /* PS2 +0xB8 */
    float maxStep1; /* PS2 +0xBC */
    float maxStep0; /* PS2 +0xC0 */
    float maxStep3; /* PS2 +0xC4 */
    float maxStep2; /* PS2 +0xC8 */
    float pressureThreshold; /* PS2 +0xCC */
    EeU8 opaque_D0[24];
    EeS32 backend; /* PS2 +0xE8 */
    EeS32 port; /* PS2 +0xEC */
inline bool Connected() const {return connected!=0;}
bool Open(unsigned int backendHandle, unsigned int portIndex);
void Update();void UpdateMotors();};}
typedef char check_field_C[(((int)&((CampaignGraphics::Controller*)0)->connected)==12)?1:-1];
typedef char check_opaque_E[(((int)&((CampaignGraphics::Controller*)0)->previousStates)==14)?1:-1];
typedef char check_field_2A[(((int)&((CampaignGraphics::Controller*)0)->button0)==42)?1:-1];
typedef char check_field_4C[(((int)&((CampaignGraphics::Controller*)0)->pressure0)==76)?1:-1];
typedef char check_field_E8[(((int)&((CampaignGraphics::Controller*)0)->backend)==232)?1:-1];

#endif
