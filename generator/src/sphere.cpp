#include "../headers/sphere.h"
//#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring>

using namespace std;


Sphere::Sphere(float r, int slices, int stacks) {

    this->center = Point_3D(0.0f, 0.0f, 0.0f);
    this->raio = r;
    this->stacks = stacks;
    this->slices = slices;
    this->points = vector<Point_3D>();
    this->normals = vector<Point_3D>();
    this->indexes = vector<short>();
    this->texs = vector<Point_2D>();
    calculateSphere(center, raio, stacks, slices);
    calculateIndexes();
}



float Sphere::getRadius() {
    return raio;
}

int Sphere::getStacks() {
    return stacks;
}

int Sphere::getSlices() {
    return slices;
}

void Sphere::calculateSphere(Point_3D center, float radius, int stacks, int slices) {

    float sliceStep = 2 * M_PI / slices;                    // Angulo de cada slice
    float stackStep = M_PI / stacks;                        // Angulo de cada stack
    float s = 0.0f, t = 0.0f;

    /* to speed up computation, using multiplication instead of divisions
            "Vertex normals is pretty easy for a sphere, it just the line from the center of the sphere to the vertex, and maybe normalize it.
            if the spheres origin is at 0,0,0 it’s very simple, or to put it simple, if you have the radius of the sphere set to one, then
            the coordinate of each vertex is the normal for the vertex.", comment from khronos community
    */
    float lengthInv = 1.0f / radius;

    float angle1, xz, x, y, z, angle2;

    for (int i = 0; i <= stacks; i++) {

        angle1 = M_PI / 2 - i * stackStep;        // Apartir de 0, angulo atual
        xz = radius * cosf(angle1);               // Plano desa stack
        y = radius * sinf(angle1);                // Como para cada stack o y é sempre igual,
                                                        // Calcula-se fora do ciclo

        for (int j = 0; j <= slices; j++) {

            angle2 = j * sliceStep;     // angulo atual das slices
            z = xz * cosf(angle2);      // Valor do x
            x = xz * sinf(angle2);      // Valor do z
            Point_3D vertex = Point_3D(x, y, z);
            points.push_back(vertex);

            Point_3D n = getNormalize(vertex);
            normals.push_back(n);

            s = (float)j / slices;
            t = 1- ((float)i / stacks);
            texs.push_back(Point_2D(s, t));
        }
    }
}

void Sphere::calculateIndexes() {

    int nLinhas = (stacks + 1) * slices;
    int k1, k2;
    for (short i = 0; i < stacks; ++i) {

        k1 = i * (slices + 1);
        k2 = k1 + slices + 1;

        for (short j = 0; j < slices; ++j, ++k1, ++k2) {
            if (i != 0) {                                //Para a stack inicial, que só tem 1 triangulo por ciclo

                indexes.push_back(k1);          //1
                indexes.push_back(k2);          //3
                indexes.push_back(k1 + 1);      //2  
            }
            if (i != (stacks - 1)) {                    //Para a stack final, que só tem 1 triangulo por ciclo
                indexes.push_back(k1 + 1);      //2
                indexes.push_back(k2);          //3
                indexes.push_back(k2 + 1);      //4
            }
        }
    }
}

std::vector<Point_3D> Sphere::getPoints() {

    return vector<Point_3D>(points);
}

std::vector<short> Sphere::getIndexes() {

    return vector<short>(indexes);
}

vector<Point_2D> Sphere::getTexs() {

    return vector<Point_2D>(texs);
}

void Sphere::toFile(string file) {

    ofstream outFile;
    string outputFile = "../3D/" + file;

    vector<short> idxs = indexes;
    int nIndexes = idxs.size();

    //int nPoints = (stacks + 1) * slices;                    //Nº pontos

    outFile.open(outputFile, ios::out | ios::trunc);
    if (outFile.is_open()) {

        outFile << points.size() << "," << nIndexes << endl;
        Point_3D p1, p2, p3, n1, n2, n3;
        short i1, i2, i3;
        Point_2D s1, s2, s3;

        for (int i = 0; i < nIndexes; i += 3) {

            i1 = idxs[i];
            i2 = idxs[i + 1];
            i3 = idxs[i + 2];

            p1 = points.at(i1);
            p2 = points.at(i2);
            p3 = points.at(i3);

            n1 = normals.at(i1);
            n2 = normals.at(i2);
            n3 = normals.at(i3);

            s1 = texs.at(i1);
            s2 = texs.at(i2);
            s3 = texs.at(i3);

            outFile << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", " << n3.toString() << ", "
                << s1.toString() << ", " << s2.toString() << ", " << s3.toString() << endl;
        }
    }
}