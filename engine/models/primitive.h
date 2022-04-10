#ifndef PRIMITIVE_HEADER
#define PRIMITIVE_HEADER

#include <string>
#include <vector>
#include "../../utils/point_3d.h"

using namespace std;


class Primitive {

    private:
        string filename;
        string primitiveName;
        //GLuint vbuffer;
        unsigned int vBuffer;
        unsigned int nPoints;
        unsigned int nIndexes;
        float r,g,b;

    public:
        
        Primitive() = default;

        Primitive(string file) {
            filename = file;
            getFigure(file);
            r = 1.0f; g = 0.0f; b = 0.0f;
        }

        void getFigure(string file);

        string getFilename();
        string getPrimitiveName();
        vector<float> getColor();
        int getVBO();
        int getNPoints();
        int getNIndexes();

        void setColor(vector<float> rgbColor);
        void setFilename(string s);
        void setPrimitiveName(string s);
        Primitive clone();

        void draw();
};

#endif