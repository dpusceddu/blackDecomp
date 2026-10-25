#include "include_asm.h"

#include "kynapse/point_mapper.hpp"
#ifdef NON_MATCHING
#include "kynapse/classes/Kaim_CPointMapper.hpp"
#include "kynapse/graph/tables.hpp"
#endif

extern const float D_00405B60;

unsigned int PointMapper::FindTarget(PointContainer *source, PointContainer *target, const Vec3 *point) {
    unsigned int best = (unsigned int)-1;
    float bestDistance = D_00405B60;
    for (unsigned int i = 0; i < target->Count(); ++i) {
        const Vec3 *candidate = target->Get(i);
        float absolute = candidate->y-point->y;
        if (absolute<0.0f) absolute = -absolute;
        if (!(absolute>this->maxDeltaUp)) {
            float value = (candidate->z - point->z) * (candidate->z - point->z) +
                          (candidate->x - point->x) * (candidate->x - point->x) +
                          (candidate->y - point->y) * (candidate->y - point->y);
            if (!(value > bestDistance) &&
                (D_00451228.visible(point, candidate, this->entityWidth, 0, 2) & 255) &&
                value < bestDistance) {
                bestDistance = value;
                best = i;
            }
        }
    }
    return best;
}

extern const float D_00405B60 = 3.4028235e38f;
extern const float nearestPointPadding = 0.0f;

#ifdef NON_MATCHING
extern "C" const char *func_002E3920(void *);
struct RegisteredClass { const char *name; PointContainer *(*create)(); };
extern "C" RegisteredClass *func_0038B150(const char *);
extern const char D_00405B48[], D_00405B58[];
extern "C" ChildBuffers *func_002E33E0(ChildBuffers *, unsigned int);
extern const char D_00405B68[], D_00405B98[];
extern const unsigned int D_00405BB4;
extern "C" int LoadSmall(PointMapper *, const void *, int) __asm__("func_002DBCE0");
extern const char D_00405B98[];
// Unmatched: allocator lifetimes and saved-register allocation.
int PointMapper::Save(const void *path) {
 unsigned int i,j,k;

    void *file = D_00451228.open(path, D_00405B68);
    if (!file) return 0;
    unsigned int version = D_00405BB4, word;
    if (D_00451228.write(D_00405B98, 1, func_0035CCD8(D_00405B98), file) != func_0035CCD8(D_00405B98)) goto fail;
    if (D_00451228.write(&version, 4, 1, file) != 1) goto fail;
    word = this->count;
    if (D_00451228.write(&word, 4, 1, file) != 1) goto fail;
    for (i = 0;i<this->count;++i) {
        word = this->pointCounts[i];
        if (D_00451228.write(&word, 4, 1, file) != 1) goto fail;
    }
    for (i = 0;i<this->count;++i) {
        unsigned int length = func_0035CCD8(this->names[i])+1;
        if (D_00451228.write(this->names[i], 1, length, file) != length) goto fail;
    }
    for (i = 0;i<this->count;++i)
        for (j = 0;j<this->count;++j)
            if (i != j)
                for (k = 0;k<this->pointCounts[i];++k) {
        word = this->cells[i][j][k];
        if (D_00451228.write(&word, 4, 1, file) != 1) goto fail;
    }
    D_00451228.close(file);
    return 1;
    fail:
    D_00451228.close(file);
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DB9C8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DBCE0);
#ifdef NON_MATCHING
// Unmatched: allocator lifetimes and saved-register allocation.
int PointMapper::Load(const void *resource) {
 unsigned int i,j,k;

    func_002DADD0(this);
    FileService *files = D_003C9ED4->files;
    if (!files) return 0;
    if (!files->Exists(resource)) return 0;
    char header[0x40];
    unsigned int version;
    unsigned int length = files->Read(resource, header, func_0035CCD8(D_00405B98));
    if (length != func_0035CCD8(D_00405B98)) goto fail;
    if (files->Read(resource, &version, 4) != 4) goto fail;
    header[length] = 0;
    if (func_00360838(D_00405B98, header)) goto fail;
    if (version == 1) return LoadSmall(this, resource, 1);
    if (version != 2) goto fail;
    if (files->Read(resource, &this->count, 4) != 4) goto fail;
    if (this->count) {
        this->pointCounts = new unsigned int[this->count];
        for (i = 0;i<this->count;++i)
            if (files->Read(resource, &this->pointCounts[i], 4) != 4) goto fail;
        this->names = new char *[this->count];
        for (i = 0;i<this->count;++i) {
            char text[0x400];
            unsigned int length = 0;
            text[0] = 0;
            do {
                if (files->Read(resource, text+length, 1) != 1) goto fail;
            }
            while (text[length++] != 0);
            this->names[i] = new char[length];
            func_0035CBC0(this->names[i], text);
        }
        this->cells = new unsigned int **[this->count];
        for (i = 0;i<this->count;++i) {
            this->cells[i] = new unsigned int *[this->count];
            for (j = 0;j<this->count;++j) {
                if (i == j) this->cells[i][j] = 0;
                else {
                    this->cells[i][j] = new unsigned int[this->pointCounts[i]];
                    for (k = 0;k<this->pointCounts[i];++k)
                        if (files->Read(resource, &this->cells[i][j][k], 4) != 4) goto fail;
                }
            }
        }
    }
    files->Close(resource);
    return 1;
    fail:
    files->Close(resource);
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DC238);
#endif
