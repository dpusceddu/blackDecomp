// Inferred point-mapping names; member offsets are verified by the matched PS2 users.
#ifndef BLACK_CONTEXT_BEHAVIORS_POINTMAPPER_HPP
#define BLACK_CONTEXT_BEHAVIORS_POINTMAPPER_HPP

struct Vec3 {
    float x, y, z;
};
struct ChildBuffers {
    char unknown00[12];
    const char *first;
    char unknown10[16];
    unsigned int count;
    const char* GetSecond() const __asm__("func_002E3920");
    ChildBuffers* GetChild(unsigned int i) const __asm__("func_002E33E0");
    const char* FindValue(const char* key) const __asm__("func_002E3330");
};
struct PointContainer {
    virtual ~PointContainer();
    virtual int Configure(ChildBuffers *);
    virtual unsigned int Count();
    virtual const Vec3 *Get(unsigned int);
};
struct PointLocator {
    virtual void Slot0();
    virtual void Slot1();
    virtual int Resolve(unsigned int *, unsigned int *);
};
extern void (*D_003C87E0)(void *);
struct PolymorphicBase {
    virtual ~PolymorphicBase();
};
struct PointMapper : PolymorphicBase {
    PointMapper() __asm__("func_002DADA8");
    static void *operator new(unsigned int);
    static void operator delete(void *p) {
        D_003C87E0(p);
    }
    virtual ~PointMapper();
    virtual int Configure(ChildBuffers *);
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual int Map(PointLocator *, unsigned int, unsigned int *) __asm__("func_002DC930");
    virtual int Build(ChildBuffers *) __asm__("func_002DB140");
    virtual unsigned int FindTarget(PointContainer *, PointContainer *, const Vec3 *);
    virtual int Load(const void *) __asm__("func_002DC238");
    virtual int Save(const void *) __asm__("func_002DB9C8");
    void Clear() __asm__("func_002DADD0");
    int LoadSmall(const void *) __asm__("func_002DBCE0");
    float maxDeltaUp, entityWidth;
    unsigned int count;
    unsigned int *pointCounts;
    char **names;
    unsigned int ***cells;
};
struct FileService {
    virtual void Slot0();
    virtual void Slot1();
    virtual int Exists(const void *);
    virtual int Read(const void *, void *, unsigned int);
    virtual void Close(const void *);
};
struct EngineInfo {
    void *vtable;
    FileService *files;
    int unknown08;
    float unit;
};
extern EngineInfo *D_003C9ED4;
struct Allocator {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual unsigned int Allocate(unsigned int, void **);
};
extern Allocator *D_003C87E8;
extern void (*D_003C87EC)(void *, unsigned int, unsigned int);
inline void *Allocate(unsigned int size) {
    void *block = 0;
    unsigned int tag = D_003C87E8->Allocate(size, &block);
    if (D_003C87EC) D_003C87EC(block, size, tag);
    return block;
}
struct Hooks {
    char unknown00[0x2c];
    int (*visible)(const Vec3 *, const Vec3 *, float, void *, int);
    char unknown30[0x24];
    void *(*open)(const void *, const char *);
    void (*close)(void *);
    char unknown5c[8];
    unsigned int (*write)(const void *, unsigned int, unsigned int, void *);
};
extern Hooks D_00451228;
inline void* operator new[](unsigned int size){return Allocate(size);}
inline void operator delete[](void* p){D_003C87E0(p);}
extern "C" {
    unsigned int func_0035CCD8(const char *);
    char *func_0035CBC0(char *, const char *);
    int func_00360838(const char *, const char *);
    const char *func_002E3330(ChildBuffers *, const char *);
    ChildBuffers *func_002E31E0(ChildBuffers *, const char *);
    int func_002E52C8(const char *, char *);
    long func_0035E730(const char *);
    float func_00291C68(long);
    void func_002DADD0(PointMapper *);
    int func_002DBCE0(PointMapper *, const void *);
}

inline void *PointMapper::operator new(unsigned int size) {
    return Allocate(size);
}

#define POINT_OFFSET(member, offset) typedef char PointMapper_##member##_offset[(unsigned int)&((PointMapper *)0)->member == offset ? 1 : -1]
POINT_OFFSET(maxDeltaUp, 4);
POINT_OFFSET(entityWidth, 8);
POINT_OFFSET(count, 0xC);
POINT_OFFSET(pointCounts, 0x10);
POINT_OFFSET(names, 0x14);
POINT_OFFSET(cells, 0x18);
#undef POINT_OFFSET
typedef char PointMapper_size[sizeof(PointMapper) == 0x1C ? 1 : -1];

#endif
