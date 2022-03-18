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
		vector<Point_3D> camera_specs;
	
	public:
		
		vector<vector<float>> getPontos() const;
		int getPontos(int i);
		vector<std::string> getFicheiros() const;
		vector<rgb> getCor() const;
		void setPontos(const vector<vector<float>> modelo);
    	void setFicheiros(const vector<const char *> ficheiros);
    	void setCor(const vector<rgb> cor);

		vector<Point_3D> getCameraSettings();

    	void build(char* filename);
};

#endif