#include "../../headers/xmlparser.h"
#include "../../headers/rotation.h"
#include "../../headers/translation.h"
#include "../../headers/scale.h"
#include <sstream>
#include <iostream>



void parseValues(TiXmlElement* elem, char* value1, char* value2, char* value3, Point_3D* point) {
    TiXmlAttribute* attribute = elem->FirstAttribute();

    float x = 0, y = 0, z = 0;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, value1) == 0) {
            x = atof(attribute->Value());
        }
        if (strcmp(name, value2) == 0) {
            y = atof(attribute->Value());
        }
        if (strcmp(name, value3) == 0) {
            z = atof(attribute->Value());
        }
        attribute = attribute->Next();
    }
    point->setX(x);
    point->setY(y);
    point->setZ(z);
}



void parseCamera2(TiXmlElement* camera, Camera* c) {

    Point_3D pos = Point_3D(), lookAt = Point_3D(), up = Point_3D(), persp = Point_3D();

    TiXmlElement* elem = camera->FirstChildElement();
    while (elem) {
        const char* name = elem->Value();
        printf("\n name: %s", name);
        if (strcmp(name, "position") == 0) {
            parseValues(elem, "X", "Y", "Z", &pos);
        }
        else if (strcmp(name, "lookAt") == 0) {
            parseValues(elem, "X", "Y", "Z", &lookAt);
        }
        else if (strcmp(name, "up") == 0) {
            parseValues(elem, "X", "Y", "Z",&up);
        }
        else if (strcmp(name, "projection") == 0) {
            parseValues(elem, "fov", "near", "far",&persp);
        }
        elem = elem->NextSiblingElement();
    }
    printf("\nposition -> %0.f, %0.f, %0.f", pos.getX(), pos.getY(), pos.getZ());
    printf("\nlookAt -> %2.f, %2.f, %2.f", lookAt.getX(), lookAt.getY(), lookAt.getZ());
    printf("\nup -> %2.f, %2.f, %2.f", up.getX(), up.getY(), up.getZ());
    printf("\npersp -> %2.f, %2.f, %2.f\n\n\n", persp.getX(), persp.getY(), persp.getZ());

    c->setPos(pos.getX(), pos.getY(), pos.getZ());
    c->setLookAt(lookAt.getX(), lookAt.getY(), lookAt.getZ());
    c->setPersp(persp.getX(), persp.getY(), persp.getZ());
    // what about UP ?
}



void parseCor(TiXmlElement *color, std::vector<float> *cores){

    const char* r = color->Attribute("R");
    const char* g = color->Attribute("G");
    const char* b = color->Attribute("B");

    cores->push_back(atof(r));
    cores->push_back(atof(g));
    cores->push_back(atof(b));
}



void parseFigura(TiXmlElement *models, Primitive *p) {

    TiXmlElement *model = models->FirstChildElement("model");

    
    string filename = string(model->Attribute("file"));
    string texture = string(model->Attribute("texture"));

    (*p).setFilename(filename);
    (*p).setTextureFilename(texture);
    (*p).readPrimitive(filename);
}



void parsePoint(TiXmlElement* element, Point_3D *p) {
    parseValues(element, "X", "Y", "Z", p);
}



void parseTranslate2(TiXmlElement* operation, Primitive *p) { 
    TiXmlAttribute* attribute = operation->FirstAttribute();
    vector<Point_3D*> translatePoints = vector<Point_3D*>();

    float time = 0;
    bool allign = false;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, "allign") == 0) {
            if (strcmp(name, "true") == 0 || strcmp(name, "True") == 0) {
                allign = true;
            }
        }
        else if (strcmp(name, "timeT") == 0) {
            time = atof(attribute->Value());
        }
        attribute = attribute->Next();
    }

    printf("#> Warning, translation with time 0.\n");

    TiXmlElement* child = operation->FirstChildElement();
    
    while (child) {
        Point_3D *point = new Point_3D();
        parsePoint(child, point);
        
        translatePoints.push_back(point);
        child = child->NextSiblingElement();
    }


    Transformation *t = new Translation(0.0f,0.0f,0.0f,time,translatePoints);
    (*p).addTransformation(t);
}



void parseTranslate(TiXmlElement *operation, Primitive *p){
    TiXmlAttribute *attribute = operation->FirstAttribute();

    float x = 0, y = 0, z = 0;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, "allign") == 0 || strcmp(name, "timeT") == 0) {  
            parseTranslate2(operation, p);
            return;
        }
        else {
            if (strcmp(name, "X") == 0) {
                x = atof(attribute->Value());
            }
            if (strcmp(name, "Y") == 0) {
                y = atof(attribute->Value());
            }
            if (strcmp(name, "Z") == 0) {
                z = atof(attribute->Value());
            }
        }
        attribute = attribute->Next();
    }

    Transformation *t = new Translation(x,y,z);
    (*p).addTransformation(t);
}



void parseRotation(TiXmlElement* operation, Primitive *p) {
    TiXmlAttribute* attribute = operation->FirstAttribute();
    float x = 0, y = 0, z = 0, time = 0, angle = 0;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, "axisX") == 0) {
            x = atof(attribute->Value());
        }
        if (strcmp(name, "axisY") == 0) {
            y = atof(attribute->Value());
        }
        if (strcmp(name, "axisZ") == 0) {
            z = atof(attribute->Value());
        }
        if (strcmp(name, "timeR") == 0) {
            time = atof(attribute->Value());
        }
        if (strcmp(name, "angle") == 0) {
            angle = atof(attribute->Value());
        }
        attribute = attribute->Next();
    }
    if (time == 0 || angle == 0) {
        printf("#> Warning, rotation with time 0.");
    }

    Transformation *r = new Rotation(angle, x, y, z , time);
    (*p).addTransformation(r);
}



