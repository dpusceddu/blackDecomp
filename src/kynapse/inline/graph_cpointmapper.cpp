#include "include_asm.h"

#include "kynapse/classes/Kaim_CPointMapper.hpp"
extern "C" const char *func_002E3920(void *);

int Unnamed::Kaim_CPointMapper::Function_0038E768(void *config) {
    if (config && func_002E3920(config) && *(const signed char *)func_002E3920(config) == '_') return 1;
    return 0;
}

// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0

// Unmatched: allocator lifetimes and saved-register allocation.
#include "kynapse/graph/tables.hpp"
struct RegisteredClass { const char *name; PointContainer *(*create)(); };
extern "C" RegisteredClass *func_0038B150(const char *);
extern const char D_00405B48[], D_00405B58[];
extern "C" ChildBuffers *func_002E33E0(ChildBuffers *, unsigned int);
extern "C" const char *func_002E3920(ChildBuffers *);
int PointMapper::Build(ChildBuffers *config) {
 unsigned int i,j,k;

    this->count = 0;
    for (i = 0;i<config->count;++i)
        if (!func_00360838(func_002E3920(func_002E33E0(config, i)), D_00405B48))++this->count;
    if (!this->count) return 1;
    this->names = new char *[this->count];
    this->pointCounts = new unsigned int[this->count];
    this->cells = new unsigned int **[this->count];
    for (i = 0;i<this->count;++i) {
        this->pointCounts[i] = 0;
        this->names[i] = 0;
        this->cells[i] = new unsigned int *[this->count];
        for (j = 0;j<this->count;++j) this->cells[i][j] = 0;
    }
    PointContainer **containers = new PointContainer *[this->count];
    unsigned int made = 0;
    for (i = 0;i<config->count;++i) {
        ChildBuffers *child = func_002E33E0(config, i);
        if (func_00360838(func_002E3920(child), D_00405B48)) continue;
        const char *className = func_002E3330(child, D_00405B58);
        if (!className) {
            for (k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        RegisteredClass *factory = func_0038B150(className);
        if (!factory) {
            for (k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        PointContainer *container = factory->create();
        containers[made] = container;
        if (!container->Configure(child)) {
            for (k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        const char *name = child->first;
        this->names[made] = new char[func_0035CCD8(name)+1];
        func_0035CBC0(this->names[made], name);
        ++made;
    }
    for (i = 0;i<this->count;++i) {
        PointContainer *from = containers[i];
        this->pointCounts[i] = from->Count();
        for (j = 0;j<this->count;++j) {
            if (i == j) continue;
            PointContainer *to = containers[j];
            this->cells[i][j] = new unsigned int[from->Count()];
            for (k = 0;k<from->Count();++k) this->cells[i][j][k] = this->FindTarget(from, to, from->Get(k));
        }
    }
    for (i = 0;i<this->count;++i) if (containers[i]) delete containers[i];
    D_003C87E0(containers);
    return 1;
}
// Unmatched: stream failure-branch layout and saved-register allocation.
#include "kynapse/point_mapper.hpp"
extern const char D_00405B68[], D_00405B98[];
extern const unsigned int D_00405BB4;
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
// Unmatched: stream-loader stack lifetimes and scheduling.
#include "kynapse/graph/tables.hpp"
extern "C" int LoadSmall(PointMapper *, const void *, int) __asm__("func_002DBCE0");
extern const char D_00405B98[];
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
#endif
