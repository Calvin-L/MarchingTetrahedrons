//
//  Sphere.cpp
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#include "Sphere.h"
#include <cmath>

float Sphere::valueAt(float x, float y, float z) const
{
    return sqrtf(x*x + y*y + z*z);
}

Vector3D Sphere::gradientAt(float x, float y, float z) const
{
    Vector3D grad = { x, y, z };
    normalize(grad);
    return grad;
}
