#include "../../headers/xmlparser.h"
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
    (* point).setPointTo(x, y, z);
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
    printf("\npersp -> %2.f, %2.f, %2.f", persp.getX(), persp.getY(), persp.getZ());

    c->setPos(pos.getX(), pos.getY(), pos.getZ());
    c->setLookAt(lookAt.getX(), lookAt.getY(), lookAt.getZ());
    c->setPersp(persp.getX(), persp.getY(), persp.getZ());
}



void parseCor(TiXmlElement *color, std::vector<rgb> *cores){
    rgb cor = rgb ();

    const char* r = color->Attribute("R");
    const char* g = color->Attribute("G");
    const char* b = color->Attribute("B");

    cor.setR(atof(r));
    cor.setG(atof(g));
    cor.setB(atof(b));

    cores->push_back(cor);
}

void parseFigura(TiXmlElement *models, std::vector<const char *> *files) {
    TiXmlElement *model = models->FirstChildElement("model");
    const char* ficheiro = "";
    ficheiro = model->Attribute("file");

    const char* texture = "";
    texture = model->Attribute("texture");

    files->push_back(ficheiro);
    printf(ficheiro);
}

Point_3D parsePoint(TiXmlElement* element) {
    Point_3D point = Point_3D();
    parseValues(element, "X", "Y", "Z", &point);
    return point;
}


void parseTranslate2(TiXmlElement* operation) { 
    TiXmlAttribute* attribute = operation->FirstAttribute();
    vector<Point_3D> translatePoints;

    float time = 0;
    bool allign = false;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, "allign") == 0) {
            if (strcmp(name, "true") == 0 || strcmp(name, "True") == 0) {
                allign = true;
            }
            else {
                allign = false;
            }
        }
        if (strcmp(name, "time") == 0) {
            time = atof(attribute->Value());
        }
        attribute = attribute->Next();
    }

    printf("#> Warning, translation with time 0.\n");

    TiXmlElement* child = operation->FirstChildElement();
    while (child) {
        translatePoints.push_back(parsePoint(child));
        child = child->NextSiblingElement();
    }
    

}

void parseTranslate(TiXmlElement *operation){
    TiXmlAttribute *attribute = operation->FirstAttribute();

    float x = 0, y = 0, z = 0;

    while (attribute) {
        const char* name = attribute->Name();
        if (strcmp(name, "allign") == 0 || strcmp(name, "time") == 0) {  
            parseTranslate2(operation);
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
  //  printf("\ntranslate concluido x=%0.f y=%0.f z=%0.f", x, y, z);

}

void parseRotation(TiXmlElement* operation) {
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
        if (strcmp(name, "time") == 0) {
            time = atof(attribute->Value());
        }
        if (strcmp(name, "angle") == 0) {
            angle = atof(attribute->Value());
        }
        attribute = attribute->Next();
    }
    if (time == 0 || angle == 0) {
        printf("#> Warning, rotation with time 0.\n");
    }
  //  printf("\nrotate concluido x=%0.f y=%0.f z=%0.f angle=%0.f time=%0.f", x, y, z, angle, time);
}


void parseScale(TiXmlElement* operation) {

    Point_3D scale = Point_3D();
    parseValues(operation, "scaleX", "scaleY", "scaleZ",&scale);

  
    //printf("\nscale concluido x=%0.f y=%0.f z=%0.f", scale.getX(), scale.getY(), scale.getZ());
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

void parseGroup(TiXmlElement* group) {
    TiXmlElement* elem = group->FirstChildElement();

    while (elem) {

        const char* name = elem->Value();

        if (strcmp(name, "group") == 0) {
            parseGroup(elem);

        }
        else if (strcmp(name, "models") == 0) {
          //  parseFigura(elem, files);

        }
        else if (strcmp(name, "color") == 0) {
            //parseCor(elem, cores);
        }
        else if (strcmp(name, "translate") == 0) {
            parseTranslate(elem);
        }
        else if (strcmp(name, "rotate") == 0) {
            parseRotation(elem);
        }
        else if (strcmp(name, "scale") == 0) {
            parseScale(elem);
        }
        elem = elem->NextSiblingElement();
    }
}



void Parser::lerXML(char *filename, Camera* c) {

    TiXmlDocument config;
    if (!config.LoadFile(filename)) {
        cout << "file doesnt exist" << endl;
        return;
    }

    TiXmlElement *scene = config.FirstChildElement();
    TiXmlElement *camera = scene->FirstChildElement();
    cout << "ola" << endl;
    parseCamera2(camera,c);

    TiXmlElement *group = camera->NextSiblingElement();

    while (group) { 
        parseGroup(group);
        group = group->NextSiblingElement();
    }
    
}