#include "xmlparser.h"

char* parseTranslacao(TiXmlElement *translate) {
    printf("-> entrei para dar parse a uma translacao\n");
    const char* x = translate -> Attribute("X");
    const char* y = translate -> Attribute("Y");
    const char* z = translate -> Attribute("Z");
    const char* tempo = translate -> Attribute("tempo");

    printf("estou a ler translacao %s %s %s", x,y,z);

    char *buf =(char*) malloc(sizeof(char)*25);
    sprintf(buf, "T %s %s %s %s", x,y,z,tempo);

    return buf;
}

char* parseRotacao(TiXmlElement *rotate) {
    const char* x = rotate->Attribute("X");
    const char* y = rotate->Attribute("Y");
    const char* z = rotate->Attribute("Z");
    const char* tempo = rotate->Attribute("tempo");
    const char* angle = rotate->Attribute("angle");

    char *buf =(char*) malloc(sizeof(char)*25);
    sprintf(buf, "R %s %s %s %s %s", x,y,z,tempo,angle);

    return buf;
}

char* parseEscala(TiXmlElement *scale){
    const char* x = scale->Attribute("X");
    const char* y = scale->Attribute("Y");
    const char* z = scale->Attribute("Z");

    printf("estou a ler escala %s %s %s", x,y,z);

    char *buf =(char*) malloc(sizeof(char)*25);
    sprintf(buf, "S %s %s %s", x,y,z);

    return buf;
}

char* parseCor(TiXmlElement *color, std::vector<rgb> *cores){
    rgb cor = rgb ();

    const char* r = color->Attribute("R");
    const char* g = color->Attribute("G");
    const char* b = color->Attribute("B");

    cor.setR(atof(r));
    cor.setG(atof(g));
    cor.setB(atof(b));

    cores->push_back(cor);

    printf("estou a ler cor %s %s %s", r,g,b);

    char *buf =(char*) malloc(sizeof(char)*25);
    sprintf(buf, "COR %d", cores->size());
    return buf;
}

char* parseFigura(TiXmlElement *models, std::vector<const char *> *files) {
    TiXmlElement *model = models->FirstChildElement("model");
    const char* ficheiro = model->Attribute("file");

    files->push_back(ficheiro);

    char *buf =(char*) malloc(sizeof(char)*10);
    sprintf(buf, "FIG %d", files->size());

    return buf;
}

void parseGroup(TiXmlElement *group, std::vector<const char *> *files,
               std::vector<rgb> *cores,
               std::vector<char*> *operacoes) {
    TiXmlElement *elem = group->FirstChildElement();

    operacoes->push_back(_strdup("PUSH"));
    while (elem) {

        const char *name = elem->Value();

        printf("\nencontrei um >%s<\n", name);
        if (strcmp(name, "group") == 0) {
            parseGroup(elem, files, cores, operacoes);

        } else if (strcmp(name, "translate") == 0) {
            operacoes->push_back(parseTranslacao(elem));

        } else if (strcmp(name, "rotate") == 0) {
            operacoes->push_back(parseRotacao(elem));

        } else if (strcmp(name, "scale") == 0) {
            operacoes->push_back(parseEscala(elem));

        } else if (strcmp(name, "models") == 0) {
            operacoes->push_back(parseFigura(elem, files));

        } else if (strcmp(name, "color") == 0) {
            operacoes->push_back(parseCor(elem, cores));

        } elem = elem->NextSiblingElement();
    }

    operacoes->push_back(_strdup("POP"));
}

std::vector<char *> Parser::lerXML(char *filename, std::vector<const char *> *ficheiros, std::vector<rgb> *cores) {
    std::vector<char *> operacoes;

    TiXmlDocument config;
    config.LoadFile(filename);

    printf("\nim inside lerXML de %s\n", filename);

    TiXmlElement *scene = config.FirstChildElement("scene");
    TiXmlElement *group = scene->FirstChildElement("group");

    while (group) {
        parseGroup(group, ficheiros, cores, &operacoes);
        group = group->NextSiblingElement("group");
    }

    printf("\nfinished com %d cores e %d files\n", cores->size(), ficheiros->size());

    for(int i = 0; i < operacoes.size(); i++){
        printf("\n%d|%s",i,operacoes.at(i));
    }

    return operacoes;
}