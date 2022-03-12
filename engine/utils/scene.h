#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H
#include <vector>
#include "xmlparser.h"
#include "rgb.h"

using namespace std;

class Scene {

	private:
		vector<vector<float>> modelo;
		vector<const char *> ficheiros;
		vector<rgb> cor;
	public:
		vector<vector<float>> getPontos() const;
		int getPontos(int i);
		vector<const char *> getFicheiros() const;
		vector<rgb> getCor() const;
		void setPontos(const vector<vector<float>> modelo);
    	void setFicheiros(const vector<const char *> ficheiros);
    	void setCor(const vector<rgb> cor);

    	void build(char* filename);
};

#endif