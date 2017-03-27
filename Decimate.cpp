//
//  Decimate.cpp
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#include <cassert>
#include <iostream>
#include <cmath>
#include "common.h"
#include GLUT_INCLUDE
#include "Decimate.h"
#include "Array3D.h"

static inline void drawVert(const Isosurface& surface, const Point3D& p1, const Point3D& p2, float isolevel)
{

    float v1 = p1.value;
    float v2 = p2.value;

    float x, y, z;

    if (v2 == v1) {
        x = (p1.x + p2.x) / 2.0f;
        y = (p1.y + p2.y) / 2.0f;
        z = (p1.z + p2.z) / 2.0f;
    } else {

        /*

         <----+-----+---+----->
              v1    |   v2
                 isolevel


         <----+-----+---+----->
              0     |   1
                  interp

         */


        // interp == 0: vert should be at p1
        // interp == 1: vert should be at p2
        float interp = (isolevel - v1) / (v2 - v1);
        float oneMinusInterp = 1 - interp;

        x = p1.x * oneMinusInterp + p2.x * interp;
        y = p1.y * oneMinusInterp + p2.y * interp;
        z = p1.z * oneMinusInterp + p2.z * interp;
    }

    Vector3D normal = surface.gradientAt(x, y, z);

    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(x, y, z);
}

static void drawTetrahedron(const Isosurface& surface, const Point3D p[4], float isolevel)
{

    /*

     Tetrahedron layout:

           0
           *
          /|
         / |
      3 *-----* 1
         \ | /
          \|/
           *
           2
     */

    unsigned char index = 0;
    for (int i = 0; i < 4; ++i)
        if (p[i].value < isolevel)
            index |= (1 << i);

    switch (index) {

        // we don't do anything if everyone is inside or outside
        case 0x00:
        case 0x0F:
            break;

        // only vert 0 is inside
        case 0x01:
            drawVert(surface, p[0], p[1], isolevel);
            drawVert(surface, p[0], p[3], isolevel);
            drawVert(surface, p[0], p[2], isolevel);
            break;

        // only vert 1 is inside
        case 0x02:
            drawVert(surface, p[1], p[0], isolevel);
            drawVert(surface, p[1], p[2], isolevel);
            drawVert(surface, p[1], p[3], isolevel);
            break;

        // only vert 2 is inside
        case 0x04:
            drawVert(surface, p[2], p[0], isolevel);
            drawVert(surface, p[2], p[3], isolevel);
            drawVert(surface, p[2], p[1], isolevel);
            break;

        // only vert 3 is inside
        case 0x08:
            drawVert(surface, p[3], p[1], isolevel);
            drawVert(surface, p[3], p[2], isolevel);
            drawVert(surface, p[3], p[0], isolevel);
            break;

        // verts 0, 1 are inside
        case 0x03:
            drawVert(surface, p[3], p[0], isolevel);
            drawVert(surface, p[2], p[0], isolevel);
            drawVert(surface, p[1], p[3], isolevel);

            drawVert(surface, p[2], p[0], isolevel);
            drawVert(surface, p[2], p[1], isolevel);
            drawVert(surface, p[1], p[3], isolevel);
            break;

        // verts 0, 2 are inside
        case 0x05:
            drawVert(surface, p[3], p[0], isolevel);
            drawVert(surface, p[1], p[2], isolevel);
            drawVert(surface, p[1], p[0], isolevel);

            drawVert(surface, p[1], p[2], isolevel);
            drawVert(surface, p[3], p[0], isolevel);
            drawVert(surface, p[2], p[3], isolevel);
            break;

        // verts 0, 3 are inside
        case 0x09:
            drawVert(surface, p[0], p[1], isolevel);
            drawVert(surface, p[1], p[3], isolevel);
            drawVert(surface, p[0], p[2], isolevel);

            drawVert(surface, p[1], p[3], isolevel);
            drawVert(surface, p[3], p[2], isolevel);
            drawVert(surface, p[0], p[2], isolevel);
            break;

        // verts 1, 2 are inside
        case 0x06:
            drawVert(surface, p[0], p[1], isolevel);
            drawVert(surface, p[0], p[2], isolevel);
            drawVert(surface, p[1], p[3], isolevel);

            drawVert(surface, p[1], p[3], isolevel);
            drawVert(surface, p[0], p[2], isolevel);
            drawVert(surface, p[3], p[2], isolevel);
            break;

        // verts 2, 3 are inside
        case 0x0C:
            drawVert(surface, p[1], p[3], isolevel);
            drawVert(surface, p[2], p[0], isolevel);
            drawVert(surface, p[3], p[0], isolevel);

            drawVert(surface, p[2], p[0], isolevel);
            drawVert(surface, p[1], p[3], isolevel);
            drawVert(surface, p[2], p[1], isolevel);
            break;

        // verts 1, 3 are inside
        case 0x0A:
            drawVert(surface, p[3], p[0], isolevel);
            drawVert(surface, p[1], p[0], isolevel);
            drawVert(surface, p[1], p[2], isolevel);

            drawVert(surface, p[1], p[2], isolevel);
            drawVert(surface, p[2], p[3], isolevel);
            drawVert(surface, p[3], p[0], isolevel);
            break;

        // verts 0, 1, 2 are inside
        case 0x07:
            drawVert(surface, p[3], p[0], isolevel);
            drawVert(surface, p[3], p[2], isolevel);
            drawVert(surface, p[3], p[1], isolevel);
            break;

        // verts 0, 1, 3 are inside
        case 0x0B:
            drawVert(surface, p[2], p[1], isolevel);
            drawVert(surface, p[2], p[3], isolevel);
            drawVert(surface, p[2], p[0], isolevel);
            break;

        // verts 0, 2, 3 are inside
        case 0x0D:
            drawVert(surface, p[1], p[0], isolevel);
            drawVert(surface, p[1], p[3], isolevel);
            drawVert(surface, p[1], p[2], isolevel);
            break;

        // verts 1, 2, 3 are inside
        case 0x0E:
            drawVert(surface, p[0], p[1], isolevel);
            drawVert(surface, p[0], p[2], isolevel);
            drawVert(surface, p[0], p[3], isolevel);
            break;

        // what is this I don't even
        default:
            assert(false);
    }

}

