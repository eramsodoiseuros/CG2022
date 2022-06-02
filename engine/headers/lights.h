#ifndef LIGHTS_HEADER_FILE
#define LIGHTS_HEADER_FILE

#include "GL_lib.h"
#include <string>
#include <vector>

using namespace std;


/**
 * @brief Classe relativa a pontos de luz
 *
 */
class PointLight {

private:
    float posX, posY, posZ;

public:
    PointLight(float x, float y, float z);
    vector<float> getPos();
    void setPos(float x, float y, float z);
    void Apply();
};


/**
 * @brief Classe relativa a luz direcionada
 *
 */
class DirectionalLight {

private:
    float dirX, dirY, dirZ;

public:
    DirectionalLight(float x, float y, float z);
    vector<float> getDirectional();
    void setDirectional(float x, float y, float z);
    void Apply();
};


/**
 * @brief Classe relativa a um spotlight
 *
 */
class SpotLight {

private:
    float posX, posY, posZ, dirX, dirY, dirZ, cutoff;

public:

    SpotLight(float posX, float posY, float posZ,
        float dirX, float dirY, float dirZ,
        float cutoff);

    vector<float> getPos();
    void setPos(vector<float> value);
    vector<float> getDirectional();
    void setDirectional(vector<float> value);
    float getCutoff();
    void setCutoff(float value);
    void Apply();
};



/**
 * @brief Classe que agrupa todas as luzes
 * 
 */
class Lights{

    private:
        
        vector<PointLight> pointLights;
        vector<DirectionalLight> directionalLights;
        vector<SpotLight> spotLights;
        

    public:

        Lights();

        vector<PointLight> getPointLights();
        vector<DirectionalLight> getDirectionalLights();
        vector<SpotLight> getSpotLights();

        void addPointLight(PointLight pl);
        void addDirectionalLight(DirectionalLight dl);
        void addSpotLight(SpotLight sl);

        void Apply();
};

#endif