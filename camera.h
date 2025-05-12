#pragma once

#include "hittable.h"
#include "ray.h"

class Camera {
public:
  void render(const Hittable &world);

private:
  double aspectRatio_ = 16.0 / 9.0;
  int imageWidth_ = 400;
  int imageHeight_;
  Point3 center_;
  Point3 pixel00Location_;
  Vec3 pixelDeltaU_;
  Vec3 pixelDeltaV_;

  void initialize();
  auto getRayColor(const Ray &ray, const Hittable &world) -> Color;
};