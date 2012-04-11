//
//  Decimator.h
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#ifndef DECIMATOR_H
#define DECIMATOR_H

#include <cstdlib>
#include "Isosurface.h"

void decimate(const Isosurface& surface,
              float xMin, float xMax,
              float yMin, float yMax,
              float zMin, float zMax,
              float isolevel,
              size_t resolution);

#endif
