#include "color.h"
#include "interval.h"

namespace rt::color {

void writeColor(std::ostream &out, const Color &color) {
  auto r = color.x();
  auto g = color.y();
  auto b = color.z();

  static const Interval intensity(0.0, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
} // namespace rt::color