#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
  HittableList() = default;

  void add(std::shared_ptr<Hittable> object) {
    objects_.push_back(std::move(object));
  }

  void clear() { objects_.clear(); }

  auto hit(const Ray &ray,
           const Interval &rayT) const -> std::optional<HitRecord> override;

private:
  std::vector<std::shared_ptr<Hittable>> objects_;
};