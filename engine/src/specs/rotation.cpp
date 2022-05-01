#include "../../headers/rotation.h"
#include "../../headers/GL_lib.h"

/**
 * @brief Construct a new Rotation:: Rotation object
 * 
 */
Rotation::Rotation(){
    angle = x = y = z = time = 0.0f;
}

/**
 * @brief Construct a new Rotation:: Rotation object
 * 
 * @param angle 
 * @param x 
 * @param y 
 * @param z 
 * @param time 
 */
Rotation::Rotation(float angle, float x, float y, float z, float time){
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
    this->time = time;
}

/**
 * @brief get angle
 * 
 * @return float 
 */
float Rotation::getAngle(){
    return angle;
}

/**
 * @brief get x value from rotation
 * 
 * @return float 
 */
float Rotation::getX(){
    return x;
}


/**
 * @brief get y value from rotation
 * 
 * @return float 
 */
float Rotation::getY(){
    return y;
}

/**
 * @brief get z value from rotation
 * 
 * @return float 
 */
float Rotation::getZ(){
    return z;
}

/**
 * @brief get time value from rotation
 * 
 * @return float 
 */
float Rotation::getTime(){
    return time;
}

/**
 * @brief set angle
 * 
 * @param a 
 */
void Rotation::setAngle(float a){
    this->angle = a;
}

/**
 * @brief set x
 * 
 * @param n 
 */
void Rotation::setX(float n){
    this->x = n;
}

/**
 * @brief set y
 * 
 * @param n 
 */
void Rotation::setY(float n){
    this->y = n;
}

/**
 * @brief set z
 * 
 * @param n 
 */
void Rotation::setZ(float n){
    this->z = n;
}

/**
 * @brief set time
 * 
 * @param t 
 */
void Rotation::setTime(float t){
    this->time = t;
}

/**
 * @brief apply rotation
 * 
 */
void Rotation::Apply(){

    if(!time){

        glRotatef(angle, x, y, z);
    }
    else{

        float elapsed, newAngle;
        elapsed = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
        newAngle = (elapsed*360) / (time * 1000);

        glRotatef(angle+newAngle, x, y, z);
    }
}
