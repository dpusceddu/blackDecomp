#include "include_asm.h"

#include "kynapse/point_mapper.hpp"

extern unsigned int D_003E6438[], D_003E0040, D_003E6428;
extern unsigned int D_00450FD8, D_003E5E40;
extern unsigned int *D_004510E8;
extern "C" void func_002E7610(void *, const char *, PointMapper *(*)(), int, int, int);
extern "C" PointMapper *func_002DAD10();

extern "C" PointMapper *func_002DADA8(PointMapper *self) {
    self->count = 0;
    *(void **) self = D_003E6438;
    self->pointCounts = 0;
    self->names = 0;
    self->cells = 0;
    return self;
}
extern "C" void func_002DC7E0(int initialize, int priority) {
    if (priority == 0xffff) {
        if (initialize) {
            func_002E7610(&D_00450FD8, "CPointMapper", func_002DAD10, 0, 0, 0);
            return;
        }
        D_004510E8 = &D_003E5E40;
    }
}
extern "C" void func_002DC840(PointMapper *self, int flags) {
    *(void **) self = D_003E6438;
    func_002DADD0(self);
    *(void **) self = &D_003E0040;
    if (flags&1) D_003C87E0(self);
}
extern "C" int func_002DC8A0(PointMapper *self, const char *name, unsigned int *index) {
    *index = 0;
    while (*index<self->count) {
        if (!func_00360838(name, self->names[*index])) return 1;
        ++*index;
    }
    return 0;
}
extern "C" void func_002DC9F0() {
    D_003E6428 = 0;
}
extern "C" void func_002DCA00() {
    func_002DC7E0(1, 0xffff);
}
extern "C" void func_002DCA20() {
    func_002DC7E0(0, 0xffff);
}

#ifdef NONMATCHING
// Unmatched: inner-loop scheduling differs.
extern "C" void func_002DADD0(PointMapper *self) {
    unsigned int i, j, k;
    if (self->names) {
        for (i = 0; i<self->count; ++i)
            if (self->names[i]) D_003C87E0(self->names[i]);
        D_003C87E0(self->names);
    }
    self->names = 0;
    if (self->pointCounts) D_003C87E0(self->pointCounts);
    self->pointCounts = 0;
    if (self->cells) {
        for (k = 0; k<self->count; ++k) {
            if (self->cells[k]) {
                for (j = 0; j<self->count; ++j)
                    if (self->cells[k][j]) D_003C87E0(self->cells[k][j]);
                D_003C87E0(self->cells[k]);
            }
        }
        D_003C87E0(self->cells);
    }
    self->cells = 0;
}
#endif

