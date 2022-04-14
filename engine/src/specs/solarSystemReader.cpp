#include <iostream>
#include <string>
#include <vector>

#include "../../headers/celestialBody.h"
#include "../../headers/solarSystemReader.h"
#include "../../headers/camera.h"


void printAttrib(TiXmlElement* a){

  TiXmlAttribute* atrib = a->FirstAttribute();
  for (;atrib != NULL; atrib = atrib->Next() ) {
      cout << atrib->Name() << " : " << atrib->Value() << std::endl;
  }
}


/**
 * @brief Recolhe as specs de um corpo celeste e adiciona a um vector auxiliar
 * 
 * @param a tinyxml element
 */
vector<float> getSpecs(TiXmlElement* a, vector<float> xmlValues){


  TiXmlAttribute* atrib = a->FirstAttribute();
  for (;atrib != NULL; atrib = atrib->Next() ) {
    
    float value;
    try {
      value = stof(atrib->Value());
      xmlValues.push_back(value);
    } catch(exception){
      continue;
    }
    
  }
  return xmlValues;
}

/**
 * @brief Atualiza o model name de um objeto specs
 * 
 * @param a 
 * @param sets 
 */
string getModelName(TiXmlElement* a){

  TiXmlAttribute* atrib = a->FirstAttribute();
  return atrib->Value();
}

/**
 * @brief Create a Settings object
 * 
 * @param specs 
 * @param modelName 
 * @return Settings 
 */
Settings createSettings(vector<float> specs, string modelName){
  Settings setts = Settings(specs, modelName);
  return setts;
}

/**
 * @brief Create a Orbit object
 * 
 * @param orbs 
 * @return Orbit 
 */
Orbit createOrbit(vector<float> orbs){

  Orbit orb = Orbit(orbs);
  return orb;
}
   
void parseCamera(TiXmlElement *camera, Camera* c) {
    vector<float> cameraValues = vector<float>();

    for (TiXmlElement* cameraV = camera->FirstChildElement(); cameraV != NULL; cameraV = cameraV->NextSiblingElement()) {
        cameraValues = getSpecs(cameraV, cameraValues);
    }
    Point_3D pos = Point_3D(cameraValues.at(0), cameraValues.at(1), cameraValues.at(2));
    Point_3D lookAt = Point_3D(cameraValues.at(3), cameraValues.at(4), cameraValues.at(5));
    Point_3D up = Point_3D(cameraValues.at(6), cameraValues.at(7), cameraValues.at(8));
    Point_3D persp = Point_3D(cameraValues.at(9), cameraValues.at(10), cameraValues.at(11));

    c->setPos(pos.getX(), pos.getY(), pos.getZ());
    c->setLookAt(lookAt.getX(), lookAt.getY(), lookAt.getZ());
    c->setPersp(persp.getX(), persp.getY(), persp.getZ());
}



CelestialBody parseCelestialBody(TiXmlElement *bodyXml, bool isSun){

  CelestialBody body = CelestialBody();
  vector<float> orbitValues = vector<float>();
  vector<float> specsValues = vector<float>();
  string modelName;

  if (isSun == false){

    for(TiXmlElement* orbit = bodyXml->FirstChildElement(); orbit != NULL; orbit = orbit->NextSiblingElement()){

      orbitValues = getSpecs(orbit, orbitValues);

        for(TiXmlElement* specs = orbit->FirstChildElement(); specs != NULL; specs = specs->NextSiblingElement()){

          specsValues = getSpecs(specs, specsValues);

            for(TiXmlElement* model = specs->FirstChildElement();model != NULL; model = model->NextSiblingElement()){
              modelName = getModelName(model);
              }
          }
    }
    Settings setts = createSettings(specsValues, modelName);
    Orbit orbs = createOrbit(orbitValues);
    body.setOrbit(orbs);
    body.setSettings(setts);
  }
  else {

    for(TiXmlElement* specs = bodyXml->FirstChildElement(); specs != NULL; specs = specs->NextSiblingElement()){

          specsValues = getSpecs(specs, specsValues);

            for(TiXmlElement* model = specs->FirstChildElement();model != NULL; model = model->NextSiblingElement()){
              modelName = getModelName(model);
              }
          }
    Settings setts = createSettings(specsValues, modelName);
    body.setSettings(setts);
    body.setOrbit(Orbit());
  }

  return body;
}


