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

vector<CelestialBody> solarSystem;

// C�mara do engine
Camera *camera = Camera::getInstance();


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

/**
 * @brief Setup das definições da câmara com os valores lidos no XML
 * 
 */
void cameraSetup(){

	//Point_3D pos = cameraSettings.at(0);
	//Point_3D lookAt = cameraSettings.at(1);
	//Point_3D up = cameraSettings(2);

	//camera->setPos(pos.getX(), pos.getY(), pos.getZ());
	//camera->setLookAt(lookAt.getX(), lookAt.getY(), lookAt.getZ());

	//Point_3D persp = cameraSettings.at(3);
	//fovy = persp.getX(); zNear = persp.getY(); zFar = persp.getZ();
}


/**
 * @brief Dado um qualquer corpo celeste, desenha-o
 * 
 * @param cb Corpo celeste com as informações necessárias para a sua configuração
 */
void drawCelestialBody(CelestialBody cb) {

	Settings planetSetts = cb.getSettings();
	string primitiveFile = planetSetts.getPrimitiveName();

	// translate
	posX = planetSetts.getTranslX(); posY = planetSetts.getTranslY(); posZ = planetSetts.getTranslZ();
	// rotate
	rAngle = planetSetts.getRotateAngle(); rotateX = planetSetts.getRotateX(); rotateY = planetSetts.getRotateY(); rotateZ = planetSetts.getRotateZ();
	// scale
	scaleX = planetSetts.getScaleX(); scaleY = planetSetts.getScaleY(); scaleZ = planetSetts.getScaleZ();
	// color
	r = planetSetts.getColorR(); g = planetSetts.getColorG(); b = planetSetts.getColorB();

	Primitive currentPrimitive = storedFigures.getSphere(primitiveFile);

	vector<float> colorRGB = vector<float>();
	colorRGB.push_back(r); colorRGB.push_back(g); colorRGB.push_back(b);
	currentPrimitive.setColor(colorRGB);

	glPushMatrix();
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(rAngle, rotateX, rotateY, rotateZ);
	glTranslatef(posX, posY, posZ);

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
	if(h == 0)
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
	gluPerspective(800.0f ,ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

}

void cameraSetup() {
	Point_3D perspective = camera->getPersp();
	fovy = perspective.getX();
	zNear = perspective.getY();
	zFar = perspective.getZ();
}

static void idle() {
	 glutPostRedisplay(); 
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camera->getPos().getX(), camera->getPos().getY(),
		camera->getPos().getZ(), camera->getLookAt().getX(),
		camera->getLookAt().getY(), camera->getLookAt().getZ(), 
		0.0f, 1.0f, 0.0f);

	/*
	gluLookAt(camera.getPos().getX(), camera.getPos().getY(), camera.getPos().getZ(), 
				camera.getLookAt().getX(), camera.getLookAt().getY(), camera.getLookAt().getZ(), 
				0.0f, 1.0f, 0.0f);
	*/
	

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

	solarSystem = readSolarSystem(solarSystemPath,camera);
	cameraSetup();
	getSolarSystemPrimitives(solarSystem);

	cout << "\n#> li " << solarSystem.size() << " corpos celestes!!" << endl;
	return solarSystem;
}




int main(int argc, char **argv) {

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
	glFrontFace(GL_CW);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
