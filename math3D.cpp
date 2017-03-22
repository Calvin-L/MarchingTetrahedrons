//
//  math3D.cpp
//  VolumeRenderer
//
//  Created by Calvin Loncaric on 6/26/11.
//

#include "math3D.h"
#include <cmath>
#include <cassert>

void normalize(Vector3D& v)
{
    float l = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    assert(l > 0);
    v.x /= l;
    v.y /= l;
    v.z /= l;
}
