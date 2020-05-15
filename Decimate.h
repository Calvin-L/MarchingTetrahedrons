#ifndef DECIMATOR_H
#define DECIMATOR_H

#include <cstddef> // std::size_t
#include "Isosurface.h"

//
// decimate
//
// Draws a bunch of GL_TRIANGLES (with correct normals and vertex order)
// in order to render the given surface at the given isolevel.
//

void decimate(const Isosurface& surface,
              float xMin, float xMax,
              float yMin, float yMax,
              float zMin, float zMax,
              float isolevel,
              std::size_t resolution);

#endif
