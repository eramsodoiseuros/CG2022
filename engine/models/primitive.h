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
        vector<Point_3D> points;
        float r,g,b;

    public:
        
        Primitive() = default;

        Primitive(string file) {
            filename = file;
            points = vector<Point_3D>();
            getFigure(file);
            r = 1.0f; g = 0.0f; b = 0.0f;
        }

        void getFigure(string file);

        string getFilename();
        string getPrimitiveName();
        vector<Point_3D> getPoints();
        vector<float> getColor();

        void setFilename(string file);
        void setPrimitiveName(string name);
        void setPoints(vector<Point_3D> p);
        void setColor(vector<float> rgbColor);

        Primitive clone();

        void drawPlane();
        void drawBox();
        void drawCone();
        void drawSphere();
};

#endif