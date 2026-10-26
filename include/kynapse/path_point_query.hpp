#ifndef KYNAPSE_PATH_POINT_QUERY_HPP
#define KYNAPSE_PATH_POINT_QUERY_HPP

/* Accessed prefixes only; object roles and remaining fields are UNVERIFIED. */
struct Recovered_KynapsePathVector {
    float x, y, z;
    Recovered_KynapsePathVector(float a, float b, float c) : x(a), y(b), z(c) {}
    float SquaredLength() const { return x * x + y * y + z * z; }
};
struct Recovered_KynapsePositionOwner {
    char unk_00[0x30];
    Recovered_KynapsePathVector position;
};
struct Recovered_KynapseDistanceWorld {
    char unk_00[12];
    float distanceLimitSquared;
};

#endif
