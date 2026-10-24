#if defined(STEERING_FACTORY_ONLY)
// Ported from an unpublished companion project.
#include "kynapse/factories.hpp"

// /SLUS_213.76 0x305538
ObjectBase* CreateObject62D40(int a) { return new Object62D40(a); }

#elif defined(STEERING_REGISTRATION_ONLY)
/* Translation unit kynapse/tu_305538 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

// Native class and iterator names; SN supplies their natural eight-byte placement.
const char SteeringClassName[] __asm__("D_00408630") = "CRepulsorDynamicAvoidance";
const char RootTypeName[] __asm__("D_00408650") = "Q24Kaim7CObject";
const char IteratorTypeName[] __asm__("D_00408660") = "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator";
struct SteeringRegistrationState;
struct NativeVirtualTable;
typedef void* (*SteeringFactory)(int);
extern void* func_0030D0E0(void*,const char*,SteeringFactory);
extern struct SteeringRegistrationState D_00455AD0;
extern void* func_00305538(int);
extern const struct NativeVirtualTable* D_00455BE0;
extern const struct NativeVirtualTable D_003F07A0,D_003E0040;
extern void (*D_003C87E0)(void *);

/* Register the factory during initialization, or restore its base class table. */
void func_003063A8(s32 initialize, s32 phase) {
    if (phase == 0xFFFF) {
        if (initialize != 0) {
            func_0030D0E0(&D_00455AD0, SteeringClassName, func_00305538);
            return;
        }
        D_00455BE0 = &D_003F07A0;
    }
}

/* Base destruction resets the vptr and conditionally releases the allocation. */
void func_00306400(void **object, unsigned deleteFlags)
{
    *object = (void*)&D_003E0040;
    if (deleteFlags & 1) D_003C87E0(object);
}

void func_00306438(void) {

}

void func_00306440(void) {

}

/* Assembly between the functions: func_00306448 (240 bytes), func_00306538 (336 bytes), func_00306688 (216 bytes) */

void func_00306760(void) {
    func_003063A8(1, 0xFFFF);
}

void func_00306780(void) {
    func_003063A8(0, 0xFFFF);
}

#else
#include "kynapse/agents/repulsor.hpp"

