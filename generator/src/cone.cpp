#include "../headers/cone.h"


Cone::Cone(float r, float h, int s1, int s2) {
    this->raio = r;
    this->altura = h;
    this->slices = s1;
    this->stacks = s2;
}

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
    
    Point_3D p = polarToPoint3D(radius, height, alpha);
    return std::to_string(p.getX()) + ", " + std::to_string(p.getY()) + ", " + std::to_string(p.getZ())+"\n";
}



void Cone::toFile(std::string s) {

    std::ofstream file;
    int n_indices = 0, n_pontos = 0, n_normais = 0;
    Point_3D p1, p2, p3, p4, p5, p6, n1, n2, n3;

    n_pontos = slices*3 + 6*stacks;
    n_indices = slices*3 + 6*stacks;
    n_normais = (slices*3 + 6*stacks)/3;
       
    std::string outputFile = "../3D/" + s;
    file.open(outputFile);

    if (file.is_open()){

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

            n1 = normal(p1);
            n2 = normal(p2);
            n3 = normal(p3);

            file << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", "<< n3.toString() << endl;
        }

        for(int i = 0; i < stacks; i++){

            r = (((float)stacks-i)/stacks)*raio;
            rUp = (((float)stacks-(i+1))/stacks)*raio;
            for(int j = 0; j < slices; j++){

                alpha=j*sliceSize;

                p1 = polarToPoint3D(rUp,yy+stackSize*(i+1),alpha);
                p2 = polarToPoint3D(r,yy+stackSize*i,alpha);
                p3 = polarToPoint3D(r,yy+stackSize*i,alpha+sliceSize);

                n1 = normal(p1);
                n2 = normal(p2);
                n3 = normal(p3);

                file << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", "<< n3.toString() << endl;

                p4 = polarToPoint3D(rUp,yy+stackSize*(i+1),alpha);
                p5 = polarToPoint3D(r,yy+stackSize*i,alpha+sliceSize);
                p6 = polarToPoint3D(rUp,yy+stackSize*(i+1),alpha+sliceSize);
                
                n1 = normal(p4);
                n2 = normal(p5);
                n3 = normal(p6);

                file << p4.toString() << ", " << p5.toString() << ", " << p6.toString() << ", " << n1.toString() << ", " << n2.toString() << ", "<< n3.toString() << endl;
            }
        }
        file.close();
    }
}