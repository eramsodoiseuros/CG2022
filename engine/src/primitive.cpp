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
    transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();

	isEmissiva = true;
    emissiva = Point_3D(1,1,1);

    isAmbiente = true;
    ambiente = Point_3D(1,1,1);

    isDifusa = true;
    difusa = Point_3D(1,1,1);

    isEspecular = true;
    especular = Point_3D(1,1,1);
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
    transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();

	isEmissiva = false;
    emissiva = Point_3D(1,1,1);

    isAmbiente = false;
    ambiente = Point_3D(1,1,1);

    isDifusa = true;
    difusa = Point_3D(1,1,1);

    isEspecular = true;
    especular = Point_3D(1,1,1);
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


bool Primitive::isLuzEmissiva(){
	return isEmissiva;
}

bool Primitive::isLuzAmbiente(){
	return isAmbiente;
}

bool Primitive::isLuzDifusa(){
	return isDifusa;
}

bool Primitive::isLuzEspecular(){
	return isEspecular;
}

Point_3D Primitive::getEmissiva(){
	return emissiva;
}

Point_3D Primitive::getAmbiente(){
	return ambiente;
}

Point_3D Primitive::getDifusa(){
	return difusa;
}

Point_3D Primitive::getEspecular(){
	return especular;
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

void Primitive::setIsEmissiva(bool b){
	isEmissiva = b;
}

void Primitive::setIsAmbiente(bool b){
	isAmbiente = b;
}

void Primitive::setIsDifusa(bool b){
	isDifusa = b;
}

void Primitive::setIsEspecular(bool b){
	isEspecular = b;
}


void Primitive::setEmissiva(Point_3D p){
	emissiva = p;
}

void Primitive::setAmbiente(Point_3D p){
	ambiente = p;
}

void Primitive::setDifusa(Point_3D p){
	difusa = p;
}

void Primitive::setEspecular(Point_3D p){
	especular = p;
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
}


/**
 * @brief Desenho da primitiva
 * 
 */
void Primitive::Draw(){

    int totalPoints = nIndexes * 3;

	glPushMatrix();

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

    if (isLuzEmissiva()) {
        
        Point_3D e = getEmissiva();
        float l2[] = { e.getX(), e.getY(), e.getZ(), 1.0 };
        glMaterialfv(GL_FRONT, GL_EMISSION, l2);
        glMaterialf(GL_FRONT,GL_SHININESS,128);

    }

    if (isLuzAmbiente()) {

        Point_3D a = getAmbiente();
        float l3[] = { a.getX(), a.getY(), a.getZ(), 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, l3);
        glMaterialf(GL_FRONT,GL_SHININESS,128);

    }

    if (isLuzDifusa()) {

        Point_3D d = getDifusa();
        float l0[] = { d.getX(), d.getY(), d.getZ(), 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, l0);
        glMaterialf(GL_FRONT,GL_SHININESS,128);

    }

    if (isLuzEspecular()) {

        Point_3D s = getEspecular();
        float l1[] = { s.getX(), s.getY(), s.getZ(), 1.0 };
        glMaterialfv(GL_FRONT, GL_SPECULAR, l1);
        glMaterialf(GL_FRONT,GL_SHININESS,128);

    }

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

	cout << "filename::" << filename << ",texture::" << textureFilename << ",nPoints::" << nPoints << ",nIndexes::" << nIndexes << endl;
	cout << "number of moons: " << appendedPrimitives.size() << endl;
	cout << "\n" << endl;
}