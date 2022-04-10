#ifndef FIGURES_HEADER
#define FIGURES_HEADER

#include <string>
#include <vector>
#include "primitive.h"

using namespace std;

class Figures {

    private:
        vector<Primitive> primitives;

    public:

        Figures(){

            primitives = vector<Primitive>();
        }

        int addPrimitive(Primitive p);
        int addPrimitive(string file3d);
        int removePrimitive(Primitive p);
        int removePrimitive(string file3d);

        Primitive getPrimitive(string file3d);

        Primitive getPlane();
        Primitive getBox();
        Primitive getCone();
        Primitive getSphere();
        
        int getSize();

};
#endif