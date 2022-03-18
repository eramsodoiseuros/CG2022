#include "xmlparser.h"
#include <iostream>

void parseCamera(TiXmlElement* cam, vector<Point_3D> *cam_specs) {
    
    TiXmlElement* elem = cam->FirstChildElement();

    while (elem) {

        const char* name = elem->Value();

        if (strcmp(name, "position") == 0) {
            const char* x = elem->Attribute("x");
            const char* y = elem->Attribute("y");
            const char* z = elem->Attribute("z");

            cam_specs->push_back(Point_3D(atof(x), atof(y), atof(z)));
        }
        else if (strcmp(name, "lookAt") == 0) {
            const char* x = elem->Attribute("x");
            const char* y = elem->Attribute("y");
            const char* z = elem->Attribute("z");

            cam_specs->push_back(Point_3D(atof(x), atof(y), atof(z)));
        }
        else if (strcmp(name, "up") == 0) {
            const char* x = elem->Attribute("x");
            const char* y = elem->Attribute("y");
            const char* z = elem->Attribute("z");

            cam_specs->push_back(Point_3D(atof(x), atof(y), atof(z)));
        }
        else if (strcmp(name, "projection") == 0) {
            const char* x = elem->Attribute("fov");
            const char* y = elem->Attribute("near");
            const char* z = elem->Attribute("far");

            cam_specs->push_back(Point_3D(atof(x), atof(y), atof(z)));

        }
        
        elem = elem->NextSiblingElement();
    }

    printf("\n\t a sair de camera");
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
    const char* ficheiro = model->Attribute("file");

    files->push_back(ficheiro);
    printf(ficheiro);
}

void parseGroup(TiXmlElement *group, std::vector<const char *> *files,
               std::vector<rgb> *cores) {
    TiXmlElement *elem = group->FirstChildElement();

    while (elem) {

        const char *name = elem->Value();

        printf("\nencontrei um >%s<\n", name);
        if (strcmp(name, "group") == 0) {
            parseGroup(elem, files, cores);

        } else if (strcmp(name, "models") == 0) {
            parseFigura(elem, files);

        } else if (strcmp(name, "color") == 0) {
            parseCor(elem, cores);

        } elem = elem->NextSiblingElement();
    }
}

void Parser::lerXML(char *filename, std::vector<const char *> *ficheiros, std::vector<rgb> *cores, vector<Point_3D> *cam) {

    TiXmlDocument config;
    if (!config.LoadFile(filename)) {
        cout << "file doesnt exist" << endl;
        return;
    }

    TiXmlElement *scene = config.FirstChildElement();
    TiXmlElement *camera = scene->FirstChildElement();

    parseCamera(camera,cam);

    TiXmlElement *group = camera->NextSiblingElement();

    while (group) {
        parseGroup(group, ficheiros, cores);
        group = group->NextSiblingElement();
    }
    
}