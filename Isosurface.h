//
//  Isosurface.h
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#ifndef ISOSURFACE_H
#define ISOSURFACE_H

#include "math3D.h"

class Isosurface
{

public:
    virtual float valueAt(float x, float y, float z) const = 0;

    // returns a normalized vector
    virtual Vector3D gradientAt(float x, float y, float z) const;

};

#endif
