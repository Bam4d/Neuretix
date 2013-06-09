#ifndef GLOBALS
#define GLOBALS

#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <iostream>			// Header File for file writing
#include <fstream>			// Header File for file writing
#include <string.h>
#include <vector>
#include <cstdlib>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

//mathGL libraries
#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <mgl2/qmathgl.h>
using namespace std;

/* ascii code for the escape key */
#define ESCAPE 27

#include "GLEngine.h"
#include "../CavalCade/CNNGlobals.h"
#include "../NeuroPlasticity/NeuroplasticityGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"
#include "../Structures/Structures.h"

#endif