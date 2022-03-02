#include "polar.h"

double Polar::polarX() {
    return this->radius * cos(this->beta) * sin(this->alpha);
}

double Polar::polarY() {
    return this->radius * sin(this->beta);
}

double Polar::polarZ() {
    return this->radius * cos(this->beta) * cos(this->alpha);
}

double Polar::getRadius(){
    return this->radius;
}

double Polar::getAlpha(){
    return this->alpha;
}

double Polar::getBeta(){
    return this->beta;
}

void Polar::changeRadius(double r){
    this->radius = r;
}

void Polar::changeAlpha(double a){
    this->alpha = a;
}

void Polar::changeBeta(double b){
    this->beta = b;
}
