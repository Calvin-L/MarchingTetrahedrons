#include "Gyroid.h"
#include <cmath>

float Gyroid::valueAt(float x, float y, float z) const
{
    return (std::cos(x) * std::sin(y) + std::cos(y) * std::sin(z) + std::cos(z) * std::sin(x));
}

Vector3D Gyroid::gradientAt(float x, float y, float z) const
{
    float gx = std::cos(x) * std::cos(z) - std::sin(x) * std::sin(y);
    float gy = std::cos(x) * std::cos(y) - std::sin(y) * std::sin(z);
    float gz = std::cos(y) * std::cos(z) - std::sin(x) * std::sin(z);

    Vector3D result = { gx, gy, gz };
    normalize(result);

    return result;
}
