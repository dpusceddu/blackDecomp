#include "include_asm.h"
#include "ps2/prelude.h"
#include "animation/expression.h"

extern f32 func_00348A38(s32, void*);
extern f32 (*D_003D5060[])(PS2AnimationExpression*, void*);

/* Logical expressions return 0 or 1 as a float. All rejects only zero;
 * Any and Parity accept exactly 1, preserving the native scalar semantics. */
f32 AnimationExpression_All(PS2AnimationExpression* expression, void* context) {
    s32 i;
    s32 count = expression->childCount;
    for (i = 0; i < count; i++) {
        if (AnimationExpression_Evaluate(expression->children[i], context) == 0.0f) return 0.0f;
    }
    return 1.0f;
}

f32 AnimationExpression_Any(PS2AnimationExpression* expression, void* context) {
    s32 i;
    s32 count = expression->childCount;
    for (i = 0; i < count; i++) {
        if (AnimationExpression_Evaluate(expression->children[i], context) == 1.0f) return 1.0f;
    }
    return 0.0f;
}

f32 AnimationExpression_Parity(PS2AnimationExpression* expression, void* context) {
    s32 i;
    s32 parity = 0;
    s32 count = expression->childCount;
    for (i = 0; i < count; i++) {
        if (AnimationExpression_Evaluate(expression->children[i], context) == 1.0f) parity ^= 1;
    }
    return (f32)parity;
}

f32 AnimationExpression_Not(PS2AnimationExpression* expression, void* context) {
    f32 result;
    if (AnimationExpression_Evaluate(expression->children[0], context) != 0.0f) return 0.0f;
    result = 1.0f;
    return result;
}

f32 AnimationExpression_Equal(PS2AnimationExpression* expression, void* context) {
    f32 first = AnimationExpression_Evaluate(expression->children[0], context);
    f32 second = AnimationExpression_Evaluate(expression->children[1], context);
    f32 result = 1.0f;
    if (!(first == second)) result = 0.0f;
    return result;
}

f32 AnimationExpression_NotEqual(PS2AnimationExpression* expression, void* context) {
    f32 first = AnimationExpression_Evaluate(expression->children[0], context);
    f32 second = AnimationExpression_Evaluate(expression->children[1], context);
    f32 result = 1.0f;
    if (!(first != second)) result = 0.0f;
    return result;
}

f32 AnimationExpression_Greater(PS2AnimationExpression* expression, void* context) {
    f32 first = AnimationExpression_Evaluate(expression->children[0], context);
    f32 second = AnimationExpression_Evaluate(expression->children[1], context);
    f32 result = 1.0f;
    if (!(first > second)) result = 0.0f;
    return result;
}

f32 AnimationExpression_Less(PS2AnimationExpression* expression, void* context) {
    f32 first = AnimationExpression_Evaluate(expression->children[0], context);
    f32 second = AnimationExpression_Evaluate(expression->children[1], context);
    f32 result = 1.0f;
    if (!(first < second)) result = 0.0f;
    return result;
}

f32 AnimationExpression_GreaterEqual(PS2AnimationExpression* expression, void* context) {
    f32 first = AnimationExpression_Evaluate(expression->children[0], context);
    f32 second = AnimationExpression_Evaluate(expression->children[1], context);
    f32 result = 1.0f;
    if (!(first >= second)) result = 0.0f;
    return result;
}

f32 AnimationExpression_LessEqual(PS2AnimationExpression* expression, void* context) {
    f32 first = AnimationExpression_Evaluate(expression->children[0], context);
    f32 second = AnimationExpression_Evaluate(expression->children[1], context);
    f32 result = 1.0f;
    if (!(first <= second)) result = 0.0f;
    return result;
}

f32 AnimationExpression_Event(PS2AnimationExpression* expression, void* context) {
    return func_00348A38(expression->event, context);
}

f32 AnimationExpression_Constant(PS2AnimationExpression* expression, void* context) { return expression->value; }

f32 AnimationExpression_Evaluate(PS2AnimationExpression* expression, void* context) {
    if (expression->kind < 12) { return D_003D5060[expression->kind](expression, context); }
    return 0.0f;
}
