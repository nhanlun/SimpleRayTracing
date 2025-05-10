#include "hittableList.h"

auto HittableList::hit(const Ray &ray, double rayTMin,
                       double rayTMax) const -> std::optional<HitRecord> {
  HitRecord tempRec;
  auto closestSoFar = rayTMax;
  std::optional<HitRecord> hitRecord;

  for (const auto &object : objects_) {
    if (auto rec = object->hit(ray, rayTMin, closestSoFar)) {
      closestSoFar = rec->t;
      hitRecord = rec;
    }
  }

  return hitRecord;
}