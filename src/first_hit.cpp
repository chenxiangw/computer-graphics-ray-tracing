#include "first_hit.h"

bool first_hit(
    const Ray &ray,
    const double min_t,
    const double max_t,
    const std::vector<std::shared_ptr<Object>> &objects,
    int &hit_id,
    double &t,
    Eigen::Vector3d &n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // return false;
  ////////////////////////////////////////////////////////////////////////////
  t = std::numeric_limits<double>::infinity();
  bool intersected = false;
  for (size_t i = 0; i < objects.size(); i++)
  {
    double t_cur;
    Eigen::Vector3d n_cur;
    bool intersected_cur = objects[i]->intersect(ray, min_t, t_cur, n_cur);
    if (intersected_cur && (t_cur < max_t) && (t_cur < t))
    {
      intersected = true;
      t = t_cur;
      n = n_cur;
      hit_id = i;
    }
  }
  return intersected;
}
