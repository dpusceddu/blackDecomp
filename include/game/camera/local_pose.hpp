#ifndef BLACK_MOD_CAMERA_LOCAL_POSE_HPP
#define BLACK_MOD_CAMERA_LOCAL_POSE_HPP
#include "game/camera/motion.hpp"
namespace Camera {
/* Partial animation access chain used by the local-pose consumer.
   Names are descriptive; the complete animation class identity is unknown. */
struct LocalPoseDefinition { unsigned char unknown00[0x34]; int rootIndex; };
struct LocalPoseAnimation { unsigned char unknown00[0x50]; LocalPoseDefinition *definition; };
/* Subtract a scalar from Y, preserving X/Z/W. Explicit scalar transfer avoids
   a full signed128 conversion; the read/write operand retains untouched lanes. */
inline Game::Vec LowerY(Game::Vec value,int bits) {
 Game::Vec amount,delta;
 asm("qmtc2.ni srcr, dstv" : "=j dstv"(amount) : "r srcr"(bits));
 asm("vsubx.y dstv, srcv, argvx" : "=j dstv"(delta) : "j srcv"(value), "j argv"(amount));
 asm("vaddy.y dstv, vf0, srcvy" : "+j dstv"(value) : "j srcv"(delta));
 return value;
}
}
#endif
