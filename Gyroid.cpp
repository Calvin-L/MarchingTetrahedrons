//
//  Gyroid.cpp
//  VolumeRenderer
//
//  Created by Calvin Loncaric on 6/26/11.
//

#include "Gyroid.h"
#include <cmath>

float Gyroid::valueAt(float x, float y, float z) const
{
    return (cosf(x) * sinf(y) + cosf(y) * sinf(z) + cosf(z) * sinf(x));
}

vector Gyroid::gradientAt(float x, float y, float z) const
{
    return Isosurface::gradientAt(x, y, z);
    float gx = cosf(x) * cosf(z) - sinf(x) * sinf(y);
    float gy = cosf(x) * cosf(y) - sinf(y) * sinf(z);
    float gz = cosf(y) * cosf(z) - sinf(x) * sinf(z);
    
    vector result = { gx, gy, gz };
    normalize(result);
    
    return result;
}
