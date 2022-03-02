#include "point_3d.h"

float Point_3D::getX() {
    return this->x;
}

float Point_3D::getY() {
    return this->y;
}

float Point_3D::getZ() {
    return this->z;
}

void Point_3D::setPointTo(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

char* Point_3D::toString() {
    char *s = (char*) malloc(30);
    sprintf(s, "%f,%f,%f\n", this->x, this->y, this->z);
    return s;
}