#pragma
#ifndef GENERATOR_SPHERE_H
#define GENERATOR_SPHERE_H

#include <math.h>
#define _USE_MATH_DEFINES
#include <fstream>
#include <vector>
#include "../utils/point_3d.h"

class Sphere {
    private:
        float raio;
        int stacks;
        int slices;

    public:
        Sphere(float r, int s1, int s2) {
            this->raio = r;
            this->stacks = s1;
            this->slices = s2;
        }

        /**
        *	Retorna o raio da Esfera
        *	@return `float` radius
        */
        float getRadius();

        /**
        *	Retorna as ?? da Esfera
        *	@return `int` stacks
        */
        int getStacks();

        /**
        *	Retorna as divisões da Esfera
        *	@return `int` slices
        */
        int getSlices();

        /**
        *	Retorna o Modelo da Esfera
        *	@param output_file ficheiro resultante
        */
        void toFile(char* output_file) const;
};


#endif //GENERATOR_SPHERE_H
