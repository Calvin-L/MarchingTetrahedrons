//
//  Isosurface.cpp
//  VolumeRenderer
//
//  Created by Calvin Loncaric on 4/11/12.
//

#include "Isosurface.h"

vector Isosurface::gradientAt(float x, float y, float z) const
{
    const float epsilon = 0.0001;
    
    float dx = valueAt(x + epsilon, y, z) - valueAt(x - epsilon, y, z);
    float dy = valueAt(x, y + epsilon, z) - valueAt(x, y - epsilon, z);
    float dz = valueAt(x, y, z + epsilon) - valueAt(x, y, z - epsilon);
    
    vector result = { dx, dy, dz };
    normalize(result);
    return result;
}

