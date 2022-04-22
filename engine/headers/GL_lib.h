#ifndef ENGINE_GL_LIB_H
#define ENGINE_GL_LIB_H

#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../utils/point_3d.h"

#endif