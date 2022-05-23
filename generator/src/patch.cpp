#include "../headers/patch.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Construct a new Patch:: Patch object
 * 
 * @param filename 
 * @param tess 
 * @param outputFile 
 */
Patch::Patch(string filename, unsigned int tess, string outputFile){
    
    patchFile = string(filename);
    patchOutputFile = string(outputFile);
    tesselation = tess;
    nPatches = 0;
    nVertices = 0;
    patchIndices = vector<vector<int>>();
    patchVertices = vector<Point_3D>();

    parsePatchFile();
}

/**
 * @brief devolve o número de patches
 * 
 * @return unsigned int 
 */
unsigned int Patch::getNPatches(){
    return nPatches;
}

/**
 * @brief devolve o número de pontos
 * 
 * @return unsigned int 
 */
unsigned int Patch::getNVertices(){
    return nVertices;
}

/**
 * @brief devolve o nome do ficheiro do patch
 * 
 * @return string 
 */
string Patch::getPatchFilename(){
    return string(patchFile);
}

/**
 * @brief devolve o nome do ficheiro de output gerado
 * 
 * @return string 
 */
string Patch::getOutputFilename(){
    return string(patchOutputFile);
}

/**
 * @brief Captura os índices presentes numa linha do patch file
 * 
 * @param line 
 * @return vector<int> 
 */
vector<int> catchIndexes(string line){

    vector<string> parser = vector<string>();
    stringstream ss(line);

	while (ss.good()){
	    string subs;
	    getline(ss,subs,',');
	    parser.push_back(subs);
	}
    vector<int> indexes = vector<int>();
    for(string s : parser){
        indexes.push_back(stoi(s));
    }
    return indexes;
}

/**
 * @brief captura os pontos presentes numa linha do patch file
 * 
 * @param line 
 * @return Point_3D 
 */
Point_3D catchPoint(string line){

    vector<string> parser = vector<string>();
    stringstream ss(line);

	while (ss.good()){
	    string subs;
	    getline(ss,subs,',');
	    parser.push_back(subs);
    }
    
    float x = stof(parser.at(0));
	float y = stof(parser.at(1));
	float z = stof(parser.at(2));

    return Point_3D(x,y,z);
}

/**
 * @brief Leitura completa de um patch file
 * 
 */
void Patch::parsePatchFile(){

    string openFile = "../models/" + patchFile;
    ifstream inFile;
    inFile.open(openFile);

    if (inFile.is_open()){

        int index = 0;
        string line = "";

        // PATCH INDEXES

        getline(inFile, line);
        nPatches = stoi(line);

        while (index < nPatches && getline(inFile, line)){
            
            vector<int> indexes = catchIndexes(line);
            patchIndices.push_back(indexes);
            index++;
        }

        // PATCH POINTS

        getline(inFile, line);
        nVertices = stoi(line);
        index = 0;

        while (getline(inFile, line) && index < nVertices){
            
            Point_3D p = catchPoint(line);
            patchVertices.push_back(p);
            index++;
        }
    }
    else {
        cout << "Error: could not open file \"" << openFile << "\"" << endl;
        exit(0);
    }

    inFile.close();
}

/**
 * @brief Dado o índice do patch que se pretende, devolve os pontos associados a esse patch
 * 
 * @param index 
 * @return vector<Point_3D> 
 */
vector<Point_3D> Patch::getPatchLevel(int index){

    vector<int> patch = patchIndices.at(index);
    int patchSize = patch.size();                       // numero de pontos no patch
    vector<Point_3D> points = vector<Point_3D>();       // pontos do patch


    for(int i = 0; i < patchSize; i++){

        // adicionar cada ponto do patch
        points.push_back(patchVertices.at(patch.at(i)));
    }

    return points;
}

/**
 * BEZIER POLYNOMIAL
 * 
 * p(t) = (1-t)^3 * t^0 * p0   +   (1-t)^2 * t^1 * p1   +   (1-t)^1 * t^2 * p2   +   (1-t)^0 * t^3 * p3
 * 
 * 1 : (1 - 3t + 3t^2 - t^3) p0
 * 2 : (t - 2t^2 + t^3) p1
 * 3 : (t^2 - t^3) p2
 * 4 : (t^3) p3
 */


/**
 * @brief Multiplicação do vetor T pela matriz dos coeficientes de Bezier
 * 
 * @param vector 1x4
 * @param matrix (4x4) converted to (1x16)
 * @param answer 1x4
 * @return float* matriz com o resultado final da multiplicação
 */
void vectorByMatrix(float* vector, float *matrix, float *answer){

    for (int l = 0; l < 4; l++){

        answer[l] = 0;

        for (int c = 0; c < 4; c++){
            
            answer[l] += vector[c] * matrix[4 * l + c];
        }
    }
}

/**
 * @brief Multiplicação de um vector por uma matriz de pontos 3D
 * 
 * @param vector (1x4) vector de floats
 * @param pointMatrix (4x4) -> (1x16) matriz de pontos 3d
 * @param answer (1x4) array de pontos 3d
 */
void vectorByPointMatrix(float *vector, Point_3D *pointMatrix, Point_3D *answer){

    float x,y,z;

    for (int l = 0; l < 4; l++){

        x = 0.f, y = 0.f, z = 0.f;

        for (int c = 0; c < 4; c++){

            Point_3D p = (pointMatrix[4*l+c]);
            x += vector[c] * p.getX();
            y += vector[c] * p.getY();
            z += vector[c] * p.getZ();
        }
        answer[l] = Point_3D(x,y,z);
    }
}

