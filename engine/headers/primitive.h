#ifndef PRIMITIVE_HEADER
#define PRIMITIVE_HEADER

#include <string>
#include <vector>
#include "../../utils/point_3d.h"

using namespace std;


class Primitive {

    private:
        string filename;                // filename from 3d file
        string primitiveName;           // primitive name (ex: sphere, plane, ...)
        unsigned int vBuffer[2];           // VBOs
        unsigned int nPoints;           // number of points from the primitive
        unsigned int nIndexes;          // number of indexes used to print primitive's points
        float r,g,b;                    // r g and b values for primitive's color

    public:
        
        Primitive() {

            filename = string("");
            primitiveName = string("");
            vBuffer[0] = 0;
            vBuffer[1] = 0;
            nPoints = 0;
            nIndexes = 0;
            r = 0.0f; g = 0.0f; b = 0.0f;
        }

        Primitive(string file) {
            filename = file;
            getFigure(file);
            r = 1.0f; g = 0.0f; b = 0.0f;
        }

        void getFigure(string file);

        string getFilename();
        string getPrimitiveName();
        vector<float> getColor();
        unsigned int* getVBO();
        int getNPoints();
        int getNIndexes();

        void setColor(vector<float> rgbColor);
        void setFilename(string s);
        void setPrimitiveName(string s);
        Primitive clone();

        void draw();
};

#endif