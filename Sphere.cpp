#include "Sphere.h"
#include <cmath>

float Sphere::valueAt(float x, float y, float z) const
{
    return std::sqrt(x*x + y*y + z*z);
}

Vector3D Sphere::gradientAt(float x, float y, float z) const
{
    Vector3D grad = { x, y, z };
    normalize(grad);
    return grad;
}
