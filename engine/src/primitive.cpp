#include "../headers/primitive.h"
#include "../headers/transformation.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>    // MUDAR


/**
 * @brief Construct a new Primitive:: Primitive object
 * 
 */
Primitive::Primitive(){

    filename = "";
    textureFilename = "";
	vBuffer[2];
    nPoints = 0;
    nIndexes = 0;
    r = g = b = 0.0f;
    transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();
}

/**
 * @brief Construct a new Primitive:: Primitive object
 * 
 * @param filename ficheiro 3d
 */
Primitive::Primitive(string filename){

    readPrimitive(filename);
    textureFilename = "";
	vBuffer[2];
    r = g = b = 0.0f;
    transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();
}

/**
 * @brief Leitura de um ficheiro 3d
 * 
 * @param primitive3D 
 */
void Primitive::readPrimitive(string primitive3D){

	// 3d file path
	string inputFile = "../3D/" + primitive3D;
	ifstream dFile(inputFile);
	if(!dFile.is_open()){

		cerr << "Could not open the specified file:" << inputFile << endl;
		return ;
	}

	// auxiliar variables for parsing
	string l = "";
	vector<string> parser = vector<string>();

	// flag to check if we are in the first line
	bool fstLine = true;

	int pointsArraySize = 0;
	int normalsArraySize = 0;
	// points array
	float* points = NULL;
	// normals array
	float* normals = NULL;

	int pointsIndex = 0;
	int normalsIndex = 0;

	// [0-2]=points, [3]=normal, [4-5]=texture
	int type = 0;

	while(getline(dFile,l)){


		// separar todos os dados pela vírgula que os delimita
		stringstream ss(l);
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			parser.push_back(subs);
		}

		// a primeira linha apenas lê o número de pontos e de índices utilizados
		if(fstLine){
			nPoints = stoi(parser.at(0));
			nIndexes = stoi(parser.at(1));
			fstLine = false;

			pointsArraySize = nIndexes * 3;
			normalsArraySize = nIndexes;

			points = (float*) malloc(pointsArraySize * sizeof(float));
			normals = (float*) malloc(normalsArraySize * sizeof(float));

		}
		else {
			float x,y,z;
			x = stof(parser.at(0));
			y = stof(parser.at(1));
			z = stof(parser.at(2));

			if (type >= 0 && type <= 2){
				points[pointsIndex++] = x;
				points[pointsIndex++] = y;
				points[pointsIndex++] = z;
				type++;
			}
			else if (type == 3){
				normals[normalsIndex++] = x;
				normals[normalsIndex++] = y;
				normals[normalsIndex++] = z;

				type = 0;
				// enquanto não houver texture, voltar aqui a 0!
				// quando houver textura, o type tem de incrementar aqui
			}
		}
		parser.clear();
	}
	
	dFile.close();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	
	// VBOs
	glGenBuffers(2, vBuffer);

	// points
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, pointsArraySize * sizeof(float), points, GL_STATIC_DRAW);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, normalsArraySize * sizeof(float), normals, GL_STATIC_DRAW);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	free(points);
	free(normals);
}


/**
 * @brief get ficheiro 3d de origem
 * 
 * @return string 
 */
string Primitive::getFilename(){
    return string(filename);
}

/**
 * @brief get ficheiro da textura
 * 
 * @return string 
 */
string Primitive::getTextureFilename(){
	return string(textureFilename);
}

/**
 * @brief get número de índices
 * 
 * @return unsigned int 
 */
unsigned int Primitive::getNIndexes(){
    return nIndexes;
}

/**
 * @brief devolve array com os valores do rgb
 * 
 * @return vector<float> 
 */
vector<float> Primitive::getColor(){
    vector<float> colors = vector<float>();
    colors.push_back(r);
    colors.push_back(g);
    colors.push_back(b);
    return colors;
}

/**
 * @brief devolve uma lista das transformações a serem aplicadas à corrente primitiva
 * 
 * @return vector<Transformation*> 
 */
vector<Transformation*> Primitive::getTransformations(){

    return vector<Transformation*>(transformations);
}

/**
 * @brief devolve uma lista de primitivas anexadas a uma principal
 * 
 * @return vector<Primitive> 
 */
vector<Primitive> Primitive::getAppendedPrimitives(){

	return vector<Primitive>(appendedPrimitives);
}

/**
 * @brief set dos valores rgb da cor
 * 
 * @param rgbColor 
 */
void Primitive::setColor(vector<float> rgbColor){
    r = rgbColor.at(0);
    g = rgbColor.at(1);
    b = rgbColor.at(2);
}

/**
 * @brief set nome do ficheiro 3d de origem
 * 
 * @param s 
 */
void Primitive::setFilename(string s){
    filename = string(s);
}

/**
 * @brief set nome do ficheiro da textura
 * 
 * @param s 
 */
void Primitive::setTextureFilename(string s){
    textureFilename = string(s);
}

/**
 * @brief set da lista de transformações a serem aplicadas
 * 
 * @param transf 
 */
void Primitive::setTransformations(vector<Transformation*> transf){
    transformations = vector<Transformation*>(transf);
}

/**
 * @brief set da lista de primitivas anexadas
 * 
 * @param primitives 
 */
void Primitive::setAppendedPrimitives(vector<Primitive> primitives) {
	appendedPrimitives = vector<Primitive>(primitives);
}

/**
 * @brief adiciona uma transformação à primitiva
 * 
 * @param a 
 */
void Primitive::addTransformation(Transformation *a){
	
	transformations.push_back(a);
}

/**
 * @brief adiciona uma primitiva às anexadas
 * 
 * @param p 
 */
void Primitive::addAppendedPrimitive(Primitive p){

	appendedPrimitives.push_back(p);
}

/**
 * @brief object clone
 * 
 * @return Primitive 
 */
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


/**
 * @brief Desenho da primitiva
 * 
 */
void Primitive::Draw(){

    int totalPoints = nIndexes * 3;

	glPushMatrix();
	glColor3f(r, g, b);

	for (Transformation* t : transformations){
		t->Apply();
	}

    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	// Para adicionar cores a cada triângulo, tem de se adicionar um VBO e redefinir o readFile

	// Dar bind ao identificador associado da primitiva
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	// Definir o modo de leitura do VBO (3 vértices por triangulo, utilizando floats)
	glVertexPointer(3, GL_FLOAT, 0, 0);

	//// normals
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	// Draw da primitiva, a começar no índice 0, nPoints
	glDrawArrays(GL_TRIANGLES, 0, totalPoints);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	for (Primitive p : appendedPrimitives){
		p.Draw();
	}

	glPopMatrix();
}


/**
 * @brief imprime a informação básica relativa a uma primitiva
 * 
 */
void Primitive::printInfo(){

	cout << "filename::" << filename << ",texture::" << textureFilename << ",nPoints::" << nPoints << ",nIndexes::" << nIndexes << ", color::" << r << g << b << endl;
	cout << "number of moons: " << appendedPrimitives.size() << endl;
	cout << "\n" << endl;
}