/**
 * @brief Multiplicaçã de um vector de pontos 3d por uma matriz de floats
 * 
 * @param pointVector (1x4) vector de pontos 3d
 * @param matrix (4x4) vector de floats
 * @param answer (1x4) array de pontos 3d
 */
void pointVectorByMatrix(Point_3D *pointVector, float *matrix, Point_3D *answer){

    float x,y,z;

    for (int l = 0; l < 4; l++){

        x = 0, y = 0, z = 0;

        for (int c = 0; c < 4; c++){

            Point_3D p = pointVector[c];

            float current = matrix[4*l+c];

            x += p.getX() * current;
            y += p.getY() * current;
            z += p.getZ() * current;
        }

        answer[l] = Point_3D(x,y,z);
    }
}

/**
 * @brief Calcula um vértice de um patch
 * 
 * @param index patch associado
 * @param u 
 * @param v 
 * @return Point_3D 
 */
Point_3D Patch::calculatePatchVertex(int index, float u, float v){

    // pontos de controlo do patch neste nível
    vector<Point_3D> controlPoints = getPatchLevel(index);

    float BezierMatrix[4][4] = {

                    {-1.0f, 3.0f, -3.0f, 1.0f},
                    {3.0f, -6.0f, 3.0f, 0.0f},
                    {-3.0f, 3.0f, 0.0f, 0.0f},
                    {1.0f, 0.0f, 0.0f, 0.0f}
                };

    Point_3D points[4][4];

    for (int l = 0; l < 4; l++){
        for (int c = 0; c < 4; c++){
            points[l][c] = controlPoints.at(4*l+c);
        }
    }

    /* auxiliar vectors:
        U = [U^3    U^2   U   1]
        V = [V^3    V^2   V   1]
    */
    float V[4] = {v * v * v, v * v, v, 1};
    float U[4] = {u * u * u, u * u, u, 1};

    /*
        P(u,v) = U * MBezier * Mpts * MBezier^T * V

        mv = MBezier^T * V
        pM = Mpts * mv
        finalM = pM * MBezier

        P(u,v) = U * finalM
    */
    float mv[4];
    vectorByMatrix(V, (float*) BezierMatrix, mv);
    Point_3D pM[4];
    vectorByPointMatrix(mv, (Point_3D*)points, pM);

    Point_3D finalM[4];
    pointVectorByMatrix(pM, (float*) BezierMatrix, finalM);

    float x = U[0] * finalM[0].getX() + U[1] * finalM[1].getX() + U[2] * finalM[2].getX() + U[3] * finalM[3].getX();
    float y = U[0] * finalM[0].getY() + U[1] * finalM[1].getY() + U[2] * finalM[2].getY() + U[3] * finalM[3].getY();
    float z = U[0] * finalM[0].getZ() + U[1] * finalM[1].getZ() + U[2] * finalM[2].getZ() + U[3] * finalM[3].getZ();

    return Point_3D(x,y,z);
}

/**
 * @brief Calcula os pontos de uma curva associada a um patch, num dado intervalo
 * 
 * @param patchLevel 
 * @param u 
 * @param v 
 * @param interval 
 */
void Patch::calculateCurve(vector<Point_3D> *result, int patchLevel, float u, float v, float interval){

    Point_3D p01 = calculatePatchVertex(patchLevel, u, v);
    Point_3D p02 = calculatePatchVertex(patchLevel, u, v + interval);
    Point_3D p03 = calculatePatchVertex(patchLevel, u + interval, v);
    Point_3D p04 = calculatePatchVertex(patchLevel, u + interval, v + interval);

    /**
     *      2 ----- 4
     *      |       |
     *      |       |
     *      1 ----- 3
     */

    result->push_back(p01);
    result->push_back(p04);
    result->push_back(p02);

    result->push_back(p04);
    result->push_back(p01);
    result->push_back(p03);
}

/**
 * @brief cálculo dos pontos que formam a superfície de bezier
 * 
 * @param result 
 */
void Patch::patchResultPoints(vector<Point_3D> *result){

    float u, v, interval;

    for (int i = 0; i < nPatches; i++){

        u = 0.0f; v = 0.0f;
        if (tesselation == 0)
            interval = 1;
        else
            interval = (float) 1.0 / tesselation;

        for (int uSlice = 0; uSlice < tesselation; uSlice++){

            for (int vSlice = 0; vSlice < tesselation; vSlice++){

                calculateCurve(result, i, u, v, interval);
                v += interval;
            }
            u += interval;
            v = 0.0f;
        }
    }
}


/**
 * @brief escrita da informação da figura num ficheiro 3d
 * 
 */
void Patch::toFile(){

    vector<Point_3D> patchPoints = vector<Point_3D>();
    patchResultPoints(&patchPoints);

    ofstream outFile;
    string outputFile = "../3D/" + patchOutputFile;

    outFile.open(outputFile, ios::out | ios::trunc);

    if (outFile.is_open()){
        
        int size = patchPoints.size();
        // Número de pontos, número de índices
        outFile << size << "," << (size) << endl;
        
        
        for (int i = 0; i < size; i += 3) {

            // point 1 2 3
            Point_3D p1 = patchPoints.at(i);
            Point_3D p2 = patchPoints.at(i+1);
            Point_3D p3 = patchPoints.at(i+2);

            // calculate normal from triangle
            Point_3D normal = getNormal(p1,p2,p3);

            // output vertex + normal
            outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << normal.toString() << ", " << endl;
        }
        outFile.close();
    }
}