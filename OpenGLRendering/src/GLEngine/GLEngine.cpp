/*
 * GLEngine.cpp
 *
 *  Created on: 15 Aug 2013
 *      Author: bam4d
 */

#include <GL/gl.h>	 // Header File For The OpenGL32 Library
#include <GL/glu.h>	 // Header File For The GLu32 Library
#include <GL/glut.h> // Header File For The GLUT Library
#include <unistd.h>
#include "../inc/GLEngine.h"
#include "../inc/Rendering.h"

static PlotPoint cube[] = { { -1.0f, 1.0f, -1.0f, }, //A
		{ 1.0f, 1.0f, -1.0f, }, //B
		{ 1.0f, -1.0f, -1.0f, }, //C
		{ -1.0f, -1.0f, -1.0f, }, //D

		{ -1.0f, 1.0f, 1.0f, }, //E
		{ 1.0f, 1.0f, 1.0f, }, //F
		{ 1.0f, -1.0f, 1.0f, }, //G
		{ -1.0f, -1.0f, 1.0f, }, //H

		{ -1.0f, 1.0f, -1.0f, }, //A
		{ 1.0f, 1.0f, -1.0f, }, //B
		{ 1.0f, 1.0f, 1.0f, }, //F
		{ -1.0f, 1.0f, 1.0f, }, //E

		{ -1.0f, 1.0f, -1.0f, }, //A
		{ -1.0f, 1.0f, 1.0f, }, //E
		{ -1.0f, -1.0f, 1.0f, }, //H
		{ -1.0f, -1.0f, -1.0f, }, //D

		{ 1.0f, 1.0f, -1.0f, }, //B
		{ 1.0f, 1.0f, 1.0f, }, //F
		{ 1.0f, -1.0f, 1.0f, }, //G
		{ 1.0f, -1.0f, -1.0f, }, //C

		{ -1.0f, -1.0f, -1.0f, }, //D
		{ 1.0f, -1.0f, -1.0f, }, //C
		{ 1.0f, -1.0f, 1.0f, }, //G
		{ -1.0f, -1.0f, 1.0f, } //H
};

GLEngine::GLEngine(void) {
	pmx = 0;
	pmy = 0;
	zDelta = 0;
	windowposx = 0;
	windowposy = 0;
	windowposz = 0;
	windowrotx = 0;
	windowroty = 0;
	fullscreen = false;
}

void GLEngine::ResetGLScene(void) {
	nmx = 0;
	nmy = 0;
	zDelta = 0;
	pmx = 0;
	pmy = 0;
	windowposx = 0;
	windowposy = 0;
	windowposz = 0;
	windowrotx = 0;
	windowroty = 0;
}

GLEngine::~GLEngine(void) {
}

void GLEngine::beginRender() {
	//need to select the window here
	glutSetWindow(window);
	Clear();
	TranslateP();
}

void GLEngine::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();	// Reset The Current Modelview Matrix
}

void GLEngine::swapBuffer() {
	glutSwapBuffers(); //swap the buffers of GLWindow
}

void GLEngine::ReSizeGLScene(int width, int height)	// Resize And Initialize The GL Window
{

	sc_width = width;
	sc_height = height;

	glViewport(0, 0, width, height);			// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);				// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat) sc_width / (GLfloat) sc_height, 0.1f,
			300.0f);

	glMatrixMode(GL_MODELVIEW);					// Select The Modelview Matrix
	glLoadIdentity();							// Reset The Modelview Matrix
}

void GLEngine::TranslateP() {
	glTranslatef(0, 0, windowposz - 10.0f);
	glRotatef(windowrotx, 0, 1.0f, 0);
	glRotatef(windowroty, 1.0f, 0, 0);
	glTranslatef(-windowposx, -windowposy, 0);
}

int GLEngine::InitGL()						// All Setup For OpenGL Goes Here
{
	int a = 0;
	glutInit(&a, NULL);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1280, 1024);
	glutInitWindowPosition(0, 0);

	return 0;										// Initialization Went OK
}

int GLEngine::drawLine(float x1, float y1, float z1, float x2, float y2,
		float z2, float r, float g, float b) {
	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
	return 0;
}

void GLEngine::drawCurve(GLfloat *ctrlpoints, int stride, int order, float r,
		float g, float b) {

	glColor3f(r, g, b);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, stride, order, ctrlpoints);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat) i / 30.0);
	glEnd();
}

int GLEngine::drawPoint(float x, float y, float z, float r, float g, float b,
		float point_size) {
	glLoadIdentity();
	TranslateP();
	glPointSize(point_size);
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd();
	return 0;
}

int GLEngine::drawCube(float posx, float posy, float posz, float edge, float r,
		float g, float b) {
	float q = edge / 2;
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	for (int x = 0; x < 24; x++)
		glVertex3f(cube[x].x * q + posx, cube[x].y * q + posy,
				cube[x].z * q + posz);
	glEnd();

	return 0;
}

int GLEngine::drawFilledSquare(float x, float y, float z, float r, float g,
		float b, float edge) {
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(x - edge, y + edge, 0.0f);
	glVertex3f(x + edge, y + edge, 0.0f);
	glVertex3f(x + edge, y - edge, 0.0f);
	glVertex3f(x - edge, y - edge, 0.0f);
	glEnd();
	return 0;
}

void GLEngine::KillGLWindow()						// Properly Kill The Window
{
	glutDestroyWindow(window);
}

int GLEngine::CreateGLWindow(char * title, int width, int height) {
	/* Initialize openGL */
	InitGL();

	/* Open a window */
	window = glutCreateWindow(title);

	glutSetWindow(window);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_MAP1_VERTEX_3);
	glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Really Nice Perspective Calculations

	if (fullscreen) {
		/* Go fullscreen.  This is as soon as possible. */
		glutFullScreen();

	} else {

	}
}

/* The function called whenever a key is pressed. */
void GLEngine::KeyPressed(unsigned char key, int x, int y) {
	/* avoid thrashing this procedure */
	usleep(100);

	/* If escape is pressed, kill everything. */
	switch (key) {
	case GLUT_KEY_F1:
		fullscreen = !fullscreen;
		if (fullscreen) {
			glutFullScreen();
		}
		break;
	case GLUT_KEY_F6:
		ResetGLScene();
		break;
	case GLUT_KEY_UP:
		windowposy += 1;
		break;
	case GLUT_KEY_DOWN:
		windowposy -= 1;
		break;
	case GLUT_KEY_LEFT:
		windowposx -= 1;
		break;
	case GLUT_KEY_RIGHT:
		windowposx += 1;
		break;
	}

}

GLfloat GLEngine::CalcPan(int oldx, int newx) {
	int d = newx - oldx;

	return d / 100.0f;
}

GLfloat GLEngine::CalcRot(int oldx, int newx) {
	int d = newx - oldx;

	return d / 5.0f;
}

GLfloat GLEngine::CalcZoom(int zDelta) {
	return zDelta / 100.0f;
}

