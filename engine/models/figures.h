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

        Primitive getPlane();
        Primitive getPlane(string file3d);

        Primitive getBox();
        Primitive getBox(string file3d);

        Primitive getCone();
        Primitive getCone(string file3d);

        Primitive getSphere();
        Primitive getSphere(string file3d);

        int getSize();

};
#endif