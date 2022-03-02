#pragma
#ifndef GENERATOR_BOX_H
#define GENERATOR_BOX_H

#include "plane.h"
#include <fstream>
#include <math.h>

class Box {
    private:
        float x; // comprimento
        float y; // largura
        float z; // altura
        int d;	 // divisões

    public:
        Box(float x, float y, float z, int d) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->d = d;
        }

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
        *	@param output_file ficheiro resultante
        */
        void toFile(char* output_file);
};


#endif //GENERATOR_BOX_H
