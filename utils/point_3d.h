#pragma
#ifndef GENERATOR_POINT_3D_H
#define GENERATOR_POINT_3D_H

#include <cstdlib>
#include <cstdio>

class Point_3D {
private:
    float x;
    float y;
    float z;

public:

    Point_3D() = default;

    Point_3D(float p1, float p2, float p3) {
        this->x = p1;
        this->y = p2;
        this->z = p3;
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
    *	Retorna a coordenada em Z do ponto
    *	@return `float` a coordenada em Z
    */
    float getZ();


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
    *   Coloca o ponto nas coordenadas indicadas
    *   @param z coordenada em Z 
    */
    void setZ(float z);

    /**
    *	Coloca o ponto nas coordenadas indicadas
    *	@param x coordenada em X
    *	@param y coordenada em Y
    *	@param z coordenada em Z
    */
    void setPointTo(float x, float y, float z);

    /**
    *	Formata uma string com o conteudo do Ponto
    *	@return `char*`	correspondente ao conteudo do Ponto
    */
    char* toString();

    Point_3D crossProduct(Point_3D p);

    void normalize();
};


#endif //GENERATOR_POINT_3D_H
