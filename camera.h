#pragma once

#include "color.h"
#include "hittable.h"
#include "ray.h"

namespace rt {

class Camera {
public:
  void render(const Hittable &world);

private:
  using Color = color::Color;
  double aspectRatio_ = 16.0 / 9.0;
  int imageWidth_ = 900;
  int imageHeight_;
  Point3 center_;
  Point3 pixel00Location_;
  Vec3 pixelDeltaU_;
  Vec3 pixelDeltaV_;
  int samplesPerPixel_ = 100;
  double pixelSampleScale_;

  void initialize();
  auto getRay(int i, int j) const -> Ray;
  auto sampleSquare() const -> Vec3;
  auto getRayColor(const Ray &ray, const Hittable &world) -> color::Color;
};
} // namespace rt