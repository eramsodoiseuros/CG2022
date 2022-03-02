#ifndef GENERATOR_POLAR_H
#define GENERATOR_POLAR_H

#include <cmath>

class Polar {
private:
    double radius;
    double alpha;
    double beta;

public:
    Polar(double r, double a, double b) {
        this->radius = r;
        this->alpha = a;
        this->beta = b;
    }

    double polarX();
    double polarY();
    double polarZ();

    double getRadius();
    double getAlpha();
    double getBeta();

    void changeRadius(double r);
    void changeAlpha(double a);
    void changeBeta(double b);
};

#endif //GENERATOR_POLAR_H
