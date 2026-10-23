#include "campaign/graph/constraint_registration.hpp"

namespace ConstraintRegistration {
void Register(int initialize,int priority){
 if(priority==65535){
  if(initialize){
   new(&ConstraintClass)ConstraintMeta("CConstraint",0,0);
   new(&ShortestClass)ConstraintMeta("CConstraintShortestPath",Shortest,&ConstraintClass);
   new(&StealthClass)ConstraintMeta("CConstraintStealthPath",Stealth,&ConstraintClass);
   new(&ConeClass)ConstraintMeta("CConstraintConeVisionStealthPath",Cone,&ConstraintClass);
   new(&FleeClass)ConstraintMeta("CConstraintPointToFleePath",Flee,&ConstraintClass);
   new(&SphereClass)ConstraintMeta("CSphereConstraint",Sphere,&ShortestClass);
   new(&EuclidianClass)HeuristicMeta("CHeuristicEuclidianDistance",Euclidian);
   new(&ZeroClass)HeuristicMeta("CZeroHeuristic",Zero);
   new(&PathCostClass)HeuristicMeta("CPathCostHeuristic",PathCost);
  }else{
   PathCostClass.HeuristicMeta::~HeuristicMeta();ZeroClass.HeuristicMeta::~HeuristicMeta();EuclidianClass.HeuristicMeta::~HeuristicMeta();
   SphereClass.ConstraintMeta::~ConstraintMeta();FleeClass.ConstraintMeta::~ConstraintMeta();ConeClass.ConstraintMeta::~ConstraintMeta();StealthClass.ConstraintMeta::~ConstraintMeta();ShortestClass.ConstraintMeta::~ConstraintMeta();ConstraintClass.ConstraintMeta::~ConstraintMeta();
  }
 }
}
}