#ifdef BLACK_NONMATCHING
// Unmatched: SelectDirection is 52 bytes short; normalization and aggregate-copy lifetimes remain unresolved.
namespace KaimAvoidance {
struct EntityMaskDefinition {
    unsigned char unknown00[0x10c];
    unsigned int flags;
};
extern EntityMaskDefinition entityMaskDefinition;
static inline const volatile EntityMaskDefinition& ContactMaskDefinition() {return entityMaskDefinition;}

static inline Vec3 NormalizeContactDirection(Vec3& value,float length) {
    if(length>0.0f) {
        value.x/=length;value.y/=length;value.z/=length;
    } else {value=Vec3(0,0,0);}
    return value;
}
static inline Vec3 ContactScaleRight(const Vec3& v,float k) {return Vec3(k*v.x,k*v.y,k*v.z);}
static inline Vec3 ContactScaleLeft(float k,const Vec3& v) {
    return Vec3(k*v.x,k*v.y,k*v.z);
}
}
namespace KaimAvoidance {
#ifndef STEERING_CONTACT_OUTLINE
inline
#endif
unsigned char Steering::SteeringContactTimes(const Vec3 *velocity, Vec3 displacement, const float *radius, float *first, float *last)
{
  float vx = velocity->x;
  float dx = displacement.x;
  float dy = displacement.y;
  float vz = velocity->z;
  float vy = velocity->y;
  float dz = displacement.z;
  float c = (((dx * dx) + (dy * dy)) + (dz * dz)) - (((*radius) * 1.5f) * ((*radius) * 1.5f));
  float b = 2.0f * (((dx * vx) + (dy * vy)) + (dz * vz));
  float a = ((vx * vx) + (vy * vy)) + (vz * vz);
  if (a == 0.0f)
  {
    if (b != 0.0f)
    {
      *first = (-c) / b;
      *last = *first;
      return 1;
    }
    return 0;
  }
  float discriminant = (b * b) - ((a * 4.0f) * c);
  if (discriminant < 0.0f)
  {
    return 0;
  }
  float root = sqrtf(discriminant);
  float negativeB = -b;
  float denominator = 2.0f * a;
  *first = (negativeB + root) / denominator;
  *last = (negativeB - root) / denominator;
  return 1;
}
}
namespace KaimAvoidance {
unsigned char Steering::PredictContacts(const Vec3* goal) {
    Entity* self=RouteEntity(route);
    if(!self)return 0;
    contactActive=0;contactEntity=0;contactTime=1000000.0f;contactCount=0;
    for(Kaim::ActorIterator it((Kaim::ListNode<Kaim::Actor*>*)world->entities->head);it.node;++it) {
        Entity* other=(Entity*)it.node->value;
        if(other==self)continue;
        // Preserve the native global-mask then entity-flag observation order.
        unsigned mask=ContactMaskDefinition().flags;
        unsigned entityFlags=((const volatile Entity*)other)->flags;
        if(!(entityFlags&mask))continue;
        float otherWidth=other->GetAuthoredProperty(&obstacleWidthKey)->value;
        Vec3 direction=other->position-self->position;
        float distanceSquared=direction.x*direction.x+direction.y*direction.y+direction.z*direction.z;
        if(width*width*detectionDistanceSquared<distanceSquared)continue;
        float distance=sqrtf(distanceSquared);
        if(distance>0.0f)direction=direction/distance;else direction=Vec3(0,0,0);
        if(!(self->forward.Dot(direction)>0.0f || distance<width))continue;
        Vec3 velocity=ContactScaleLeft(other->speed,other->forward)-ContactScaleLeft(self->speed,self->forward);
        float destinationTime=10000.0f;
        Vec3 displacement=other->position-self->position;
        if(self->speed!=0.0f) {
            Vec3 goalOffset=self->position-*goal;
            destinationTime=sqrtf(goalOffset.Squared())/self->speed;
        }
        float combinedRadius=(width+otherWidth)*0.5f;
        float first=10000.0f,last=10000.0f;
        unsigned char admitted=SteeringContactTimes(&velocity,displacement,&combinedRadius,&first,&last);
        float time=first<last?first:last;
        if(!(admitted && time<maximumTime && time<destinationTime && minimumTime<time))continue;
        if((int)contactCount>=25)break;
        contacts[contactCount]=other;contactCount=contactCount+1;
        if(time<contactTime) {
            contactEntity=other;contactActive=1;contactTime=time;
            contactOffset=ContactScaleRight(ContactScaleLeft(time,self->forward),self->speed);
        }
    }
    return 1;
}
}


namespace KaimAvoidance {
static inline float ContactLength(const Vec3& value){return sqrtf(value.Squared());}
static inline float ContactLengthSteps(const Vec3& value){float square=value.Squared();float length=sqrtf(square);return length;}
static inline void ContactAccumulateValue(Vec3& target,Vec3 increment){target.x+=increment.x;target.y+=increment.y;target.z+=increment.z;}
static inline void ContactAccumulateReference(Vec3& target,const Vec3& increment){target.x+=increment.x;target.y+=increment.y;target.z+=increment.z;}
static inline Vec3 SelectUnit0(const Vec3& value){float length=sqrtf(value.Squared());return value/length;}
static inline Vec3 SelectUnit1(const Vec3& value){float length=sqrtf(value.Squared());return value/length;}
static inline Vec3& SelectUnit2(Vec3& value){float length=sqrtf(value.Squared());value.x/=length;value.y/=length;value.z/=length;return value;}
static inline Vec3 SelectScale(float k,const Vec3& v) {return Vec3(k*v.x,k*v.y,k*v.z);}
unsigned char Steering::SelectDirection(const Vec3* goal) {
    Entity* self=RouteEntity(route);
    if(!self)return 0;
    Vec3 mean;
    Vec3 goalVector;
    Vec3 orientation;
    mean=Vec3(0,0,0);
    for(int i=0;i<(int)contactCount;++i) {
        Vec3 offset=self->position-contacts[i]->position;
        ContactAccumulateValue(mean,offset);
    }
    float count=(float)(int)contactCount;mean.x/=count;mean.y/=count;mean.z/=count;
    Vec3 away=SelectUnit0(mean);
    float sign=1.0f;
    goalVector=*goal-self->position;
    Vec3 toward=SelectUnit1(goalVector);
    orientation=toward.Cross(away);
    if(orientation.y<0.0f)sign=-1.0f;
    Vec3 lateral=upVector.Cross(toward);
    Vec3 repel=SelectScale(sign,lateral);
    repel=SelectScale(1.0f-attractionRatio,repel);
    Vec3 attract=SelectScale(attractionRatio,toward);
    Vec3 direction=attract+repel;
    selectedDirection=SelectUnit2(direction);
    return 1;
}
}

