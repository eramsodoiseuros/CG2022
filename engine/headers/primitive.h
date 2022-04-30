#ifndef PRIMITIVE_HEADER_FILE
#define PRIMITIVE_HEADER_FILE

#include <string>
#include <vector>
#include "transformation.h"

using namespace std;

class Primitive{

    private:
        string filename;                            // 3d file name
        unsigned int vBuffer[2];                    // VBOs (points, ??)
        unsigned int nPoints;                       // primitive's number of points
        unsigned int nIndexes;                      // primitive's number of indexes used to write 3d file
        float r,g,b;                                // r,g,b values for primitive's color (4th phase CHANGE)

        string textureFilename;                     // texture filename
        vector<Transformation*> transformations;    // list of transformations

        vector<Primitive> appendedPrimitives;

    public:

        void readPrimitive(string file);
        // constructors
        Primitive();
        Primitive(string filename);

        //gets
        string getFilename();
        string getTextureFilename();
        unsigned int getNPoints();
        unsigned int getNIndexes();
        vector<float> getColor();
        vector<Transformation*> getTransformations();
        vector<Primitive> getAppendedPrimitives();

        // sets
        void setColor(vector<float> rgbColor);
        void setFilename(string s);
        void setTextureFilename(string s);
        void setTransformations(vector<Transformation*> transf);
        void setAppendedPrimitives(vector<Primitive> primitives);
        
        // drawing function
        void addAppendedPrimitive(Primitive p);
        void addTransformation(Transformation *a);
        Primitive clone();
        void printInfo();
        void Draw();
};

#endif