#include "../headers/sphere.h"
//#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring>

using namespace std;


float Sphere::getRadius(){
        return raio;
}

int Sphere::getStacks(){
        return stacks;
}

int Sphere::getSlices(){
        return slices;
}

vector<Point_3D> Sphere::calculateSphere(Point_3D center, float radius, int stacks, int slices){

        //int nPoints = (stacks + 1) * slices;                    //Nº pontos

        vector<Point_3D> points;
        
        float sliceStep = 2 * M_PI / slices;                    // Angulo de cada slice
        float stackStep = M_PI / stacks;                        // Angulo de cada stack
       
        for(int i = 0; i <= stacks; i++){

                float angle1 = M_PI / 2 - i * stackStep;        // Apartir de 0, angulo atual
                float xz = radius * cosf(angle1);               // Plano desa stack
                float y = radius * sinf(angle1);                // Como para cada stack o y é sempre igual,
                                                                // Calcula-se fora do ciclo

                        for(int j = 0; j <= slices; j++){

                                float angle2 = j * sliceStep;     // angulo atual das slices
                                float x = xz * cosf(angle2);      // Valor do x
                                float z = xz * sinf(angle2);      // Valor do z
                                points.push_back(Point_3D(x,y,z));
                        }
                
        }

        return points;
}

vector<short> Sphere::calculateIndexes(){

        vector<short> indexes;

        int nLinhas = (stacks+1) * slices;

        for(short i = 0; i < nLinhas; i+= slices){

                for(short j = i; j < i+slices; j++){
                        if(i==0){                                //Para a stack inicial, que só tem 1 triangulo por ciclo
                                indexes.push_back(j);
                                indexes.push_back(j+slices+1);
                                indexes.push_back(j+slices);    
                        }
                        else if(i == nLinhas-1){                 //Para a stack final, que só tem 1 triangulo por ciclo
                                indexes.push_back(j);
                                indexes.push_back(j+1);
                                indexes.push_back(j+slices+1);
                        }
                        else {
                                indexes.push_back(j);                           
                                indexes.push_back(j+slices+1);
                                indexes.push_back(j+slices);

                                indexes.push_back(j);
                                indexes.push_back(j+1);
                                indexes.push_back(j+slices+1);
                        }
                }
        }

        return indexes;
}

std::vector<Point_3D> Sphere::getSpherePoints(){

    return vector<Point_3D>(spherePoints);
}

std::vector<short> Sphere::getSpherePointsIndexes(){

    return vector<short>(sphereIndexes);
}

void Sphere::toFile(string file){

    ofstream outFile;
    string outputFile = "../3D/" + file;

    vector<short> idxs = sphereIndexes;
    int nIndexes = idxs.size();


    outFile.open(outputFile, ios::out | ios::trunc);
    if (outFile.is_open()){

        outFile << spherePoints.size() << "," << idxs.size() << endl;
        int nLinhas = (stacks+1) * slices;
        Point_3D p1, p2, p3, normal;


        for(short i = 0; i < nLinhas; i+= slices){

                for(short j = i; j < i+slices; j++){
                        if(i==0){          

                                                      //Para a stack inicial, que só tem 1 triangulo por ciclo
                                p1 = spherePoints.at(j);
                                p2 = spherePoints.at(j + slices + 1);
                                p3 = spherePoints.at(j + slices);
                                normal = getNormal(p1, p2, p3);
                                outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << normal.toString() << ", " << endl;
                        }
                        else if(i == nLinhas-1){                 //Para a stack final, que só tem 1 triangulo por ciclo
                                
                                p1 = spherePoints.at(j);
                                p2 = spherePoints.at(j + 1);
                                p3 = spherePoints.at(j + slices + 1);
                                normal = getNormal(p1, p2, p3);
                                outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << normal.toString() << ", " << endl;
                        }
                        else {
                                p1 = spherePoints.at(j);
                                p2 = spherePoints.at(j + slices + 1);
                                p3 = spherePoints.at(j + slices);
                                normal = getNormal(p1, p2, p3);
                                outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << normal.toString() << ", " << endl;
                                
                                p1 = spherePoints.at(j);
                                p2 = spherePoints.at(j + 1);
                                p3 = spherePoints.at(j + slices + 1);
                                normal = getNormal(p1, p2, p3);
                                outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << normal.toString() << ", " << endl;
                        }
                }
        }
        outFile.close();
    }
}
