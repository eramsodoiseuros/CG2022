#pragma
#ifndef GENERATOR_SPHERE_H
#define GENERATOR_SPHERE_H

#include <math.h>
#define _USE_MATH_DEFINES
#include <fstream>
#include <vector>
#include "../../utils/point_3d.h"
#include "../../utils/point_2d.h"

class Sphere {
    private:
        float raio;
        int stacks;
        int slices;
        Point_3D center;

        std::vector<Point_3D> points;         // Pontos da esfera
        std::vector<Point_3D> normals;        // normais
        std::vector<short> indexes;           // índices para construção
        std::vector<Point_2D> texs;

    public:
        Sphere(float r, int slices, int stacks);

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
        void calculateSphere(Point_3D center, float height, int slices, int stacks);
        
        /**
         * @brief Calcula os indices para construção
         * @param points Pontos da esfera
         * @return vetor com os indices
         */
        void calculateIndexes();
        
        /**
         * @brief Get the Sphere Points object
         * @return Pontos da esfera
         */
        std::vector<Point_3D> getPoints();

        /**
         * @brief Get the Normals object
         * 
         * @return std::vector<Point_3D> 
         */
        std::vector<Point_3D> getNormals();

        /**
         * @brief Get the Sphere Points Indexes object
         * @return Indexes
         */
        std::vector<short> getIndexes();


        std::vector<Point_2D> getTexs();
};


#endif //GENERATOR_SPHERE_H
