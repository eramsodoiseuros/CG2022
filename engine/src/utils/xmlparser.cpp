#include "../../headers/xmlparser.h"
#include "../../headers/rotation.h"
#include "../../headers/translation.h"
#include "../../headers/scale.h"
#include "../../headers/color.h"
#include "../../headers/lights.h"
#include <sstream>
#include <iostream>


/**
 * @brief Parses a tag with 3 attributes with names equal to the strings value
 *
 * @param elem
 * @param value1
 * @param value2
 * @param value3
 */
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


/**
 * @brief Parses the camera's values
 *
 * @param camera
 * @param c
 */
void parseCamera2(TiXmlElement* camera, Camera* c) {

    Point_3D pos = Point_3D(), lookAt = Point_3D(), up = Point_3D(), persp = Point_3D();

    TiXmlElement* elem = camera->FirstChildElement();
    while (elem) {
        const char* name = elem->Value();

        if (strcmp(name, "position") == 0) {
            parseValues(elem, "X", "Y", "Z", &pos);
        }
        else if (strcmp(name, "lookAt") == 0) {
            parseValues(elem, "X", "Y", "Z", &lookAt);
        }
        else if (strcmp(name, "up") == 0) {
            parseValues(elem, "X", "Y", "Z", &up);
        }
        else if (strcmp(name, "projection") == 0) {
            parseValues(elem, "fov", "near", "far", &persp);
        }
        elem = elem->NextSiblingElement();
    }
    //Debugg
    //printf("\nposition -> %0.f, %0.f, %0.f", pos.getX(), pos.getY(), pos.getZ());
    //printf("\nlookAt -> %2.f, %2.f, %2.f", lookAt.getX(), lookAt.getY(), lookAt.getZ());
    //printf("\nup -> %2.f, %2.f, %2.f", up.getX(), up.getY(), up.getZ());
    //printf("\npersp -> %2.f, %2.f, %2.f\n\n\n", persp.getX(), persp.getY(), persp.getZ());

    //Setting the values
    c->setPos(pos.getX(), pos.getY(), pos.getZ());
    c->setLookAt(lookAt.getX(), lookAt.getY(), lookAt.getZ());
    c->setPersp(persp.getX(), persp.getY(), persp.getZ());
    float radius = sqrt(powf(pos.getX(), 2) + powf(pos.getY(), 2) + powf(pos.getZ(), 2));
    c->setR(radius);
    float vertical = asin(pos.getY() / radius);
    float horizontal = acos(pos.getZ() / (radius * cos(vertical)));
    c->setHorizontalAngle(horizontal);
    c->setVerticalAngle(vertical);
}


/**
 * @brief Parses a color
 *
 * @param color
 * @param cores
 */
void parseCor(TiXmlElement *color, std::vector<float> *cores) {

    const char* r = color->Attribute("R");
    const char* g = color->Attribute("G");
    const char* b = color->Attribute("B");

    cores->push_back(atof(r));
    cores->push_back(atof(g));
    cores->push_back(atof(b));
}

void parseColor(TiXmlElement *color, Primitive *p) {

    TiXmlElement* child = color->FirstChildElement();
    Color c = (*p).getColorComponents();

    while (child) {

        const char* name = child->Value();

        if (strcmp(name, "diffuse") == 0) {
            vector<float> rgb = vector<float>();
            parseCor(child, &rgb);
            c.setDiffuse(rgb);
        }
        else if (strcmp(name, "ambient") == 0) {
            vector<float> rgb = vector<float>();
            parseCor(child, &rgb);
            c.setAmbient(rgb);
        }
        else if (strcmp(name, "specular") == 0) {
            vector<float> rgb = vector<float>();
            parseCor(child, &rgb);
            c.setSpecular(rgb);
        }
        else if (strcmp(name, "emissive") == 0) {
            vector<float> rgb = vector<float>();
            parseCor(child, &rgb);
            c.setEmissive(rgb);
        }
        else if (strcmp(name, "shininess") == 0) {
            TiXmlAttribute* atrib = child->FirstAttribute();
            if (strcmp(atrib->Name(), "value") == 0) {
                c.setShininess(atof(atrib->Value()));
            }
        }
        p->setColorComponents(c);
        child = child->NextSiblingElement();
    }
}
/**
 * @brief Parses the tag model, finding the file and texture strings
 *
 * @param models
 * @param p
 */
