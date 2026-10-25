#include "include_asm.h"

#include "kynapse/graph/pathfinder.hpp"
namespace Kaim {
extern "C" long func_0035E730(const char*);
extern "C" float func_00291C68(long);

static inline float ParseFloat(const char *s){return func_00291C68(func_0035E730(s));}
static inline float Kaim_WorldUnit(){return gWorldScale?gWorldScale->unit:0.0f;}
static inline float Degrees_WrapUnsigned(float v){if(v>360.0f)v-=360.0f;else if(v<0.0f)v+=360.0f;return v;}
static inline bool Kaim_IsHiddenName(ChildBuffers* p){if(p){if(!p->GetSecond())return false;if(*p->GetSecond()=='_')return true;}return false;}
extern "C" void *func_00393A18(const char*);
extern "C" void *func_00393AC0(const char*);
extern "C" void *func_00393B68(const char*);
extern "C" void *func_00393C10(const char*);


void CPathFinder::Reset()
{
    route.Clear();
    activated = false;
    searchOk = false;
    startNode = 0;
    goalNode = 0;
    waypoint = -1;
    savedStart = 0;
    savedGoal = 0;
    restartSearch = false;
    turnState = 0;
    previous = controller->actor->position;
    target = previous;
    ControlChannel* channel = speedChannel;
    if (channel || (channel = speedChannelAlt) != 0)
        ResetChannel(channel, 0, true);
    channel = yawChannel;
    if (channel || (channel = turnChannel) != 0)
        ResetChannel(channel, 0, true);
    channel = verticalChannel;
    if (channel)
        ResetChannel(channel, 0, true);
    if (policy)
        policy->Reset();
}
bool CPathFinder::SetGraphByName(const char* name)
{
    GraphRegistry* registry = gEngineHandle->FindByClass(&gGraphRegistryClass);
    if (!registry)
        return false;
    int id = registry->IdByName(name);
    if (id == 0)
        return false;
    graph = (NavigationGraph*)id;
    if (converter) {
        if (!converter->NameToId(name, &graphId))
            graphId = -1;
    } else {
        graphId = -1;
    }
    routeTable = (RouteTable*)registry->Find(id, &gRouteTableClass);
    looseGraph = (NavigationGraph*)registry->Find(id, &gLooseGraphClass);
    for (unsigned int i = 0; i < agentCount; ++i) {
        if (agentList[i])
            agentList[i]->SetGraph(graph);
    }
    for (unsigned int i = 0; i < serviceCount; ++i) {
        if (serviceList[i])
            serviceList[i]->SetGraph(graph);
    }
    return true;
}
void CPathFinder::UpdateProgress()
{
    if (!flag198) {
        if (GetNameTables()->Raise(slotIndex, controller->actor)) {
            float length = position.DistanceFrom(previous);
            if (segmentLength < 0.0f || segmentLength * 0.95f < length) {
                flag198 = true;
                GetNameTables()->Restart(slotIndex, controller->actor);
            }
            segmentLength = length;
        }
    }
}

struct PathRegistry {void *items[256];int count;};
extern "C" PathRegistry *func_00390168();
extern "C" void *func_002EC058(void*,const void*);
extern "C" void func_003053F0(float,void*);
extern "C" void func_002F5A40(void*,void*,void*,void*);
extern const Vec3f pathOrigin __asm__("D_004514F8");
extern char pathManagerClass __asm__("D_004525B8");
CPathFinder::CPathFinder(void *brain):IPathFinder(brain)
{
 activated=true;waypoint=(unsigned int)-1;restartSearch=false;searchPaused=false;
 routeTable=0;looseGraph=0;hold=false;searchOk=false;goalNode=0;startNode=0;
 pendingTarget=pathOrigin;target=pathOrigin;previous=pathOrigin;turnState=0;savedTarget=pathOrigin;savedStart=0;savedGoal=0;
 if(serviceCount)records=new SearchRecord[serviceCount];else records=0;
 unknown1c=0;agentCount=func_00390168()->count;
 if(!agentCount)agentList=0;else{agentList=(AgentObject**)Allocate(agentCount*4);for(unsigned int i=0;i<agentCount;++i)agentList[i]=0;}
 lastProbe=pathOrigin;segmentLength=-1.0f;policy=0;
}


extern "C" NavigationGraph::NodeRecord *func_0038F2B0(const EdgeRef*);
extern "C" NavigationGraph::NodeRecord *func_0038F2F0(const EdgeRef*);
inline float EdgeRef::GetAuthoredLength()const
{
 SegmentGraph*owner=(SegmentGraph*)graph;
 if(this==(EdgeRef*)&owner->syntheticIndex)return owner->syntheticLength;
 if(!owner->edgeLengths){const float*a=(const float*)((char*)func_0038F2B0(this)+4);const float*b=(const float*)((char*)func_0038F2F0(this)+4);float dx=b[0]-a[0],dz=b[2]-a[2],dy=b[1]-a[1];return sqrtf(dz*dz+dx*dx+dy*dy);}return owner->edgeLengths[index];
}
unsigned char CPathFinder_IsAtGoal(CPathFinder*self){float d=sqrtf(self->lateralDelta.HorizontalSquared());if(d<self->heightRadiusA && fabsf(self->lateralDelta.y)<self->radius)return 1;return 0;}
extern "C" unsigned char func_002E27F8(float,const float*,const float*,Actor*,int);
void CPathFinder_BeginSegment(CPathFinder*self)
{
 self->segmentLength=self->position.DistanceFrom(self->previous);
 GetNameTables()->Store(self->slotIndex,self->controller->actor);
 self->flag198=false;
}


struct ServiceClass {int index;unsigned char unknown04[0x104];ServiceClass*parent;};
extern ServiceClass allowedServiceClass __asm__("D_00451778");
extern "C" void func_002E5218(CPathFinder*,const void*);
inline bool ServiceIsA(const ServiceClass*want,const ServiceClass*info){do{if(want==info)return true;info=info->parent;}while(info);return false;}

}

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: remaining class-call context, lifetime or scheduling differences.
CPathFinder::~CPathFinder()
{
 void *listeners=func_002EC058(gWorldScale,&pathManagerClass);
 if(listeners)func_002F5A40(listeners,(void*)func_003053F0,this,controller->actor);
 delete[] records;
 if(agentList){for(unsigned int i=0;i<agentCount;++i){if(agentList[i])delete agentList[i];}D_003C87E0(agentList);}
 delete policy;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FEFB0);
