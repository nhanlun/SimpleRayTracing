#include "hittableList.h"

auto HittableList::hit(const Ray &ray,
                       const Interval &rayT) const -> std::optional<HitRecord> {
  HitRecord tempRec;
  auto closestSoFar = rayT.max;
  std::optional<HitRecord> hitRecord;

  for (const auto &object : objects_) {
    if (auto rec = object->hit(ray, {rayT.min, closestSoFar})) {
      closestSoFar = rec->t;
      hitRecord = rec;
    }
  }

  return hitRecord;
}