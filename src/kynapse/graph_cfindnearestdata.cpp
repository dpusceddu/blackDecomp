#include "include_asm.h"

#include "kynapse/graph/nearest.hpp"

#ifdef NON_MATCHING
// Ported from an unpublished companion project.
#include "kynapse/buffers3.hpp"

// /SLUS_213.76 0x2eef88
ObjectBase* CreateBoundBuffers(BufferOwner* bound)
{
    return new BoundBuffers(bound);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EEF88);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EF030);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EF1A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EF3D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EF6F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EF7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EF850);

Kaim::CFindNearestData::~CFindNearestData(){if(order)D_003C87E0(order);if(rank)D_003C87E0(rank);if(aux)D_003C87E0(aux);}
extern Kaim::SearchGraph *D_003CA804;
extern "C" int func_002EF6F0(const void *,const void *);
extern "C" int func_002EF7A0(const void *,const void *);
extern "C" int func_002EF850(const void *,const void *);
extern "C" void func_0035EC50(void *,unsigned int,unsigned int,int (*)(const void *,const void *));

int Kaim::CFindNearestData::Build()
{
    if (order)
        D_003C87E0(order);
    if (rank)
        D_003C87E0(rank);
    if (aux)
        D_003C87E0(aux);
    count = graph->liveNodes;
    order = new int[count * 3];
    rank = new int[count * 3];
    aux = new int[count];
    int i;
    for (i = 0; i < count; ++i) {
        order[i] = i;
        order[i + count] = i;
        order[i + count * 2] = i;
    }
    D_003CA804 = graph;
    func_0035EC50(order, count, 4, func_002EF6F0);
    func_0035EC50(order + count, count, 4, func_002EF7A0);
    func_0035EC50(order + count * 2, count, 4, func_002EF850);
    for (int axis = 0; axis < 3; ++axis) {
        for (i = 0; i < count; ++i) {
            int k;
            for (k = 0; k < count; ++k) {
                if (order[i + axis * count] == k) {
                    rank[k + axis * count] = i;
                    break;
                }
            }
            if (progress)
                progress(axis * 33 + ((i * count + k) * 33) / (count * count));
        }
    }
    return true;
}
#if 0

// Unmatched: auxiliary-pointer store scheduling persists with the typed lookup, inline loader and full TU context.
#include "kynapse/graph/nearest.hpp"
extern const char D_00407268[];
extern const int D_00407284;
extern Kaim::SearchGraph *D_003CA804;
extern "C" int func_002EF6F0(const void *,const void *);
extern "C" int func_002EF7A0(const void *,const void *);
extern "C" int func_002EF850(const void *,const void *);
extern "C" void func_0035EC50(void *,unsigned int,unsigned int,int (*)(const void *,const void *));
int Kaim::CFindNearestData::Init(ChildBuffers* config)
{
    if (count > 0) {
        order = new int[count * 3];
        rank = new int[count * 3];
        aux = new int[count];
        ChildBuffers* raw = func_002E31E0(config, "RawData");
        if (raw)
            return Load(raw);
    }
    return false;
}


#include "kynapse/graph/nearest.hpp"
extern const char D_00407268[];
extern const int D_00407284;
extern Kaim::SearchGraph *D_003CA804;
extern "C" int func_002EF6F0(const void *,const void *);
extern "C" int func_002EF7A0(const void *,const void *);
extern "C" int func_002EF850(const void *,const void *);
extern "C" void func_0035EC50(void *,unsigned int,unsigned int,int (*)(const void *,const void *));


// Unmatched: stream cleanup block order and callback-base register lifetimes.
#include "kynapse/graph/nearest.hpp"
extern const char D_00407268[];
extern const int D_00407284;
extern Kaim::SearchGraph *D_003CA804;
extern "C" int func_002EF6F0(const void *,const void *);
extern "C" int func_002EF7A0(const void *,const void *);
extern "C" int func_002EF850(const void *,const void *);
extern "C" void func_0035EC50(void *,unsigned int,unsigned int,int (*)(const void *,const void *));
extern const char D_00407228[];
int Kaim::CFindNearestData::Save(const void* path)
{
    if (order) {
    if (!rank)
        return false;
    if (count > 0) {
    void* file = D_00451228.open(path, D_00407228);
    if (!file)return 0;
    {
        int version = D_00407284;
        if (D_00451228.write(D_00407268, 1, func_0035CCD8(D_00407268), file) == func_0035CCD8(D_00407268) && D_00451228.write(&version, 4, 1, file) == 1) {
            int* buffer = 0;
            if (count > 0)
                buffer = new int[count * 3];
            for (int i = 0; i < count * 3; ++i)
                buffer[i] = order[i];
            if (D_00451228.write(buffer, 4, count * 3, file) == count * 3) {
                for (int i = 0; i < count * 3; ++i)
                    buffer[i] = rank[i];
                if (D_00451228.write(buffer, 4, count * 3, file) == count * 3) {
                    if (buffer)
                        D_003C87E0(buffer);
                    D_00451228.close(file);
                    return true;
                }
            }
            D_00451228.close(file);
            if (buffer)
                D_003C87E0(buffer);
            return false;
        }
    }
    }}
    return false;
}