void parseFigura(TiXmlElement *models, Primitive *p) {

    TiXmlElement* model = models->FirstChildElement();
    string filename = string(model->Attribute("file"));
    string texture = string(model->Attribute("texture"));
    TiXmlElement* colors = models->NextSiblingElement();
    
    if (model->NextSiblingElement()) {
        TiXmlElement* color = model->NextSiblingElement();
        parseColor(color, p);
    }

    

    (*p).setFilename(filename);
    (*p).setTextureFilename(texture);
    (*p).readPrimitive(filename);




    //printf("Found model\n");
    //printf("file = %s, textura = %s, luz = %s, cor = %s %s %s\n\n", filename, texture, lightType, r, g, b);

    //cout << "file = " << filename << ", textura = " << texture << ", luz = " << lightType << ", cor = " << r << "," << g << "," << b << endl;
}


/**
 * @brief Parses a point (X,Y,Z)
 *
 * @param element
 * @param p
 */
void parsePoint(TiXmlElement* element, Point_3D *p) {
    parseValues(element, "X", "Y", "Z", p);
}


/**
 * @brief Parses a translation with the attributes time and allign and a subgroup with a list of points
 *
 * @param operation
 * @param p

 */
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
    if (time == 0) {
        printf("\n#> Warning, translation with time 0.");
    }

    TiXmlElement* child = operation->FirstChildElement();

    while (child) {
        Point_3D* point = new Point_3D();
        parsePoint(child, point);

        translatePoints.push_back(point);
        child = child->NextSiblingElement();
    }

    if (translatePoints.size() < 4) {
        cout << "\n#Error: Number of points lower than 4. \n" << endl;
        exit(EXIT_FAILURE);
    }
    Transformation* t = new Translation(0.0f, 0.0f, 0.0f, time, align, translatePoints);
    (*p).addTransformation(t);
}


/**
 * @brief Find if its an instant translation (tag with atributes X,Y and Z) and parses it or a time-based translation (tag with time and allign),
 * sending it to the function parseTranslate2
 *
 * @param operation
 * @param p

 */
void parseTranslate(TiXmlElement* operation, Primitive *p) {
    TiXmlAttribute* attribute = operation->FirstAttribute();

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

    Transformation* t = new Translation(x, y, z);
    (*p).addTransformation(t);
}


/**
 * @brief Parses a rotation, sending a warning if both time and angle are 0
 *
 * @param operation
 * @param p
 */
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
    if (time == 0 && angle == 0) {
        printf("\n#> Warning, rotation with time 0.");
    }

    Transformation* r = new Rotation(angle, x, y, z, time);
    (*p).addTransformation(r);
}


/**
 * @brief Parses a scale
 *
 * @param operation
 * @param p
 */
void parseScale(TiXmlElement* operation, Primitive *p) {

    Point_3D scale = Point_3D();
    parseValues(operation, "scaleX", "scaleY", "scaleZ", &scale);
    Transformation* s = new Scale(scale.getX(), scale.getY(), scale.getZ());
    (*p).addTransformation(s);
}


/**
 * @brief Parses a light of type "point"
 *
 * @param lights
 * @return Point_3D
 */
void parseLightPoint(TiXmlElement* elem, Lights *l) {
    Point_3D point = Point_3D();
    parseValues(elem, "posX", "posY", "posZ", &point);
    PointLight pl = PointLight(point.getX(), point.getY(), point.getZ());
    (*l).addPointLight(pl);
}


/**
 * @brief Parses a light of type "directional"
 *
 * @param lights
 * @return Point_3D
 */
void parseLightDirec(TiXmlElement* lights, Lights *l) {
    Point_3D point = Point_3D();
    parseValues(lights, "dirX", "dirY", "dirZ", &point);
    DirectionalLight dl = DirectionalLight(point.getX(), point.getY(), point.getZ());
    (*l).addDirectionalLight(dl);
}


/**
 * @brief Parses a light of type "spotlight" (for now its only reading but not saving anywhere)
 *
 * @param lights
 */
