#include "../../headers/camera.h"

Camera* Camera::c = NULL;

Point_3D Camera::getPos() { return this->position; }

Point_3D Camera::getLookAt() { return this->lookAt; }

Point_3D Camera::getPersp() { return this->persp; }

int Camera::getStartX() { return this->startX; }

int Camera::getStartY() { return this->startY; }

int Camera::getTracking() { return this->tracking; }

float Camera::getRotatingStep() { return this->rotating_step; }

int Camera::getHorizontalAngle() { return this->horizontal_angle; }

int Camera::getVerticalAngle() { return this->vertical_angle; }

float Camera::getR() { return this->r; }

void Camera::setPos(float x, float y, float z) {
    this->position.setX(x);
    this->position.setY(y);
    this->position.setZ(z);
}

void Camera::setLookAt(float x, float y, float z) {
    this->lookAt.setX(x);
    this->lookAt.setY(y);
    this->lookAt.setZ(z);
}

void Camera::setPersp(float x, float y, float z) {
    this->persp.setX(x);
    this->persp.setY(y);
    this->persp.setZ(z);
}

void Camera::setStartX(int startX) { this->startX = startX; }

void Camera::setStartY(int startY) { this->startY = startY; }

void Camera::setTracking(int tracking) { this->tracking = tracking; }

void Camera::setRotationStep(float rotationStep) {
    this->rotating_step = rotationStep;
}

void Camera::setHorizontalAngle(float alpha) {
    this->horizontal_angle = alpha;
}

void Camera::setVerticalAngle(float beta) { this->vertical_angle = beta; }

void Camera::setR(float r) { this->r = r; }

void Camera::updateR(float delta) { this->r = max(10.0f, this->r + delta); }

void Camera::nextCameraMode() {

    this->camera_mode = (this->camera_mode + 1) % 2;
    this->horizontal_angle += M_PI;
    this->vertical_angle = -this->vertical_angle;

    this->r =
        sqrt(powf(this->position.getX(), 2) + powf(this->position.getY(), 2) +
             powf(this->position.getZ(), 2));

    float x =
        this->r * cosf(this->vertical_angle) * sinf(this->horizontal_angle);
    
    float y = this->r * sinf(this->vertical_angle);
    float z =
        this->r * cosf(this->vertical_angle) * cosf(this->horizontal_angle);

    if (this->camera_mode == THIRD) {

        this->lookAt = {0, 0, 0};
        setPos(x, y, z);

    } else {
        Point_3D lookVector = {x, y, z};
        lookVector.normalize();

        // n�o deveria faltar algo aqui?
    }
}

void Camera::updateHorizontalAngle(float delta) {

    this->horizontal_angle += delta;
    if (this->horizontal_angle >= 2 * M_PI) {
        this->horizontal_angle = this->horizontal_angle - 2 * M_PI;
    }
    if (this->horizontal_angle < 0) {
        this->horizontal_angle = 2 * M_PI - (-this->horizontal_angle);
    }
}

void Camera::updateVerticalAngle(float delta) {

    this->vertical_angle += delta;
    if (this->vertical_angle > M_PI / 2)
        this->vertical_angle = M_PI / 2 - 0.001;
    if (this->vertical_angle < (-M_PI / 2))
        this->vertical_angle = -M_PI / 2 + 0.001;

    // valores pequenos evitam movimentos estranhos
}

void Camera::updateLookAt() {

    // pela teoria, o raio n�o entra nestas contas.... ?
    float x = //this->r * 
        cosf(this->vertical_angle) * sinf(this->horizontal_angle);
    
    float y = //this->r * 
        sinf(this->vertical_angle);
    
    float z = //this->r *
        cosf(this->vertical_angle) * cosf(this->horizontal_angle);

    Point_3D lookVector = {x, y, z};
    // pela teoria, este vetor j� n�o vai estar normalizado
    lookVector.normalize();

    this->lookAt.setX(this->position.getX() + lookVector.getX());
    this->lookAt.setY(this->position.getY() + lookVector.getY());
    this->lookAt.setZ(this->position.getZ() + lookVector.getZ());
}

void Camera::updateCameraPos() {

    float x =
        this->r * cosf(this->vertical_angle) * sinf(this->horizontal_angle);

    float y = this->r * sinf(this->vertical_angle);
    float z =
        this->r * cosf(this->vertical_angle) * cosf(this->horizontal_angle);

    setPos(x, y, z);
}

