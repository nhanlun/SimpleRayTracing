cmake_minimum_required(VERSION 3.22)

project(ray_tracing)

set(CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(main main.cpp
    camera.cpp
    color.cpp
    hittable.cpp
    hittableList.cpp
    interval.cpp
    sphere.cpp
    utils.cpp
)