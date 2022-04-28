#include "../../headers/translation.h"

/**
 * @brief Construct a new Translation:: Translation object
 * 
 */
Translation::Translation(){

    x = y = z = time = 0.0f;
    align = hasTime = false; 
    catmullCurvePoints = vector<Point_3D*>();
}


Translation::Translation(float x, float y, float z){

    this->x = x; 
    this->y = y; 
    this->z = z; 
    this->time = 0.0f;
    this->catmullCurvePoints = vector<Point_3D*>();
}


/**
 * @brief Construct a new Translation:: Translation object
 * 
 * @param x 
 * @param y 
 * @param z 
 * @param time 
 * @param catmull 
 */
Translation::Translation(float x, float y, float z, float time, vector<Point_3D*> catmull){

    this->x = x; 
    this->y = y; 
    this->z = z; 
    this->time = time;
    this->catmullCurvePoints = vector<Point_3D*>(catmull);

    for (Point_3D* p : catmull)
        printf("\n#> %s", p->toString());
}

/**
 * @brief get x value from translation
 * 
 * @return float 
 */
float Translation::getX(){
    return x;
}

/**
 * @brief get y value from translation
 * 
 * @return float 
 */
float Translation::getY(){
    return y;
}

/**
 * @brief get z value from translation
 * 
 * @return float 
 */
float Translation::getZ(){
    return z;
}

/**
 * @brief get time value from translation
 * 
 * @return float 
 */
float Translation::getTime(){
    return time;
}

/**
 * @brief get align value from translation
 * 
 * @return true 
 * @return false 
 */
bool Translation::getAlign(){
    return align;
}

/**
 * @brief confirm if translation has time
 * 
 * @return true 
 * @return false 
 */
bool Translation::getHasTime(){
    return hasTime;
}

/**
 * @brief get translation curve's points
 * 
 * @return vector<Point_3D> 
 */
vector<Point_3D*> Translation::getCurvePoints(){
    return vector<Point_3D*>(catmullCurvePoints);
}

/**
 * @brief number of curve's points
 * 
 * @return int 
 */
int Translation::getCurveNPoints(){
    return catmullCurvePoints.size();
}

/**
 * @brief set x
 * 
 * @param x 
 */
void Translation::setX(float x){
    this->x = x;
}

/**
 * @brief set y
 * 
 * @param y 
 */
void Translation::setY(float y){
    this->y = y;
}

/**
 * @brief set z
 * 
 * @param z 
 */
void Translation::setZ(float z){
    this->z = z;
}

/**
 * @brief set time
 * 
 * @param t 
 */
void Translation::setTime(float t){
    time = t;
}

/**
 * @brief set align
 * 
 * @param a 
 */
void Translation::setAlign(bool a){
    align = a;
}

/**
 * @brief set hasTime
 * 
 * @param t 
 */
void Translation::setHasTime(bool t){
    hasTime = t;
}

/**
 * @brief set curve points
 * 
 * @param points 
 */
void Translation::setCurvePoints(vector<Point_3D*> points){
    catmullCurvePoints = vector<Point_3D*>(points);
}



/**
 * @brief FALTA CATMULL TODO
 * 
 */


/**
 * @brief Normaliza um vector
 * 
 * v = v / |v|
 * 
 * @param v 
 */
void Translation::normalizeVector(float* v){

    float modulus = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] = v[0] / modulus;
    v[1] = v[1] / modulus;
    v[2] = v[2] / modulus;
}


/**
 * @brief Multiplica um vetor por uma matrix 4x4
 * 
 * @param vector 
 * @param matrix 
 * @param answer 
 */
void Translation::vectorByMatrix(float *vector, float *matrix, float *answer){

    for (int l = 0; l < 4; l++){
        answer[l] = 0;

        for (int c = 0; c < 4; c++){

            answer[l] += vector[c] * matrix[l * 4 + c];
        }
    }
}

/**
 * @brief Produto vetorial - vector cross product
 * 
 * @param v1 
 * @param v2 
 * @param answer 
 */
void Translation::vectorsCross(float *v1, float *v2, float *answer){

    answer[0] = v1[1] * v2[2] - v1[2] * v2[1];
    answer[1] = v1[2] * v2[0] - v1[0] * v2[2];
    answer[2] = v1[0] * v2[1] - v1[1] * v2[0];
}


/**
 * @brief Cálculo da matrix de rotação
 * 
 * @param x 
 * @param y 
 * @param z 
 * @param answer 
 */
void Translation::calculateRotMatrix(float *x, float *y, float *z, float *answer){

    answer[0] = x[0]; answer[1] = x[1]; answer[2] = x[2]; answer[3] = 0.0f;

    answer[4] = y[0]; answer[5] = y[1]; answer[6] = y[2]; answer[7] = 0.0f;

    answer[8] = z[0]; answer[9] = z[1]; answer[10] = z[2]; answer[11] = 0.0f;

    answer[12] = 0.0f; answer[13] = 0.0f; answer[14] = 0.0f; answer[15] = 1.0f;
}



