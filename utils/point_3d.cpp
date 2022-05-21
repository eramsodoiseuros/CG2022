#include "point_3d.h"

using namespace std;

Point_3D::Point_3D(){
    
    x = 0; y = 0; z = 0;
}

Point_3D::Point_3D(float p1, float p2, float p3) {
    x = p1;
    y = p2;
    z = p3;
}

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


Point_3D sum(Point_3D p1, Point_3D p2){

    Point_3D a = Point_3D();
    a.setX(p1.getX() + p2.getX());
    a.setY(p1.getY() + p2.getY());
    a.setZ(p1.getZ() + p2.getZ());
    return a;
}

Point_3D sub(Point_3D p1, Point_3D p2){

    Point_3D a = Point_3D();
    a.setX(p1.getX() - p2.getX());
    a.setY(p1.getY() - p2.getY());
    a.setZ(p1.getZ() - p2.getZ());
    return a;
}

Point_3D mul(Point_3D p1, Point_3D p2){

    Point_3D a = Point_3D();
    a.setX(p1.getX() * p2.getX());
    a.setY(p1.getY() * p2.getY());
    a.setZ(p1.getZ() * p2.getZ());
    return a;
}


Point_3D Point_3D::crossProduct(Point_3D p) {

    /*
        Nx = Ay * Bz - Az * By
        Ny = Az * Bx - Ax * Bz
        Nz = Ax * By - Ay * Bx
    */

    return Point_3D(    this->y * p.getZ() - this->z * p.getY(),
                        this->z * p.getX() - this->x * p.getZ(),
                        this->x * p.getY() - this->y * p.getZ()
                    );
}

void Point_3D::normalize() {

    float length = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));

    this->setX(this->getX() / length);
    this->setY(this->getY() / length);
    this->setZ(this->getZ() / length);
}

Point_3D getNormal(Point_3D p1, Point_3D p2, Point_3D p3){

    /*
        A = p1 - p2
        B = p3 - p2
    */
    Point_3D a = Point_3D(p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ());
    Point_3D b = Point_3D(p3.getX() - p2.getX(), p3.getY() - p2.getY(), p3.getZ() - p2.getZ());
    
    Point_3D normal = a.crossProduct(b);
    normal.normalize();

    return normal;
}




string Point_3D::toString() {

    stringstream ss;
    ss.precision(4);
    ss << fixed << x << "," << y << "," << z << "\n";
    string s = ss.str();
    return s;
}