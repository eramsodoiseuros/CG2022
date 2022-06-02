#include "../../headers/color.h"

/**
 * @brief Construct a new Color:: Color object with default values
 * 
 */
Color::Color(){
    diffR = 0.0f; diffG = 0.0f; diffB = 0.0f;
    ambiR = 0.0f; ambiG = 0.0f; ambiB = 0.0f;
    specR = 0.0f; specG = 0.0f; specB = 0.0f;
    emissR = 0.0f; emissG = 0.0f; emissB = 0.0f;
    shininess = 0.0f;
}

/**
 * @brief Construct a new Color:: Color object
 * 
 * @param diffR 
 * @param diffG 
 * @param diffB 
 * @param specR 
 * @param specG 
 * @param specB 
 * @param ambiR 
 * @param ambiG 
 * @param ambiB 
 * @param emissR 
 * @param emissG 
 * @param emissB 
 * @param shininess 
 */
Color::Color(float diffR, float diffG, float diffB,
                float specR, float specG, float specB,
                float ambiR, float ambiG, float ambiB,
                float emissR, float emissG, float emissB,
                float shininess){

    this->diffR = diffR; this->diffG = diffG; this->diffB = diffB;
    this->ambiR = ambiR; this->ambiG = ambiG; this->ambiB = ambiB;
    this->specR = specR; this->specG = specG; this->specB = specB;
    this->emissR = emissR; this->emissG = emissG; this->emissB = emissB;
    this->shininess = shininess;
}
        
/**
 * @brief get diffuse values
 * 
 * @return vector<float> 
 */
vector<float> Color::getDiffuse(){

    vector<float> answer = vector<float>();
    answer.push_back(diffR);
    answer.push_back(diffG); 
    answer.push_back(diffB);
    return answer;
}

/**
 * @brief get specular values
 * 
 * @return vector<float> 
 */
vector<float> Color::getSpecular(){

    vector<float> answer = vector<float>();
    answer.push_back(specR);
    answer.push_back(specG); 
    answer.push_back(specB);
    return answer;
}

/**
 * @brief get ambient values
 * 
 * @return vector<float> 
 */
vector<float> Color::getAmbient(){

    vector<float> answer = vector<float>();
    answer.push_back(ambiR);
    answer.push_back(ambiG); 
    answer.push_back(ambiB);
    return answer;
}

/**
 * @brief get emissive values
 * 
 * @return vector<float> 
 */
vector<float> Color::getEmissive(){

    vector<float> answer = vector<float>();
    answer.push_back(emissR);
    answer.push_back(emissG); 
    answer.push_back(emissB);
    return answer;
}

/**
 * @brief get shininess value
 * 
 * @return float 
 */
float Color::getShininess(){

    return shininess;
}

/**
 * @brief set diffuse values
 * 
 * @param value 
 */
void Color::setDiffuse(vector<float> value){
    diffR = value.at(0);
    diffG = value.at(1);
    diffB = value.at(2);
}

/**
 * @brief set specular values
 * 
 * @param value 
 */
void Color::setSpecular(vector<float> value){
    specR = value.at(0);
    specG = value.at(1);
    specB = value.at(2);
}

/**
 * @brief set ambient values
 * 
 * @param value 
 */
void Color::setAmbient(vector<float> value){
    ambiR = value.at(0);
    ambiG = value.at(1);
    ambiB = value.at(2);
}

/**
 * @brief set emissive values
 * 
 * @param value 
 */
void Color::setEmissive(vector<float> value){
    emissR = value.at(0);
    emissG = value.at(1);
    emissB = value.at(2);
}

/**
 * @brief set shininess
 * 
 * @param value 
 */
void Color::setShininess(float value){
    shininess = value;
}



void Color::Apply(){

    float ambientStrength = 0.1f;

    float l2[] = { diffR, diffG, diffB, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, l2);

    float l0[] = { emissR, emissG, emissB, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, l0);

    float l3[] = { specR, specG, specB, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, l3);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
   
    float l1[] = { ambiR * ambientStrength, ambiG * ambientStrength, ambiB * ambientStrength, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, l1);
}