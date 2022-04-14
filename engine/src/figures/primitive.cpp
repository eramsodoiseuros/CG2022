#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../../headers/primitive.h"
#include <GL/glew.h>


/**
 * @brief devolve o nome do ficheiro onde se encontra a primitiva
 * 
 * @return string 
 */
string Primitive::getFilename(){

    return string(filename);
}

string Primitive::getPrimitiveName(){

    return string(primitiveName);
}

vector<float> Primitive::getColor(){

	vector<float> color = vector<float>();
	color.push_back(r);color.push_back(g);color.push_back(b);
	return color;
}

unsigned int* Primitive::getVBO(){
	return vBuffer;
}
int Primitive::getNPoints(){
	return nPoints;
}
int Primitive::getNIndexes() {
	return nIndexes;
}

/**
 * @brief recolhe, por um ficheiro .3d, as informações relativas à primitiva
 * 
 * @param primitive3D 
 */
void Primitive::getFigure(string primitive3D){

	string inputFile = "../3D/" + primitive3D;
	string l = "";
	vector<string> parser = vector<string>();
	ifstream dFile(inputFile);
	
	if(!dFile.is_open()){

		cerr << "Could not open the specified file:" << inputFile << endl;
		return ;
	}

	bool fstLine = true;
	int primitiveType = 0;
	int arraySize = 0;
	float* points = NULL;

	int index = 0;
	glEnableClientState(GL_VERTEX_ARRAY);

	while(getline(dFile,l)){

		stringstream ss(l);
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			parser.push_back(subs);
		}

		if(fstLine){
			primitiveType = stoi(parser.at(0));
			int np = stoi(parser.at(1));
			nPoints = np;
			int ni = stoi(parser.at(2));
			nIndexes = ni;
			fstLine = false;


			if (primitiveType == 0)
				arraySize = nPoints * 3;
			else
				arraySize = nIndexes * 3;
			points = (float*) malloc(arraySize * sizeof(float));

		}
		else {
			float x,y,z;
			x = stof(parser.at(0));
			y = stof(parser.at(1));
			z = stof(parser.at(2));

			points[index++] = x;
			points[index++] = y;
			points[index++] = z;
		}
		parser.clear();
	}
	
	dFile.close();

	// VBO
	glGenBuffers(1, &vBuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, arraySize * sizeof(float), points, GL_STATIC_DRAW);
	glDisableClientState(GL_VERTEX_ARRAY);
	free(points);

	switch (primitiveType)
    {
	case 0:
		primitiveName = string("patch");
		break;
    case 1:
        primitiveName = string("plane");
        break;
    case 2:
        primitiveName = string("box");
        break;
    case 3:
        primitiveName = string("cone");
        break;
    case 4:
        primitiveName = string("sphere");
		break;
    
    default:
        primitiveName = string("none");
        break;
    }

}

void Primitive::setFilename(string s){

	filename = string(s);
}

void Primitive::setPrimitiveName(string s){

	primitiveName = string(s);
}

/**
 * @brief Define uma cor para a primitiva
 * 
 * @param rgbColor 
 */
void Primitive::setColor(vector<float> rgbColor){

	r = rgbColor.at(0);
	g = rgbColor.at(1);
	b = rgbColor.at(2);
}


/**
 * @brief Devolve a cópia de uma primitiva
 * 
 * @return Primitive 
 */
Primitive Primitive::clone(){

	Primitive p = Primitive();
	p.setFilename(filename);
	p.setPrimitiveName(primitiveName);
	p.vBuffer[0] = vBuffer[0];
	p.vBuffer[1] = vBuffer[1];

	p.nPoints = nPoints;
	p.nIndexes = nIndexes;
	p.r = r; p.g = g; p.b = b;

	return p;
}

/**
 * @brief Desenha uma primitiva com VBO
 * 
 */
void Primitive::draw(){

	int totalPoints = 0;
	if (primitiveName.compare("patch") == 0)
		totalPoints = nPoints * 3;
	else
		totalPoints = nIndexes * 3;
		
	glEnableClientState(GL_VERTEX_ARRAY);
	// Para adicionar cores a cada triângulo, tem de se adicionar um VBO e redefinir o readFile
	glColor3f(r,g,b);

	// Dar bind ao identificador associado da primitiva
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	// Definir o modo de leitura do VBO (3 vértices por triangulo, utilizando floats)
	glVertexPointer(3, GL_FLOAT, 0, 0);
	// Draw da primitiva, a começar no índice 0, nPoints
	glDrawArrays(GL_TRIANGLES, 0, totalPoints);
	glDisableClientState(GL_VERTEX_ARRAY);
}