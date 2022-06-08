#include "../utils/point_3d.h"
#include "../generator/plane.h"
#include "../generator/box.h"
#include <list>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std; 

float Box::getDimension(){
    return dimension;
}

int Box::getDivisions(){
    return divisionsPerAxis;
}


vector<Plane> Box::calculateBox(float dimension, int divisions){

    vector<Plane> faces;

    Plane xzBase = Plane(dimension, divisions, false);      // Base xz         
    xzBase.setPlaneVertices(xzBase.planeVerticesInverted());

    Plane xyFront = xzBase.planeXY();                // Front xy       

    Plane yzLeft = xzBase.planeYZ();                 // Left yz     
    yzLeft.setPlaneVertices(yzLeft.planeVerticesInverted());

    
    Plane xzTop = Plane(dimension, divisions, false);       // Top xz         
    xzTop.addY();

    Plane xyBack = xzBase.planeXY();                // Back xy          
    xyBack.addZ();
    xyBack.setPlaneVertices(xyBack.planeVerticesInverted());

    Plane yzRight = xzBase.planeYZ();               // Right yz       
    yzRight.addX();

    faces.push_back(xzBase);   // Base  (I)
    faces.push_back(yzLeft);   // Left  (I)
    faces.push_back(xyFront);  // Front (N)

    faces.push_back(xzTop);    // Top   (D)
    faces.push_back(yzRight);  // Right (N)
    faces.push_back(xyBack);   // Back  (I)

    return faces;
}


vector<Plane> Box::getBoxPlanes(){

    return vector<Plane>(boxPlanes);
}


void Box::toFile(string file) {

    ofstream outFile;
    
    string outputFile = "../3D/" + file;
    outFile.open(outputFile, ios::out | ios::trunc);

    vector<Plane> boxPlanes = getBoxPlanes();
    int totalPoints = 0;
    int totalIndexes = 0;

    for(Plane p : boxPlanes){
        totalPoints += p.getNumberOfPoints();
        totalIndexes += p.getNumberOfIndexes();
    }

    outFile << "02," << totalPoints << "," << totalIndexes << endl;

    for(Plane p : boxPlanes){

        vector<Point_3D> points = p.getPlanePoints();
        vector<int> indexes = p.getPlanePointsIndexes();

        for(int i : indexes){

            outFile << points.at(i).toString();
        }
    }

    outFile.close();
}
