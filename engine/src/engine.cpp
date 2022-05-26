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

// luzes
Lights l = Lights();

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
float fovy, zNear, zFar;

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

	// Set perspective
	gluPerspective(fovy, ratio, zNear, zFar);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

}

void cameraSetup() {
	Point_3D perspective = camera->getPersp();
	fovy = perspective.getX();
	zNear = perspective.getY();
	zFar = perspective.getZ();
	float vertical = asin(camera->getPos().getY() / camera->getR());
	float horizontal = acos(camera->getPos().getZ() / (camera->getR() * cos(vertical)));
	camera->setHorizontalAngle(horizontal);
	camera->setVerticalAngle(vertical);
}


void updateFPS(){
	frame++;
	times = glutGet(GLUT_ELAPSED_TIME);

	if (times - timeBase > 1000) {

		fps = frame * 1000.0 / (times - timeBase);
		timeBase = times;
		frame = 0;
	}

	sprintf(title, "CG@DI-UM - Fase 3 - Grupo 11 <-> FPS: %d - Time: %d ", fps, times / 1000);
	glutSetWindowTitle(title);
}

static void idle() { glutPostRedisplay(); }

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camera->getPos().getX(), camera->getPos().getY(),camera->getPos().getZ(),
		camera->getLookAt().getX(), camera->getLookAt().getY(), camera->getLookAt().getZ(),
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here

	// put drawing instructions here
	for (Primitive p : scenePrimitives){

		p.Draw();
	}
	

	// FPS CALCULATIONS
	updateFPS();

	// End of frame
	glutSwapBuffers();
}




int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "Invalid number of arguments\n";
		return -1;
	}

	glutInit(&argc, argv);
	glEnableClientState(GL_VERTEX_ARRAY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Engine - Projeto CG");

	glutDisplayFunc(renderScene);
	glutKeyboardFunc(Camera::keyFunc);
	glutSpecialFunc(Camera::specialKeyFunc);
	glutReshapeFunc(changeSize);
	glutIdleFunc(idle);
	glutMouseFunc(Camera::processMouseButtons);
	glutMotionFunc(Camera::processMouseMotion);

	#ifndef __APPLE__
	glewInit();
	#endif

	// aqui
	cout << argv[1] << endl;
	//getSolarSystem(argv[1]);
	Parser p;
	scenePrimitives = p.lerXML(argv[1], camera);
	cameraSetup();


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_LINE);
	
	// luzes
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_NORMALIZE);
	//glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}