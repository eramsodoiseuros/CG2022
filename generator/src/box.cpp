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

    int totalPoints = 0;
    int totalIndexes = 0;

    vector<Plane> boxPlanes = getBoxPlanes();
    for(Plane p : boxPlanes){
        totalPoints += p.getNumberOfPoints();
        totalIndexes += p.getNumberOfIndexes();
    }

    outFile.open(outputFile, ios::out | ios::trunc);
    if(outFile.is_open()){

        outFile << totalPoints << "," << totalIndexes << endl;
        for(Plane p : boxPlanes){

            vector<Point_3D> points = p.getPlanePoints();
            vector<int> indexes = p.getPlanePointsIndexes();
            vector<Point_3D> normals = p.getNormals();
            vector<Point_2D> texs = p.getTexs();
            int nIndexes = indexes.size();

            for (int i = 0; i < nIndexes; i += 3) {

                // index 1 2 3
                int index1 = indexes.at(i);
                int index2 = indexes.at(i + 1);
                int index3 = indexes.at(i + 2);

                // point 1 2 3
                Point_3D p1 = points.at(index1);
                Point_3D p2 = points.at(index2);
                Point_3D p3 = points.at(index3);

                // calculate normal from triangle
                Point_3D n1 = normals.at(index1);
                Point_3D n2 = normals.at(index2);
                Point_3D n3 = normals.at(index3);

                Point_2D t1 = texs.at(index1);
                Point_2D t2 = texs.at(index2);
                Point_2D t3 = texs.at(index3);
                cout << t1.toString() << endl;

                // output vertex + normal
                outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", "<< n3.toString() << ", "
                    << t1.toString() << ", "<< t2.toString() << ", " << t3.toString() << endl;
            }
        }
        outFile.close();
    }
}
