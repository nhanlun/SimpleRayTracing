#include "hittable.h"

namespace rt {

void HitRecord::setFaceNormal(const Ray &ray, const Vec3 &outwardNormal) {
  frontFace = dot(ray.direction(), outwardNormal) < 0;
  normal = frontFace ? outwardNormal : -outwardNormal;
}

} // namespace rt
