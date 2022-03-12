#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "GL_lib.h"
#define _USE_MATH_DEFINES
#include <algorithm>
#include <math.h>

using namespace std;

enum mode { FIRST, THIRD };

class Camera {

private:
    static Camera* c;
	Point_3D position;
	Point_3D lookAt;
	int startX;
    int startY;
    int tracking;
    float rotating_step;
    float horizontal_angle;
    float vertical_angle;
    float r;
	float camera_speed;
	int camera_mode;

public:
    
    Camera() {
        this->horizontal_angle = 0;
        this->vertical_angle = 0;
        this->r = 60;
        
        float x =
            this->r * cosf(this->vertical_angle) * sinf(this->horizontal_angle);
        
        float y = this->r * sinf(this->vertical_angle);
        
        float z =
            this->r * cosf(this->vertical_angle) * cosf(this->horizontal_angle);
        
        this->position = Point_3D(x, y, z);
        this->lookAt = Point_3D(0, 0, 0);
        this->startX = 0;
        this->startY = 0;
        this->tracking = 0;
        this->rotating_step = 0.03;

        this->camera_speed = 2;
        this->camera_mode = THIRD;
    }

	static Camera *getInstance() {
		if (!c) {
			c = new Camera();
		}
		return c;
	}

    static void keyFunc(unsigned char key, int x, int y) {

        switch (key) {
            case '.': {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            }
            case ',': {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            }
            case 'l': {
                // LookRight
                if (c->camera_mode == FIRST) {
                    c->updateHorizontalAngle(-c->rotating_step);
                    c->updateLookAt();
                }
                break;
            }
            case 'h': {
                // LookLeft
                if (c->camera_mode == FIRST) {
                    c->updateHorizontalAngle(c->rotating_step);
                    c->updateLookAt();
                }
                break;
            }
            case 'k': {
                // LookUp
                if (c->camera_mode == FIRST) {
                    c->updateVerticalAngle(c->rotating_step);
                    c->updateLookAt();
                }
                break;
            }
            case 'j': {
                // LookDown
                if (c->camera_mode == FIRST) {
                    c->updateVerticalAngle(-c->rotating_step);
                    c->updateLookAt();
                }
                break;
            }
            case 'w': {
                // MoveForward
                if (c->camera_mode == FIRST) {
                    c->fpsMoveForward();
                } else {
                    c->updateR(-c->camera_speed);
                    c->updateCameraPos();
                }
                break;
            }
            case 's': {
                // MoveBackwards
                if (c->camera_mode == FIRST) {
                    c->fpsMoveBack();
                } else {
                    c->updateR(c->camera_speed);
                    c->updateCameraPos();
                }
                break;
            }
            case 'q': {
                if (c->camera_mode == FIRST) {
                    c->fpsMoveUp();
                } else {
                    c->updateVerticalAngle(c->rotating_step);
                    c->updateCameraPos();
                }
                break;
            }
            case 'z': {
                if (c->camera_mode == FIRST) {
                    c->fpsMoveDown();
                } else {
                    c->updateVerticalAngle(-c->rotating_step);
                    c->updateCameraPos();
                }
                break;
            }
            case 'a': {
                if (c->camera_mode == FIRST) {
                    c->fpsMoveLeft();
                } else {
                    c->updateHorizontalAngle(-c->rotating_step);
                    c->updateCameraPos();
                }
                break;
            }
            case 'd': {
                if (c->camera_mode == FIRST) {
                    c->fpsMoveRight();
                } else {
                    c->updateHorizontalAngle(c->rotating_step);
                    c->updateCameraPos();
                }
                break;
            }
            case 'v': {
                c->nextCameraMode();
            }
        }
    }


    static void processMouseButtons(int button, int state, int xx, int yy) {

        if (state == GLUT_DOWN) {
            c->setStartX(xx);
            c->setStartY(yy);
            if (button == GLUT_LEFT_BUTTON)
                c->setTracking(1);
            else if (button == GLUT_RIGHT_BUTTON)
                c->setTracking(2);
            else
                c->setTracking(0);
        } else if (state == GLUT_UP) {

            c->setTracking(0);
        }
    }

