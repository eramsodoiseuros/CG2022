#pragma
#ifndef GENERATOR_SPHERE_H
#define GENERATOR_SPHERE_H

#include <math.h>
#define _USE_MATH_DEFINES
#include <fstream>
#include <vector>
#include "../../utils/point_3d.h"

class Sphere {
    private:
        float raio;
        int stacks;
        int slices;
        Point_3D center;

        std::vector<Point_3D> spherePoints;         // Pontos da esfera
        std::vector<short> sphereIndexes;           // índices para construção

    public:
        Sphere(float r, int s1, int s2) {
            this->center = Point_3D(0.0f,0.0f,0.0f);
            this->raio = r;
            this->stacks = s1;
            this->slices = s2;

            spherePoints = calculateSphere(center,raio,stacks,slices);
            sphereIndexes = calculateIndexes();

        }

        /**
        *	Retorna o raio da Esfera
        *	@return `float` radius
        */
        float getRadius();

        /**
        *	Retorna as stacks da Esfera
        *	@return `int` stacks
        */
        int getStacks();

        /**
        *	Retorna as slices da Esfera
        *	@return `int` slices
        */
        int getSlices();

        /**
        *	Retorna o Modelo da Esfera
        *	@param output_file ficheiro resultante
        */
        void toFile(std::string s);


        /**
         * @brief Calcula os pontos da esfera
         * @return vetor com os pontos
         */
        static std::vector<Point_3D> calculateSphere(Point_3D center, float height, int slices, int stacks);
        
        /**
         * @brief Calcula os indices para construção
         * @param points Pontos da esfera
         * @return vetor com os indices
         */
        std::vector<short> calculateIndexes();
        
        /**
         * @brief Get the Sphere Points object
         * @return Pontos da esfera
         */
        std::vector<Point_3D> getSpherePoints();
        /**
         * @brief Get the Sphere Points Indexes object
         * @return Indexes
         */
        std::vector<short> getSpherePointsIndexes();
};


#endif //GENERATOR_SPHERE_H
