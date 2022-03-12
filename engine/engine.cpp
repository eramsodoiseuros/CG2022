#include "utils/camera.h"
#include "utils/scene.h"

#include <iostream>

using namespace std;

/*

	>> chamar o parser

	>> dar set da posiçao da camera

	>> recolher e guardar objetos no xml

	>> imprimir uma scene com os objetos

	>> done

*/

Camera *c = nullptr;
Camera *camera = Camera::getInstance();

Scene s = Scene();

static void changeSize(int w, int h) {

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
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

static void idle() { glutPostRedisplay(); }

void renderScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
    gluLookAt(camera->getPos().getX(), camera->getPos().getY(),
              camera->getPos().getZ(), camera->getLookAt().getX(),
              camera->getLookAt().getY(), camera->getLookAt().getZ(), 0.0f,
              1.0f, 0.0f);

	rgb cor = rgb();
	s.getCor();

	glBegin(GL_TRIANGLES);


	glColor3f(cor.getR(), cor.getG(), cor.getB());


	glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv){

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
	glutMouseFunc(Camera ::processMouseButtons);
	glutMotionFunc(Camera ::processMouseMotion);

	#ifndef __APPLE__
		glewInit();
	#endif

	// ler o xml

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutMainLoop();

	return 1;
}