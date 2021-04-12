#include "Plane.h"
#include "Ray.h"
#include <iostream>
#include <float.h>

bool Plane::intersect(
    const Ray &ray, const double min_t, double &t, Eigen::Vector3d &n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // return false;
  ////////////////////////////////////////////////////////////////////////////
  /*
    t=(a-e)*n/(d*n)
  */
  double d_mutiply_n = ray.direction.dot(this->normal);
  if (fabs(d_mutiply_n) < DBL_EPSILON)
  {
    return false;
  }
  t = (this->point - ray.origin).dot(this->normal) / d_mutiply_n;
  if (t < min_t)
  {
    return false;
  }
  if ((this->normal).dot(ray.origin - this->point) < 0)
  {
    n = -this->normal;
  }
  else
  {
    n = this->normal;
  }
  return true;
}
