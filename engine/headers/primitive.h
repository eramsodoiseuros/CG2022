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
        
        bool isEmissiva;
        Point_3D emissiva;

        bool isAmbiente;
        Point_3D ambiente;

        bool isDifusa;
        Point_3D difusa;

        bool isEspecular;
        Point_3D especular;

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
        vector<Transformation*> getTransformations();
        vector<Primitive> getAppendedPrimitives();
        
        bool isLuzEmissiva();
        bool isLuzAmbiente();
        bool isLuzDifusa();
        bool isLuzEspecular();

        Point_3D getEmissiva();
        Point_3D getAmbiente();
        Point_3D getDifusa();
        Point_3D getEspecular();

        // sets
        void setTypeMaterial(string s);
        void setFilename(string s);
        void setTextureFilename(string s);
        void setTransformations(vector<Transformation*> transf);
        void setAppendedPrimitives(vector<Primitive> primitives);
        
        void setIsEmissiva(bool b);
        void setIsAmbiente(bool b);
        void setIsDifusa(bool b);
        void setIsEspecular(bool b);

        void setEmissiva(Point_3D p);
        void setAmbiente(Point_3D p);
        void setDifusa(Point_3D p);
        void setEspecular(Point_3D p);

        // drawing function
        void addAppendedPrimitive(Primitive p);
        void addTransformation(Transformation *a);
        Primitive clone();
        void printInfo();
        void Draw();
};

#endif