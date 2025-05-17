#pragma once

#include "vec3.h"

namespace rt::color {

using Color = Vec3;

void writeColor(std::ostream &out, const Color &color);
} // namespace rt::color