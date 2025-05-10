#include <iostream>
#include <memory>

#include "constants.h"
#include "hittable.h"
#include "hittableList.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

/*
sphere equation: (x_c - x)^2 + (y_c - y)^2 + (z_c - z)^2 = r^2
<-> (C - O) . (C - O) = r^2
<-> (O - C) . (O - C) = r^2
<-> (O - (P + at)) . (O - (P + at)) = r^2     # "P" is ray's origin, "a" is
direction
<-> (at + (O - P)) . (at + (O - P)) = r^2
<-> (t^2) * a.a - 2at . (O - P) + (O - P) . (O - P) = r^2
=> quadratic equation with variable "t"
=> we can solve for t
a = a.a
b = 2a . (O - P) / 2 = a . (O - P)
c = (O - P) . (O - P) - r^2

delta' = b^2 - ac
*/
auto hitSphere(const Point3 &center, double radius, const Ray &ray) -> double {
  auto OC = center - ray.origin();
  auto a = ray.direction().lengthSquared();
  auto b = dot(ray.direction(), OC);
  auto c = dot(OC, OC) - radius * radius;
  auto discriminant = b * b - a * c;

  if (discriminant < 0) {
    return -1;
  }
  // temporary choose the result nearer to the camera
  return (b - sqrt(discriminant)) / a;
}

auto getRayColor(const Ray &ray, const Hittable &world) -> Color {
  if (auto hitRecord = world.hit(ray, 0.0, kInfinity)) {
    return 0.5 * Color(hitRecord->normal + Color(1, 1, 1));
  }

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

  HittableList world;
  world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  auto focalLength = 1.0;
  auto viewportHeight = 2.0;
  auto viewportWidth = viewportHeight / height * width;
  auto cameraCenter = Point3(0, 0, 0);

  auto viewportU = Vec3(viewportWidth, 0, 0);
  auto viewportV = Vec3(0, -viewportHeight, 0);

  auto pixelDeltaU = viewportU / width;
  auto pixelDeltaV = viewportV / height;

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
      auto rayColor = getRayColor(ray, world);
      writeColor(std::cout, rayColor);
    }
  }
  std::clog << "done\n";
  return 0;
}