//
//  Sphere.h
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "Isosurface.h"
#include "math3D.h"

class Sphere : public Isosurface
{

public:
    virtual float valueAt(float x, float y, float z) const;
    virtual Vector3D gradientAt(float x, float y, float z) const;

};

#endif
