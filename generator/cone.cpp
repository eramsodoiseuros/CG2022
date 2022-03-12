#include "cone.h"

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

void Cone::toFile(char *output_file) {
    std::ofstream file;

    int n_indices = 0, n_pontos = 0;

    file.open(output_file);
    file << "Numero de Pontos do Cone\n";
    n_pontos = slices*3 + 6*stacks;
    file << n_pontos;
    file << "\n";

    float stackSize = altura/stacks;
    float sliceSize = 2*M_PI/slices;
    float alpha = 0.0f;
    float r = 0.0f;
    float rUp = 0.0f;
    float yy= altura/-2;

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

    file << "Numero de Indices do Cone\n";
    n_indices = slices*3 + 6*stacks;
    file << n_indices;

    file.close();
}