#pragma
#ifndef GENERATOR_PLANE_H
#define GENERATOR_PLANE_H

#include "../utils/point_3d.h"
#include <fstream>
#include <vector>

class Plane {

    private:
        Point_3D p1;
        Point_3D p2;
        Point_3D p3;
        Point_3D p4;
	
	public:
        Plane() { }

        Plane(Point_3D p1, Point_3D p2, Point_3D p3, Point_3D p4) {
            this->p1 = p1;
            this->p2 = p2;
            this->p3 = p3;
            this->p4 = p4;
        }

                /**
        *	Retorna o ponto pretendido do plano
        *	@return `Point_3D` o ponto pedido
        */
        Point_3D getP1();

        /**
        *	Retorna o ponto pretendido do plano
        *	@return `Point_3D` o ponto pedido
        */
        Point_3D getP2();

        /**
        *	Retorna o ponto pretendido do plano
        *	@return `Point_3D` o ponto pedido
        */
        Point_3D getP3();

        /**
        *	Retorna o ponto pretendido do plano
        *	@return `Point_3D` o ponto pedido
        */
        Point_3D getP4();

                /**
        *	Retorna um plano paralelo a XY
        *	@param x Dimensão em X do plano
        *	@param y Dimensão em Y do plano
        *	@return `Plane` o plano criado
        */
        static Plane planeXY(float x, float y);

        /**
        *	Retorna um plano paralelo a XZ
        *	@param x Dimensão em X do plano
        *	@param z Dimensão em Z do plano
        *	@return `Plane` o plano criado
        */
        static Plane planeXZ(float x, float z);

        /**
        *	Retorna um plano paralelo a YZ
        *	@param y Dimensão em Y do plano
        *	@param z Dimensão em Z do plano
        *	@return `Plane` o plano criado
        */
        static Plane planeYZ(float y, float z);

        /**
        *	Retorna o Modelo do Plano
        *	@param output_file ficheiro resultante
        */
        void toFile(char* output_file);
}


#endif //GENERATOR_PLANE_H