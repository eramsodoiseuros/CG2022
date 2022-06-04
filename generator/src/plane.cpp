#include "../headers/plane.h"
#include <list>
#include <cmath>
#include <vector>
#include <cstring>

#include <iostream>

using namespace std;

Plane::Plane() {

    length = 0;
    divisions = 0;
    p1 = Point_3D();
    p2 = Point_3D();
    p3 = Point_3D();
    planePoints = vector<Point_3D>();
    planePointsIndexes = vector<int>();
    normals = vector<Point_3D>();
    texs = vector<Point_2D>();
    nPoints = 0;
    nIndexes = 0;
}

Plane::Plane(float l, int div, bool onXZ) {

    length = l;
    divisions = div;

    float y = 0.0f;
    float reference = length / 2.0f;

    // if plane is not an XZ plane, it has Y value different from 0
    if (!onXZ) y = -reference;

    /*
       p3          p4
        -------------
        |           |
        |           |
        |     O     |
        |           |
        |           |
        -------------
       p1           p2
    */

    p1 = Point_3D(-reference, y, reference);             // external points (plane's limits)
    p2 = Point_3D(reference, y, reference);
    p3 = Point_3D(reference, y, -reference);
    p4 = Point_3D(-reference, y, -reference);


    planePoints = calculatePlanePoints();                       // calculate plane's points
    planePointsIndexes = calculatePlaneVertices();              // get point's indexes
    nPoints = planePoints.size();
    nIndexes = planePointsIndexes.size();
}



Point_3D Plane::getP1(){
    return p1;
}
Point_3D Plane::getP2(){
    return p2;
}
Point_3D Plane::getP3(){
    return p3;
}
Point_3D Plane::getP4(){
    return p4;
}
float Plane::getLength(){
    return length;
}
int Plane::getDivisions(){
    return divisions;
}
int Plane::getNumberOfPoints(){
    return nPoints;
}
int Plane::getNumberOfIndexes(){
    return nIndexes;
}
void Plane::setPlanePoints(std::vector<Point_3D> points){
    planePoints = points;
}   
void Plane::setPlaneVertices(std::vector<int> vertices){
    planePointsIndexes = vertices;
}
void Plane::setP1(Point_3D p){
    p1 = p;
}
void Plane::setP2(Point_3D p){
    p2 = p;
}
void Plane::setP3(Point_3D p){
    p3 = p;
}
void Plane::setP4(Point_3D p){
    p4 = p;
}


/*
  (12)   (13)  (14)  (15)
    ---------------------
    |                   |
    |                   |
8   |-------------------| 11
    |                   |
4   |----5-------6------| 7
    |                   |
    ---------------------
  (0)    (1)    (2)    (3)

    #-> (1) é o ponto utilizado como referência para o conseguinte cálculo dos pontos/vértices do plano ! 
*/

/**
 * @brief Dadas as informações necessárias e um ponto de referência do plano, constrói um vetor com todos os pontos3D
 * associados à configuração do plano
 * 
 * @param length Comprimento do plano
 * @param dividions Número de divisões aplicadas ao plano, em cada eixo 
 * @param p1 Ponto de referência do plano, Inferior esquerdo!
 * 
 * @return vector<Point_3D> Vetor com os pontos constituintes do plano
 */
vector<Point_3D> Plane::calculatePlanePoints(){

    // length of each division
    float divionFactor = length / (float)divisions;

    vector<Point_3D> lista = vector<Point_3D>();
    lista.clear();

    float X,Y,Z;
    X = p1.getX();  // reference point for calculations
    Y = p1.getY();  
    Z = p1.getZ();  
    Point_3D p;
    float s = 0.0f, t = 0.0f;

    for(int j = 0; j <= divisions; j++){

        // lower left limit for x
        X = p1.getX();

        for(int i = 0; i <= divisions; i++){
            
            p = Point_3D(X, Y, Z);
            lista.push_back(p);

            Point_3D n = getNormalize(p);
            normals.push_back(n);

            s = (float)i / divisions;
            t = (float)j / divisions;
            texs.push_back(Point_2D(s, t)); // tex coords

            X = X + divionFactor;   // update x value for each line
        }

        Z = Z - divionFactor;       // update z value
    }

    return lista;
}

