#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <utility>

namespace rt {

class Ray {
public:
  Ray(Point3 origin, Vec3 dir)
      : origin_(std::move(origin)), dir_(std::move(dir)) {}
  Point3 at(double t) const { return origin_ + dir_ * t; }
  Vec3 direction() const { return dir_; }
  Point3 origin() const { return origin_; }

private:
  Point3 origin_;
  Vec3 dir_;
};

} // namespace rt

#endif