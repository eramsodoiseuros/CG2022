#include "scene.h"

void Scene::setPontos(const vector<vector<float>> m) {
    Scene::modelo = m;
}

void Scene::setFicheiros(const vector<const char *> f) {
    Scene::ficheiros = f;
}

vector<std::string> Scene::getFicheiros() const {
    vector<string> files;

    for(const char* c : ficheiros){
        string aux = std::string(c);
        files.push_back(aux);
    }
    return files;
}

vector<vector<float>> Scene::getPontos() const {
    return vector<vector<float>>();
}

int Scene::getPontos(int i){
    return modelo[i].size()/3;
}

vector<rgb> Scene::getCor() const {
    return cor;
}

vector<Point_3D> Scene::getCameraSettings(){

    return vector<Point_3D>(camera_specs);
}


void Scene::setCor(const vector<rgb> cor) {
    Scene::cor = cor;
}

void Scene::build(char *filename) {
    this->modelo.clear();
    this->ficheiros.clear();
    this->cor.clear();
    Parser p;

    p.lerXML(filename, &(this->ficheiros), &(this->cor), &(this->camera_specs));

    printf("\nout of lerXML de %s\n", filename);
}