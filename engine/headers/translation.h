#ifndef TRANSLATION_HEADER_FILE
#define TRANSLATION_HEADER_FILE

#include <vector>
#include "transformation.h"
#include "../../utils/point_3d.h"

using namespace std;

class Translation : public Transformation{

    private:
        float x,y,z;                    // translate se for só um translate
        float time;                     
        bool hasTime;
        bool align;
        vector<Point_3D*> catmullCurvePoints;  // pontos que definem a curva catmmull

    public:
        // constructors
        Translation();
        Translation(float x, float y, float z);
        Translation(float x, float y, float z, float time, vector<Point_3D*> catmull);
        
        // gets & sets
        float getX();
        float getY();
        float getZ();
        float getTime();
        bool getAlign();
        bool getHasTime();
        vector<Point_3D*> getCurvePoints();
        int getCurveNPoints();
        void setX(float n);
        void setY(float n);
        void setZ(float n);
        void setTime(float t);
        void setAlign(bool a);
        void setHasTime(bool t);
        void setCurvePoints(vector<Point_3D*> points);


        // catmull calculations
        void normalizeVector(float* v);

        void vectorByMatrix(float *vector, float *matrix, float *answer);

        void vectorsCross(float *v1, float *v2, float *answer);

        void calculateRotMatrix(float *x, float *y, float *z, float *answer);

        void calculateCatmullPoint(float t, Point_3D p01, Point_3D p02, Point_3D p03, Point_3D p04, float *pos, float *derivative);

        void getCatmullPoint(float time, float *pos, float *derivative);

        void drawCurve();
        
        void Apply(void);
};


#endif