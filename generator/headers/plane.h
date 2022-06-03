#pragma
#ifndef GENERATOR_PLANE_H
#define GENERATOR_PLANE_H

#include <fstream>
#include "../../utils/point_3d.h"
#include "../../utils/point_2d.h"
#include <vector>

/*
 | Plane (vista cima) |
      (3)-------(4)
        |       |
        |       |
        |       |
      (1)-------(2)
*/

class Plane {

    private:

        float length;           // plane's side length
        int divisions;          // Plane's side divisions

        Point_3D p1;            // Point N=1
        Point_3D p2;            // Point N=2
        Point_3D p3;            // Point N=3
        Point_3D p4;            // Point N=4
        
        std::vector<Point_3D> planePoints;              // Plane's list of points
        std::vector<int> planePointsIndexes;            // Point's indexes
        std::vector<Point_3D> normals;
        std::vector<Point_2D> texs;
        int nPoints;
        int nIndexes;

	
	public:

        // constructors
        Plane();
        Plane(float l, int div, bool onXZ);
        

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
         * @brief Get the Length variable
         * 
         * @return float 
         */
        float getLength();

        /**
         * @brief Get the Divisions variable
         * 
         * @return int 
         */
        int getDivisions();
        
        /**
         * @brief Get the Number Of Points
         * 
         * @return int 
         */
        int getNumberOfPoints();

        /**
         * @brief Get the Number Of Indexes
         * 
         * @return int 
         */
        int getNumberOfIndexes();

        /**
         * @brief Set the Plane Points
         * 
         * @param points List of Points
         */
        void setPlanePoints(std::vector<Point_3D> points);
        
        /**
         * @brief Set the Plane Vertices/Point's indexes
         * 
         * @param vertices list of vertices/Point's indexes
         */
        void setPlaneVertices(std::vector<int> vertices);

        /**
         * @brief Change plane's reference point (p1)
         * 
         * @param p new Point
         */
        void setP1(Point_3D p);

        /**
         * @brief Change plane's external point (p2)
         * 
         * @param p new point
         */
        void setP2(Point_3D p);

        /**
         * @brief Change plane's external point (p3)
         * 
         * @param p new Point
         */
        void setP3(Point_3D p);

        /**
         * @brief Change plane's external point (p4)
         * 
         * @param p new Point
         */
        void setP4(Point_3D p);


        /**
        *	Retorna um plano paralelo a XY, com P1 como ponto de referência do plano
        *
        *	@return `Plane` o plano criado
        */
        Plane planeXY();

        /**
        *	Retorna um plano paralelo a YZ, com P1 como ponto de referência do plano
        *
        *	@return `Plane` o plano criado
        */
        Plane planeYZ();

        /**
        *	Retorna o Modelo do Plano
        *       Primeira linha com o número de pontos utilizados, assim como o número de indices utilizados para
        *       configurar a representação gráfica
        *       Linhas seguintes com os pontos utilizados, em cada índice
        * 
        *	@param output_file ficheiro resultante
        */
        void toFile(std::string s);


        /**
         * @brief Calcula os pontos necessários para configurar o plano
         * 
         * @param length lado do plano
         * @param dividions número de divisões a aplicar por eixo
         * @return std::vector<Point_3D> lista com os pontos calculados
         */
        std::vector<Point_3D> calculatePlanePoints();

        /**
         * @brief Calcula os índices dos pontos utilizados para construir os triângulos que formam o plano
         * 
         * @return std::vector<int> lista de índices
         */
        std::vector<int> calculatePlaneVertices();

        std::vector<int> planeVerticesInverted();


        /**
         * @brief Devolve a informação contida pelo plano, a lista de pontos e a dos índices utilizados
         * para a configuração gráfica
         * 
         * @return std::pair < std::vector<Point_3D>, std::vector<int >> 
         */
        std::pair < std::vector<Point_3D>, std::vector<int >> PlaneInfo();


        /**
         * @brief Get the Plane Points
         * 
         * @return std::vector<Point_3D> 
         */
        std::vector<Point_3D> getPlanePoints();

        /**
         * @brief Get the Plane Points Indexes
         * 
         * @return std::vector<int> 
         */
        std::vector<int> getPlanePointsIndexes();

        /**
         * @brief Adiciona ao plano uma profundidade positiva, no eixo do X
         * 
         */
        void addX();

        /**
         * @brief Adiciona ao plano uma profundidade positiva, no eixo do Y (altura)
         * 
         */
        void addY();

        /**
         * @brief Adiciona ao plano uma profundidade negativa, no eixo do Z
         * 
         */
        void addZ();

        std::vector<Point_3D> getNormals();

        std::vector<Point_2D> getTexs();
        
        
};

#endif //GENERATOR_PLANE_H