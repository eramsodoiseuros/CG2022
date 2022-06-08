#ifndef COLOR_HEADER_FILE
#define COLOR_HEADER_FILE

#include "GL_lib.h"
#include <vector>
using namespace std;

class Color {

    private:

        float   diffR, diffG, diffB,
                specR, specG, specB,
                ambiR, ambiG, ambiB,
                emissR, emissG, emissB,
                shininess, r, g, b;
    
    public:

        Color();
        Color(float diffR, float diffG, float diffB,
                float specR, float specG, float specB,
                float ambiR, float ambiG, float ambiB,
                float emissR, float emissG, float emissB,
                float shininess, float r, float g, float b);
        
        
        vector<float> getDiffuse();
        vector<float> getSpecular();
        vector<float> getAmbient();
        vector<float> getEmissive();
        float getShininess();
        vector<float> getRGB();

        void setDiffuse(vector<float> value);
        void setSpecular(vector<float> value);
        void setAmbient(vector<float> value);
        void setEmissive(vector<float> value);
        void setShininess(float value);
        void setRGB(vector<float> value);

        void Apply();
};

#endif