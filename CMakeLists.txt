cmake_minimum_required(VERSION 3.8)
project(MarchingTetrahedrons)

add_executable(MarchingTetrahedrons
    common.h
    Array3D.h
    Decimate.h
    Decimate.cpp
    Gyroid.h
    Gyroid.cpp
    Isosurface.h
    Isosurface.cpp
    Sphere.h
    Sphere.cpp
    main.cpp
    math3D.h
    math3D.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(MarchingTetrahedrons PRIVATE
    OpenGL::GL
    GLUT::GLUT)
