#ifndef KYNAPSE_BYTE_MATRIX_H
#define KYNAPSE_BYTE_MATRIX_H

/* Partial view; the first eight bytes and the matrix's broader role are UNVERIFIED. */
typedef struct Recovered_KynapseByteMatrix {
    char unk_00[8];
    unsigned char* values;
    int row_stride;
    float divisor;
} Recovered_KynapseByteMatrix;

#endif
