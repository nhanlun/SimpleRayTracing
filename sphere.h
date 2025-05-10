#pragma once

#include "hittable.h"

class Sphere : public Hittable {
public:
  Sphere(Point3 center, double radius);
  auto hit(const Ray &ray, double rayTMin,
           double rayTMax) const -> std::optional<HitRecord> override;

private:
  Point3 center_;
  double radius_;
};