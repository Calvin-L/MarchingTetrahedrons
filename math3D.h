#ifndef MATH3D_H
#define MATH3D_H

struct Point3D {
    float x, y, z, value;
};

struct Vector3D {
    float x, y, z;
};

void normalize(Vector3D& v);

#endif
