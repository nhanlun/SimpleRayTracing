#include "diffusedMethods.h"

namespace rt::diffused_methods {

auto UniformDiffused::getRayColor(const Ray &ray, int depth,
                                  const Hittable &world) -> color::Color {
  // Implement uniform diffused color logic here
  if (depth <= 0) {
    return color::Color(0, 0, 0); // Return black for max depth
  }
  if (auto hitRecord = world.hit(ray, {0.0001, kInfinity})) {
    auto direction = hitRecord->normal + randomUnitVector();
    return 0.5 * getRayColor(Ray(hitRecord->p, direction), depth - 1, world);
  }

  Vec3 unitDirection = ray.direction().toUnitVector();
  auto a = 0.5 * (unitDirection.y() + 1);
  return (1 - a) * color::Color(1.0, 1.0, 1.0) +
         a * color::Color(0.5, 0.7, 1.0);
}

auto LambertianDiffused::getRayColor(const Ray &ray, int depth,
                                     const Hittable &world) -> color::Color {
  if (depth <= 0) {
    return color::Color(0, 0, 0); // Return black for max depth
  }
  if (auto hitRecord = world.hit(ray, {0.0001, kInfinity})) {
    auto direction = hitRecord->normal + randomUnitVector();
    return 0.5 * getRayColor(Ray(hitRecord->p, direction), depth - 1, world);
  }

  Vec3 unitDirection = ray.direction().toUnitVector();
  auto a = 0.5 * (unitDirection.y() + 1);
  return (1 - a) * color::Color(1.0, 1.0, 1.0) +
         a * color::Color(0.5, 0.7, 1.0);
}

} // namespace rt::diffused_methods