
#include <iostream>

#include "camera.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

namespace rt {
void Camera::render(const Hittable &world) {
  initialize();

  std::cout << "P3\n"
            << imageWidth_ << ' ' << imageHeight_ << '\n'
            << 255 << '\n';
  for (int i = 0; i < imageHeight_; ++i) {
    std::clog << "Scanlines remaining: " << (imageHeight_ - i) << '\n';
    for (int j = 0; j < imageWidth_; ++j) {
      Color pixelColor(0, 0, 0);
      for (int sample = 0; sample < samplesPerPixel_; ++sample) {
        Ray ray = getRay(j, i);
        pixelColor += getRayColor(ray, maxDepth_, world);
      }
      color::writeColor(std::cout, pixelColor * pixelSampleScale_);
    }
  }
  std::clog << "done\n";
}

void Camera::initialize() {
  imageHeight_ = std::max(int(imageWidth_ / aspectRatio_), 1);
  auto viewportHeight = 2.0;
  auto viewportWidth = viewportHeight / (double)imageHeight_ * imageWidth_;
  auto focalLength = 1.0;

  pixelSampleScale_ = 1.0 / samplesPerPixel_;

  center_ = Point3(0, 0, 0);
  auto viewportU = Vec3(viewportWidth, 0, 0);
  auto viewportV = Vec3(0, -viewportHeight, 0);

  pixelDeltaU_ = viewportU / imageWidth_;
  pixelDeltaV_ = viewportV / imageHeight_;
  auto viewportUpperLeft =
      center_ - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
  pixel00Location_ = viewportUpperLeft + 0.5 * (pixelDeltaU_ + pixelDeltaV_);
}

auto Camera::getRay(int i, int j) const -> Ray {
  auto offset = sampleSquare();
  auto pixel = pixel00Location_ + (i + offset.x()) * pixelDeltaU_ +
               (j + offset.y()) * pixelDeltaV_;

  return Ray(center_, pixel - center_);
}

auto Camera::sampleSquare() const -> Vec3 {
  return Vec3(utils::randomDouble() - 0.5, utils::randomDouble() - 0.5, 0);
}

auto Camera::getRayColor(const Ray &ray, int depth,
                         const Hittable &world) -> Color {
  if (depth <= 0) {
    return Color(0, 0, 0); // Return black for max depth
  }
  if (auto hitRecord = world.hit(ray, {0.0001, kInfinity})) {
    auto direction = hitRecord->normal + randomUnitVector();
    return 0.5 * getRayColor(Ray(hitRecord->p, direction), depth - 1, world);
  }

  Vec3 unitDirection = ray.direction().toUnitVector();
  auto a = 0.5 * (unitDirection.y() + 1);
  return (1 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
} // namespace rt