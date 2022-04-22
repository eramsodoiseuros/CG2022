#ifndef CELESTIALBODY_HEADER
#define CELESTIALBODY_HEADER

#include "orbit.h"
#include "specs.h"

#include <vector>

using namespace std;

class CelestialBody{

    private:

        Orbit bodyOrbit;
        Settings bodySettings;
        vector<CelestialBody> moons;

    public:
        CelestialBody() = default;

        CelestialBody(Settings specs){
            
            bodySettings = specs;
            moons = vector<CelestialBody>();
        }
        
        CelestialBody(Orbit orbit, Settings specs){

            bodyOrbit = orbit;
            bodySettings = specs;

            moons = vector<CelestialBody>();
        }

        Orbit getOrbit();
        void setOrbit(Orbit o);

        Settings getSettings();
        void setSettings(Settings s);

        vector<CelestialBody> getMoons();
        void addMoon(CelestialBody m);
        void setMoons(vector<CelestialBody> m);

};

#endif