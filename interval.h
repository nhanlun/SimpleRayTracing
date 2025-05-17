#pragma once

#include "constants.h"

namespace rt {

class Interval {
public:
  double min, max;
  Interval(double min, double max) : min(min), max(max) {}
  Interval() : min(-kInfinity), max(kInfinity) {}
  auto size() const -> double { return max - min; }
  auto contains(double t) const -> bool { return t >= min && t <= max; }
  auto surrounds(double t) const -> bool { return t > min && t < max; }
  auto clamp(double t) const -> double;

  static const Interval empty;
  static const Interval universe;
};
} // namespace rt