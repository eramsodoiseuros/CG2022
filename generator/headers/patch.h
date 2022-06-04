#ifndef PATCH_HEADER
#define PATCH_HEADER

#include <vector>
#include <string>
#include "../../utils/point_3d.h"
#include "../../utils/point_2d.h"

using namespace std;

class Patch {

private:

    string patchFile;
    string patchOutputFile;

    unsigned int tesselation;
    unsigned int nPatches;              // number of lines with patch's indexes
    unsigned int nVertices;             // number of lines with patch's points

    vector<vector<int>> patchIndices;
    vector<Point_3D> patchVertices;
    vector<Point_3D> normals;
    vector<Point_2D> texs;

    void parsePatchFile();

public:

    /**
     * @brief Construct a new Patch object
     * 
     * @param filename 
     * @param tess 
     * @param outputFile 
     */
    Patch(string filename, unsigned int tess, string outputFile);

    unsigned int getNPatches();
    unsigned int getNVertices();
    string getPatchFilename();
    string getOutputFilename();
    vector<vector<int>> getPatchIndices();
    vector<Point_3D> getPatchVertices();
    vector<Point_3D> getNormals();

    vector<Point_3D> getPatchLevel(int index);
    Point_3D calculatePatchVertex(int index, float u, float v, Point_3D* uTangent, Point_3D* vTangent);
    void calculateCurve(vector<Point_3D>* result, int patchLevel, float u, float v, float interval);
    
    /**
     * @brief calculate all points from patch's figure (main function)
     * 
     * @param result 
     */
    void patchResultPoints(vector<Point_3D>* result);
    void toFile();
};



// auxiliar functions



/**
  * @brief Multiplicação do vetor T pela matriz dos coeficientes de Bezier
  *
  * @param vector 1x4
  * @param matrix (4x4) converted to (1x16)
  * @param answer 1x4
  * @return float* matriz com o resultado final da multiplicação
  */
void vectorByMatrix(float vector[], float* matrix, float* answer);

/**
 * @brief Multiplicação de um vector por uma matriz de pontos 3D
 *
 * @param vector (1x4) vector de floats
 * @param pointMatrix (4x4) -> (1x16) matriz de pontos 3d
 * @param answer (1x4) array de pontos 3d
 */
void vectorByPointMatrix(float* vector, Point_3D* pointMatrix, Point_3D* answer);

/**
 * @brief Multiplicaçã de um vector de pontos 3d por uma matriz de floats
 *
 * @param pointVector (1x4) vector de pontos 3d
 * @param matrix (4x4) vector de floats
 * @param answer (1x4) array de pontos 3d
 */
void pointVectorByMatrix(Point_3D* pointVector, float* matrix, Point_3D* answer);

#endif