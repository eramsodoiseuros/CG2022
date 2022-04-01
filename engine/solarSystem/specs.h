#ifndef CELESTIAL_BODY_SETTINGS_HEADER
#define CELESTIAL_BODY_SETTINGS_HEADER

#include <string>
#include <vector>

using namespace std;

class Settings{

    private:
        float translX, translY, translZ;
        float rotateAngle, rotateX, rotateY, rotateZ;
        float scaleX, scaleY, scaleZ;
        float r,g,b;
        string primitiveModel;

    public:

        Settings() = default;

        Settings(vector<float> sets, string model){

            if (sets.size() != 13){
                throw 1;
            }
            else{
                translX = sets.at(0); translY = sets.at(1); translZ = sets.at(2);
                rotateAngle = sets.at(3); rotateX = sets.at(4); rotateY = sets.at(5); rotateZ = sets.at(6);
                scaleX = sets.at(7); scaleY = sets.at(8); scaleZ = sets.at(9);

                r = sets.at(10); g = sets.at(11); b = sets.at(12);

                primitiveModel = model;
            }
        }

        void setTranslX(float x);
        float getTranslX();
        void setTranslY(float y);
        float getTranslY();
        void setTranslZ(float z);
        float getTranslZ();

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

        void setRGB(float x, float y, float z);
        float getColorR();
        float getColorG();
        float getColorB();

        void setPrimitiveName(string name);
        string getPrimitiveName();

        string toString();
};

#endif