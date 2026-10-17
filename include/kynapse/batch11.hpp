// Declarations of the Kynapse source module "batch11" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_BATCH11_HPP
#define BLACK_KYNAPSE_MODULE_BATCH11_HPP
#include "kynapse/compat.hpp"

// Lookups over a list of named items, with the configuration step that precedes them.
extern "C" int __cdecl _stricmp(const char*, const char*);

struct ItemInfo {
    unsigned char unknown00[4];
    unsigned char flags;
    unsigned char unknown05[0xf];
    unsigned int size;
};

struct Item {
    char name[0x84];                       // 0x00 (the name starts at 0x04)
    int id;
};

struct ItemInfoHolder {
    unsigned char unknown00[0x84];
    ItemInfo* info;
};

struct ItemList {
    unsigned char unknown00[4];
    Item** items;
    unsigned int count;

    int IdByName(const char* name);
};



struct ConfigBuffers;

struct ConfigList {
    unsigned char unknown00[4];
    ItemInfoHolder** items;
    unsigned int count;
    unsigned char unknown0c[4];
    bool configured;

    bool ConfigureAll(ConfigBuffers* config);
    bool Setup(ConfigBuffers* config);
};

bool ReserveSize(unsigned int size);



#endif
