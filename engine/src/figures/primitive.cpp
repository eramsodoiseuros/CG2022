#include "../../headers/primitive.h"
#include "../../headers/transformation.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>    // MUDAR

Primitive::Primitive(){

    filename = "";
    textureFilename = "";
    vBuffer[0] = 0;
    vBuffer[1] = 0;
    nPoints = 0;
    nIndexes = 0;
    r = g = b = 0.0f;
    transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();
}


Primitive::Primitive(string filename){

    readPrimitive(filename);
    textureFilename = "";

    vBuffer[1] = 0;
    r = g = b = 0.0f;
    transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();
}


void Primitive::readPrimitive(string primitive3D){

	// 3d file path
	string inputFile = "../3D/" + primitive3D;
	ifstream dFile(inputFile);
	if(!dFile.is_open()){

		cerr << "Could not open the specified file:" << inputFile << endl;
		return ;
	}

	string l = "";
	vector<string> parser = vector<string>();

	bool fstLine = true;
	int arraySize = 0;
	float* points = NULL;

	int index = 0;

	while(getline(dFile,l)){

		stringstream ss(l);
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			parser.push_back(subs);
		}

		if(fstLine){
			nPoints = stoi(parser.at(0));
			nIndexes = stoi(parser.at(1));
			fstLine = false;

			arraySize = nIndexes * 3 * 3;
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

	glEnableClientState(GL_VERTEX_ARRAY);
	// VBO
	glGenBuffers(1, &vBuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, arraySize * sizeof(float), points, GL_STATIC_DRAW);
	glDisableClientState(GL_VERTEX_ARRAY);
	free(points);
}


string Primitive::getFilename(){
    return string(filename);
}


string Primitive::getTextureFilename(){
	return string(textureFilename);
}

//unsigned int* getVBOs();
unsigned int Primitive::getPointsVBO(){
    return vBuffer[0];
}


// unsigned int get???VBO();
unsigned int Primitive::getNPoints(){
    return nPoints;
}


unsigned int Primitive::getNIndexes(){
    return nIndexes;
}


vector<float> Primitive::getColor(){
    vector<float> colors = vector<float>();
    colors.push_back(r);
    colors.push_back(g);
    colors.push_back(b);
    return colors;
}


vector<Transformation*> Primitive::getTransformations(){

    return vector<Transformation*>(transformations);
}


vector<Primitive> Primitive::getAppendedPrimitives(){

	return vector<Primitive>(appendedPrimitives);
}


void Primitive::setColor(vector<float> rgbColor){
    r = rgbColor.at(0);
    g = rgbColor.at(1);
    b = rgbColor.at(2);
}



void Primitive::setFilename(string s){
    filename = string(s);
}


void Primitive::setTextureFilename(string s){
    textureFilename = string(s);
}


void Primitive::setTransformations(vector<Transformation*> transf){
    transformations = vector<Transformation*>(transf);
}

void Primitive::setAppendedPrimitives(vector<Primitive> primitives) {
	appendedPrimitives = vector<Primitive>(primitives);
}

void Primitive::addTransformation(Transformation *a){
	
	transformations.push_back(a);
}

void Primitive::addAppendedPrimitive(Primitive p){

	appendedPrimitives.push_back(p);
}


Primitive Primitive::clone(){

    Primitive p = Primitive();
    p.setFilename(filename);
    p.setTextureFilename(textureFilename);

    p.setTransformations(transformations);
	p.setAppendedPrimitives(appendedPrimitives);
    p.nPoints = nPoints;
    p.nIndexes = nIndexes;
    p.vBuffer[0] = vBuffer[0];
    p.vBuffer[1] = vBuffer[1];
    p.r = r; p.g = g; p.b = b;
}



void Primitive::Draw(){

    int totalPoints = nIndexes * 3;

	glPushMatrix();
	
	glColor3f(r, g, b);

	for (Transformation* t : transformations){
		t->Apply();
	}

    glEnableClientState(GL_VERTEX_ARRAY);
	// Para adicionar cores a cada triângulo, tem de se adicionar um VBO e redefinir o readFile

	// Dar bind ao identificador associado da primitiva
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	// Definir o modo de leitura do VBO (3 vértices por triangulo, utilizando floats)
	glVertexPointer(3, GL_FLOAT, 0, 0);
	// Draw da primitiva, a começar no índice 0, nPoints
	glDrawArrays(GL_TRIANGLES, 0, totalPoints);
	glDisableClientState(GL_VERTEX_ARRAY);

	for (Primitive p : appendedPrimitives){
		p.Draw();
	}

	glPopMatrix();
}

void Primitive::printInfo(){

	cout << "filename::" << filename << ",texture::" << textureFilename << ",nPoints::" << nPoints << ",nIndexes::" << nIndexes << ", color::" << r << g << b << endl;
	cout << "number of moons: " << appendedPrimitives.size() << endl;
	cout << "\n" << endl;
}