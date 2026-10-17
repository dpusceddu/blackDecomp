// Declarations of the Kynapse source module "misc5" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_MISC5_HPP
#define BLACK_KYNAPSE_MODULE_MISC5_HPP
#include "kynapse/compat.hpp"

// Small Kynapse helpers (fifth batch): sorted-value comparator, distance, accessors.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

extern float gSortValues[];


int Kaim_CompareSortValues(const unsigned int* a, const unsigned int* b);


struct Vec3 {
    float x, y, z;
};


float Kaim_ManhattanDistance(const Vec3* a, const Vec3* b);


struct SortEntry {
    int id;
    float weight;
    float scale;
    float bias;
    int unknown10;
};

struct SortTable {
    unsigned char unknown00[0x0c];
    unsigned int count;
    unsigned char unknown10[4];
    int field14;
    SortEntry* entries;

    SortEntry* Get(unsigned int index)
    {
        if (index >= count)
            return 0;
        SortEntry* entry = &entries[index];
        return entry->id == -1 ? 0 : entry;
    }
};

struct TableView {
    unsigned char unknown00[4];
    SortTable* table;

    int GetField() const;
    float* GetWeight(unsigned int index);
};





extern void (*memoryRelease)(void*);

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct BookmarkBase : ObjectBase {
    void* owner;
    int field08;
    int field0c;
    short field10;
    int field14;

    BookmarkBase(void* bound)
    {
        field08 = 0;
        field0c = 0;
        field10 = 0;
        field14 = 0;
        owner = bound;
    }
};

struct Bookmark : BookmarkBase {
    Bookmark(void* bound) : BookmarkBase(bound) {}
    virtual ~Bookmark();
};


ObjectBase* CreateBookmark(void* bound);


#endif
