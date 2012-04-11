//
//  math3D.h
//  VolumeRenderer
//
//  Created by Calvin Loncaric on 6/26/11.
//

#ifndef MATH3D_H
#define MATH3D_H

struct point {
    float x, y, z, value;
};

struct vector {
    float x, y, z;
};

void normalize(vector& v);

#endif
