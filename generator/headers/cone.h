#pragma
#ifndef GENERATOR_CONE_H
#define GENERATOR_CONE_H

#include <math.h>
#define _USE_MATH_DEFINES
#include <fstream>
#include <vector>
#include <string>
#include "../../utils/point_3d.h"
#include "../../utils/polar.h"

class Cone {
    private:
        float raio;
        float altura;
        int stacks;
        int slices;
    
    public:
        Cone(float r, float h, int s1, int s2);

        /**
        *	Retorna o raio da base
        *	@return `float` radius
        */
        float getRadius();

        /**
        *	Retorna a altura do cone
        *	@return `float` height
        */
        float getHeight();

        /**
        *	Retorna as slices do cone
        *	@return `int` slices
        */
        float getSlices();

        /**
        *	Retorna as stacks do cone
        *	@return `int` stacks
        */
        float getStacks();

        /**
        *	Retorna o Modelo do Cone
        *	@param output_file ficheiro resultante
        */
        void toFile(std::string s);
};

#endif //GENERATOR_CONE_H