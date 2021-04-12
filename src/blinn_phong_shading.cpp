#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <float.h>

Eigen::Vector3d blinn_phong_shading(
    const Ray &ray,
    const int &hit_id,
    const double &t,
    const Eigen::Vector3d &n,
    const std::vector<std::shared_ptr<Object>> &objects,
    const std::vector<std::shared_ptr<Light>> &lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // return Eigen::Vector3d(0,0,0);
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d L(0, 0, 0);
  Eigen::Vector3d Ia(0.1, 0.1, 0.1);
  Eigen::Vector3d p = ray.origin + t * ray.direction;

  Eigen::Vector3d ambient = ((objects[hit_id]->material->ka).array() * Ia.array()).matrix();
  L += ambient;

  for (auto &light : lights)
  {
    Eigen::Vector3d l;
    double max_t;
    light->direction(p, l, max_t);
    Ray ray_pl = {p, l};
    int hit_id_pl;
    double t_pl;
    Eigen::Vector3d n_pl;
    bool first_hitted = first_hit(ray_pl, DBL_EPSILON, max_t, objects, hit_id_pl, t_pl, n_pl);

    if (!first_hitted)
    {
      double cosnl = std::max(0.0, n.dot(l));
      Eigen::Vector3d lambertian = ((objects[hit_id]->material->kd).array() * light->I.array()).matrix() * cosnl;
      L += lambertian;

      Eigen::Vector3d h = (l - ray.direction.normalized()).normalized();
      double cosnh = std::max(0.0, n.dot(h));
      Eigen::Vector3d phong = ((objects[hit_id]->material->ks).array() * light->I.array()).matrix() * pow(cosnh, objects[hit_id]->material->phong_exponent);
      L += phong;
    }
  }

  return L;
}
