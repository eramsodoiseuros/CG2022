#include "point_2d.h"

/**
 * @brief Construct a new Point_2D::Point_2D object
 * 
 */
Point_2D::Point_2D() {
    x = 0.0f;
    y = 0.0f;
}

/**
 * @brief Construct a new Point_2D::Point_2D object
 * 
 * @param p1 x value
 * @param p2 y value
 */
Point_2D::Point_2D(float p1, float p2) {
    this->x = p1;
    this->y = p2;
}

/**
 * @brief get x value
 * 
 * @return float x value
 */
float Point_2D::getX() { return this->x; }

/**
 * @brief get y value
 * 
 * @return float y value
 */
float Point_2D::getY() { return this->y; }

/**
 * @brief set x value
 * 
 * @param x x value
 */
void Point_2D::setX(float x) { this->x = x; }

/**
 * @brief set y value
 * 
 * @param y y value
 */
void Point_2D::setY(float y) { this->y = y; }


/**
 * @brief change (x,y) values of point
 * 
 * @param x x value
 * @param y y value
 */
void Point_2D::setPointTo(float x, float y) {
    this->x = x;
    this->y = y;
}

/**
 * @brief point's info
 * 
 * @return string 
 */
string Point_2D::toString() {
    stringstream ss;
    ss.precision(4);
    ss << fixed << x << "," << y;
    string s = ss.str();
    return s;
}