    static void processMouseMotion(int xx, int yy) {

        int deltaX, deltaY;

        if (!c->getTracking())
            return;

        deltaX = xx - c->getStartX();
        deltaY = yy - c->getStartY();
        c->setStartX(xx);
        c->setStartY(yy);

        float deltaXinRad = ((float)deltaX / 1920.0f) * 2.0f * M_PI;
        float deltaYinRad = ((float)deltaY / 1080.0f) * M_PI;

        if (c->getTracking() == 1) {

            if (c->camera_mode == FIRST) {

                c->updateHorizontalAngle(deltaXinRad * 0.3);
                c->updateVerticalAngle(deltaYinRad * 0.3);
                c->updateLookAt();

            } else {

                c->updateHorizontalAngle(-deltaXinRad);
                c->updateVerticalAngle(-deltaYinRad);
                c->updateCameraPos();
            }

        } else if (c->getTracking() == 2) {

            if (c->camera_mode == FIRST) {

                float x =
                    c->r * cosf(c->vertical_angle) * sinf(c->horizontal_angle);
                float y = c->r * sinf(c->vertical_angle);
                float z =
                    c->r * cosf(c->vertical_angle) * cosf(c->horizontal_angle);

                Point_3D lookVector = {x, y, z};
                lookVector.normalize();

                float normalizeDeltaY = (float)deltaY / 11.0f;

                c->lookAt.setX(c->lookAt.getX() +
                               lookVector.getX() * normalizeDeltaY);
                c->lookAt.setY(c->lookAt.getY() +
                               lookVector.getY() * normalizeDeltaY);
                c->lookAt.setZ(c->lookAt.getZ() +
                               lookVector.getZ() * normalizeDeltaY);

                c->position.setX(c->position.getX() +
                                 lookVector.getX() * normalizeDeltaY);
                c->position.setY(c->position.getY() +
                                 lookVector.getY() * normalizeDeltaY);
                c->position.setZ(c->position.getZ() +
                                 lookVector.getZ() * normalizeDeltaY);

                float normalizeDeltaX = (float)deltaX / 11.0f;

                x = c->r * cosf(0) * sinf(c->horizontal_angle - M_PI / 2);
                y = c->r * sinf(0);
                z = c->r * cosf(0) * cosf(c->horizontal_angle - M_PI / 2);

                lookVector = {x, y, z};
                lookVector.normalize();

                c->lookAt.setX(c->lookAt.getX() +
                               lookVector.getX() * normalizeDeltaX);
                c->lookAt.setY(c->lookAt.getY() +
                               lookVector.getY() * normalizeDeltaX);
                c->lookAt.setZ(c->lookAt.getZ() +
                               lookVector.getZ() * normalizeDeltaX);

                c->position.setX(c->position.getX() +
                                 lookVector.getX() * normalizeDeltaX);
                c->position.setY(c->position.getY() +
                                 lookVector.getY() * normalizeDeltaX);
                c->position.setZ(c->position.getZ() +
                                 lookVector.getZ() * normalizeDeltaX);

            } else {

                c->updateR((float)deltaY * 0.1f);
                c->updateCameraPos();
            }
        }
    }

    Point_3D getPos();

    Point_3D getLookAt();

    int getStartX();

    int getStartY();

    int getTracking();

    float getRotatingStep();

    int getHorizontalAngle();

    int getVerticalAngle();

    float getR();

    void setPos(float x, float y, float z);

    void setLookAt(float x, float y, float z);

    void setStartX(int startX);

    void setStartY(int startY);

    void setTracking(int tracking);

    void setRotationStep(float rotationStep);

    void setHorizontalAngle(float alpha);

    void setVerticalAngle(float beta);

    void setR(float r);

    void nextCameraMode();

    void updateHorizontalAngle(float delta);

    void updateVerticalAngle(float delta);

    void updateLookAt();

    void updateCameraPos();

    void fpsMoveForward();

    void fpsMoveBack();

    void fpsMoveUp();

    void fpsMoveDown();

    void fpsMoveRight();

    void fpsMoveLeft();

    void updateR(float delta);
};

#endif