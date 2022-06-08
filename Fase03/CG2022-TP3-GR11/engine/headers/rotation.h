#ifndef ROTATION_HEADER_FILE
#define ROTATION_HEADER_FILE

#include "transformation.h"

class Rotation : public Transformation{

    private:
        float x,y,z,time,angle;

    public:
        Rotation();
        Rotation(float angle, float x, float y, float z, float time);

        float getAngle();
        float getX();
        float getY();
        float getZ();
        float getTime();

        void setAngle(float a);
        void setX(float n);
        void setY(float n);
        void setZ(float n);
        void setTime(float t);

        void Apply();
};

#endif