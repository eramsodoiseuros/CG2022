#include "../utils/point_3d.h"
#include "../generator/plane.h"
#include <list>
#include <cmath>
#include <vector>
#include <cstring>

#include <iostream>

using namespace std;

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
8   |-------------------|
    |                   |
4   |----5--------------|
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

    float divionFactor = length / (float)divisions;
    vector<Point_3D> lista;
    lista.clear();
    float X,Z;
    X = p1.getX();
    Z = p1.getZ();
    Point_3D p;

    for(int j = 0; j <= divisions; j++){

        X = p1.getX();

        for(int i = 0; i <= divisions; i++){
            
            p = Point_3D(X, 0.0f, Z);
            lista.push_back(p);

            X = X + divionFactor;
        }

        Z = Z - divionFactor;
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

            pointsIndex.push_back(i);
            pointsIndex.push_back(i + (divisions + 2));
            pointsIndex.push_back(i + (divisions + 1));

            pointsIndex.push_back(i);
            pointsIndex.push_back(i + 1);
            pointsIndex.push_back(i + (divisions + 2));
                
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
            pointsIndex.push_back(i + (divisions + 1));         // 3
            pointsIndex.push_back(i + (divisions + 2));         // 4

            pointsIndex.push_back(i + (divisions + 2));         // 4
            pointsIndex.push_back(i + 1);                       // 2
            pointsIndex.push_back(i);                           // 1
                
        }

    }

    return pointsIndex;
}



/**
 * @brief Esta função é a principal que calcula todos os pontos necessários à construção de um plano, assim como
 * a ligação de todos os vértices de modo a construir os triângulos que formarão a futura figuração
 * 
 * @param length Comprimento do plano
 * @param divisions Número de divisões a aplicar em cada eixo do plano
 * 
 * @return std::pair<vector<Point_3D>, vector<int>> Par com um vetor com os pontos que formam o plano, assim como os índices dos pontos que formarão
 * os respetivos triângulos, de modo a constituir o plano graficamente
 */

std::pair<vector<Point_3D>, vector<int>> Plane::PlaneInfo() {

    return std::make_pair(planePoints, planePointsIndexes);
}

std::vector<Point_3D> Plane::getPlanePoints(){

    return vector<Point_3D>(planePoints);
}


std::vector<int> Plane::getPlanePointsIndexes(){

    return vector<int>(planePointsIndexes);
}


void Plane::toFile(string file){

    ofstream outFile;
    
    string outputFile = "3D/" + file;

    outFile.open(outputFile, ios::out | ios::trunc);

    vector<Point_3D> pts = planePoints;
    vector<int> idxs = planePointsIndexes;

    outFile << pts.size() << " " << idxs.size() << endl;

    for(int i : idxs){

        outFile << pts.at(i).toString();
    }

    outFile.close();
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

    for(int j = 0; j <= divisions; j++){

        X = p1.getX();

        for(int i = 0; i <= divisions; i++){
            
            p = Point_3D(X, Y, Z);
            lista.push_back(p);

            X = X + divionFactor;
        }

        Y = Y + divionFactor;
    }

    Plane plane = Plane(length, divisions);
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

    for(int j = 0; j <= divisions; j++){

        Z = p1.getZ();

        for(int i = 0; i <= divisions; i++){
            
            p = Point_3D(X, Y, Z);
            lista.push_back(p);

            Z = Z - divionFactor;
        }

        Y = Y + divionFactor;
    }

    Plane plane = Plane(length, divisions);
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





/*
int main(){


    Plane p01 = Plane(5.0, 10);

    pair<vector<Point_3D>, vector<int>> planeInfo = p01.PlaneInfo();

    vector<Point_3D> pontos = planeInfo.first;
	vector<int> indexes = planeInfo.second;

    printf("\n#> Plano com %d pontos e %d vertices a formar triangulos;", pontos.size(), indexes.size());


    for (int i : indexes) {

        Point_3D p = pontos.at(i);
        printf("\nglVertex3f(%.5f,%.5f,%.5f);", p.getX(), p.getY(), p.getZ());
        //printf("\n:: %d", i);
	}

    //const char* name = "plane01.3d";
    //p01.toFile(name);

    return(0);
}
*/