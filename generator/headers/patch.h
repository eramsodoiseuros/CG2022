#ifndef PATCH_HEADER
#define PATCH_HEADER

#include <vector>
#include <string>
#include "../../utils/point_3d.h"

using namespace std;

class Patch{

    private:

        string patchFile;
        string patchOutputFile;
        unsigned int tesselation;
        unsigned int nPatches;              // number of lines with patch's indexes
        unsigned int nVertices;             // number of lines with patch's points
        vector<vector<int>> patchIndices;
        vector<Point_3D> patchVertices;

        void parsePatchFile();
    
    public:

        Patch(string filename, unsigned int tess, string outputFile){
            patchFile = string(filename);
            patchOutputFile = string(outputFile);
            tesselation = tess;
            nPatches = 0;
            nVertices = 0;
            patchIndices = vector<vector<int>>();
            patchVertices = vector<Point_3D>();

            parsePatchFile();
        }

        unsigned int getNPatches();
        unsigned int getNVertices();
        string getPatchFilename();
        string getOutputFilename();
        vector<vector<int>> getPatchIndices;
        vector<Point_3D> getPatchVertices;
        
        vector<Point_3D> getPatchLevel(int index);
        Point_3D calculatePatchVertex(int index, float u, float v);
        void calculateCurve(vector<Point_3D> *result, int patchLevel, float u, float v, float interval);
        void patchResultPoints(vector<Point_3D> *result);
        void toFile();
};


void vectorByMatrix(float vector[], float* matrix, float* answer);
void vectorByPointMatrix(float *vector, Point_3D *pointMatrix, Point_3D *answer);
void pointVectorByMatrix(Point_3D *pointVector, float *matrix, Point_3D *answer);

#endif