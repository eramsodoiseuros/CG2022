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

void Cone::toFile(std::string s) {
    std::ofstream file;

    int n_indices = 0, n_pontos = 0;
       
    std::string outputFile = "../../3D/" + s;

    file.open(outputFile);
    n_pontos = slices*3 + 6*stacks;
    n_indices = slices*3 + 6*stacks;
    file << "03," << n_pontos << "," << n_indices << std::endl; 


    float stackSize = altura/stacks;
    float sliceSize = 2*M_PI/slices;
    float alpha = 0.0f;
    float r = 0.0f;
    float rUp = 0.0f;
    float yy = 0.0f;

    for(int i=0;i<slices;i++){
        alpha = i*sliceSize;
        file << polarToCartCone(0,yy,0);
        file << polarToCartCone(raio,yy,alpha+sliceSize);
        file << polarToCartCone(raio,yy,alpha);

    }

    for(int i = 0; i < stacks; i++){

        r=(((float)stacks-i)/stacks)*raio;
        rUp=(((float)stacks-(i+1))/stacks)*raio;
        for(int j = 0; j < slices; j++){

            alpha=j*sliceSize;

            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha+sliceSize);
            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha+sliceSize);
            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha+sliceSize);
        }
    }

    file.close();
}