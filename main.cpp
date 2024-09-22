#include <iostream>

#include "ray.h"
#include "vec3.h"

Color getRayColor(const Ray &ray) {
  Vec3 unitDirection = ray.direction().toUnitVector();
  auto a = 0.5 * (unitDirection.y() + 1);
  return (1 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

void writeColor(std::ostream &out, const Color &color) {
  auto r = color.x();
  auto g = color.y();
  auto b = color.z();

  int rbyte = int(255.999 * r);
  int gbyte = int(255.999 * g);
  int bbyte = int(255.999 * b);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

int main() {
  double ratio = 16.0 / 9.0;
  int width = 400;
  int height = std::max(int(width / ratio), 1);

  auto focalLength = 1.0;
  auto viewportHeight = 2.0;
  auto viewportWidth = viewportHeight / height * width;
  auto cameraCenter = Point3(0, 0, 0);

  auto viewportU = Vec3(viewportWidth, 0, 0);
  auto viewportV = Vec3(0, -viewportHeight, 0);

  auto pixelDeltaU = viewportU / viewportWidth;
  auto pixelDeltaV = viewportV / viewportHeight;

  auto viewportUpperLeft =
      cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
  auto pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

  std::cout << "P3\n" << width << ' ' << height << '\n' << 255 << '\n';
  for (int i = 0; i < height; ++i) {
    std::clog << "Scanlines remaining: " << (height - i) << '\n';
    for (int j = 0; j < width; ++j) {
      auto pixelCenter = pixel00Location + i * pixelDeltaV + j * pixelDeltaU;
      auto rayDirection = pixelCenter - cameraCenter;
      Ray ray{cameraCenter, rayDirection};
      auto rayColor = getRayColor(ray);
      writeColor(std::cout, rayColor);
    }
  }
  std::clog << "done\n";
  return 0;
}