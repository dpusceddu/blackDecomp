// Segment ray queries and the bounded hit buffer.
#include "physics/segment_query.hpp"


#ifdef BLACK_NONMATCHING
// Unmatched: resumable traversal, SN callback member pointers and VU0 frame lifetimes.
static inline PhysicsMatrix Compose(const PhysicsMatrix& a,const PhysicsMatrix& b){PhysicsMatrix r;r.row[0]=PhysicsDirection(a,b.row[0]);r.row[1]=PhysicsDirection(a,b.row[1]);r.row[2]=PhysicsDirection(a,b.row[2]);r.row[3]=PhysicsPosition(a,b.row[3]);return r;}
inline unsigned int PhysicsSegmentQuery::QueueLeaf(const SegmentShapePS2* shapeToQueue, const PhysicsMatrix* frame,
                                            unsigned int identity, unsigned char tag)
{
    if (leafCount >= secondCount)
        return 0;
    LeafSlot().shape = shapeToQueue;
    if (frame) {
        LeafSlot().frameCopy=*frame;
        LeafSlot().frame = &LeafSlot().frameCopy;
    } else {
        LeafSlot().frame = 0;
    }
    LeafSlot().identity = identity;
    LeafSlot().tag = tag;
    ++leafCount;
    return 1;
}

inline unsigned int PhysicsSegmentQuery::QueueShape(const SegmentShapePS2* shapeToQueue, const PhysicsMatrix* frame,
                                             unsigned int identity, unsigned char tag)
{
    if (shapeToQueue->type->kind != 5)
        return QueueLeaf(shapeToQueue, frame, identity, tag);
    if (compoundCount >= firstCount)
        return 0;
    CompoundSlot().shape = shapeToQueue;
    if (frame) {
        CompoundSlot().frameCopy=*frame;
        CompoundSlot().frame = &CompoundSlot().frameCopy;
    } else {
        CompoundSlot().frame = 0;
    }
    CompoundSlot().identity = identity;
    CompoundSlot().tag = tag;
    ++compoundCount;
    return 1;
}
static inline unsigned int& QueryWord(PhysicsSegmentQuery* query, unsigned int offset)
{
    return *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(query)+offset);
}
static inline PhysicsQueuedShape& ActiveSegmentShape(PhysicsSegmentQuery* query)
{
    return *reinterpret_cast<PhysicsQueuedShape*>(reinterpret_cast<char*>(query)+0x50);
}

int PhysicsSegmentQuery::Execute()
{
    QueryWord(this,0x14)=0;
    QueryWord(this,0xe8)=0;
    identityPrefix=0;
    *reinterpret_cast<unsigned char*>(&identityBits)=0;
    for (;;) {
        PhysicsQueuedShape& active=ActiveSegmentShape(this);
        if (((rootCount<=rootCursor && !active.shape && leafCount+compoundCount==0)) || maxHits<=QueryWord(this,0x14))
            return QueryWord(this,0x14);
        bool blocked=false;
        while ((rootCursor<rootCount || active.shape || compoundCount) && !blocked) {
            if (!active.shape && !compoundCount && rootCursor<rootCount) {
                const SegmentShapePS2* const* roots=*reinterpret_cast<const SegmentShapePS2* const**>(this);
                const PhysicsMatrix* const* frames=*reinterpret_cast<const PhysicsMatrix* const**>(reinterpret_cast<char*>(this)+4);
                const PhysicsMatrix* frame=frames ? frames[rootCursor] : 0;
                QueueShape(roots[rootCursor],frame,0,0);
                ++rootCursor;
            }
            if (!active.shape) {
                if (!compoundCount) break;
                --compoundCount;
                PhysicsQueuedShape& source=static_cast<PhysicsQueuedShape*>(buffer)[compoundCount];
                active.shape=source.shape;
                active.frame=source.frame;
                active.frameCopy=source.frameCopy;
                active.transform[0]=source.transform[0];
                active.transform[1]=source.transform[1];
                active.identity=source.identity;
                active.tag=source.tag;
            }
            identityPrefix=active.identity;
            *reinterpret_cast<unsigned char*>(&identityBits)=active.tag;
            if (active.shape->type->kind==5) {
                PhysicsMatrix composed;
                const PhysicsMatrix* frame=&active.shape->frame;
                if (active.frame) { composed=Compose(active.shape->frame,*active.frame); frame=&composed; }
                SegmentGeometryPS2* geometry=*reinterpret_cast<SegmentGeometryPS2* const*>(&active.shape->dimensions[0]);
                const SegmentGeometryTablePS2* callbacks=reinterpret_cast<const SegmentGeometryTablePS2*>(geometry->callbacks);
                if ((geometry->*callbacks->segment)(this,frame)) {
                    QueryWord(this,0xf8)=0;
                    memberCursor=0;
                    active.shape=0;
                    continue;
                }
            } else if (QueueLeaf(active.shape,active.frame,active.identity,active.tag)) {
                active.shape=0;
                continue;
            }
            blocked=true;
        }
        while (leafCount && QueryWord(this,0x14)<maxHits) {
            --leafCount;
            PhysicsQueuedShape& leaf=static_cast<PhysicsQueuedShape*>(firstItems)[leafCount];
            PhysicsSegmentHit* hit=hits+QueryWord(this,0x14);
            const SegmentShapePS2* shape=leaf.shape;
            if ((shape->unknown5c&1) && (shape->*shape->type->ray)(reinterpret_cast<const PhysicsVec*>(reinterpret_cast<char*>(this)+0x20),reinterpret_cast<const PhysicsVec*>(reinterpret_cast<char*>(this)+0x30),leaf.frame,static_cast<void*>(hit))) {
                if (mode && fractionLimit>hit->fraction) fractionLimit=hit->fraction;
                const SegmentShapePS2* const* roots=*reinterpret_cast<const SegmentShapePS2* const**>(this);
                hit->shape=reinterpret_cast<unsigned int>(roots[rootCursor-1]);
                hit->unknown50=reinterpret_cast<unsigned int>(shape);
                if (leaf.frame) {
                    hit->frame[0]=leaf.frame->row[0];
                    hit->frame[1]=leaf.frame->row[1];
                    hit->frame[2]=leaf.frame->row[2];
                    hit->frame[3]=leaf.frame->row[3];
                    hit->unknown54=reinterpret_cast<unsigned int>(&hit->frame[0]);
                } else hit->unknown54=0;
                hit->unknownC0=leaf.identity;
                ++QueryWord(this,0x14);
            }
        }
    }
}
#endif


