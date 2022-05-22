#include "../headers/cone.h"

float Cone::getRadius() {
    return this->raio;
}

float Cone::getHeight() {
    return this->altura;
}

float Cone::getSlices() {
    return this->slices;
}

float Cone::getStacks(){
    return this->stacks;
}

std::string polarToCartCone(float radius,float height, float alpha){
    float x = radius*sin(alpha);
    float y = height;
    float z = radius*cos(alpha);
    return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z)+"\n";
}

Point_3D polarToPoint3D(float radius,float height, float alpha){
    float x = radius*sin(alpha);
    float y = height;
    float z = radius*cos(alpha);
    return Point_3D(x,y,z);
}

void Cone::toFile(std::string s) {
    std::ofstream file;

    int n_indices = 0, n_pontos = 0, n_normais = 0;

    Point_3D p1, p2, p3, p4, p5, p6, n0, n1, n2;
       
    std::string outputFile = "../3D/" + s;

    file.open(outputFile);
    n_pontos = slices*3 + 6*stacks;
    n_indices = slices*3 + 6*stacks;
    n_normais = (slices*3 + 6*stacks)/3;

    file << n_pontos << "," << n_indices << std::endl; 


    float stackSize = altura/stacks;
    float sliceSize = 2*M_PI/slices;
    float alpha = 0.0f;
    float r = 0.0f;
    float rUp = 0.0f;
    float yy = 0.0f;

    for(int i=0;i<slices;i++){
        alpha = i*sliceSize;
        
        p1 = polarToPoint3D(0,yy,0);
        p2 = polarToPoint3D(raio,yy,alpha+sliceSize);
        p3 = polarToPoint3D(raio,yy,alpha);

        pontos.push_back(p1);
        pontos.push_back(p2);
        pontos.push_back(p3);

        file << p1.to_string();
        file << p2.to_string();
        file << p3.to_string();

        n0 = getNormal(p1,p2,p3);
        normais.push_back(n0);
    }

    for(int i = 0; i < stacks; i++){

        r = (((float)stacks-i)/stacks)*raio;
        rUp = (((float)stacks-(i+1))/stacks)*raio;
        for(int j = 0; j < slices; j++){

            alpha=j*sliceSize;

            p1 = polarToPoint3D(rUp,yy+stackSize*(i+1),alpha);
            p2 = polarToPoint3D(r,yy+stackSize*i,alpha);
            p3 = polarToPoint3D(r,yy+stackSize*i,alpha+sliceSize);

            pontos.push_back(p1);
            pontos.push_back(p2);
            pontos.push_back(p3);

            file << p1.to_string();
            file << p2.to_string();
            file << p3.to_string();

            n1 = getNormal(p1,p2,p3);
            normais.push_back(n1);

            p4 = polarToPoint3D(rUp,yy+stackSize*(i+1),alpha);
            p5 = polarToPoint3D(r,yy+stackSize*i,alpha+sliceSize);
            p6 = polarToPoint3D(rUp,yy+stackSize*(i+1),alpha+sliceSize);

            pontos.push_back(p4);
            pontos.push_back(p5);
            pontos.push_back(p6);

            file << p4.to_string();
            file << p5.to_string();
            file << p6.to_string();

            n2 = getNormal(p4,p5,p6);
            normais.push_back(n2);
        }
    }

    file.close();
}