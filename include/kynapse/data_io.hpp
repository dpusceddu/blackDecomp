// Ported from an unpublished companion project.
#ifndef BLACK_KYNAPSE_DATA_IO_HPP
#include "kynapse/compat.hpp"
#define BLACK_KYNAPSE_DATA_IO_HPP

// File access shared by the data tables that load and save themselves ("Kynogon ... Data" files).
// Loading goes through the engine's file service (resources are addressed by the configuration node
// that names them); saving uses the host application's stdio-like hooks.

namespace Kaim {

struct FileService {
    virtual void Slot0();
    virtual void Slot1();
    virtual bool Exists(const void* resource);                           // slot 2
    virtual int Read(const void* resource, void* buffer, int size);     // slot 3
    virtual void Close(const void* resource);                           // slot 4
};

struct DataEngine {
    unsigned char unknown00[4];
    FileService* files;
};
extern DataEngine* gEngine;

extern void* (*gFileOpen)(const void* path, const char* mode);
extern void (*gFileClose)(void* file);
extern int (*gFileWrite)(const void* data, int size, int count, void* file);

void Word_Convert(unsigned int* out, const unsigned int* in, int mode);
void* Kaim_AllocateTagged(unsigned int size, const void* tag);
extern const unsigned char gTextTag;

}  // namespace Kaim

#endif
