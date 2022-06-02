#include "point_2d.h"

Point_2D::Point_2D(){
    x = 0.0f;
    y = 0.0f;
}

Point_2D::Point_2D(float p1, float p2) {
    this->x = p1;
    this->y = p2;
}


float Point_2D::getX() { return this->x; }

float Point_2D::getY() { return this->y; }

void Point_2D::setX(float x) { this->x = x; }

void Point_2D::setY(float y) { this->y = y; }

void Point_2D::setPointTo(float x, float y) {
    this->x = x;
    this->y = y;
}

string Point_2D::toString() {
    stringstream ss;
    ss.precision(4);
    ss << fixed << x << "," << y;
    string s = ss.str();
    return s;
}