#include "celestialBody.h"

#include <vector>

Orbit CelestialBody::getOrbit(){

    return bodyOrbit;
}

void CelestialBody::setOrbit(Orbit o){

    bodyOrbit = o;
}


Settings CelestialBody::getSettings(){

    return bodySettings;
}

void CelestialBody::setSettings(Settings s){

    bodySettings = s;
}

void CelestialBody::addMoon(CelestialBody m){

    moons.push_back(m);
}

vector<CelestialBody> CelestialBody::getMoons(){
    return vector<CelestialBody>(moons);
}

void CelestialBody::setMoons(vector<CelestialBody> m){

    moons = m;
}