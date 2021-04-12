#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <float.h>

#define MAX_REFLECT_RECURSIVE 10

bool raycolor(
    const Ray &ray,
    const double min_t,
    const std::vector<std::shared_ptr<Object>> &objects,
    const std::vector<std::shared_ptr<Light>> &lights,
    const int num_recursive_calls,
    Eigen::Vector3d &rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // rgb = Eigen::Vector3d(0, 0, 0);
  // return false;
  ////////////////////////////////////////////////////////////////////////////
  int cur_num_recursive_calls = num_recursive_calls + 1;
  if (cur_num_recursive_calls > MAX_REFLECT_RECURSIVE)
  {
    return false;
  }

  int hit_id;
  double t;
  Eigen::Vector3d n;
  bool first_hitted = first_hit(ray, min_t, std::numeric_limits<double>::infinity(), objects, hit_id, t, n);
  if (first_hitted)
  {
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

    Eigen::Vector3d p = ray.origin + t * ray.direction;
    Eigen::Vector3d r = reflect(ray.direction.normalized(), n);
    Ray ray_r = {p, r};
    if (fabs((objects[hit_id]->material->km).norm()) > DBL_EPSILON)
    {
      Eigen::Vector3d rgb_r;
      bool hitted = raycolor(ray_r, DBL_EPSILON, objects, lights, cur_num_recursive_calls, rgb_r);
      if (hitted)
      {
        rgb += ((objects[hit_id]->material->km).array() * rgb_r.array()).matrix();
      }
    }

    return true;
  }
  else
  {
    rgb = Eigen::Vector3d(0, 0, 0);
    return false;
  }
}