void parseLightSpot(TiXmlElement* lights, Lights *l) {
    TiXmlAttribute* attribute = lights->FirstAttribute();

    float posX = 0, posY = 0, posZ = 0,
        dirX = 0, dirY = 0, dirZ = 0,
        cutoff = 0;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, "posX") == 0) {
            posX = atof(attribute->Value());
        }
        else if (strcmp(name, "posY") == 0) {
            posY = atof(attribute->Value());
        }
        else if (strcmp(name, "posZ") == 0) {
            posZ = atof(attribute->Value());
        }
        else if (strcmp(name, "dirX") == 0) {
            dirX = atof(attribute->Value());
        }
        else if (strcmp(name, "dirY") == 0) {
            dirY = atof(attribute->Value());
        }
        else if (strcmp(name, "dirZ") == 0) {
            dirZ = atof(attribute->Value());
        }
        else if (strcmp(name, "cutoff") == 0) {
            cutoff = atof(attribute->Value());
        }
        attribute = attribute->Next();
    }

    SpotLight sl = SpotLight(posX, posY, posZ, dirX, dirY, dirZ, cutoff);
    (*l).addSpotLight(sl);
   
}


/**
 * @brief Parses the light types (only parsing and saving in a Point_3D, not currently being used)
 *
 * @param group
 */
void parseLight(TiXmlElement* group,Lights *l) {
    TiXmlElement* lights = group->FirstChildElement();
    while (lights) {
        TiXmlAttribute* light_type = lights->FirstAttribute();

        if (strcmp(light_type->Value(), "point") == 0) {
            parseLightPoint(lights,l);
        }
        else if (strcmp(light_type->Value(), "directional") == 0) {
            parseLightDirec(lights,l);
        }
        else if (strcmp(light_type->Value(), "spotlight") == 0) {
            parseLightSpot(lights,l);
        }
        lights = lights->NextSiblingElement();
    }
}

/**
 * @brief Finds if a planet has moons (if it has, one of the siblings has to be called group)
 *
 * @param elem
 * @return
 */

bool hasMoon(TiXmlElement* elem) {
    TiXmlElement* nextElem = elem->NextSiblingElement();
    if (nextElem) {
        return (strcmp(nextElem->Value(), "group") == 0);
    }
    return false;
}

/**
 * @brief parses a group, reading their child's name and choosing the correct parsing option
 *
 * @param group
 * @param planet        true if it's parsing a planet
 * @param planetWmoons  true if the planet being parsed has moons
 * @param p
 * @return
 */
TiXmlElement* parseGroup(TiXmlElement* group, bool planet, bool* planetWmoons, Primitive* p) {
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
        else if (strcmp(name, "translate") == 0) {
            parseTranslate(elem, p);
        }
        else if (strcmp(name, "rotate") == 0) {
            parseRotation(elem, p);
        }
        else if (strcmp(name, "scale") == 0) {
            parseScale(elem, p);
        }
        else if (strcmp(name, "lights") == 0) {
            //printf("ola");
            //parseLight(elem, p);
        }

        if (*planetWmoons) {
            elem = elem->NextSiblingElement();
            return elem;
        }
        elem = elem->NextSiblingElement();

    }
    return group;
}

/**
 * @brief Parses a planet, including orbit, moons and moon's orbits
 *
 * @param group
 * @param p
 * @return
 */
void parsePlanet(TiXmlElement* group, Primitive* p) {
    TiXmlElement* aux = group;
    bool planetWmoons = false;

    aux = parseGroup(aux, false, &planetWmoons, p);   //Parsing de orbita
    aux = parseGroup(aux, true, &planetWmoons, p);    //Parsing de planeta


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
vector<Primitive> Parser::lerXML(char* filename, Camera* c, Lights *lights) {

    TiXmlDocument config;
    if (!config.LoadFile(filename)) {
        cout << "file doesnt exist" << endl;
        return vector<Primitive>();
    }

    TiXmlElement* scene = config.FirstChildElement();
    TiXmlElement* camera = scene->FirstChildElement();
    parseCamera2(camera, c);

    TiXmlElement* group;

    if (strcmp(camera->NextSiblingElement()->Value(), "lights") == 0) {

        TiXmlElement* lightsElem = camera->NextSiblingElement();
        parseLight(lightsElem,lights);
        group = lightsElem->NextSiblingElement();
    }
    else {
        group = camera->NextSiblingElement();
    }

    vector<Primitive> primitives = vector<Primitive>();

    
    TiXmlElement* planetGroup = group->FirstChildElement();

    while (planetGroup) {

        Primitive planet = Primitive();

        parsePlanet(planetGroup, &planet);
        primitives.push_back(planet);
        planetGroup = planetGroup->NextSiblingElement();
    }

    return primitives;
}