void decimate(const Isosurface& surface,
              float xMin, float xMax,
              float yMin, float yMax,
              float zMin, float zMax,
              float isolevel,
              size_t resolution) // resolution indicates # of cubes
{

    size_t pointRes = resolution + 1; // indicates the # of points per side

    float xrange = xMax - xMin;
    float yrange = yMax - yMin;
    float zrange = zMax - zMin;

    Array3D<float> grid(pointRes, pointRes, pointRes);

    for (size_t i = 0; i <= resolution; ++i) {
        float x = (float)i/resolution * xrange + xMin;
        for (size_t j = 0; j <= resolution; ++j) {
            float y = (float)j/resolution * yrange + yMin;
            for (size_t k = 0; k <= resolution; ++k) {
                float z = (float)k/resolution * zrange + zMin;
                float value = surface.valueAt(x, y, z);
                grid.set(i, j, k, value);
            }
        }
    }


    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < resolution; ++i) {
        float x1 = (float)i/resolution * xrange + xMin;
        float x2 = (float)(i+1)/resolution * xrange + xMin;
        for (size_t j = 0; j < resolution; ++j) {
            float y1 = (float)j/resolution * yrange + yMin;
            float y2 = (float)(j+1)/resolution * yrange + yMin;
            for (size_t k = 0; k < resolution; ++k) {
                float z1 = (float)k/resolution * zrange + zMin;
                float z2 = (float)(k+1)/resolution * zrange + zMin;

                /*

                 Coordinates:

                      z
                      |
                      |___ y
                      /
                     /
                    x

                 Cube layout:

                    4-------7
                   /|      /|
                  / |     / |
                 5-------6  |
                 |  0----|--3
                 | /     | /
                 |/      |/
                 1-------2


                 Tetrahedrons are:
                     0, 7, 3, 2
                     0, 7, 2, 6
                     0, 4, 6, 7
                     0, 6, 1, 2
                     0, 6, 1, 4
                     5, 6, 1, 4

                 */

                const Point3D v[8] = {
                    {x1, y1, z1, grid.get(i,     j,     k    )},
                    {x2, y1, z1, grid.get(i + 1, j,     k    )},
                    {x2, y2, z1, grid.get(i + 1, j + 1, k    )},
                    {x1, y2, z1, grid.get(i,     j + 1, k    )},
                    {x1, y1, z2, grid.get(i,     j,     k + 1)},
                    {x2, y1, z2, grid.get(i + 1, j,     k + 1)},
                    {x2, y2, z2, grid.get(i + 1, j + 1, k + 1)},
                    {x1, y2, z2, grid.get(i,     j + 1, k + 1)}
                };

                const Point3D tetrahedra[6][4] = {
                    { v[0], v[7], v[3], v[2] },
                    { v[0], v[7], v[2], v[6] },
                    { v[0], v[4], v[7], v[6] },
                    { v[0], v[1], v[6], v[2] },
                    { v[0], v[4], v[6], v[1] },
                    { v[5], v[1], v[6], v[4] }
                };

                for (int t = 0; t < 6; ++t)
                    drawTetrahedron(surface, tetrahedra[t], isolevel);

            }
        }
    }
    glEnd();

}
