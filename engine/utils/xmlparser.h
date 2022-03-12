#ifndef ENGINE_XMLPARSER_H
#define ENGINE_XMLPARSER_H

#include <string>
#include <vector>
#include "tinyxml.h"
#include "rgb.h"
#include "../../utils/point_3d.h"

using namespace std;

class Parser {
	private:
		Point_3D position;
		Point_3D lookAt;
		Point_3D up;
		Point_3D proj;
		Point_3D prespective;

	public:
    	void lerXML(char *filename, std::vector<const char *> *ficheiros, vector<rgb> *cores, vector<Point_3D> *cam);
};

#endif