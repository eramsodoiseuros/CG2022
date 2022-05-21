#pragma
#ifndef GENERATOR_POINT_3D_H
#define GENERATOR_POINT_3D_H

#include <cstdlib>
#include <cstdio>
#include <math.h>


class Point_2D {
private:
    float x;
    float y;

public:

    Point_2D() = default;

    Point_2D(float p1, float p2) {
        this->x = p1;
        this->y = p2;
    }

    /**
    *	Retorna a coordenada em X do ponto
    *	@return `float` a coordenada em X
    */
    float getX();

    /**
    *	Retorna a coordenada em Y do ponto
    *	@return `float` a coordenada em Y
    */
    float getY();


    /**
    *   Coloca o ponto nas coordenadas indicadas
    *   @param x coordenada em X 
    */
    void setX(float x);

    /**
    *   Coloca o ponto nas coordenadas indicadas
    *   @param y coordenada em Y 
    */
    void setY(float y);

    /**
    *	Coloca o ponto nas coordenadas indicadas
    *	@param x coordenada em X
    *	@param y coordenada em Y
    */
    void setPointTo(float x, float y);

    /**
    *	Formata uma string com o conteudo do Ponto
    *	@return `char*`	correspondente ao conteudo do Ponto
    */
    char* toString();
};


#endif //GENERATOR_POINT_2D_H