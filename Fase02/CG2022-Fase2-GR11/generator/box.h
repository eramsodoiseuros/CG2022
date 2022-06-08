#pragma
#ifndef GENERATOR_BOX_H
#define GENERATOR_BOX_H

#include "../generator/plane.h"
#include <fstream>
#include <math.h>

class Box {
    private:
        float dimension;
        int divisionsPerAxis;

        std::vector<Plane> boxPlanes;

    public:
        Box(float l, int divisions) {
            
            dimension = l;
            divisionsPerAxis = divisions;

            boxPlanes = calculateBox(dimension, divisionsPerAxis);
        }

        float getDimension();
        int getDivisions();

        /**
        * 	Rotorna o comprimento
        *	@return `float` X
        */
        float getX();

        /**
        * 	Rotorna a largura
        *	@return `float` Y
        */
        float getY();

        /**
        * 	Rotorna a altura
        *	@return `float` Z
        */
        float getZ();

        /**
        * 	Rotorna o número de divisões
        *	@return `int` d
        */
        float getD();

        std::vector<Point_3D> vertices() const;

        /**
        *	Retorna o Modelo da Caixa
        *	@param s ficheiro resultante
        */
       void toFile(std::string s);


        std::vector<Plane> calculateBox(float dimension, int divisions);

        std::vector<Plane> getBoxPlanes();
};


#endif //GENERATOR_BOX_H
