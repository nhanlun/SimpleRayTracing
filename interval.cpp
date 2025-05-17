#include "interval.h"

namespace rt {

const Interval Interval::empty = Interval(kInfinity, -kInfinity);
const Interval Interval::universe = Interval(-kInfinity, kInfinity);

auto Interval::clamp(double t) const -> double {
  if (t < min) {
    return min;
  } else if (t > max) {
    return max;
  }
  return t;
}
} // namespace rt