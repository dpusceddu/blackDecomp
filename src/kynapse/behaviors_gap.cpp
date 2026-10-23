#include "context/behaviors/gap.hpp"

namespace KaimAvoidance {
inline float SquaredDistance(const Vec3& b,const Vec3& a)
{
    float z=a.z-b.z,x=a.x-b.x,y=a.y-b.y;
    return z*z+x*x+y*y;
}
unsigned char Avoidance::DetectStalledProgress()
{
    float first=WorldUnits(),second=WorldUnits();
    if(SquaredDistance(stallAnchor,goal)>first*second) {
        stallAnchor=goal;stallAnchorTime=avoidanceTime;stallDistance=goalDistance;return 0;
    }
    if(goalDistance<stallDistance) {
        stallDistance=goalDistance;stallAnchorTime=avoidanceTime;return 0;
    }
    if(avoidanceTime-stallAnchorTime>stallThreshold) {
        stallEscapeDeadline=avoidanceTime+stallDelay;return 1;
    }
    return 0;
}
void Avoidance::ScoreCandidate(Candidate* candidate,const float* right,const float* middle,const float* left)
{
    Interval* frontier=candidate->frontier;
    float penalty;
    if(frontier->time<goalTime) {
        penalty=candidate->lateral;
        if(frontier->high<penalty) penalty=*right;
        else if(penalty<frontier->low) penalty=*left;
        else penalty=*middle;
    } else {
        penalty=candidate->lateral;
        if(penalty<0) {candidate->cost-=penalty;return;}
    }
    candidate->cost+=penalty;
}

// Unmatched: constructor (1928 B) retains ten allocator-base register differences.
// Unmatched: contact prediction (4640 B), generation (5416 B), selection (1424 B), and update (1600 B) require original aggregate and iterator lifetimes.
// Unmatched: collection (728 B), refresh (380 B), begin-update (876 B), diagram (676 B), scoring (564 B), ranking (568 B), and removal (184 B) differ in helpers and scheduling.
}
