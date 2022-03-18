#include "utils/camera.h"
#include "utils/scene.h"
#pragma
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

vector<string> files;
vector<Point_3D> points;
vector<Point_3D> cameraSettings;

Camera *camera = Camera::getInstance();
Scene s = Scene();

/**
 * gluPerspective settings - variables
 * 
 */
float eyeX,eyeY,eyeZ, centerX,centerY,centerZ, upX,upY,upZ;
float fovy, zNear, zFar;


void cameraSetup(){

	Point_3D pos = cameraSettings.at(0);
	Point_3D lookAt = cameraSettings.at(1);
	//Point_3D up = cameraSettings(2);

	camera->setPos(pos.getX(), pos.getY(), pos.getZ());
	camera->setLookAt(lookAt.getX(), lookAt.getY(), lookAt.getZ());

	Point_3D persp = cameraSettings.at(3);
	fovy = persp.getX(); zNear = persp.getY(); zFar = persp.getZ();
}


void getFigure(string s){

	string inputFile = "../3D/" + s;
	string l = "";
	vector<string> parser;
	ifstream dFile(inputFile);
	
	if(!dFile.is_open()){

		cerr << "Could not open the specified file:" << inputFile << endl;
		return ;
	}

	bool fstLine = true;
	int nPoints = 0;
	int nIndexes = 0;

	while(getline(dFile,l)){

		stringstream ss(l);
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			parser.push_back(subs);
		}

		if(fstLine){
			nPoints = stoi(parser.at(1));
			nIndexes = stoi(parser.at(2));
			fstLine = false;
		}
		else {

			float x = stof(parser.at(0));
			float y = stof(parser.at(1));
			float z = stof(parser.at(2));
			//cout << l;
			//glVertex3f(x,y,z);
			points.push_back(Point_3D(x,y,z));	
		}
		parser.clear();
	}
	dFile.close();
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
	gluPerspective(fovy ,ratio, zNear , zFar);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

}


void drawPrimitives() {

	rgb cor = rgb();
	s.getCor();

	for(string file : files) {

		getFigure(file);

		glBegin(GL_TRIANGLES);

		//glColor3f(cor.getR(), cor.getG(), cor.getB());
		glColor3f(1.0f,0.0f,0.0f);

		for(Point_3D p : points){
			glVertex3f(p.getX(), p.getY(), p.getZ());
		}

		glEnd();
		points.clear();
	}
}

static void idle() { glutPostRedisplay(); }

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camera->getPos().getX(), camera->getPos().getY(),
              camera->getPos().getZ(), camera->getLookAt().getX(),
              camera->getLookAt().getY(), camera->getLookAt().getZ(), 0.0f,
              1.0f, 0.0f);

// put the geometric transformations here


// put drawing instructions here

	drawPrimitives();

	// End of frame
	glutSwapBuffers();
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

	s.build(argv[1]);
	files = s.getFicheiros();
	cameraSettings = s.getCameraSettings();
	cameraSetup();
	


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
