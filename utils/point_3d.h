#pragma
#ifndef GENERATOR_POINT_3D_H
#define GENERATOR_POINT_3D_H

#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Point_3D {

    private:
        float x;
        float y;
        float z;

    public:

        Point_3D();
        Point_3D(float p1, float p2, float p3);


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
        string toString();
    
        Point_3D Point_3D::crossProduct(Point_3D p);
        
        void Point_3D::normalize();

};

Point_3D polarToPoint3D(float radius,float height, float alpha);
Point_3D sum(Point_3D p1, Point_3D p2);
Point_3D mul(Point_3D p1, Point_3D p2);
Point_3D sub(Point_3D p1, Point_3D p2);

Point_3D getNormal(Point_3D p1, Point_3D p2, Point_3D p3);
Point_3D normal(Point_3D p);

#endif //GENERATOR_POINT_3D_H
