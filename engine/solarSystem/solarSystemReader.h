#ifndef SOLAR_SYSTEM_READER_HEADER
#define SOLAR_SYSTEM_READER_HEADER

#include "../utils/tinyxml.h"
#include "../solarSystem/celestialBody.h"
#include <vector>

using namespace std;



void printAttrib(TiXmlElement* a);

vector<float> getSpecs(TiXmlElement* a, vector<float> xmlValues);

string getModelName(TiXmlElement* a);

Settings createSettings(vector<float> specs, string modelName);

Orbit createOrbit(vector<float> orbs);

CelestialBody parseCelestialBody(TiXmlElement *bodyXml, bool isSun);

CelestialBody parseCelestialBodyWithMoons(TiXmlElement *bodyXml);

vector<CelestialBody> readSolarSystem(string xmlPath);

#endif