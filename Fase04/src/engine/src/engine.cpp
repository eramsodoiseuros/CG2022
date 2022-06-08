#include "../headers/camera.h"
#include "../headers/xmlparser.h"
#include "../headers/lights.h"
#pragma
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <typeinfo>
using namespace std;


// Camera
Camera* camera = Camera::getInstance();

// lights
Lights lights = Lights();

// primitives
vector<Primitive> scenePrimitives = vector<Primitive>();


// settings variables
float posX = 0, posY = 0, posZ = 0,
rAngle = 0, rotateX = 0, rotateY = 0, rotateZ = 0,
scaleX = 0, scaleY = 0, scaleZ = 0,
r = 0, g = 0, b = 0;

// fps variables
int frame = 0, fps = 0, times, timeBase;
char title[50] = "";

// gluPerspective settings - variables
float fovy, zNear, zFar, ntriangles = 0.0f;



/**
 * @brief draws xyz axis'
 * 
 */
void drawXYZ() {

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
	glEnable(GL_LIGHTING);
}


/**
 * @brief camera setup with xml values
 *
 */
void cameraSetup() {
	Point_3D perspective = camera->getPersp();
	fovy = perspective.getX();
	zNear = perspective.getY();
	zFar = perspective.getZ();
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);

	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	cameraSetup();
	// Set perspective
	gluPerspective(fovy, ratio, zNear, zFar);

	// return to the model view matrix mode

	glMatrixMode(GL_MODELVIEW);
}


/**
 * @brief update fps values for title
 * 
 */
void updateFPS() {
	frame++;
	times = glutGet(GLUT_ELAPSED_TIME);

	if (times - timeBase > 1000) {

		fps = frame * 1000.0 / (times - timeBase);
		timeBase = times;
		frame = 0;
	}

	sprintf(title, "CG@DI-UM - Grupo11 <-> Triangles: %.0f - FPS: %d - Time: %d ", ntriangles, fps, times / 1000);
	glutSetWindowTitle(title);
}


static void idle() {
	glutPostRedisplay(); 
}


void renderScene(void) {


	ntriangles = 0.0f;

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	gluLookAt(camera->getPos().getX(), camera->getPos().getY(), camera->getPos().getZ(),
		camera->getLookAt().getX(), camera->getLookAt().getY(), camera->getLookAt().getZ(),
		0.0f, 1.0f, 0.0f);

	// put drawing instructions here

	if (camera->getShowXYZ())
		drawXYZ();
	
	for (Primitive p : scenePrimitives) {

		ntriangles += p.getNIndexes() / 3;
		p.Draw();
	}

	lights.Apply();

	// FPS CALCULATIONS
	updateFPS();

	lights.setCounter(0);
	// End of frame
	glutSwapBuffers();
}




int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "Invalid number of arguments\n";
		return -1;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Engine - Projeto CG");
	
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutKeyboardFunc(Camera::keyFunc);
	glutSpecialFunc(Camera::specialKeyFunc);
	glutIdleFunc(idle);
	glutMouseFunc(Camera::processMouseButtons);
	glutMotionFunc(Camera::processMouseMotion);

#ifndef __APPLE__
	glewInit();
#endif
	
	//glutFullScreen();

	cout << argv[1] << endl;
	Parser p;
	
	try {
		scenePrimitives = p.lerXML(argv[1], camera, &lights);
		cameraSetup();

		//  OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_NORMALIZE);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		// luzes
		glEnable(GL_LIGHTING);
		glEnable(GL_RESCALE_NORMAL);
		glEnable(GL_TEXTURE_2D);
		//glEnable(GL_BLEND);
		glShadeModel(GL_SMOOTH);

		// enter GLUT's main cycle
		glutMainLoop();
	}
	catch (const std::exception& ex) {
		cerr << ex.what() << endl;
	}
	return 1;
}