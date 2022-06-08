#include "point_3d.h"

using namespace std;

/**
 * @brief Construct a new Point_3D::Point_3D object
 * 
 */
Point_3D::Point_3D(){
    
    x = 0; y = 0; z = 0;
}

/**
 * @brief Construct a new Point_3D::Point_3D object
 * 
 * @param p1 x value
 * @param p2 y value
 * @param p3 z value
 */
Point_3D::Point_3D(float p1, float p2, float p3) {
    x = p1;
    y = p2;
    z = p3;
}

/**
 * @brief get x valye
 * 
 * @return float x value
 */
float Point_3D::getX() { return this->x; }

/**
 * @brief get y valye
 * 
 * @return float y value
 */
float Point_3D::getY() { return this->y; }

/**
 * @brief get z value
 * 
 * @return float z value
 */
float Point_3D::getZ() { return this->z; }

/**
 * @brief set x value
 * 
 * @param x x value
 */
void Point_3D::setX(float x) { this->x = x; }

/**
 * @brief set y value
 * 
 * @param y y value
 */
void Point_3D::setY(float y) { this->y = y; }

/**
 * @brief set z value
 * 
 * @param z z value
 */
void Point_3D::setZ(float z) { this->z = z; }

/**
 * @brief change (x,y,z) coordinates of point
 * 
 * @param x x coord
 * @param y y coord
 * @param z z coord
 */
void Point_3D::setPointTo(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * @brief calculates the cross product between itself and another point
 * 
 * @param p point
 * @return Point_3D cross product result 
 */
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

/**
 * @brief normalizes a point
 * 
 */
void Point_3D::normalize() {

    float length = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));

    if (length != 0){
        this->setX(this->getX() / length);
        this->setY(this->getY() / length);
        this->setZ(this->getZ() / length);
    }
}

/**
 * @brief toString operation
 * 
 * @return string 
 */
string Point_3D::toString() {

    stringstream ss;
    ss.precision(4);
    ss << fixed << x << "," << y << "," << z;
    string s = ss.str();
    return s;
}


// ------------------------------------------------------------------------------- out of class functions


/**
 * @brief normalizes a point, without changing it's original value
 * 
 * @param p1 point to normalize
 * @return Point_3D normalized point
 */
Point_3D getNormalize(Point_3D p1){
    Point_3D p;
    float length = sqrt(pow(p1.getX(), 2) + pow(p1.getY(), 2) + pow(p1.getZ(), 2));

    if (length != 0){
        p.setX(p1.getX() / length);
        p.setY(p1.getY() / length);
        p.setZ(p1.getZ() / length);
    }

    return p;
}

/**
 * @brief calculates a surface (triangle) normal by it's vertices
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 * @return Point_3D 
 */
Point_3D getNormal(Point_3D p1, Point_3D p2, Point_3D p3){

    /*
        A = p2 - p1
        B = p3 - p1
    */
    Point_3D a = Point_3D(p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ());
    Point_3D b = Point_3D(p3.getX() - p1.getX(), p3.getY() - p1.getY(), p3.getZ() - p1.getZ());
    
    Point_3D normal = a.crossProduct(b);
    normal.normalize();

    return normal;
}


Point_3D polarToPoint3D(float radius,float height, float alpha){
    float x = radius*sin(alpha);
    float y = height;
    float z = radius*cos(alpha);

    return Point_3D(x,y,z);
}


/**
 * @brief sum of two points
 * 
 * @param p1 point 1
 * @param p2 point 2
 * @return Point_3D sum's result
 */
Point_3D sum(Point_3D p1, Point_3D p2){

    Point_3D a = Point_3D();
    a.setX(p1.getX() + p2.getX());
    a.setY(p1.getY() + p2.getY());
    a.setZ(p1.getZ() + p2.getZ());
    return a;
}

/**
 * @brief subtraction of two points
 * 
 * @param p1 point 1
 * @param p2 point 2
 * @return Point_3D subtraction's result
 */
Point_3D sub(Point_3D p1, Point_3D p2){

    Point_3D a = Point_3D();
    a.setX(p1.getX() - p2.getX());
    a.setY(p1.getY() - p2.getY());
    a.setZ(p1.getZ() - p2.getZ());
    return a;
}

/**
 * @brief multiplication of two points
 * 
 * @param p1 point 1
 * @param p2 point 2
 * @return Point_3D product's result
 */
Point_3D mul(Point_3D p1, Point_3D p2){

    Point_3D a = Point_3D();
    a.setX(p1.getX() * p2.getX());
    a.setY(p1.getY() * p2.getY());
    a.setZ(p1.getZ() * p2.getZ());
    return a;
}