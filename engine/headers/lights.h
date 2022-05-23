#ifndef LIGHTS_HEADER_FILE
#define LIGHTS_HEADER_FILE

#include "GL_lib.h"
#include <string>
#include <vector>

using namespace std;

class Lights{

    private:
        Point_3D position;
        string type; // Point | Directional | Spot

    public:

        void setLightsAt(float x, float y, float z);

        void changeType(string type);

        Point_3D getLightsPosition();

        string getType();
};

#endif