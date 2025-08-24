#pragma once

#include "color.h"
#include "hittable.h"
#include "ray.h"

namespace rt::diffused_methods {

class DiffusedMethod {
public:
  virtual auto getRayColor(const Ray &ray, int depth,
                           const Hittable &world) -> color::Color = 0;
};

class UniformDiffused : public DiffusedMethod {
public:
  auto getRayColor(const Ray &ray, int depth,
                   const Hittable &world) -> color::Color override;
};

class LambertianDiffused : public DiffusedMethod {
public:
  auto getRayColor(const Ray &ray, int depth,
                   const Hittable &world) -> color::Color override;
};

} // namespace rt::diffused_methods