/**
 * @brief Recolhe um vetor com os índices, por ordem, da construção do plano através dos triângulos que o constituem
 * 
 * @param PlanePoints Pontos pertencentes ao plano, respeitando o n.º de divisões
 * @param divisions N.º de divisões aplicadas em cada eixo do plano
 * 
 * @return vector<int> Vetor com os índices requeridos
 */
vector<int> Plane::calculatePlaneVertices(){

    vector<int> pointsIndex;
    int limit = divisions * divisions;
    pointsIndex.clear();

    for(int j = 0; j < limit; j += (divisions + 1)){

        int limit02 = j + divisions;
        
        for(int i = j; i < limit02; i++){

            pointsIndex.push_back(i);                           // 1
            pointsIndex.push_back(i + (divisions + 2));         // 4
            pointsIndex.push_back(i + (divisions + 1));         // 3

            pointsIndex.push_back(i);                           // 1
            pointsIndex.push_back(i + 1);                       // 2
            pointsIndex.push_back(i + (divisions + 2));         // 4 
        }
    }

    return pointsIndex;
}


vector<int> Plane::planeVerticesInverted(){

    vector<int> pointsIndex;
    int limit = divisions * divisions;
    pointsIndex.clear();

    for(int j = 0; j < limit; j += (divisions + 1)){

        int limit02 = j + divisions;
        
        for(int i = j; i < limit02; i++){
            
            pointsIndex.push_back(i);                           // 1
            pointsIndex.push_back(i + (divisions + 2));         // 4
            pointsIndex.push_back(i + 1);                       // 2

            pointsIndex.push_back(i);                           // 1
            pointsIndex.push_back(i + (divisions + 1));         // 3
            pointsIndex.push_back(i + (divisions + 2));         // 4
        }

    }

    return pointsIndex;
}



std::pair<vector<Point_3D>, vector<int>> Plane::PlaneInfo() {
    return std::make_pair(planePoints, planePointsIndexes);
}

std::vector<Point_3D> Plane::getPlanePoints(){
    return vector<Point_3D>(planePoints);
}

std::vector<int> Plane::getPlanePointsIndexes(){
    return vector<int>(planePointsIndexes);
}

std::vector<Point_3D> Plane::getNormals() {
    return vector<Point_3D>(normals);
}

std::vector<Point_2D> Plane::getTexs() {
    return vector<Point_2D>(texs);
}

void Plane::toFile(string file){

    ofstream outFile;
    string outputFile = "../3D/" + file;

    outFile.open(outputFile, ios::out | ios::trunc);


    if (outFile.is_open()){

        vector<Point_3D> pts = planePoints;
        vector<int> idxs = planePointsIndexes;
        
        outFile << pts.size() << "," << idxs.size() << endl;

        int limit = divisions * divisions;
        for(int j = 0; j < limit; j += (divisions + 1)){

            int limit02 = j + divisions;
            short i1, i2, i3;

            for(int i = j; i < limit02; i++){

                i1 = i;                         // 1
                i2 = i + (divisions + 2);       // 4
                i3 = i + (divisions + 1);       // 3


                Point_3D p1 = pts.at(i1);
                Point_3D p2 = pts.at(i2);
                Point_3D p3 = pts.at(i3);
                
                Point_3D n1 = normals.at(i1);
                Point_3D n2 = normals.at(i2);
                Point_3D n3 = normals.at(i3);
                
                Point_2D t1 = texs.at(i1);
                Point_2D t2 = texs.at(i2);
                Point_2D t3 = texs.at(i3);

                outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", " << n3.toString() 
                    << ", " << t1.toString() << ", " << t2.toString() << ", " << t3.toString() << endl;

                p1 = pts.at(i1);                // 1
                p2 = pts.at(i1 + 1);            // 2
                p3 = pts.at(i2);                // 4

                n1 = normals.at(i1);
                n2 = normals.at(i1 + 1);
                n3 = normals.at(i2);
                
                t1 = texs.at(i1);
                t2 = texs.at(i1 + 1);
                t3 = texs.at(i2);

                outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", " << n3.toString() 
                    << ", " << t1.toString() << ", " << t2.toString() << ", " << t3.toString() << endl;
            }
        }
        outFile.close();
    }

}


