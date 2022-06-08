#ifndef ENGINE_XMLPARSER_H
#define ENGINE_XMLPARSER_H

#include "tinyxml.h"
#include <string>
#include <vector>
#include "../../utils/point_3d.h"
#include "camera.h"
#include "primitive.h"
#include "lights.h"

using namespace std;

class Parser {
	private:
		Point_3D position;
		Point_3D lookAt;
		Point_3D up;
		Point_3D proj;
		Point_3D prespective;

	public:
    	vector<Primitive> lerXML(char *filename, Camera* c, Lights *lights);
};

#endif