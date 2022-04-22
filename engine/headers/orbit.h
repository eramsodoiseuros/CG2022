#ifndef BODY_ORBIT_HEADER
#define BODY_ORBIT_HEADER

#include <vector>
using namespace std;

class Orbit {

    private:
        float rotateAngle, rotateX, rotateY, rotateZ;
        float scaleX, scaleY, scaleZ;
        float radX, radZ;
    
    public:

        Orbit() = default;

        Orbit(vector<float> values){

            if (values.size() != 9){
                throw 1;
            }
            else{
                rotateAngle = values.at(0); rotateX = values.at(1); rotateY = values.at(2); rotateZ = values.at(3);
                scaleX = values.at(4); scaleY = values.at(5); scaleZ = values.at(6);
                radX = values.at(7); radZ = values.at(8);
            }
        }

        Orbit(float rX, float rY, float rZ, float sX, float sY, float sZ, float radXX, float radZZ){

            rotateX = rX; rotateY = rY; rotateZ = rZ;
            scaleX = sX; scaleY = sY; scaleZ = sZ;
            radX = radXX; radZ = radZZ;
        }

        void setRotateAngle(float x);
        float getRotateAngle();

        void setRotateX(float x);
        float getRotateX();
        void setRotateY(float y);
        float getRotateY();
        void setRotateZ(float z);
        float getRotateZ();
        void setScaleX(float x);
        float getScaleX();
        void setScaleY(float y);
        float getScaleY();
        void setScaleZ(float z);
        float getScaleZ();
        void setRadX(float x);
        float getRadX();
        void setRadZ(float z);
        float getRadZ();
};

#endif