#ifdef NONMATCHING
// Unmatched: allocator lifetimes and loop register allocation differ.
struct RegisteredClass {
    const char *name;
    PointContainer *(*create)();
};
extern "C" RegisteredClass *func_0038B150(const char *);
extern const char D_00405B48[], D_00405B58[];
extern "C" ChildBuffers *func_002E33E0(ChildBuffers *, unsigned int);
extern "C" const char *func_002E3920(ChildBuffers *);
extern "C" int func_002DB140(PointMapper *self, ChildBuffers *config) {
    self->count = 0;
    for (unsigned int i = 0;i<config->count;++i)
        if (!func_00360838(func_002E3920(func_002E33E0(config, i)), D_00405B48))++self->count;
    if (!self->count) return 1;
    self->names = (char **) Allocate(self->count*4);
    self->pointCounts = (unsigned int *) Allocate(self->count*4);
    self->cells = (unsigned int ***) Allocate(self->count*4);
    for (unsigned int i = 0;i<self->count;++i) {
        self->pointCounts[i] = 0;
        self->names[i] = 0;
        self->cells[i] = (unsigned int **) Allocate(self->count*4);
        for (unsigned int j = 0;j<self->count;++j) self->cells[i][j] = 0;
    }
    PointContainer **containers = (PointContainer **) Allocate(self->count*4);
    unsigned int made = 0;
    for (unsigned int i = 0;i<config->count;++i) {
        ChildBuffers *child = func_002E33E0(config, i);
        if (func_00360838(func_002E3920(child), D_00405B48)) continue;
        const char *className = func_002E3330(child, D_00405B58);
        if (!className) {
            for (unsigned int k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        RegisteredClass *factory = func_0038B150(className);
        if (!factory) {
            for (unsigned int k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        PointContainer *container = factory->create();
        containers[made] = container;
        if (!container->Configure(child)) {
            for (unsigned int k = 0;k<made;++k) if (containers[k]) delete containers[k];
            return 0;
        }
        const char *name = child->first;
        self->names[made] = (char *) Allocate(func_0035CCD8(name)+1);
        func_0035CBC0(self->names[made], name);
        ++made;
    }
    for (unsigned int i = 0;i<self->count;++i) {
        PointContainer *from = containers[i];
        self->pointCounts[i] = from->Count();
        for (unsigned int j = 0;j<self->count;++j) {
            if (i == j) continue;
            PointContainer *to = containers[j];
            self->cells[i][j] = (unsigned int *) Allocate(from->Count()*4);
            for (unsigned int k = 0;k<from->Count();++k) self->cells[i][j][k] = self->FindTarget(from, to, from->Get(k));
        }
    }
    for (unsigned int i = 0;i<self->count;++i) if (containers[i]) delete containers[i];
    D_003C87E0(containers);
    return 1;
}
#endif

#ifdef NONMATCHING
// Unmatched: failure-branch placement and saved registers differ.
extern const char D_00405B68[], D_00405B98[];
extern const unsigned int D_00405BB4;
extern "C" int func_002DB9C8(PointMapper *self, const void *path) {
    void *file = D_00451228.open(path, D_00405B68);
    if (!file) return 0;
    unsigned int version = D_00405BB4, word;
    if (D_00451228.write(D_00405B98, 1, func_0035CCD8(D_00405B98), file) != func_0035CCD8(D_00405B98)) goto fail;
    if (D_00451228.write(&version, 4, 1, file) != 1) goto fail;
    word = self->count;
    if (D_00451228.write(&word, 4, 1, file) != 1) goto fail;
    for (unsigned int i = 0;i<self->count;++i) {
        word = self->pointCounts[i];
        if (D_00451228.write(&word, 4, 1, file) != 1) goto fail;
    }
    for (unsigned int i = 0;i<self->count;++i) {
        unsigned int length = func_0035CCD8(self->names[i])+1;
        if (D_00451228.write(self->names[i], 1, length, file) != length) goto fail;
    }
    for (unsigned int i = 0;i<self->count;++i)
        for (unsigned int j = 0;j<self->count;++j)
            if (i != j)
                for (unsigned int k = 0;k<self->pointCounts[i];++k) {
        word = self->cells[i][j][k];
        if (D_00451228.write(&word, 4, 1, file) != 1) goto fail;
    }
    D_00451228.close(file);
    return 1;
    fail:
    D_00451228.close(file);
    return 0;
}
#endif

#ifdef NONMATCHING
// Unmatched: 16-bit loader stack lifetimes and register allocation differ.
extern "C" int func_002DBCE0(PointMapper *self, const void *resource) {
    FileService *files = D_003C9ED4->files;
    unsigned short word = 0;
    if (files->Read(resource, &word, 2) != 2) goto fail;
    self->count = word;
    if (self->count) {
        self->pointCounts = (unsigned int *) Allocate(self->count*4);
        for (unsigned short i = 0;i<self->count;++i) {
            if (files->Read(resource, &word, 2) != 2) goto fail;
            self->pointCounts[i] = word;
        }
        self->names = (char **) Allocate(self->count*4);
        for (unsigned short i = 0;i<self->count;++i) {
            char text[0x400];
            unsigned short length = 0;
            text[0] = 0;
            do {
                if (files->Read(resource, text+length, 1) != 1) goto fail;
            }
            while (text[length++] != 0);
            self->names[i] = (char *) Allocate(length);
            func_0035CBC0(self->names[i], text);
        }
        self->cells = (unsigned int ***) Allocate(self->count*4);
        for (unsigned short i = 0;i<self->count;++i) {
            self->cells[i] = (unsigned int **) Allocate(self->count*4);
            for (unsigned short j = 0;j<self->count;++j) {
                if (i == j) self->cells[i][j] = 0;
                else {
                    self->cells[i][j] = (unsigned int *) Allocate(self->pointCounts[i]*4);
                    for (unsigned short k = 0;k<self->pointCounts[i];++k) {
                        unsigned short cellWord = 0;
                        if (files->Read(resource, &cellWord, 2) != 2) goto fail;
                        self->cells[i][j][k] = cellWord;
                        if (cellWord == 0xffff) self->cells[i][j][k] = (unsigned int)-1;
                        else self->cells[i][j][k] = cellWord;
                    }
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

#ifdef NONMATCHING
// Unmatched: stream-loader stack lifetimes and register allocation differ.
extern const char D_00405B98[];
extern "C" int func_002DC238(PointMapper *self, const void *resource) {
    func_002DADD0(self);
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
    if (version == 1) return func_002DBCE0(self, resource);
    if (version != 2) goto fail;
    if (files->Read(resource, &self->count, 4) != 4) goto fail;
    if (self->count) {
        self->pointCounts = (unsigned int *) Allocate(self->count*4);
        for (unsigned int i = 0;i<self->count;++i)
            if (files->Read(resource, &self->pointCounts[i], 4) != 4) goto fail;
        self->names = (char **) Allocate(self->count*4);
        for (unsigned int i = 0;i<self->count;++i) {
            char text[0x400];
            unsigned int length = 0;
            text[0] = 0;
            do {
                if (files->Read(resource, text+length, 1) != 1) goto fail;
            }
            while (text[length++] != 0);
            self->names[i] = (char *) Allocate(length);
            func_0035CBC0(self->names[i], text);
        }
        self->cells = (unsigned int ***) Allocate(self->count*4);
        for (unsigned int i = 0;i<self->count;++i) {
            self->cells[i] = (unsigned int **) Allocate(self->count*4);
            for (unsigned int j = 0;j<self->count;++j) {
                if (i == j) self->cells[i][j] = 0;
                else {
                    self->cells[i][j] = (unsigned int *) Allocate(self->pointCounts[i]*4);
                    for (unsigned int k = 0;k<self->pointCounts[i];++k)
                        if (files->Read(resource, &self->cells[i][j][k], 4) != 4) goto fail;
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

#ifdef NONMATCHING
// Unmatched: success-branch layout differs.
extern "C" int func_002DC930(PointMapper *self, PointLocator *locator,
unsigned int container, unsigned int *mapped) {
    unsigned int point, owner;
    if (!locator->Resolve(&point, &owner)) return 0;
    if (owner == container) {
        *mapped = point;
        return 1;
    }
    unsigned int value = self->cells[owner][container][point];
    *mapped = value;
    if (value != (unsigned int)-1) return 1;
    return 0;
}
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DADD0);
