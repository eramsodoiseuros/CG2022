#include "../utils/point_3d.h"
#include "../generator/sphere.h"
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
        //printf("\n#> number of vertices to calculate: %d\n", nPoints);
        
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

    outFile.open(outputFile, ios::out | ios::trunc);

    vector<Point_3D> pts = spherePoints;
    vector<short> idxs = sphereIndexes;

    outFile << pts.size() << " " << idxs.size() << endl;

    for(short i : idxs){

        outFile << pts.at(i).toString();
    }

    outFile.close();
}




