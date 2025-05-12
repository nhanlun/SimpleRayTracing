
#include <iostream>

#include "camera.h"

namespace {

void writeColor(std::ostream &out, const Color &color) {
  auto r = color.x();
  auto g = color.y();
  auto b = color.z();

  int rbyte = int(255.999 * r);
  int gbyte = int(255.999 * g);
  int bbyte = int(255.999 * b);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
} // namespace

void Camera::render(const Hittable &world) {
  initialize();

  std::cout << "P3\n"
            << imageWidth_ << ' ' << imageHeight_ << '\n'
            << 255 << '\n';
  for (int i = 0; i < imageHeight_; ++i) {
    std::clog << "Scanlines remaining: " << (imageHeight_ - i) << '\n';
    for (int j = 0; j < imageWidth_; ++j) {
      auto pixelCenter = pixel00Location_ + i * pixelDeltaV_ + j * pixelDeltaU_;
      auto rayDirection = pixelCenter - center_;
      Ray ray{center_, rayDirection};
      auto rayColor = getRayColor(ray, world);
      writeColor(std::cout, rayColor);
    }
  }
  std::clog << "done\n";
}

void Camera::initialize() {
  imageHeight_ = std::max(int(imageWidth_ / aspectRatio_), 1);
  auto viewportHeight = 2.0;
  auto viewportWidth = viewportHeight / (double)imageHeight_ * imageWidth_;
  auto focalLength = 1.0;

  center_ = Point3(0, 0, 0);
  auto viewportU = Vec3(viewportWidth, 0, 0);
  auto viewportV = Vec3(0, -viewportHeight, 0);

  pixelDeltaU_ = viewportU / imageWidth_;
  pixelDeltaV_ = viewportV / imageHeight_;
  auto viewportUpperLeft =
      center_ - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
  pixel00Location_ = viewportUpperLeft + 0.5 * (pixelDeltaU_ + pixelDeltaV_);
}

auto Camera::getRayColor(const Ray &ray, const Hittable &world) -> Color {
  if (auto hitRecord = world.hit(ray, {0.0, kInfinity})) {
    return 0.5 * Color(hitRecord->normal + Color(1, 1, 1));
  }

  Vec3 unitDirection = ray.direction().toUnitVector();
  auto a = 0.5 * (unitDirection.y() + 1);
  return (1 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}