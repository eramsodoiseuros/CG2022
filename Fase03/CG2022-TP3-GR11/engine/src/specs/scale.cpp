#include "../../headers/scale.h"
#include "../../headers/GL_lib.h"

/**
 * @brief Construct a new Scale:: Scale object
 * 
 */
Scale::Scale(){
    x = y = z = 0.0f;
}

/**
 * @brief Construct a new Scale:: Scale object
 * 
 * @param x 
 * @param y 
 * @param z 
 */
Scale::Scale(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * @brief get x value from scale
 * 
 * @return float 
 */
float Scale::getX(){
    return x;
}

/**
 * @brief get y value from scale
 * 
 * @return float 
 */
float Scale::getY(){
    return y;
}

/**
 * @brief get z value from scale
 * 
 * @return float 
 */
float Scale::getZ(){
    return z;
}

/**
 * @brief set x
 * 
 * @param x 
 */
void Scale::setX(float x){
    this->x = x;
}

/**
 * @brief set y
 * 
 * @param y 
 */
void Scale::setY(float y){
    this->y = y;
}

/**
 * @brief set z
 * 
 * @param z 
 */
void Scale::setZ(float z){
    this->z = z;
}

/**
 * @brief apply scale
 * 
 */
void Scale::Apply(){

    glScalef(this->x, this->y, this->z);
};
