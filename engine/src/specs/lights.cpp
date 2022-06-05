#include "../../headers/lights.h"

using namespace std;

/*--------------------------------------------> LIGHTS */

Lights::Lights() {

    pointLights = vector<PointLight>();
    directionalLights = vector<DirectionalLight>();
    spotLights = vector<SpotLight>();
    counter = 0;
}

int Lights::getCounter(){
    switch(this->counter){
        case 0:{
            return GL_LIGHT0;
        }
        case 1:{
            return GL_LIGHT1;
        }
        case 2:{
            return GL_LIGHT2;
        }
        case 3:{
            return GL_LIGHT3;
        }
        case 4:{
            return GL_LIGHT4;
        }
        case 5:{
            return GL_LIGHT5;
        }
        case 6:{
            return GL_LIGHT6;
        }
        case 7:{
            return GL_LIGHT7;
        }
        default: {
            return -1;
        }
    }
}

void Lights::setCounter(int n){
    this->counter = n;
}

vector<PointLight> Lights::getPointLights() {
    return vector<PointLight>(pointLights);
}

vector<DirectionalLight> Lights::getDirectionalLights() {
    return vector<DirectionalLight>(directionalLights);
}


vector<SpotLight> Lights::getSpotLights() {
    return vector<SpotLight>(spotLights);
}


void Lights::addPointLight(PointLight pl) {
    pointLights.push_back(pl);
}


void Lights::addDirectionalLight(DirectionalLight dl) {
    directionalLights.push_back(dl);
}


void Lights::addSpotLight(SpotLight sl) {
    spotLights.push_back(sl);
}



void Lights::Apply() {

    int l1  = 0;
    GLfloat dark[4] = {0.0, 0.0, 0.0, 1};
    GLfloat white[4] = {0.9,0.9,0.9,0.9};

    // attenuation
    //float quat_att = 1.0f;
    //lLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quat_att);

    bool never = true;
    for (PointLight pl : pointLights){
        l1 = this->getCounter();

        if(l1!=-1){

            never = false;
            glLightfv(l1, GL_AMBIENT, dark);
            glLightfv(l1, GL_DIFFUSE, white);
            glLightfv(l1, GL_SPECULAR, white);
            glLightfv(l1, GL_EMISSION, white);
            pl.Apply(l1);
            setCounter(counter+1);
        }
    }

    for (DirectionalLight dl : directionalLights){
        l1 = this->getCounter();

        if(l1!=-1){
            never = false;
            glLightfv(l1, GL_AMBIENT, dark);
            glLightfv(l1, GL_DIFFUSE, white);
            glLightfv(l1, GL_SPECULAR, white);
            glLightfv(l1, GL_EMISSION, white);
            dl.Apply(l1);
            setCounter(counter+1);
        }
    }


    for (SpotLight sl : spotLights){
        l1 = this->getCounter();

        if(l1!=-1){
            never = false;
            glLightfv(l1, GL_AMBIENT, dark);
            glLightfv(l1, GL_DIFFUSE, white);
            glLightfv(l1, GL_SPECULAR, white);
            glLightfv(l1, GL_EMISSION, white);
            sl.Apply(l1);
            setCounter(counter+1);
        }
    }

    if(never){
        l1 = this->getCounter();
        glEnable(l1);

        glLightfv(l1, GL_AMBIENT, dark);
        glLightfv(l1, GL_DIFFUSE, white);
        glLightfv(l1, GL_SPECULAR, white);
        glLightfv(l1, GL_EMISSION, white);
    }
}



/*--------------------------------------------> POINT_LIGHT */

PointLight::PointLight(float x, float y, float z) {

    posX = x; posY = y; posZ = z;
}

vector<float> PointLight::getPos() {
    vector<float> answer = vector<float>();
    answer.push_back(posX);
    answer.push_back(posY);
    answer.push_back(posZ);
    return answer;
}

void PointLight::setPos(float x, float y, float z) {
    posX = x; posY = y; posZ = z;
}

void PointLight::Apply(int c) {
    glEnable(c);

    float pos[] = { posX, posY, posZ, 1.0f };
    glLightfv(c, GL_POSITION, pos);
}

string PointLight::toString() {

    string s = "PointLight: posX::" + std::to_string(posX) + ", posY::" + std::to_string(posY) + ", posZ::" + std::to_string(posZ);
    return s;
}

/*--------------------------------------------> DIRECTIONAL_LIGHT */

DirectionalLight::DirectionalLight(float x, float y, float z) {

    dirX = x; dirY = y; dirZ = z;
}

vector<float> DirectionalLight::getDirectional() {
    vector<float> answer = vector<float>();
    answer.push_back(dirX);
    answer.push_back(dirY);
    answer.push_back(dirZ);
    return answer;
}

void DirectionalLight::setDirectional(float x, float y, float z) {
    dirX = x; dirY = y; dirZ = z;
}

void DirectionalLight::Apply(int c) {
    glEnable(c);

    float dir[] = { dirX, dirY, dirZ, 0.0f };
    glLightfv(c, GL_POSITION, dir);
}

string DirectionalLight::toString() {

    string s = "DirectionalLight: dirx::" + std::to_string(dirX) + ", dirY::" + std::to_string(dirY) + ", dirZ::" + std::to_string(dirZ);
    return s;
}

/*--------------------------------------------> SPOT_LIGHT */

SpotLight::SpotLight(float posX, float posY, float posZ,
    float dirX, float dirY, float dirZ,
    float cut) {

    this->posX = posX; this->posY = posY; this->posZ = posZ;
    this->dirX = dirX; this->dirY = dirY; this->dirZ = dirZ;
    this->cutoff = (cut > 180) ? 180 : (cut < 0 ? 0 : cut);
}

vector<float> SpotLight::getPos() {
    vector<float> answer = vector<float>();
    answer.push_back(posX);
    answer.push_back(posY);
    answer.push_back(posZ);
    return answer;
}

void SpotLight::setPos(vector<float> value) {
    posX = value.at(0);
    posY = value.at(1);
    posZ = value.at(2);
}

vector<float> SpotLight::getDirectional() {
    vector<float> answer = vector<float>();
    answer.push_back(dirX);
    answer.push_back(dirY);
    answer.push_back(dirZ);
    return answer;
}

void SpotLight::setDirectional(vector<float> value) {
    dirX = value.at(0);
    dirY = value.at(1);
    dirZ = value.at(2);
}

float SpotLight::getCutoff() {
    return cutoff;
}

void SpotLight::setCutoff(float value) {

    cutoff = (value > 180) ? 180 : (value < 0 ? 0 : value);
}

void SpotLight::Apply(int c) {

    glEnable(c);

    float pos[] = { posX, posY, posZ, 1.0f };
    float dir[] = { dirX, dirY, dirZ };

    glLightfv(c, GL_POSITION, pos);
    glLightfv(c, GL_SPOT_DIRECTION, dir);
    
    glLightf(c, GL_SPOT_CUTOFF, cutoff);
    // cutoff : [0, 90] ou 180
}

string SpotLight::toString() {

    string s = "SpotLight: posX::" + std::to_string(posX) + ", posY::" + std::to_string(posY) + ", posZ::" + std::to_string(posZ) + "\ndirx::" + std::to_string(dirX) + ", dirY::" + std::to_string(dirY) + ", dirZ::" + std::to_string(dirZ);
    s += "\ncutoff::" + std::to_string(cutoff);
    return s;
}