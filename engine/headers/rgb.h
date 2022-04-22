#ifndef TPCGMIEI_RGB_H
#define TPCGMIEI_RGB_H

class rgb {
public:
    double r;
    double g;
    double b;

    double getR() const;

    double getG() const;

    double getB() const;

    void setR(double r);

    void setG(double g);

    void setB(double b);
};

class hsv {
public:
    rgb hsv2rgb();
    double h;
    double s;
    double v;
};

#endif //TPCGMIEI_RGB_H