#endif

namespace KaimAvoidance {
Steering::Steering(RouteFollower* source)
    : route(source),width(0),radius(0),height(0),target(),targetPosition(0,0,0),orientation(0,0,0),
      frameMarker(0),reservedFrame(0),contactActive(0),contactEntity(0),
      contactOffset(0,0,0),contactTime(0),contactCount(0),selectedDirection(0,0,0),
      graceActive(0),graceDeadline(0),attractionRatio(.5f),graceDuration(.1f),
      minimumTime(-1),maximumTime(10),slowSpeedFactor(.5f),verySlowSpeedFactor(.25f),
      detectionDistanceSquared(25),alignmentThreshold(.7f),slowdownTime(5)
{
    memset(contacts,0,sizeof(contacts));
    if (route) {
        ScalarProperty* p=RouteEntity(route)->GetAuthoredProperty(&obstacleWidthKey);
        if (p) { width=p->value; if (width==0) width=WorldUnits(); } else width=WorldUnits();
        p=RouteEntity(route)->GetAuthoredProperty(&obstacleHeightKey); if (p) height=p->value;
        p=RouteEntity(route)->GetAuthoredProperty(&movementSpeedKey); if (p) target.x=p->value;
    } else width=WorldUnits();
}
unsigned char Steering::Configure(const Property* property) {
    if(!_stricmp(property->GetKey(),"DynDelayTime")) {graceDuration=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"DynRatioAttrRep")) {attractionRatio=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"TimeMinTrigger")) {minimumTime=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"TimeMaxTrigger")) {maximumTime=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"SlowSpeedFactor")) {slowSpeedFactor=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"VerySlowSpeedFactor")) {verySlowSpeedFactor=(float)atof(property->GetText());return 1;}
    if(!_stricmp(property->GetKey(),"DetectionDistanceRatio")) {float value=(float)atof(property->GetText()); detectionDistanceSquared=value*value;return 1;}
    return 0;
}
void Steering::PublishMove(Movement* move) {
    Entity* self=RouteEntity(route);if(!self)return;
    float alignment=self->forward.Dot(selectedDirection);
    float factor;
    if(alignment>alignmentThreshold) {
        if(contactTime<slowdownTime) {move->direction=selectedDirection;move->speed=target.x;return;}
        factor=slowSpeedFactor;
    } else {
        move->direction=selectedDirection;
        if(contactTime<slowdownTime)factor=verySlowSpeedFactor;else factor=slowSpeedFactor;
    }
    move->speed=target.x*factor;
}
void Steering::GenerateMove(const Vec3* goal,Movement* move)
{
    PredictContacts(goal);
    Vec3 originalForward(RouteEntity(route)->forward);
    if (contactActive) {
        SelectDirection(goal); PublishMove(move);
        float deadline=gameTime+graceDuration;
        graceActive=1; graceDeadline=deadline;
    } else if (graceActive==1) {
        PublishMove(move); if (graceDeadline<gameTime) graceActive=0;
    } else GenerateRouteMove(route,move,goal);
}
}

// Native virtual-entry layout is verified; inherited callback identities remain unknown.
struct SteeringVirtualEntry {short adjustment;unsigned short reserved;void (*function)();};
struct __attribute__((aligned(8))) SteeringRegistrationStorage {
    unsigned char unverified00[0x110];SteeringVirtualEntry* classTable;
};
typedef char SteeringVirtualEntrySize[sizeof(SteeringVirtualEntry)==8?1:-1];
typedef char SteeringRegistrationSize[sizeof(SteeringRegistrationStorage)==0x118?1:-1];
extern "C" {
void func_00393ED8();void func_00306400();void func_00393F28();void func_00306448();
void func_003057E8();void func_00306440();void func_00306438();
SteeringVirtualEntry Steering_VirtualEntries[8] __attribute__((section(".data.steering_vtable"),aligned(8))) = {
    {0,0,func_00393ED8},{0,0,func_00306400},{0,0,func_00393F28},{0,0,func_00306448},
    {0,0,func_003057E8},{0,0,func_00306440},{0,0,func_00306438},{0,0,0}
};
SteeringRegistrationStorage Steering_RegistrationStorage __attribute__((aligned(8)));
}

#endif
