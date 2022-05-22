#include "../headers/lights.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
using namespace std;

void Lights::setLightsAt(float x, float y, float z){
    this->position.setX(x);
    this->position.setY(y);
    this->position.setZ(z);
}

void Lights::changeType(string type){
	this->type = type;
}

Point_3D Lights::getLightsPosition(){
	return this->position;
}

string Lights::getType(){
	return this->type;
}