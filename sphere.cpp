#include "sphere.h"

Sphere::Sphere(Point3 center, double radius)
    : center_(std::move(center)), radius_(std::fmax(0, radius)) {}

auto Sphere::hit(const Ray &ray, double rayTMin,
                 double rayTMax) const -> std::optional<HitRecord> {
  auto OC = center_ - ray.origin();
  auto a = ray.direction().lengthSquared();
  auto b = dot(ray.direction(), OC);
  auto c = dot(OC, OC) - radius_ * radius_;
  auto discriminant = b * b - a * c;

  if (discriminant < 0) {
    return std::nullopt;
  }
  // temporary choose the result nearer to the camera
  auto sqrtd = sqrt(discriminant);
  auto root = (b - sqrtd) / a;
  if (root <= rayTMin or root >= rayTMax) {
    root = (b + sqrtd) / a;
    if (root <= rayTMin or root >= rayTMax) {
      return std::nullopt;
    }
  }

  auto tmp = ray.at(root);
  HitRecord result{.p = tmp, .normal = (tmp - center_) / radius_, .t = root};

  Vec3 outwardNormal = (result.p - center_) / radius_;
  result.setFaceNormal(ray, outwardNormal);

  return result;
}