CelestialBody parseCelestialBodyWithMoons(TiXmlElement *bodyXml){

  CelestialBody body = CelestialBody();
  vector<CelestialBody> moons = vector<CelestialBody>();
  vector<float> orbitValues = vector<float>();
  vector<float> specsValues = vector<float>();
  string modelName;
  bool flag = false;

  for(TiXmlElement* bodyOrbit = bodyXml->FirstChildElement(); bodyOrbit != NULL; bodyOrbit = bodyOrbit->NextSiblingElement()){

    orbitValues = getSpecs(bodyOrbit, orbitValues);
    //printAttrib(bodyOrbit);

    for(TiXmlElement* bodySetts = bodyOrbit->FirstChildElement();bodySetts != NULL; bodySetts = bodySetts->NextSiblingElement()){

      specsValues = getSpecs(bodySetts, specsValues);
      //printAttrib(bodySetts);
      
      for(TiXmlElement* modelPlanet = bodySetts->FirstChildElement();modelPlanet != NULL; modelPlanet = modelPlanet->NextSiblingElement()){

        //printAttrib(modelPlanet);
        if (flag == false){
          modelName = getModelName(modelPlanet);

          Settings planetSettings = createSettings(specsValues, modelName);
          Orbit planetOrbit = createOrbit(orbitValues);
          body.setSettings(planetSettings);
          body.setOrbit(planetOrbit);

          specsValues.clear();
          orbitValues.clear(); modelName.clear();
          flag = true;
        }
        else {

          orbitValues = getSpecs(modelPlanet, orbitValues);
        }
        
        for(TiXmlElement* moonValues = modelPlanet->FirstChildElement();moonValues != NULL; moonValues = moonValues->NextSiblingElement()){
          //printAttrib(moonValues);

          specsValues = getSpecs(moonValues, specsValues);
          
          for(TiXmlElement* moonModel = moonValues->FirstChildElement();moonModel != NULL; moonModel = moonModel->NextSiblingElement()){
            
            //printAttrib(moonModel);

            modelName = getModelName(moonModel);

            Settings moonSettings = createSettings(specsValues, modelName);
            Orbit moonOrbit = createOrbit(orbitValues);
            CelestialBody moon = CelestialBody(moonOrbit, moonSettings);
            moons.push_back(moon);

            specsValues.clear();
            orbitValues.clear();
            modelName.clear();
          }
        }
      }
    }
  }

  body.setMoons(moons);

  return body;
}



vector<CelestialBody> readSolarSystem(string xmlPath, Camera* c){
    
  vector<CelestialBody> solarSystem = vector<CelestialBody>();

  TiXmlDocument config;
  if (!config.LoadFile(xmlPath.c_str())) {
      cout << "can not parse xml file" << endl;
      return solarSystem;
  }
  
  TiXmlElement* rootElement = config.RootElement();  //System
  //printAttrib(rootElement);

  TiXmlElement *camera = rootElement->FirstChildElement(); // Camara
  parseCamera(camera,c);

  TiXmlElement *figures = camera->NextSiblingElement(); // Figures
  //printAttrib(figures);

  vector<float> xmlSpecs = vector<float>();
  vector<float> xmlOrbit = vector<float>();
  string modelName;

 //----------------------------------------------------------------------------------------------------------------------------------------------SUN
  TiXmlElement *sun = figures->FirstChildElement();  //Sol
  CelestialBody sunBody = parseCelestialBody(sun, true);
  solarSystem.push_back(sunBody);
//----------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------MERCURY
  TiXmlElement *mercury = sun->NextSiblingElement();
  CelestialBody mercuryBody = parseCelestialBody(mercury, false);
  solarSystem.push_back(mercuryBody);
//----------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------VENUS
  
  TiXmlElement *venus = mercury->NextSiblingElement();
  CelestialBody venusBody = parseCelestialBody(venus, false);
  solarSystem.push_back(venusBody);
//----------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------EARTH

  TiXmlElement *earth = venus->NextSiblingElement();
  CelestialBody earthBody = parseCelestialBodyWithMoons(earth);
  solarSystem.push_back(earthBody);
//----------------------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------------------Mars
  TiXmlElement *mars = earth->NextSiblingElement();
  CelestialBody marsBody = parseCelestialBody(mars, false);
  solarSystem.push_back(marsBody);
//----------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------JUPITER
  TiXmlElement *jupiter = mars->NextSiblingElement();
  CelestialBody jupiterBody = parseCelestialBodyWithMoons(jupiter);
  solarSystem.push_back(jupiterBody);
//----------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------SATURN

  TiXmlElement *saturn = jupiter->NextSiblingElement();
  CelestialBody saturnBody = parseCelestialBodyWithMoons(saturn);
  solarSystem.push_back(saturnBody);
//----------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------URANUS
  TiXmlElement *uranus = saturn->NextSiblingElement();
  CelestialBody uranusBody = parseCelestialBodyWithMoons(uranus);
  solarSystem.push_back(uranusBody);
//----------------------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------------------NEPTUNE
  TiXmlElement *neptune = uranus->NextSiblingElement();
  CelestialBody neptuneBody = parseCelestialBodyWithMoons(neptune);
  solarSystem.push_back(neptuneBody);
//----------------------------------------------------------------------------------------------------------------------------------------------
  

  return solarSystem;
}