#include <iostream>
#include <memory>

#include "camera.h"
#include "hittableList.h"
#include "sphere.h"
#include "vec3.h"

int main() {

  rt::HittableList world;
  world.add(std::make_shared<rt::Sphere>(rt::Point3(0, 0, -1), 0.5));
  world.add(std::make_shared<rt::Sphere>(rt::Point3(0, -100.5, -1), 100));

  rt::Camera camera;
  camera.render(world);
  return 0;
}