#include <iostream>
#include <memory>

#include "camera.h"
#include "constants.h"
#include "hittable.h"
#include "hittableList.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

int main() {

  HittableList world;
  world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  Camera camera;
  camera.render(world);
  return 0;
}