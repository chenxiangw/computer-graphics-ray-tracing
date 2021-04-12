#include "Sphere.h"
#include "Ray.h"
#include <math.h>

using std::pow;
bool Sphere::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // return false;
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = this->center;
  double delta = pow(d.dot(e-c), 2) - (d.dot(d)) * ((e-c).dot(e-c) - pow(this->radius, 2));
  if (delta < 0)
  {
    return false;
  }
  t = (-d.dot(e - c) - sqrt(delta)) / (d.dot(d));
  if (t < min_t)
  {
    return false;
  }
  n = (e + t * d - c).normalized();
  return true;
}
