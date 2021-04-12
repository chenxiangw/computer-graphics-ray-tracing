#include "viewing_ray.h"

void viewing_ray(
    const Camera &camera,
    const int i,
    const int j,
    const int width,
    const int height,
    Ray &ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////
  double r = camera.width /2;
  double l = -r;
  double nx = width;
  double u = l + camera.width * (j + 0.5) / nx;

  double t = camera.height /2;
  double b = -t;
  double ny = height;
  double v = b + camera.height * (i + 0.5) / ny;

  ray.direction = -camera.d * camera.w + u * camera.u + v * camera.v;
  ray.origin = camera.e;

  return;
}