#ifdef BLACK_NONMATCHING
// Unmatched: static vector construction, temporary scheduling and small-data ownership.
struct PhysicsConstants {float x,y,z,w;} __attribute__((aligned(16)));
extern "C" {extern unsigned D_0040E918[2],D_0040E920[2];extern PhysicsConstants D_0045E7E0,D_0045E7F0,D_0045E800,D_0045E810;void func_00100228(void*);void func_00100258(void*);void func_00100260(void*,int);void func_00100230(void*,int);}
extern "C" void func_0033AC48(int initialize,int priority){
 if(priority==65535){if(initialize){
 func_00100228(D_0040E918);func_00100258(D_0040E920);
 PhysicsConstants a;a.x=1.5707963705062866f;a.y=-0.15915493667125702f;a.z=12582912.0f;PhysicsConstants b;b.x=-0.15915493667125702f;b.y=0.5f;b.z=0.25f;PhysicsConstants c;c.x=-76.57495880126953f;c.y=-41.3416748046875f;c.z=81.60222625732422f;PhysicsConstants d;d.x=39.71065902709961f;d.y=6.283185005187988f;d.z=0.0f;
 *(PhysicsVec*)&D_0045E7E0=*(PhysicsVec*)&a;*(PhysicsVec*)&D_0045E7F0=*(PhysicsVec*)&b;*(PhysicsVec*)&D_0045E800=*(PhysicsVec*)&c;*(PhysicsVec*)&D_0045E810=*(PhysicsVec*)&d;
 }else{func_00100260(D_0040E920,2);func_00100230(D_0040E918,2);}}
}

#endif


#ifdef BLACK_NONMATCHING
// Unmatched: inlined storage constructor register allocation and address scheduling.
extern "C" PhysicsSegmentQuery* func_0033ADD0(PhysicsStorageBlock* block,unsigned first,unsigned second){
 PhysicsSegmentQuery* query=(PhysicsSegmentQuery*)block->memory;
 if(query){
  char* buffer=(char*)query+0x110;char* firstItems=buffer+(first<<7);char* secondItems=firstItems+(second<<7);
  query->firstCount=first;query->secondCount=second;
  char* hits=secondItems+second*96;
  query->capacity=second;query->thirdCount=second;
  query->buffer=buffer;query->firstItems=firstItems;query->secondItems=secondItems;query->hits=(PhysicsSegmentHit*)hits;query->end=hits+second*208;
 }return query;
}

#endif

static inline int Complete(const PhysicsSegmentQuery* query){
 int complete=0;
 if(query->rootCursor==query->rootCount&&!*(unsigned*)((char*)query+0x50)&&!query->compoundCount&&!query->leafCount)complete=1;
 return complete;
}
template<class T>static inline T LocalMin(const T& a,const T& b){return a<b?a:b;}
PhysicsSegmentHit* PhysicsSegmentQuery::FindNearest(){
 unsigned found=0;mode=2;unsigned limit=5;unsigned count=capacity;maxHits=LocalMin(limit,count);
 PhysicsSegmentHit closest;
 while(!Complete(this)){
  unsigned count=Execute();
  for(unsigned i=0;i<count;++i){
   if(found){if(closest.fraction>hits[i].fraction){closest=hits[i];fractionLimit=closest.fraction;}}
   else{found=1;closest=hits[i];}
  }
 }
 if(found){*hits=closest;return hits;}return 0;
}

extern "C" PhysicsStorageRequirement *func_0033AD90(PhysicsStorageRequirement *storage, s32 first, s32 second)
{
  int new_var;
  new_var = 0x110;
  storage->alignment = 0x10;
  storage->size = (s32) (((((((first << 5) << 2) + new_var) + (second << 7)) + (second * 0x60)) + (second * 0xD0)) + 0x2880);
  return storage;
}


int PhysicsSegmentQuery::CollectHits()
{
    mode = 0;
    maxHits = capacity;
    return Execute();
}

PhysicsSegmentHit* PhysicsSegmentQuery::AnyHit()
{
    mode = 1;
    maxHits = 1;
    if (Execute())
        return hits;
    return 0;
}


extern "C" void func_0033AC48(int,int);
extern "C" void func_0033AEA8(){func_0033AC48(1,65535);}
extern "C" void func_0033AEC8(){func_0033AC48(0,65535);}
