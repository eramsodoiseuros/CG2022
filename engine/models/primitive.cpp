#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "primitive.h"
#include <GL/glew.h>


/**
 * @brief devolve o nome do ficheiro onde se encontra a primitiva
 * 
 * @return string 
 */
string Primitive::getFilename(){

    return string(filename);
}

/**
 * @brief devolve o nome da primitiva
 * 
 * @return string 
 */
string Primitive::getPrimitiveName(){

    return string(primitiveName);
}

/**
 * @brief devolve os pontos utilizados para definir a primitiva
 * 
 * @return vector<Point_3D> 
 */
vector<Point_3D> Primitive::getPoints() {

    return points;
}

vector<float> Primitive::getColor(){

	vector<float> color = vector<float>();
	color.push_back(r);color.push_back(g);color.push_back(b);
	return color;
}

/**
 * @brief recolhe, por um ficheiro .3d, as informações relativas à primitiva
 * 
 * @param primitive3D 
 */
void Primitive::getFigure(string primitive3D){

	string inputFile = "../3D/" + primitive3D;
	string l = "";
	vector<string> parser;
	ifstream dFile(inputFile);
	
	if(!dFile.is_open()){

		cerr << "Could not open the specified file:" << inputFile << endl;
		return ;
	}

	bool fstLine = true;
    int primitiveType = 0;
	int nPoints = 0;
	int nIndexes = 0;

	while(getline(dFile,l)){

		stringstream ss(l);
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			parser.push_back(subs);
		}

		if(fstLine){
            primitiveType = stoi(parser.at(0));
			nPoints = stoi(parser.at(1));
			nIndexes = stoi(parser.at(2));
			fstLine = false;
		}
		else {

			float x = stof(parser.at(0));
			float y = stof(parser.at(1));
			float z = stof(parser.at(2));
			points.push_back(Point_3D(x,y,z));	
		}
		parser.clear();
	}
	dFile.close();


    switch (primitiveType)
    {
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

/**
 * @brief define o nome do ficheiro 3d da primitiva
 * 
 * @param s 
 */
void Primitive::setFilename(string s){

	filename = string(s);
}

/**
 * @brief define o nome da primitiva
 * 
 * @param s 
 */
void Primitive::setPrimitiveName(string s){

	primitiveName = string(s);
}


/**
 * @brief define o conjunto dos pontos que definem a primitiva
 * 
 * @param ps 
 */
void Primitive::setPoints(vector<Point_3D> ps){

	points = vector<Point_3D>(ps);
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
	p.setPoints(points);
	return p;
}


/**
 * @brief Desenha um plano
 * 
 * Se a primitiva não for efetivamente um plano, concluirá um erro
 * 
 */
void Primitive::drawPlane(){

	if (primitiveName.compare("sphere")){

		cout << "\n#> error: not the right drawing function\n";
		return;
	}

	glBegin(GL_TRIANGLES);

		//glColor3f(cor.getR(), cor.getG(), cor.getB());
		glColor3f(r, g, b);

		for(Point_3D p : points){
			glVertex3f(p.getX(), p.getY(), p.getZ());
		}

	glEnd();
}

/**
 * @brief Desenha uma box
 * 
 * Se a primitiva não for efetivamente uma box, concluirá um erro
 * 
 */
void Primitive::drawBox(){

	if (primitiveName.compare("box")){

		cout << "\n#> error: not the right drawing function\n";
		return;
	}

	glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);

		for(Point_3D p : points){
			glVertex3f(p.getX(), p.getY(), p.getZ());
		}

	glEnd();
}

/**
 * @brief Desenha um cone
 * 
 * Se a primitiva não for efetivamente um cone, concluirá um erro
 * 
 */
void Primitive::drawCone(){

	if (primitiveName.compare("cone")){

		cout << "\n#> error: not the right drawing function\n";
		return;
	}

	glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);

		for(Point_3D p : points){
			glVertex3f(p.getX(), p.getY(), p.getZ());
		}

	glEnd();
}

/**
 * @brief Desenha uma sphere
 * 
 * Se a primitiva não for efetivamente uma sphere, concluirá um erro
 * 
 */
void Primitive::drawSphere(){

	if (primitiveName.compare("sphere")){

		cout << "\n#> error: not the right drawing function\n";
		return;
	}

	
	glBegin(GL_TRIANGLES);

		glColor3f(r, g, b);

		for(Point_3D p : points){
			glVertex3f(p.getX(), p.getY(), p.getZ());
		}

		glEnd();
}