void Camera::fpsMoveForward() {

    float x =
        this->r * cosf(this->vertical_angle) * sinf(this->horizontal_angle);
    float y = this->r * sinf(this->vertical_angle);
    float z =
        this->r * cosf(this->vertical_angle) * cosf(this->horizontal_angle);

    Point_3D forwardVector = {x, y, z};
    forwardVector.normalize();

    this->lookAt.setX(this->lookAt.getX() + forwardVector.getX());
    this->lookAt.setY(this->lookAt.getY() + forwardVector.getY());
    this->lookAt.setZ(this->lookAt.getZ() + forwardVector.getZ());

    this->position.setX(this->position.getX() + forwardVector.getX());
    this->position.setY(this->position.getY() + forwardVector.getY());
    this->position.setZ(this->position.getZ() + forwardVector.getZ());
}

void Camera::fpsMoveBack() {

    float x =
        this->r * cosf(this->vertical_angle) * sinf(this->horizontal_angle);
    float y = this->r * sinf(this->vertical_angle);
    float z =
        this->r * cosf(this->vertical_angle) * cosf(this->horizontal_angle);

    Point_3D backwardsVector = {x, y, z};
    backwardsVector.normalize();

    this->lookAt.setX(this->lookAt.getX() - backwardsVector.getX());
    this->lookAt.setY(this->lookAt.getY() - backwardsVector.getY());
    this->lookAt.setZ(this->lookAt.getZ() - backwardsVector.getZ());

    this->position.setX(this->position.getX() - backwardsVector.getX());
    this->position.setY(this->position.getY() - backwardsVector.getY());
    this->position.setZ(this->position.getZ() - backwardsVector.getZ());
}

void Camera::fpsMoveUp() {

    float x = this->r * cosf(this->vertical_angle + M_PI / 2) *
              sinf(this->horizontal_angle);
    float y = this->r * sinf(this->vertical_angle + M_PI / 2);
    float z = this->r * cosf(this->vertical_angle + M_PI / 2) *
              cosf(this->horizontal_angle);

    Point_3D realUp = {x, y, z};

    realUp.normalize();

    this->lookAt.setX(this->lookAt.getX() + realUp.getX());
    this->lookAt.setY(this->lookAt.getY() + realUp.getY());
    this->lookAt.setZ(this->lookAt.getZ() + realUp.getZ());

    this->position.setX(this->position.getX() + realUp.getX());
    this->position.setY(this->position.getY() + realUp.getY());
    this->position.setZ(this->position.getZ() + realUp.getZ());
}

void Camera::fpsMoveDown() {

    float x = this->r * cosf(this->vertical_angle - M_PI / 2) *
              sinf(this->horizontal_angle);
    float y = this->r * sinf(this->vertical_angle - M_PI / 2);
    float z = this->r * cosf(this->vertical_angle - M_PI / 2) *
              cosf(this->horizontal_angle);

    Point_3D realDown = {x, y, z};

    realDown.normalize();

    this->lookAt.setX(this->lookAt.getX() + realDown.getX());
    this->lookAt.setY(this->lookAt.getY() + realDown.getY());
    this->lookAt.setZ(this->lookAt.getZ() + realDown.getZ());

    this->position.setX(this->position.getX() + realDown.getX());
    this->position.setY(this->position.getY() + realDown.getY());
    this->position.setZ(this->position.getZ() + realDown.getZ());
}

void Camera::fpsMoveRight() {

    float x = this->r * cosf(0) * sinf(this->horizontal_angle - M_PI / 2);
    float y = this->r * sinf(0);
    float z = this->r * cosf(0) * cosf(this->horizontal_angle - M_PI / 2);

    Point_3D realRight = {x, y, z};

    realRight.normalize();

    this->lookAt.setX(this->lookAt.getX() + realRight.getX());
    this->lookAt.setY(this->lookAt.getY() + realRight.getY());
    this->lookAt.setZ(this->lookAt.getZ() + realRight.getZ());

    this->position.setX(this->position.getX() + realRight.getX());
    this->position.setY(this->position.getY() + realRight.getY());
    this->position.setZ(this->position.getZ() + realRight.getZ());
}

void Camera::fpsMoveLeft() {

    float x = this->r * cosf(0) * sinf(this->horizontal_angle + M_PI / 2);
    float y = this->r * sinf(0);
    float z = this->r * cosf(0) * cosf(this->horizontal_angle + M_PI / 2);

    Point_3D realLeft = {x, y, z};

    realLeft.normalize();

    this->lookAt.setX(this->lookAt.getX() + realLeft.getX());
    this->lookAt.setY(this->lookAt.getY() + realLeft.getY());
    this->lookAt.setZ(this->lookAt.getZ() + realLeft.getZ());

    this->position.setX(this->position.getX() + realLeft.getX());
    this->position.setY(this->position.getY() + realLeft.getY());
    this->position.setZ(this->position.getZ() + realLeft.getZ());
}


int Camera::getShowXYZ(){
    return showXYZ;
}
