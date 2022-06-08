#include "../headers/cone.h"


Cone::Cone(float radius, float height, int slices, int stacks) {
    this->raio = radius;
    this->altura = height;
    this->slices = slices;
    this->stacks = stacks;
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

    n_pontos = slices*3 + 4*stacks;
    n_indices = slices*3 + slices*(6*stacks);
       
    std::string outputFile = "../3D/" + s;
    file.open(outputFile);

    if (file.is_open()){

        file << n_pontos << "," << n_indices << std::endl; 
        float stackSize = altura/stacks;
        float sliceSize = 2*M_PI/slices;
        float alpha = 0.0f;
        float r = 0.0f;
        float rUp = 0.0f;
        float texture_x_step = 1.0f / (float)this->slices;
        float texture_y_step = 1.0f / (float)this->stacks;

        for(int i=0;i<slices;i++){
            alpha = i*sliceSize;

            p1 = polarToPoint3D(0,0,0);
            p2 = polarToPoint3D(raio,0,alpha+sliceSize);
            p3 = polarToPoint3D(raio,0,alpha);

            n1 = Point_3D(0,-1,0);
            n2 = Point_3D(0,-1,0);
            n3 = Point_3D(0,-1,0);

            Point_2D t1 = Point_2D(0.5,0.5);
            Point_2D t2 = Point_2D(1-(0.5 * cosf(alpha+sliceSize) + 0.5), 0.5 * sinf(alpha+sliceSize) + 0.5);
            Point_2D t3 = Point_2D(1 - (0.5 * cosf(alpha) + 0.5), 0.5 * sinf(alpha) + 0.5);

            file << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", "<< n3.toString() << ", "
                 << t1.toString() << ", "<< t2.toString() << ", " << t3.toString() << endl;
        }

        for(int i = 0; i < stacks; i++){

            r = (((float)stacks-i)/stacks)*raio;
            rUp = (((float)stacks-(i+1))/stacks)*raio;
            for(int j = 0; j < slices; j++){

                alpha=j*sliceSize;

                p1 = polarToPoint3D(rUp,stackSize*(i+1),alpha);
                p2 = polarToPoint3D(r,stackSize*i,alpha);
                p3 = polarToPoint3D(r,stackSize*i,alpha+sliceSize);

                n1 = getNormalize(p1);
                n2 = getNormalize(p2);
                n3 = getNormalize(p3);

                Point_2D t1 = Point_2D(texture_x_step * (float)j,texture_y_step * (float)(i+1));
                Point_2D t2 = Point_2D(texture_x_step * (float)j, texture_y_step * (float)i);
                Point_2D t3 = Point_2D(texture_x_step * (float)(j+1), texture_y_step * (float)i);

                file << p1.toString() << ", " << p2.toString() << ", " << p3.toString() << ", " << n1.toString() << ", " << n2.toString() << ", "<< n3.toString() << ", " 
                     << t1.toString() << ", "<< t2.toString() << ", " << t3.toString() << endl;

                p4 = polarToPoint3D(rUp,stackSize*(i+1),alpha);
                p5 = polarToPoint3D(r,stackSize*i,alpha+sliceSize);
                p6 = polarToPoint3D(rUp,stackSize*(i+1),alpha+sliceSize);
                
                n1 = getNormalize(p4);
                n2 = getNormalize(p5);
                n3 = getNormalize(p6);

                t1 = Point_2D(texture_x_step * (float)j, texture_y_step * (float)(i + 1));
                t2 = Point_2D(texture_x_step * (float)(j+1), texture_y_step * (float)i);
                t3 = Point_2D(texture_x_step * (float)(j+1), texture_y_step * (float)(i+1));

                file << p4.toString() << ", " << p5.toString() << ", " << p6.toString() << ", " << n1.toString() << ", " << n2.toString() << ", "<< n3.toString() << ", "
                     << t1.toString() << ", "<< t2.toString() << ", " << t3.toString() << endl;
            }
        }
        file.close();
    }
}