/**
 * @brief Cálculo de um ponto Catmull Rom
 * 
 * @param t 
 * @param p01 
 * @param p02 
 * @param p03 
 * @param p04 
 * @param pos 
 * @param derivative 
 */
void Translation::calculateCatmullPoint(float t, Point_3D p01, Point_3D p02, Point_3D p03, Point_3D p04, float *pos, float *derivative){

    float catmullMatrix[4][4] = {
        {-0.5f, 1.5f, -1.5f, 0.5f},
        {1.0f, -2.5f, 2.0f, -0.5f},
        {-0.5f, 0.0f, 0.5f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f}
    };


    // CatmullMatrix * PointsVector 
    Point_3D matrixByPoints[4];

    for (int i = 0; i < 4; i++){

        float x = p01.getX() * catmullMatrix[i][0] + p02.getX() * catmullMatrix[i][1] + p03.getX() * catmullMatrix[i][2] + p04.getX() * catmullMatrix[i][3];
        float y = p01.getY() * catmullMatrix[i][0] + p02.getY() * catmullMatrix[i][1] + p03.getY() * catmullMatrix[i][2] + p04.getY() * catmullMatrix[i][3];
        float z = p01.getZ() * catmullMatrix[i][0] + p02.getZ() * catmullMatrix[i][1] + p03.getZ() * catmullMatrix[i][2] + p04.getZ() * catmullMatrix[i][3];
        Point_3D current = Point_3D(x,y,z);
        matrixByPoints[i] = current;
    }

    // Catmull Point
    
    pos[0] = powf(t, 3) * matrixByPoints[0].getX() + powf(t,2) * matrixByPoints[1].getX() + t * matrixByPoints[2].getX() + matrixByPoints[3].getX();
    pos[1] = powf(t, 3) * matrixByPoints[0].getY() + powf(t,2) * matrixByPoints[1].getY() + t * matrixByPoints[2].getY() + matrixByPoints[3].getY();
    pos[2] = powf(t, 3) * matrixByPoints[0].getZ() + powf(t,2) * matrixByPoints[1].getZ() + t * matrixByPoints[2].getZ() + matrixByPoints[3].getZ();


    // derivative of catmullPoint

    derivative[0] = 3 * powf(t,2) * matrixByPoints[0].getX() + 2 * t * matrixByPoints[1].getX() + matrixByPoints[2].getX();
    derivative[1] = 3 * powf(t,2) * matrixByPoints[0].getY() + 2 * t * matrixByPoints[1].getY() + matrixByPoints[2].getY();
    derivative[2] = 3 * powf(t,2) * matrixByPoints[0].getZ() + 2 * t * matrixByPoints[1].getZ() + matrixByPoints[2].getZ();
}


/**
 * @brief get de um ponto catmull rom
 * 
 * @param t 
 * @param pos 
 * @param derivative 
 * @param givenPoints 
 */
void Translation::getCatmullPoint(float t, float *pos, float *derivative){

    int size = catmullCurvePoints.size();
    float currentT = t * size;
    int index = floor(currentT);
    currentT -= index;

    int indices[4];
	indices[0] = (index + size - 1) % size;
	indices[1] = (indices[0] + 1) % size;
	indices[2] = (indices[1] + 1) % size;
	indices[3] = (indices[2] + 1) % size;

	calculateCatmullPoint(currentT, *catmullCurvePoints[indices[0]], *catmullCurvePoints[indices[1]], *catmullCurvePoints[indices[2]], *catmullCurvePoints[indices[3]], pos, derivative);
}


/**
 * @brief Desenha a curva
 * 
 */
void Translation::drawCurve(){

    float pos[3], derivative[3];

    float interval = 0.01f;

    glBegin(GL_LINE_LOOP);
    for (float interv = 0.0f; interv < 1; interv += interval){

        getCatmullPoint(interv, pos, derivative);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}


/**
 * @brief Aplica a translação
 * 
 */
void Translation::Apply(){

    float elapsedT = 0, globalT = 0;
    float deriv[3];
    // y axis
    static float yAxis[3] = {0.0f, 1.0f, 0.0f};
    float pos[3], zAxis[3],
    rotationMatrix[16];  // easier because of c++ matrix mult.


    if (time != 0 && catmullCurvePoints.size() != 0){

        elapsedT = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
        globalT = elapsedT / (time * 1000);

        //drawCurve();

        getCatmullPoint(globalT, pos, deriv);
        glTranslatef(pos[0], pos[1], pos[2]);
        normalizeVector(deriv);
        normalizeVector(yAxis);
        vectorsCross(deriv, yAxis, zAxis);
        vectorsCross(zAxis, deriv, yAxis);
        //  x, y, z, rotMatrix
        calculateRotMatrix(deriv, yAxis, zAxis, rotationMatrix);
        glMultMatrixf(rotationMatrix);
    }

    else {

        glTranslatef(this->x, this->y, this->z);
    }
}