#include "../headers/plane.h"
#include "../headers/box.h"
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

    vector<Plane> faces = vector<Plane>();

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

    outFile << totalPoints << "," << totalIndexes << endl;

    for(Plane p : boxPlanes){

        vector<Point_3D> points = p.getPlanePoints();
        vector<int> indexes = p.getPlanePointsIndexes();
        int nIndexes = indexes.size();

        for (int i = 0; i < nIndexes; i += 3) {

            // index 1 2 3
            int index1 = indexes.at(i);
            int index2 = indexes.at(i+1);
            int index3 = indexes.at(i + 2);

            // point 1 2 3
            Point_3D p1 = points.at(index1);
            Point_3D p2 = points.at(index2);
            Point_3D p3 = points.at(index3);

            // calculate normal from triangle
            Point_3D normal = getNormal(p1,p2,p3);

            // output vertex
            outFile << p1.toString();
            outFile << p2.toString();
            outFile << p3.toString();

            // output normal
            outFile << normal.toString();

    }
    }

    outFile.close();
}
