#include <iostream>
#include <cstddef> // std::size_t
#include <cassert>

#include "common.h"
#include GLUT_INCLUDE

#include "Gyroid.h"
#include "Sphere.h"
#include "Decimate.h"


GLuint preDecimate(const Isosurface& surface,
                   float xMin, float xMax,
                   float yMin, float yMax,
                   float zMin, float zMax,
                   float isolevel,
                   std::size_t resolution)
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    decimate(surface, xMin, xMax, yMin, yMax, zMin, zMax, isolevel, resolution);
    glEndList();
    return list;
}

static float rotX;
static float rotY;

static bool mouseInitialized = false;
static struct { int x, y; } mouse;

static GLuint list;

void render()
{
    glClearColor(0, 0.3, 0.6, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, -1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPushMatrix();
    glRotatef(rotY, 1, 0, 0);
    glRotatef(rotX, 0, 1, 0);
    glutSolidCube(0.15);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotY, 1, 0, 0);
    glRotatef(rotX, 0, 1, 0);
    glScalef(0.1, 0.1, 0.1);
    glCallList(list);
    glPopMatrix();

    glutSwapBuffers();
}

void changeSize(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;
    float ratio = 1.0* w / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45, ratio, 1, 1000);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set up the camera
    gluLookAt(0, 0, -3, 0, 0, 0, 0, 1, 0);
}

void mouseDown(int button, int state, int x, int y)
{
    mouse.x = x;
    mouse.y = y;
    mouseInitialized = true;
}

void mouseDragged(int x, int y)
{
    if (mouseInitialized) {
        float dx = x - mouse.x;
        float dy = y - mouse.y;

        rotX += dx / 10;
        rotY -= dy / 10;
    }

    mouse.x = x;
    mouse.y = y;
    mouseInitialized = true;

    glutPostRedisplay();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Sphere surface;
    Gyroid surface;
    list = preDecimate(surface, -5, 5, -5, 5, -5, 5, -1, 30);
}

int main (int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Volume Rendering");

    init();

    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);
    glutMouseFunc(mouseDown);
    glutMotionFunc(mouseDragged);

    glutMainLoop();
    return 0;
}
