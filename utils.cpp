#include "utils.h"

#include <random>

namespace rt::utils {

auto randomDouble() -> double {
  static thread_local std::uniform_real_distribution<double> distribution(0.0,
                                                                          1.0);
  static thread_local std::mt19937 generator(std::random_device{}());
  return distribution(generator);
}

auto randomDouble(double min, double max) -> double {
  return min + (max - min) * randomDouble();
}
} // namespace rt::utils