//
//  common.h
//  MarchingCubes
//
//  Created by Calvin Loncaric on 6/26/11.
//

#ifndef COMMON_H
#define COMMON_H

/************************************************************************/

/* Windows OS detection */
#if defined(_WIN32) || defined(__WIN32__)
# ifndef OS_WIN32
#  define OS_WIN32
# endif
#endif
#if defined(_WIN64)
# ifndef OS_WIN64
#  define OS_WIN64
# endif
#endif
#if defined(_WINDOWS) || defined(OS_WIN32) || defined(OS_WIN64)
# ifndef OS_WINDOWS
#  define OS_WINDOWS
# endif
#endif

/* Mac OS detection */
#ifdef __APPLE__
# ifndef OS_MAC
#  define OS_MAC
# endif
#endif

/************************************************************************/

/*
 * GLUT header file location
 */
#ifdef OS_MAC
#define GLUT_INCLUDE <GLUT/glut.h>
#else
#define GLUT_INCLUDE <GL/glut.h>
#endif

#endif
