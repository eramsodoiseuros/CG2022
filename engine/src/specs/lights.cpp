#include "../../headers/lights.h"

using namespace std;

/*--------------------------------------------> LIGHTS */

Lights::Lights(){

    pointLights = vector<PointLight>();
    directionalLights = vector<DirectionalLight>();
    spotLights = vector<SpotLight>();
}

vector<PointLight> Lights::getPointLights(){
    return vector<PointLight>(pointLights);
}

vector<DirectionalLight> Lights::getDirectionalLights(){
    return vector<DirectionalLight>(directionalLights);
}


vector<SpotLight> Lights::getSpotLights(){
    return vector<SpotLight>(spotLights);
}


void Lights::addPointLight(PointLight pl){
    pointLights.push_back(pl);
}


void Lights::addDirectionalLight(DirectionalLight dl){
    directionalLights.push_back(dl);
}


void Lights::addSpotLight(SpotLight sl){
    spotLights.push_back(sl);
}


void Lights::Apply(){


}



/*--------------------------------------------> POINT_LIGHT */

PointLight::PointLight(float x, float y, float z){

    posX = x; posY = y; posZ = z;    
}

vector<float> PointLight::getPos(){
    vector<float> answer = vector<float>();
    answer.push_back(posX);
    answer.push_back(posY);
    answer.push_back(posZ);
    return answer;
}

void PointLight::setPos(float x, float y, float z){
    posX = x; posY = y; posZ = z;
}


/*--------------------------------------------> DIRECTIONAL_LIGHT */

DirectionalLight::DirectionalLight(float x, float y, float z){

    dirX = x; dirY = y; dirZ = z;
}

vector<float> DirectionalLight::getDirectional(){
    vector<float> answer = vector<float>();
    answer.push_back(dirX);
    answer.push_back(dirY);
    answer.push_back(dirZ);
    return answer;
}

void DirectionalLight::setDirectional(float x, float y, float z){
    dirX = x; dirY = y; dirZ = z;
}


/*--------------------------------------------> SPOT_LIGHT */

SpotLight::SpotLight(float posX, float posY, float posZ,
                        float dirX, float dirY, float dirZ,
                        float cutoff) {

    this->posX = posX; this->posY = posY; this->posZ = posZ;
    this->dirX = dirX; this->dirY = dirY; this->dirZ = dirZ;
    this->cutoff = cutoff;
}

vector<float> SpotLight::getPos(){
    vector<float> answer = vector<float>();
    answer.push_back(posX);
    answer.push_back(posY);
    answer.push_back(posZ);
    return answer;
}

void SpotLight::setPos(vector<float> value){
    posX = value.at(0);
    posY = value.at(1);
    posZ = value.at(2);
}

vector<float> SpotLight::getDirectional(){
    vector<float> answer = vector<float>();
    answer.push_back(dirX);
    answer.push_back(dirY);
    answer.push_back(dirZ);
    return answer;
}

void SpotLight::setDirectional(vector<float> value){
    dirX = value.at(0);
    dirY = value.at(1);
    dirZ = value.at(2);
}

float SpotLight::getCutoff(){
    return cutoff;
}

void SpotLight::setCutoff(float value){
    cutoff = value;
}