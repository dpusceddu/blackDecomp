#include "kynapse/agents/repulsor.hpp"

namespace KaimAvoidance {
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