// Unmatched: header-read branches and native-endian no-op loop shape.
#include "kynapse/graph/nearest.hpp"
extern const char D_00407268[];
inline void NativeWord(int *p) { *p = *p; }
int Kaim::CFindNearestData::Load(const void *path) {
 FileService *files=D_003C9ED4->files;
 if(!files || !files->Exists(path))return 0;
 char header[64];
 __builtin_strcpy(header,"none");
 unsigned int version=0;
 unsigned int length=func_0035CCD8(D_00407268);
 if(files->Read(path,header,length)!=length)goto fail;
 if(length!=func_0035CCD8(D_00407268))goto fail;
 if(files->Read(path,&version,4)!=4)goto fail;
 header[length]=0;
 if(func_00360838(D_00407268,header) || version!=1)goto fail;
 {int bytes=count*12;
 if(files->Read(path,order,bytes)!=bytes)goto fail;
 for(int i=0;i<count*3;++i)NativeWord(&order[i]);
 bytes=count*12;
 if(files->Read(path,rank,bytes)!=bytes)goto fail;
 for(int i=0;i<count*3;++i)NativeWord(&rank[i]);}
 files->Close(path);return 1;
 fail: files->Close(path);return 0;
}

// Unmatched: raw file cleanup and allocator local lifetimes.
#include "kynapse/graph/nearest.hpp"
extern const char D_00407268[];
struct RawGraphFileHooks {
 char unknown00[0x54];
 void *(*open)(const void *,const char *);
 void (*close)(void *);
 char unknown5c[8];
 unsigned int (*write)(const void *,unsigned int,unsigned int,void *);
 unsigned int (*read)(void *,unsigned int,unsigned int,void *);
};
extern RawGraphFileHooks GraphHooks __asm__("D_00451228");
inline void ConvertWord(int *p){*p=*p;}
int Kaim::CFindNearestData::LoadFile(const void *path){
 void *file=GraphHooks.open(path,"rb");
 if(!file)return 0;
 char header[64]; int version;
 unsigned int length=GraphHooks.read(header,1,func_0035CCD8(D_00407268),file);
 if(length!=func_0035CCD8(D_00407268))goto fail;
 if(GraphHooks.read(&version,4,1,file)!=1)goto fail;
 header[length]=0;
 if(func_00360838(D_00407268,header) || version!=1)goto fail;
 count=graph->liveNodes;
 if(count>0){
  order=new int[count*3]; rank=new int[count*3]; aux=new int[count];
  if(GraphHooks.read(order,4,count*3,file)!=count*3)goto fail;
  for(int i=0;i<count*3;++i)ConvertWord(&order[i]);
  if(GraphHooks.read(rank,4,count*3,file)!=count*3)goto fail;
  for(int i=0;i<count*3;++i)ConvertWord(&rank[i]);
 }
 GraphHooks.close(file);return 1;
 fail: GraphHooks.close(file);return 0;
}

// Unmatched: range arrays and register allocation.
#include "kynapse/graph/nearest.hpp"
int Kaim::CFindNearestData::CollectColumn(const Vec3 *point,int **output,float radius) {
 int axis; float defaultRadius=DefaultRadius(); int lower[3],upper[3];
 int bestAxis=-1,bestCount=-1,total=0;
 for(axis=0;axis<3;++axis) {
  float delta=axis==1 ? radius : defaultRadius;
  int number=GetRange(point,axis,&lower[axis],&upper[axis],delta);
  if(!number)return 0;
  if(bestAxis==-1 || number<bestCount){bestCount=number;bestAxis=axis;}
 }
 for(int index=lower[bestAxis];index<=upper[bestAxis];++index) {
  int entry=order[bestAxis*count+index];
  axis=0;
  while(axis<3 && (axis==bestAxis || (rank[axis*count+entry]>=lower[axis] && rank[axis*count+entry]<=upper[axis])))++axis;
  if(axis==3)aux[total++]=entry;
 }
 *output=aux;
 return total;
}