void parseScale(TiXmlElement* operation, Primitive *p) {

    Point_3D scale = Point_3D();
    parseValues(operation, "scaleX", "scaleY", "scaleZ", &scale);
    Transformation *s = new Scale(scale.getX(), scale.getY(), scale.getZ());
    (*p).addTransformation(s);
}



Point_3D parseLightPoint(TiXmlElement* lights) { 
    Point_3D point = Point_3D();
    parseValues(lights, "posX", "posY", "posZ", &point);
    return point;
}



Point_3D parseLightDirec(TiXmlElement* lights) { 
    Point_3D point = Point_3D();
    parseValues(lights, "dirX", "dirY", "dirZ", &point);
    return point;
}



void parseLightSpot(TiXmlElement* lights) {
    TiXmlAttribute* attribute = lights->FirstAttribute();

    float posX = 0, posY = 0, posZ = 0,
        dirX = 0, dirY = 0, dirZ = 0,
        cutoff = 0;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, "posX") == 0) {
            posX = atof(attribute->Value());
        }
        if (strcmp(name, "posY") == 0) {
            posY = atof(attribute->Value());
        }
        if (strcmp(name, "posZ") == 0) {
            posZ = atof(attribute->Value());
        }
        if (strcmp(name, "dirX") == 0) {
            dirX = atof(attribute->Value());
        }
        if (strcmp(name, "dirY") == 0) {
            dirY = atof(attribute->Value());
        }
        if (strcmp(name, "dirZ") == 0) {
            dirZ = atof(attribute->Value());
        }
        if (strcmp(name, "cutoff") == 0) {
            cutoff = atof(attribute->Value());
        }
        attribute = attribute->Next();
    }
}



void parseLight(TiXmlElement* group) {
    TiXmlElement* lights = group->FirstChildElement();

    while (lights) {
        TiXmlAttribute* light_type = lights->FirstAttribute();

        if (strcmp(light_type->Value(), "point")) {
            Point_3D point_light = parseLightPoint(lights);
        }
        if (strcmp(light_type->Value(), "directional")) {
            //Point_3D dirLight = parseLightDirec(lights);
            parseLightDirec(lights);
        }
        if (strcmp(light_type->Value(), "spotlight")) {
            parseLightSpot(lights);
        }
    }
}

bool hasMoon(TiXmlElement* elem) {
    TiXmlElement* nextElem = elem->NextSiblingElement();
    if (nextElem) {
        return (strcmp(nextElem->Value(), "group") == 0);
    }
    return false;
}


TiXmlElement* parseGroup(TiXmlElement* group, bool planet, bool* planetWmoons, Primitive *p) {
    TiXmlElement* elem = group->FirstChildElement();
  
    while (elem) {
        const char* name = elem->Value();

        if (planet) {
            *planetWmoons = hasMoon(elem);
        }

        if (strcmp(name, "group") == 0) {
            return elem;
        }

        else if (strcmp(name, "models") == 0) {
            parseFigura(elem, p);
        }
        else if (strcmp(name, "color") == 0) {
            vector<float> rgb = vector<float>();
            parseCor(elem, &rgb);
            (*p).setColor(rgb);
        }
        else if (strcmp(name, "translate") == 0) {
            parseTranslate(elem, p);
        }
        else if (strcmp(name, "rotate") == 0) {
            parseRotation(elem, p);
        }
        else if (strcmp(name, "scale") == 0) {
            parseScale(elem, p);
        }

        if (*planetWmoons) {
            elem = elem->NextSiblingElement();
            return elem;
        }
        elem = elem->NextSiblingElement();

    }
    return group;
}


void parsePlanet(TiXmlElement* group, Primitive *p) {
    TiXmlElement* aux = group;
    bool planetWmoons = false;

    aux = parseGroup(aux,false,&planetWmoons, p);   //Parsing de orbita
    aux = parseGroup(aux,true,&planetWmoons, p);    //Parsing de planeta


    if (planetWmoons) {     //Se houver luas
        while (aux) {       //Enquanto ha luas

            Primitive moon = Primitive();
            TiXmlElement* moons = aux;
            planetWmoons = false;
            moons = parseGroup(moons, false, &planetWmoons, &moon);    //Parsing de orbita de luas
            moons = parseGroup(moons, true, &planetWmoons, &moon);     //Parsing de lua
            aux = aux->NextSiblingElement();                    //Next
            (*p).addAppendedPrimitive(moon);
        }
    }
}


/**
 * @brief Função principal de leitura de XML
 * 
 * @param filename 
 * @param c 
 */
vector<Primitive> Parser::lerXML(char *filename, Camera* c) {

    TiXmlDocument config;
    if (!config.LoadFile(filename)) {
        cout << "file doesnt exist" << endl;
        return vector<Primitive>();
    }

    TiXmlElement *scene = config.FirstChildElement();
    TiXmlElement *camera = scene->FirstChildElement();
    parseCamera2(camera,c);


    vector<Primitive> primitives = vector<Primitive>();


    TiXmlElement *group = camera->NextSiblingElement();
    TiXmlElement* planetGroup = group->FirstChildElement();

    while (planetGroup) {

        Primitive planet = Primitive();

        parsePlanet(planetGroup, &planet);
        primitives.push_back(planet);
        planetGroup = planetGroup->NextSiblingElement();
        planet.printInfo();
    }

    return primitives;
}