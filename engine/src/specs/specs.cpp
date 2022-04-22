#include "specs.h"
#include <iostream>
#include <string>

using namespace std;

void Settings::setTranslX(float x){
    translX = x;
}
float Settings:: getTranslX(){
    return translX;
}
void Settings::setTranslY(float y){
    translY = y;
}
float Settings:: getTranslY(){
    return translY;
}
void Settings::setTranslZ(float z){
    translZ = z;
}
float Settings:: getTranslZ(){
    return translZ;
}
void Settings::setRotateAngle(float x){
    rotateAngle = x;
}
float Settings::getRotateAngle(){
    return rotateAngle;
}
void Settings::setRotateX(float x){
    rotateX = x;
}
float Settings:: getRotateX(){
    return rotateX;
}
void Settings::setRotateY(float y){
    rotateY = y;
}
float Settings:: getRotateY(){
    return rotateY;
}
void Settings::setRotateZ(float z){
    rotateZ = z;
}
float Settings:: getRotateZ(){
    return rotateZ;
}
void Settings::setScaleX(float x){
    scaleX = x;
}
float Settings:: getScaleX(){
    return scaleX;
}
void Settings::setScaleY(float y){
    scaleY = y;
}
float Settings:: getScaleY(){
    return scaleY;
}
void Settings::setScaleZ(float z){
    scaleZ = z;
}
float Settings:: getScaleZ(){
    return scaleZ;
}
void Settings::setRGB(float x, float y, float z){
    r = x; g = y; b = z;
}
float Settings:: getColorR(){
    return r;
}
float Settings:: getColorG(){
    return g;
}
float Settings:: getColorB(){
    return b;
}
void Settings::setPrimitiveName(string name){
    primitiveModel = string(name);
}
string Settings::getPrimitiveName(){
    return string(primitiveModel);
}

string Settings::toString(){

    string s = "\nTransl(" + to_string(translX) + "," + to_string(translY) + "," + to_string(translZ)
            + ")\nRotate(" + to_string(rotateX) + "," + to_string(rotateY) + "," + to_string(rotateZ)
            + ")\nScale(" + to_string(scaleX) + "," + to_string(scaleY) + "," + to_string(scaleZ)
            + ")\nRGB(" + to_string(r) + "," + to_string(g) + "," + to_string(b) 
            + ")\nMODEL: " + primitiveModel;

    return s;
}