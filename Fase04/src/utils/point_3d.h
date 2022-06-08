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

        /**
         * @brief Construct a new Point_3D object
         * 
         */
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
         * @brief Formata uma string com o conteudo do Ponto
         * 
         * @return string com os valores associados
         */
        string toString();

        /**
         * @brief calcula o produto cruzado entre dois pontos (cross product)
         * 
         * @param p ponto a utilizar no produto
         * @return Point_3D ponto resultante da operação
         */
        Point_3D Point_3D::crossProduct(Point_3D p);
        
        /**
         * @brief normaliza um ponto
         * 
         */
        void Point_3D::normalize();

};


Point_3D polarToPoint3D(float radius,float height, float alpha);

/**
 * @brief calcula a soma de dois pontos
 * 
 * @param p1 ponto 1
 * @param p2 ponto 2
 * @return Point_3D ponto resultante da operação
 */
Point_3D sum(Point_3D p1, Point_3D p2);

/**
 * @brief calcula a multiplicação entre dois pontos
 * 
 * @param p1 ponto 1
 * @param p2 ponto 2
 * @return Point_3D ponto resultante da operação
 */
Point_3D mul(Point_3D p1, Point_3D p2);

/**
 * @brief calcula a subtração entre dois pontos
 * 
 * @param p1 ponto 1
 * @param p2 ponto 2
 * @return Point_3D ponto resultante da operação
 */
Point_3D sub(Point_3D p1, Point_3D p2);

/**
 * @brief calcula da normal de uma superfície, utilizando três pontos pertencentes
 * 
 * @param p1 ponto 1
 * @param p2 ponto 2
 * @param p3 ponto 3
 * @return Point_3D ponto normal resultante da operação
 */
Point_3D getNormal(Point_3D p1, Point_3D p2, Point_3D p3);

/**
 * @brief criação de um ponto normalizado, sem alterar o original
 * 
 * @param p ponto a operar
 * @return Point_3D ponto resultante da normalização
 */
Point_3D getNormalize(Point_3D p);

#endif //GENERATOR_POINT_3D_H
