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

                float length;                           // plane's side length
                int divisions;                          // Plane's side divisions

                Point_3D p1;                            // Point N=1
                Point_3D p2;                            // Point N=2
                Point_3D p3;                            // Point N=3
                Point_3D p4;                            // Point N=4

                std::vector<Point_3D> planePoints;      // Plane's list of points
                std::vector<int> planePointsIndexes;    // Point's indexes
                std::vector<Point_3D> normals;          // normals
                std::vector<Point_2D> texs;             // texture coords
                int nPoints;                            // n points
                int nIndexes;                           // n indexes

        public:

                // constructors
                Plane();
                Plane(float l, int div, bool onXZ);


                /**
                * Retorna o ponto pretendido do plano
                * @return `Point_3D` o ponto pedido
                */
                Point_3D getP1();

                /**
                * Retorna o ponto pretendido do plano
                * @return `Point_3D` o ponto pedido
                */
                Point_3D getP2();

                /**
                * Retorna o ponto pretendido do plano
                * @return `Point_3D` o ponto pedido
                */
                Point_3D getP3();

                /**
                * Retorna o ponto pretendido do plano
                * @return `Point_3D` o ponto pedido
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
                 * @brief Set the Plane Vertices/Point's nromals
                 *
                 * @param normalsList list of vertices/Point's normals
                 */
                void Plane::setNormals(std::vector<Point_3D> normalsList);



                /**
                * Retorna um plano paralelo a XY, com P1 como ponto de refer??ncia do plano
                *
                * @return `Plane` o plano criado
                */
                Plane planeXY();

                /**
                * Retorna um plano paralelo a YZ, com P1 como ponto de refer??ncia do plano
                *
                * @return `Plane` o plano criado
                */
                Plane planeYZ();




                /**
                * Retorna o Modelo do Plano
                * Primeira linha com o n??mero de pontos utilizados, assim como o n??mero de indices utilizados para
                * configurar a representa????o gr??fica
                * Linhas seguintes com os pontos utilizados, em cada ??ndice
                * 
                * @param output_file ficheiro resultante
                */
                void toFile(std::string s);


                /**
                 * @brief Calcula os pontos necess??rios para configurar o plano
                 * 
                 * @param length lado do plano
                 * @param dividions n??mero de divis??es a aplicar por eixo
                 * @return std::vector<Point_3D> lista com os pontos calculados
                 */
                std::vector<Point_3D> calculatePlanePoints();

                /**
                 * @brief Calcula os ??ndices dos pontos utilizados para construir os tri??ngulos que formam o plano
                 * 
                 * @return std::vector<int> lista de ??ndices
                 */
                std::vector<int> calculatePlaneVertices();

                std::vector<int> planeVerticesInverted();


                /**
                 * @brief Devolve a informa????o contida pelo plano, a lista de pontos e a dos ??ndices utilizados
                 * para a configura????o gr??fica
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

                /**
                 * @brief Get the Normals coords
                 * 
                 * @return std::vector<Point_3D> 
                 */
                std::vector<Point_3D> getNormals();

                /**
                 * @brief Get the Texs coords
                 * 
                 * @return std::vector<Point_2D> 
                 */
                std::vector<Point_2D> getTexs();


};      

#endif //GENERATOR_PLANE_H