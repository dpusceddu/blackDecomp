#ifndef ANIMATION_EXPRESSION_H
#define ANIMATION_EXPRESSION_H
#include "ps2/recovered_types.h"

/* Scalar expression operators preserve native float comparisons. Child counts
 * are signed bytes; opcode values outside the 12-entry table evaluate to zero. */
f32 AnimationExpression_All(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Any(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Parity(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Not(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Equal(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_NotEqual(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Greater(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Less(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_GreaterEqual(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_LessEqual(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Event(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Constant(PS2AnimationExpression* expression, void* context);
f32 AnimationExpression_Evaluate(PS2AnimationExpression* expression, void* context);

#endif
