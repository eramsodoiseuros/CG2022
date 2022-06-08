#ifndef SCALE_FILE_HEADER
#define SCALE_FILE_HEADER

#include "transformation.h"

class Scale : public Transformation{

    private:
        float x,y,z;
    
    public:
        Scale();
        Scale(float x, float y, float z);

        float getX();
        float getY();
        float getZ();

        void setX(float n);
        void setY(float n);
        void setZ(float n);
        
        void Apply();
};

#endif