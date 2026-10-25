#ifndef BLACK_APT_VALUE_HPP
#define BLACK_APT_VALUE_HPP
// PS2 APT prefix views; historical class names and complete sizes are unverified.
// Exact Dispose/Cleanup consumers verify the +4 vptr and slots 10, 11 and 14.
// SetEnabled verifies its word at +0x1c. Other virtual signatures remain unverified.
namespace AptPS2 {
struct Value {
 int flags;
 virtual void AddRef();
 virtual void Release();
 virtual void Dispose();
 virtual void* Payload();
 virtual int IsValue();
 virtual int Slot5();
 virtual void SetEnabled(int);
 virtual Value* GetProperty(int,void*);
 virtual int SetProperty(int,void*,Value*);
 virtual void Cleanup();
 virtual void BeforeDispose();
 virtual void Clear();
 virtual int RetainForCollection();
 virtual int Slot13();
 virtual ~Value();
 inline bool Permanent() const { return ((int)flags>>24)&1; }
 inline bool Deferred() const { return ((int)flags>>5)&1; }
 inline bool Queued() const { return ((int)flags>>2)&1; }
};
struct PendingValues {
 int capacity,count;
 Value** data;
 inline bool HasSpace() const { return count<capacity; }
 inline bool Full() const { return count>=capacity; }
 inline void Queue(Value* value) { int index=count;if(index<capacity) {data[index]=value;count=index+1;}else value->flags&=~4; }
 inline bool Push(Value* value) {
  if(count<capacity) { data[count]=value;++count;return true; }
  return false;
 }
};
struct PropertyValue:Value {
 char unknown08[0x18];
 void* text;
 float real;
 int index,mode;
 unsigned int state;
 int otherIndex[3];
 Value* Read(int,void*);
 int Write(int,void*,Value*);
};
typedef char VptrAtFour[sizeof(Value)==8?1:-1];
typedef char PropertyTextAt20[(unsigned int)&((PropertyValue*)0)->text==0x20?1:-1];
extern "C" { extern PendingValues* D_003BE8E0; extern unsigned char D_0040DE48 __attribute__((section(".sdata"))); }
}
#endif
