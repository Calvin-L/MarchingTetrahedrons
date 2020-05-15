#ifndef GYROID_H
#define GYROID_H

#include "Isosurface.h"
#include "math3D.h"

class Gyroid : public Isosurface
{

public:
    virtual float valueAt(float x, float y, float z) const;
    virtual Vector3D gradientAt(float x, float y, float z) const;

};

#endif