#endif
#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char CPathFinder::Initialize(ChildBuffers* definition)
{
    if (!definition)
        return 0;
    simpleMove = CPathFinder_GenerateMove;
    complexMove = CPathFinder_GenerateMove;
    stopCondition = (StopFn)CPathFinder_IsAtGoal;
    collectNode = CPathFinder_CollectNode;
    canGo = (GuardFn)Kaim_AlwaysTrue;
    moveModeCheck = (GuardFn)Kaim_AlwaysTrue;
    nextSubgoal = (SubgoalFn)CPathFinder_AdvanceSubgoal;
    InstallService(&gRouteTypeKey);
    SetGraphType(&gGraphTypeKey);
    distMinNewGoal = gWorldScale->unit * 0.5f;
    heightRadiusA = gWorldScale->unit * 0.75f;
    heightRadiusB = gWorldScale->unit * 0.75f;
    arrivalRadius = gWorldScale->unit;
    finalRadius = gWorldScale->unit * 3.0f;
    radius = gWorldScale->unit;
    maxDeltaAngle = 359.0f;
    maxYawSpeed = 360.0f;
    unknown4cLimit = 1;
    distSubgoalMax = gWorldScale->unit * 100.0f;
    widthRatio = 1.0f;
    holeHeight = gWorldScale->unit * 0.5f;
    corridorWidth = gWorldScale ? gWorldScale->unit : 0.0f;
    cpuPrudence = 0.2f;
    avoidCpuPeaks = false;
    unknownB4 = true;
    updateTorsoRotate = false;
    yawSmoothing = false;
    graph = 0;
    converter = gClassRegistry->FindConverter(&gConverterClass);
    ChildBuffers* disable = definition->FindBySecond("DisableDA");
    bool createAvoidance = true;
    if (disable) {
        const char* value = disable->GetValue();
        if (value) {
            if (!_stricmp(value, "1"))
                createAvoidance = false;
            else
                _stricmp(value, "0");
        }
    }
    if (createAvoidance) {
        ChildBuffers* classEntry = definition->FindBySecond("DynamicAvoidanceClass");
        if(classEntry){
         const char*className=classEntry->GetValue();
         if(className){AvoidanceFactory*factory=AIAvoidance_FindClass(className);if(factory)policy=(MovePolicy*)factory->create(this);else policy=(MovePolicy*)new PathAvoidance(this);}
         else policy=(MovePolicy*)new PathAvoidance(this);
        }else policy=(MovePolicy*)new PathAvoidance(this);
    }
    if (!ConfigureAll(definition))
        return 0;
    speeds = (SpeedTable*)controller->actor->GetAuthoredProperty(&gForwardKey);
    radiusHolder = (RadiusHolder*)controller->actor->GetAuthoredProperty(&gHeightKey2);
    heightFlag = (HeightFlag*)controller->actor->GetAuthoredProperty(&gHeightFlagKey);
    yawChannel = func_002DFE08(world,&gBankA);
    turnChannel = func_002DFE08(world,&gBankB);
    speedChannel = func_002DFE08(world,&gBankC);
    speedChannelAlt = func_002DFE08(world,&gBankD);
    verticalChannel = func_002DFE08(world,&gBankE);
    if (yawChannel) {
        yawChannel->value = 0;
        yawChannel->dirty = true;
    }
    if (turnChannel) {
        turnChannel->value = 0;
        turnChannel->dirty = true;
    }
    if (speedChannel) {
        speedChannel->value = 0;
        speedChannel->dirty = true;
    }
    if (speedChannelAlt) {
        speedChannelAlt->value = 0;
        speedChannelAlt->dirty = true;
    }
    if (verticalChannel) {
        verticalChannel->value = 0;
        verticalChannel->dirty = true;
    }
    ParameterTables* tables = GetNameTables();
    slotIndex = tables->FindNameA("CPathFinder::FindNextMove::CheckAccident");
    searchSlotIndex = tables->FindNameB("CPathFinder::FindNextMove::ASTAR");
    goalSlotIndex = tables->FindNameA("CPathFinder::FindNextMove::NewSubGoal");
    turnSlotIndex = tables->FindNameA("CPathFinder::FindNextMove::Goto");
    if (Bind1() && Bind2() && Bind3() && Bind4() && Bind5()) {
        if (!route.capacity)
            ((RouteBlock*)((char*)this + 0x6c))->SetMaxPathSize(0x32);
        ListenerRegistry* listeners = gClassRegistry->FindListeners(&gListenerClass2);
        if (listeners)
            listeners->Add(CPathFinder_OnActorEvent, this, controller->actor);
        return 1;
    }
    return 0;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FF250);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FF890);
