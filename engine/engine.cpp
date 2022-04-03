#include "utils/camera.h"
#include "utils/scene.h"
#include "models/figures.h"
#include "solarSystem/solarSystemReader.h"
#pragma
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


// Objeto onde ficam guardados os .3D files!
Figures storedFigures = Figures();
Camera* camera = Camera::getInstance();
vector<CelestialBody> solarSystem;


// settings variables
float posX = 0, posY = 0, posZ = 0,
rAngle = 0, rotateX = 0, rotateY = 0, rotateZ = 0,
scaleX = 0, scaleY = 0, scaleZ = 0,
r = 0, g = 0, b = 0;



/**
 * gluPerspective settings - variables
 *
 */
float fovy, zNear, zFar;


void drawOrbit(float radX, float radZ, vector<float> colorsRGB) {
	float slice = M_PI / 180;

	glBegin(GL_LINE_STRIP);
	glColor3f(colorsRGB.at(0), colorsRGB.at(1), colorsRGB.at(2));

	for (float i = 0; i <= (2 * M_PI); i += slice)
		glVertex3f(cos(i) * radX, 0, sin(i) * radZ);

	glEnd();
}


void drawCelestialBody(CelestialBody cb) {

	Settings planetSetts = cb.getSettings();
	Orbit planetOrbit = cb.getOrbit();
	string primitiveFile = planetSetts.getPrimitiveName();


	// translate
	posX = planetSetts.getTranslX(); posY = planetSetts.getTranslY(); posZ = planetSetts.getTranslZ();
	// rotate
	rAngle = planetSetts.getRotateAngle(); rotateX = planetSetts.getRotateX(); rotateY = planetSetts.getRotateY(); rotateZ = planetSetts.getRotateZ();

	float rOrbit = planetOrbit.getRotateAngle(); float orbX = planetOrbit.getRotateX(); float orbY = planetOrbit.getRotateY(); float orbZ = planetOrbit.getRotateZ();
	// scale
	scaleX = planetSetts.getScaleX(); scaleY = planetSetts.getScaleY(); scaleZ = planetSetts.getScaleZ();
	// color
	r = planetSetts.getColorR(); g = planetSetts.getColorG(); b = planetSetts.getColorB();

	Primitive currentPrimitive = storedFigures.getSphere(primitiveFile);

	vector<float> colorRGB = vector<float>();
	colorRGB.push_back(r); colorRGB.push_back(g); colorRGB.push_back(b);
	currentPrimitive.setColor(colorRGB);

	glPushMatrix();
	glRotatef(rOrbit, orbX, orbY, orbZ);
	drawOrbit(planetOrbit.getRadX(), planetOrbit.getRadZ(), colorRGB);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX, posY, posZ);

	glRotatef(rAngle, rotateX, rotateY, rotateZ);
	glScalef(scaleX, scaleY, scaleZ);



	currentPrimitive.drawSphere();

	vector<CelestialBody> moons = cb.getMoons();

	if (moons.size() != 0) {

		for (CelestialBody moon : moons) {

			drawCelestialBody(moon);

		}
	}

	glPopMatrix();
}


void constructSolarSystem(vector<CelestialBody> solarSystem) {

	for (CelestialBody cb : solarSystem) {

		drawCelestialBody(cb);
	}
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

	//glClearColor(red, green, blue, 0.03f);

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
}


static void idle() { glutPostRedisplay(); }

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camera->getPos().getX(), camera->getPos().getY(),
		camera->getPos().getZ(), camera->getLookAt().getX(),
		camera->getLookAt().getY(), camera->getLookAt().getZ(),
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here


	// put drawing instructions here
	constructSolarSystem(solarSystem);

	// End of frame
	glutSwapBuffers();
}



void getSolarSystemPrimitives(vector<CelestialBody> solarSystem) {

	for (CelestialBody cb : solarSystem) {

		string planetName = cb.getSettings().getPrimitiveName();
		storedFigures.addPrimitive(planetName);

		vector<CelestialBody> moons = cb.getMoons();
		if (moons.size() != 0) {

			for (CelestialBody innercb : moons) {

				string moonName = innercb.getSettings().getPrimitiveName();
				storedFigures.addPrimitive(moonName);
			}
		}
	}
}


vector<CelestialBody> getSolarSystem(string solarSystemPath) {

	solarSystem = readSolarSystem(solarSystemPath, camera);
	cameraSetup();
	getSolarSystemPrimitives(solarSystem);

	cout << "\n#> li " << solarSystem.size() << " corpos celestes!!" << endl;
	return solarSystem;
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
	glutKeyboardFunc(Camera::keyFunc);
	glutReshapeFunc(changeSize);
	glutIdleFunc(idle);
	glutMouseFunc(Camera::processMouseButtons);
	glutMotionFunc(Camera::processMouseMotion);

#ifndef __APPLE__
	glewInit();
#endif

	// aqui
	cout << argv[1] << endl;
	getSolarSystem(argv[1]);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_LINE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}