// Unmatched: range arrays and loop scheduling.
#include "kynapse/graph/nearest.hpp"
int Kaim::CFindNearestData::CollectBox(const Vec3 *point,int **output,float radius) {
 int axis; int lower[3],upper[3];
 int bestAxis=-1,bestCount=-1,total=0;
 for(axis=0;axis<3;++axis) {
  float delta=radius;
  int number=GetRange(point,axis,&lower[axis],&upper[axis],delta);
  if(!number)return 0;
  if(bestAxis==-1 || number<bestCount){bestCount=number;bestAxis=axis;}
 }
 for(int index=lower[bestAxis];index<=upper[bestAxis];++index) {
  int entry=order[bestAxis*count+index];
  axis=0;
  while(axis<3 && (axis==bestAxis || (rank[axis*count+entry]>=lower[axis] && rank[axis*count+entry]<=upper[axis])))++axis;
  if(axis==3)aux[total++]=entry;
 }
 *output=aux;
 return total;
}

// Unmatched: binary-search branch layout.
#include "kynapse/graph/nearest.hpp"
extern "C" float func_00390038(void *,const Vec3 *,int);
inline float SortedCoordinate(Kaim::CFindNearestData *data,int axis,int index) {
 return func_00390038(data,(const Vec3 *)&data->OrderedNode(axis,index)->x,axis);
}
int Kaim::CFindNearestData::EqualBoundary(int position,int axis,unsigned char lower,float value) {
 int left,right;
 if(lower){
  if(!position)return 0;
  right=position-1;
  if(SortedCoordinate(this,axis,right)!=value)return position;
  left=0;
  while(left<right-1){
   int middle=(left+right)/2;
   float coordinate=SortedCoordinate(this,axis,middle);
   if(value<coordinate)return position;
   if(coordinate<value)left=middle;else right=middle;
  }
 }else{
  if(position==graph->liveNodes-1)return position;
  if(SortedCoordinate(this,axis,position+1)!=value)return position;
  left=position-1;right=graph->liveNodes-1;
  while(left<right-1){
   int middle=(left+right)/2;
   float coordinate=SortedCoordinate(this,axis,middle);
   if(coordinate<value)return position;
   if(value<coordinate)right=middle;else left=middle;
  }
 }
 return SortedCoordinate(this,axis,left)==value ? left:right;
}

// Unmatched: binary-search branch layout.
#include "kynapse/graph/nearest.hpp"
extern "C" float func_00390038(void *,const Vec3 *,int);
inline float SortedCoordinate(Kaim::CFindNearestData *data,int axis,int index) {
 return func_00390038(data,(const Vec3 *)&data->OrderedNode(axis,index)->x,axis);
}
int Kaim::CFindNearestData::FindBound(int axis,unsigned char lower,float value) {
 int left=0,right=graph->liveNodes-1;
 while(left<right-1){
  int middle=(left+right)/2;
  float coordinate=SortedCoordinate(this,axis,middle);
  if(value<coordinate)right=middle;
  else if(coordinate<value)left=middle;
  else return EqualBoundary(middle,axis,lower,coordinate);
 }
 float a=SortedCoordinate(this,axis,left);
 float b=SortedCoordinate(this,axis,right);
 if(lower){
  if(a<value && b<value)return -1;
  if(value<=a)return EqualBoundary(left,axis,lower,a);
  return EqualBoundary(right,axis,lower,b);
 }
 if(value<a && value<b)return -1;
 if(b<=value)return EqualBoundary(right,axis,lower,b);
 return EqualBoundary(left,axis,lower,a);
}

#endif

int Kaim::CFindNearestData::GetRange(const Vec3 *point,int axis,int *lower,int *upper,float radius){
 float value=Coordinate(point,axis);
 *lower=FindBound(axis,1,value-radius);
 if(*lower!=-1){
  *upper=FindBound(axis,0,value+radius);
  if(*upper!=-1)return *upper-*lower+1;
 }
 return 0;
}

void Kaim::CFindNearestData::CopyRank(const int *source)
{
    if (!rank && count > 0)
        rank = new int[count * 3];
    for (int i = 0; i < count * 3; ++i)
        rank[i] = source[i];
}

void Kaim::CFindNearestData::CopyOrder(const int *source)
{
    if (!order && count > 0)
        order = new int[count * 3];
    for (int i = 0; i < count * 3; ++i)
        order[i] = source[i];
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EFC50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EFF00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F02E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F06C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F09A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F0A00);
