#include "point_3d.h"

float Point_3D::getX() { return this->x; }

float Point_3D::getY() { return this->y; }

float Point_3D::getZ() { return this->z; }

void Point_3D::setX(float x) { this->x = x; }

void Point_3D::setY(float y) { this->y = y; }

void Point_3D::setZ(float z) { this->z = z; }

void Point_3D::setPointTo(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point_3D crossProduct(Point_3D p) {

    return Point_3D(this->y * p.getZ() - this->z * p.getY(),
                        this->z * p.getX() - this->x * p.getZ(),
                        this->x * p.getY() - this->y * p.getZ());
}

void normal_vetor() {

    float length = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
    
    this->setX(this->getX() / length);
    this->setY(this->getY() / length);
    this->setZ(this->getZ() / length);
}

Point_3D calcular_normal(Point_3D vetorA, Point_3D vetorB, Point_3D vetorC){
    Point_3D x = {(b[0]-a[0], b[1]-a[1], b[2]-a[2])};
    Point_3D y = {(c[0]-a[0], c[1]-a[1], c[2]-a[2])};

    Point_3D* r = x.crossProduct(y);

    return r;
}

char* Point_3D::toString() {
    char *s = (char*) malloc(30);
    sprintf(s, "%f,%f,%f\n", this->x, this->y, this->z);
    return s;
}