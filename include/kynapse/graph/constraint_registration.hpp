#ifndef BLACK_GRAPH_CONSTRAINT_REGISTRATION_HPP
#define BLACK_GRAPH_CONSTRAINT_REGISTRATION_HPP

#include "kynapse/compat.hpp"
// Registration payload and end-position vptr are verified by this TU's exact
// dispatcher. Factory result types are scoped views; their bodies remain separate.
// HeuristicMeta follows RTTI-confirmed CHeuristicClass inheritance.
inline void *operator new(unsigned int,void *p){return p;}
namespace ConstraintRegistration {
struct Constraint;
struct Heuristic;
typedef Constraint *(*ConstraintFactory)();
typedef Heuristic *(*HeuristicFactory)();
struct ConstraintMeta {
 int index;ConstraintFactory factory;char name[256];int attributes;unsigned int mask;
 virtual ~ConstraintMeta() {}
 ConstraintMeta(const char*,ConstraintFactory,ConstraintMeta*) __asm__("func_002E51D8");
};
struct HeuristicMetaBase {
 int index;HeuristicFactory factory;char name[256];int attributes;unsigned int mask;
 virtual ~HeuristicMetaBase(){}
 HeuristicMetaBase(const char*,HeuristicFactory,int,unsigned char,unsigned char) __asm__("func_00390818");
};
struct HeuristicMeta:HeuristicMetaBase {
 HeuristicMeta(const char*n,HeuristicFactory f):HeuristicMetaBase(n,f,0,0,0){}
 virtual ~HeuristicMeta(){}
};
extern ConstraintMeta ConstraintClass,ShortestClass,StealthClass,ConeClass,FleeClass,SphereClass;
extern HeuristicMeta EuclidianClass,ZeroClass,PathCostClass;
extern Constraint *Shortest() __asm__("func_002F0E80");
extern Constraint *Stealth() __asm__("func_002F0EE8");
extern Constraint *Cone() __asm__("func_002F12C0");
extern Constraint *Flee() __asm__("func_002F15E0");
extern Constraint *Sphere() __asm__("func_002F1B58");
extern Heuristic *Euclidian() __asm__("func_002F1D70");
extern Heuristic *Zero() __asm__("func_002F1DD8");
extern Heuristic *PathCost() __asm__("func_002F1E40");
typedef char ConstraintMetaSize[sizeof(ConstraintMeta)==0x114?1:-1];
typedef char HeuristicMetaSize[sizeof(HeuristicMeta)==0x114?1:-1];
void Register(int initialize,int priority);
}
#endif
