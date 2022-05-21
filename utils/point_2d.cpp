#include "point_2d.h"

float Point_2D::getX() { return this->x; }

float Point_2D::getY() { return this->y; }

void Point_2D::setX(float x) { this->x = x; }

void Point_2D::setY(float y) { this->y = y; }

void Point_2D::setPointTo(float x, float y) {
    this->x = x;
    this->y = y;
}

char* Point_2D::toString() {
    char *s = (char*) malloc(30);
    sprintf(s, "%f,%f,%f\n", this->x, this->y);
    return s;
}