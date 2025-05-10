#pragma once

#include "ray.h"
#include "vec3.h"

#include <optional>

struct HitRecord {
  Point3 p;
  Vec3 normal;
  double t;
  bool frontFace;

  void setFaceNormal(const Ray &r, const Vec3 &outwardNormal);
};

class Hittable {
public:
  virtual ~Hittable() = default;
  virtual auto hit(const Ray &ray, double rayTMin,
                   double rayTMax) const -> std::optional<HitRecord> = 0;
};