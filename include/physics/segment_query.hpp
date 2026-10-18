#ifndef BLACK_PHYSICS_SEGMENT_QUERY_HPP
#define BLACK_PHYSICS_SEGMENT_QUERY_HPP
#include "physics/scene.hpp"
// Partial layouts checked against the PS2 query loads; callbacks use SN member pointers.
struct SegmentShapePS2;struct PhysicsSegmentQuery;struct SegmentGeometryPS2;
struct SegmentShapeTypePS2 {
 unsigned kind;
 int (SegmentShapePS2::*worldBounds)(const PhysicsMatrix*,void*,PhysicsBounds*)const;
 int (SegmentShapePS2::*unknown0c)(void*,void*)const;
 int (SegmentShapePS2::*unknown14)(void*,void*)const;
 int (SegmentShapePS2::*buildSupport)(void*,const PhysicsMatrix*)const;
 int (SegmentShapePS2::*ray)(const PhysicsVec*,const PhysicsVec*,const PhysicsMatrix*,void*)const;
};
struct SegmentShapePS2 {PhysicsMatrix frame;float dimensions[3],radius;unsigned unknown50,unknown54;SegmentShapeTypePS2* type;unsigned unknown5c;};
struct SegmentGeometryTablePS2 {unsigned char unknown00[0x1c];int (SegmentGeometryPS2::*segment)(PhysicsSegmentQuery*,const PhysicsMatrix*);};
struct SegmentGeometryPS2 {PhysicsBounds bounds;SegmentGeometryTablePS2* callbacks;unsigned indexBits,count,unknown2c;SegmentShapePS2* shapes;};
struct PhysicsSegmentHit {
    unsigned int shape;                 // 0x00
    PhysicsVec point;                       // 0x10
    PhysicsVec normal;                      // 0x20
    PhysicsVec direction;                   // 0x30
    union {
        unsigned int feature;           // 0x40: retained word-copy representation
        float fraction;                 // 0x40: hit distance along the query
    };
    unsigned char unknown44[0x0c];
    unsigned int unknown50;
    unsigned int unknown54;
    unsigned char unknown58[8];
    PhysicsVec frame[6];                    // 0x60
    unsigned int unknownC0;
    unsigned char unknownC4;

};

struct PhysicsQueuedShape {
    const SegmentShapePS2* shape;          // 0x00
    const PhysicsMatrix* frame;                // 0x04
    unsigned char unknown08[8];
    PhysicsMatrix frameCopy;                   // 0x10
    PhysicsVec transform[2];                // 0x50
    unsigned int identity;              // 0x70
    unsigned char tag;                  // 0x74
    unsigned char padding[0x0b];
};

struct PhysicsSegmentQuery {
    unsigned char unknown00[8];
    unsigned int rootCount;             // 0x08
    unsigned int rootCursor;            // 0x0c
    PhysicsSegmentHit* hits;            // 0x10
    unsigned char unknown14[4];
    unsigned int maxHits;               // 0x18
    unsigned int capacity;              // 0x1c
    unsigned char unknown20[0x20];
    void* buffer;                       // 0x40
    unsigned char unknown44[0xd0 - 0x44];
    unsigned int compoundCount;         // 0xd0: queued compound shapes (items at buffer)
    unsigned int firstCount;            // 0xd4: compound capacity
    void* firstItems;                   // 0xd8: 128-byte items (leaf shapes)
    unsigned int leafCount;             // 0xdc
    unsigned int secondCount;           // 0xe0: leaf capacity
    void* secondItems;                  // 0xe4: 128-byte items
    unsigned char unknownE8[4];
    unsigned int thirdCount;            // 0xec
    unsigned int memberCursor;          // 0xf0
    void* end;                          // 0xf4: after the 0xd0-byte items
    unsigned char unknownF8[4];
    float fractionLimit;                // 0xfc
    unsigned int mode;                  // 0x100
    unsigned int identityPrefix;        // 0x104
    unsigned int identityBits;          // 0x108

    PhysicsSegmentQuery(unsigned int first, unsigned int second, unsigned int third);
    int Execute() __asm__("func_0033A488");                      // Ghidra /default.xbe 0x70e30
    PhysicsQueuedShape& LeafSlot() { return static_cast<PhysicsQueuedShape*>(firstItems)[leafCount]; }
    PhysicsQueuedShape& CompoundSlot() { return static_cast<PhysicsQueuedShape*>(buffer)[compoundCount]; }
    unsigned int QueueLeaf(const SegmentShapePS2* shape, const PhysicsMatrix* frame, unsigned int identity,
                           unsigned char tag);   // 0x6fc60
    unsigned int QueueShape(const SegmentShapePS2* shape, const PhysicsMatrix* frame, unsigned int identity,
                            unsigned char tag);  // 0x6fd30
    int CollectHits() __asm__("func_0033AE40");                  // 0x71140
    PhysicsSegmentHit* AnyHit() __asm__("func_0033AE68");        // 0x71160
    PhysicsSegmentHit* FindNearest() __asm__("func_0033AA98");   // 0x71190
};
void PhysicsSegmentQuery_GetStorage(PhysicsStorageRequirement* storage, unsigned int first, unsigned int second);
PhysicsSegmentQuery* PhysicsSegmentQuery_CreateInStorage(PhysicsStorageBlock* block, unsigned int first,
                                                         unsigned int second);
#endif
