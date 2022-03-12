#ifndef ENGINE_XMLPARSER_H
#define ENGINE_XMLPARSER_H

#include <string>
#include <vector>
#include "tinyxml.h"
#include "rgb.h"

using namespace std;

class Parser {

	public:
    	vector<char *> lerXML(char *filename, std::vector<const char *> *ficheiros, vector<rgb> *cores);
};

#endif