Plane Plane::planeXY(){

    Point_3D p1 = getP1();

    float divionFactor = length / (float)divisions;
    vector<Point_3D> lista;
    lista.clear();

    float X,Y,Z;
    X = p1.getX();
    Y = p1.getY();
    Z = p1.getZ();
    Point_3D p;
    float s = 0.0f, t = 0.0f;

    for(int j = 0; j <= divisions; j++){

        X = p1.getX();

        for(int i = 0; i <= divisions; i++){
            
            p = Point_3D(X, Y, Z);
            lista.push_back(p);

            Point_3D n = getNormalize(p);
            normals.push_back(n);

            s = (float)i / divisions;
            t = (float)j / divisions;
            texs.push_back(Point_2D(s, t));

            X = X + divionFactor;
        }

        Y = Y + divionFactor;
    }

    Plane plane = Plane(length, divisions, false);
    plane.setP1(p1);
    plane.setP2(Point_3D(p1.getX()+length, p1.getY(), p1.getZ()));
    plane.setP3(Point_3D(p1.getX(), p1.getY() + length, p1.getZ()));
    plane.setP4(Point_3D(p1.getX()+length, p2.getY() + length, p1.getZ()));
    plane.setPlanePoints(lista);
    return plane;
}

Plane Plane::planeYZ(){

    Point_3D p1 = getP1();

    float divionFactor = length / (float)divisions;
    vector<Point_3D> lista;
    lista.clear();

    float X,Y,Z;
    X = p1.getX();
    Y = p1.getY();
    Z = p1.getZ();
    Point_3D p;
    float s = 0.0f, t = 0.0f;

    for(int j = 0; j <= divisions; j++){

        Z = p1.getZ();

        for(int i = 0; i <= divisions; i++){
            
            p = Point_3D(X, Y, Z);
            lista.push_back(p);


            Point_3D n = getNormalize(p);
            normals.push_back(n);

            s = (float)i / divisions;
            t = (float)j / divisions;
            texs.push_back(Point_2D(s, t));

            Z = Z - divionFactor;
        }

        Y = Y + divionFactor;
    }

    Plane plane = Plane(length, divisions, false);
    plane.setP1(p1);
    plane.setP2(Point_3D(p1.getX(), p1.getY(), p1.getZ()+length));
    plane.setP3(Point_3D(p1.getX(), p1.getY()+length, p1.getZ()));
    plane.setP4(Point_3D(p1.getX(), p1.getY()+length, p1.getZ()+length));
    plane.setPlanePoints(lista);
    return plane;
}

void Plane::addX(){

    int size = planePoints.size();

    for(int i = 0; i < size; i++){

        Point_3D p = planePoints.at(i);
        p.setX(p.getX() + length);
        planePoints[i] = p;
    }
}
void Plane::addY(){

    int size = planePoints.size();

    for(int i = 0; i < size; i++){

        Point_3D p = planePoints.at(i);
        p.setY(p.getY() + length);
        planePoints[i] = p;
    }
}
void Plane::addZ(){

    int size = planePoints.size();

    for(int i = 0; i < size; i++){

        Point_3D p = planePoints.at(i);
        p.setZ(p.getZ() - length);
        planePoints[i] = p;
    }
}