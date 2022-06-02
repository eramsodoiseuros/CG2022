#ifndef PRIMITIVE_HEADER_FILE
#define PRIMITIVE_HEADER_FILE
#include <IL/il.h>
#include <string>
#include <vector>
#include "transformation.h"
#include "color.h"

using namespace std;



class Primitive{

    private:
        string filename;                            // 3d file name
        unsigned int vBuffer[3];                    // VBOs (points, ??)
        unsigned int nPoints;                       // primitive's number of points
        unsigned int nIndexes;                      // primitive's number of indexes used to write 3d file
        unsigned int textureID;
        
        string textureFilename;                     // texture filename
        vector<Transformation*> transformations;    // list of transformations
        Color colorComponents;

        vector<Primitive> appendedPrimitives;

    public:
        string DBPATH = "../3D/";

        void readPrimitive(string file);
        // constructors
        Primitive();
        Primitive(string filename);

        //gets
        string getFilename();
        string getTextureFilename();
        unsigned int getNPoints();
        unsigned int getNIndexes();
        vector<Transformation*> getTransformations();
        vector<Primitive> getAppendedPrimitives();
        Color getColorComponents();

        // sets
        void setTypeMaterial(string s);
        void setFilename(string s);
        void setTextureFilename(string s);
        void setTransformations(vector<Transformation*> transf);
        void setAppendedPrimitives(vector<Primitive> primitives);
        void setColorComponents(Color c);

        // drawing function
        void loadTexture();
        void addAppendedPrimitive(Primitive p);
        void addTransformation(Transformation *a);
        Primitive clone();
        void printInfo();
        void Draw();
};

#endif