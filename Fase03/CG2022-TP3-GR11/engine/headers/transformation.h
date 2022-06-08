#ifndef TRANSFORMATION_HEADER_FILE
#define TRANSFORMATION_HEADER_FILE

#include "GL_lib.h"

class Transformation{

    public:
        virtual void Apply(void) = 0;

};

#endif