#pragma once

#include "hittable.h"

namespace rt {

class Sphere : public Hittable {
public:
  Sphere(Point3 center, double radius);
  auto hit(const Ray &ray,
           const Interval &rayT) const -> std::optional<HitRecord> override;

private:
  Point3 center_;
  double radius_;
};
} // namespace rt