#include "rgb.h"

rgb hsv::hsv2rgb() {
    double		hh, p, q, t, ff;
    long		i;
    rgb			out;

    if(this->s <= 0.0) {
        out.r = this->v;
        out.g = this->v;
        out.b = this->v;
        return out;
    }
    hh = this->h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = this->v * (1.0 - this->s);
    q = this->v * (1.0 - (this->s * ff));
    t = this->v * (1.0 - (this->s * (1.0 - ff)));

    switch(i) {
        case 0:
            out.r = this->v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = this->v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = this->v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = this->v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = this->v;
            break;

        default:
            out.r = this->v;
            out.g = p;
            out.b = q;
            break;
    }

    return out;
}

void rgb::setR(double r) {
    rgb::r = r;
}

void rgb::setG(double g) {
    rgb::g = g;
}

void rgb::setB(double b) {
    rgb::b = b;
}

double rgb::getR() const {
    return r;
}

double rgb::getG() const {
    return g;
}

double rgb::getB() const {
    return b;
}
