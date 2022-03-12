#include "scene.h"

void Scene::setPontos(const vector<vector<float>> m) {
    Scene::modelo = m;
}

void Scene::setFicheiros(const vector<const char *> f) {
    Scene::ficheiros = f;
}

vector<const char *> Scene::getFicheiros() const {
    return vector<const char *>();
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

void Scene::setCor(const vector<rgb> cor) {
    Scene::cor = cor;
}

void Scene::build(char *filename) {
    this->modelo.clear();
    this->ficheiros.clear();
    this->cor.clear();
    Parser p;

    p.lerXML(filename, &(this->ficheiros), &(this->cor));

    printf("\nout of lerXML de %s\n", filename);
}