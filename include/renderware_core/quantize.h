#ifndef RENDERWARE_CORE_QUANTIZE_H
#define RENDERWARE_CORE_QUANTIZE_H
/* Inferred image-quantization records; offsets are verified against PS2 accesses. */
typedef unsigned char QuantByte;
typedef struct QuantRGBA { QuantByte r, g, b, a; } QuantRGBA;
typedef struct QuantVector { float r, g, b, a; } QuantVector;
typedef struct QuantMoments { float weight; QuantVector sum; float error; QuantByte index; } QuantMoments;
typedef struct QuantNode { QuantMoments moments; struct QuantNode *child[16]; } QuantNode;
typedef struct QuantPosition { int c[4]; } QuantPosition;
typedef struct QuantBox { int low[4], high[4]; } QuantBox;
typedef char quant_node_children_offset[(int)&((QuantNode *)0)->child==28 ? 1 : -1];
#endif
