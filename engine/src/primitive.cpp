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
Primitive::Primitive() {

	filename = "";
	textureFilename = "";
	this->vBuffer;
	nPoints = 0;
	nIndexes = 0;
	transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();
	colorComponents = Color();
	textureID = 0;
}

/**
 * @brief Construct a new Primitive:: Primitive object
 *
 * @param filename ficheiro 3d
 */
Primitive::Primitive(string filename) {

	readPrimitive(filename);
	textureFilename = "";
	this->vBuffer;
	transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();
	colorComponents = Color();
	textureID = 0;
}



void Primitive::loadTexture(){


	unsigned int t, tw, th;
	unsigned char* textureData;
	string realPath = DBPATH + textureFilename;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)realPath.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	textureData = ilGetData();

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}




/**
 * @brief Leitura de um ficheiro 3d
 *
 * @param primitive3D
 */
void Primitive::readPrimitive(string primitive3D) {
	// 3d file path
	string inputFile = "../3D/" + primitive3D;
	ifstream dFile(inputFile);
	if (!dFile.is_open()) {

		cerr << "Could not open the specified file:" << inputFile << endl;
		return;
	}

	// auxiliar variables for parsing
	string l = "";
	vector<string> parser = vector<string>();

	// flag to check if we are in the first line
	bool fstLine = true;

	int pointsArraySize = 0;
	float* points = NULL;
	float* normals = NULL;
	float* texs = NULL;

	int pointsIndex = 0, normalsIndex = 0, texsIndex = 0;
	float x, y, z, nx, ny, nz, s, t;

	while (getline(dFile, l)) {

		// separar todos os dados pela vírgula que os delimita
		stringstream ss(l);
		while (ss.good()) {
			string subs;
			getline(ss, subs, ',');
			parser.push_back(subs);
		}

		// a primeira linha apenas lê o número de pontos e de índices utilizados
		if (fstLine) {
			nPoints = stoi(parser.at(0));
			nIndexes = stoi(parser.at(1));
			fstLine = false;

			pointsArraySize = nIndexes * 3;

			points = (float*)malloc(pointsArraySize * sizeof(float));
			normals = (float*)malloc(pointsArraySize * sizeof(float));
			texs = (float*)malloc((nIndexes * 2) * sizeof(float));

		}
		else {

			// p1, p2, p3
			x = stof(parser.at(0)); y = stof(parser.at(1)); z = stof(parser.at(2));
			points[pointsIndex++] = x; points[pointsIndex++] = y; points[pointsIndex++] = z;

			x = stof(parser.at(3)); y = stof(parser.at(4)); z = stof(parser.at(5));
			points[pointsIndex++] = x; points[pointsIndex++] = y; points[pointsIndex++] = z;

			x = stof(parser.at(6)); y = stof(parser.at(7)); z = stof(parser.at(8));
			points[pointsIndex++] = x; points[pointsIndex++] = y; points[pointsIndex++] = z;

			// normal1, normal2, normal3

			nx = stof(parser.at(9)); ny = stof(parser.at(10)); nz = stof(parser.at(11));
			normals[normalsIndex++] = nx; normals[normalsIndex++] = ny; normals[normalsIndex++] = nz;

			nx = stof(parser.at(12)); ny = stof(parser.at(13)); nz = stof(parser.at(14));
			normals[normalsIndex++] = nx; normals[normalsIndex++] = ny; normals[normalsIndex++] = nz;

			nx = stof(parser.at(15)); ny = stof(parser.at(16)); nz = stof(parser.at(17));
			normals[normalsIndex++] = nx; normals[normalsIndex++] = ny; normals[normalsIndex++] = nz;

			// texture coords

			s = stof(parser.at(18)); t = stof(parser.at(19));
			texs[texsIndex++] = s; texs[texsIndex++] = t;

			s = stof(parser.at(20)); t = stof(parser.at(21));
			texs[texsIndex++] = s; texs[texsIndex++] = t;
		}
		parser.clear();
	}

	dFile.close();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	// VBOs
	glGenBuffers(1, &vBuffer[0]);

	// points
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, pointsArraySize * sizeof(float), points, GL_STATIC_DRAW);


	glGenBuffers(1, &vBuffer[1]);
	// normals
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, pointsArraySize * sizeof(float), normals, GL_STATIC_DRAW);

	if (textureFilename.compare(""))
		loadTexture();
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * nIndexes, texs, GL_STATIC_DRAW);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	free(points);
	free(normals);
	free(texs);
}

/**
 * @brief get objeto com as componentes das cores (diff, spec, ambi, etc.)
 *
 * @return Color
 */
Color Primitive::getColorComponents() {

	return colorComponents;
}

/**
 * @brief get ficheiro 3d de origem
 *
 * @return string
 */
string Primitive::getFilename() {
	return string(filename);
}

/**
 * @brief get ficheiro da textura
 *
 * @return string
 */
string Primitive::getTextureFilename() {
	return string(textureFilename);
}

/**
 * @brief get número de índices
 *
 * @return unsigned int
 */
unsigned int Primitive::getNIndexes() {
	return nIndexes;
}


/**
 * @brief devolve uma lista das transformações a serem aplicadas à corrente primitiva
 *
 * @return vector<Transformation*>
 */
vector<Transformation*> Primitive::getTransformations() {

	return vector<Transformation*>(transformations);
}

/**
 * @brief devolve uma lista de primitivas anexadas a uma principal
 *
 * @return vector<Primitive>
 */
vector<Primitive> Primitive::getAppendedPrimitives() {

	return vector<Primitive>(appendedPrimitives);
}


/**
 * @brief set nome do ficheiro 3d de origem
 *
 * @param s
 */
void Primitive::setFilename(string s) {
	filename = string(s);
}

/**
 * @brief set nome do ficheiro da textura
 *
 * @param s
 */
void Primitive::setTextureFilename(string s) {
	textureFilename = string(s);
}

/**
 * @brief set da lista de transformações a serem aplicadas
 *
 * @param transf
 */
void Primitive::setTransformations(vector<Transformation*> transf) {
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
 * @brief set das componentes da cor
 *
 * @param c
 */
void Primitive::setColorComponents(Color c) {

	colorComponents = c;
}


/**
 * @brief adiciona uma transformação à primitiva
 *
 * @param a
 */
void Primitive::addTransformation(Transformation* a) {

	transformations.push_back(a);
}

/**
 * @brief adiciona uma primitiva às anexadas
 *
 * @param p
 */
void Primitive::addAppendedPrimitive(Primitive p) {

	appendedPrimitives.push_back(p);
}

/**
 * @brief object clone
 *
 * @return Primitive
 */
Primitive Primitive::clone() {

	Primitive p = Primitive();
	p.setFilename(filename);
	p.setTextureFilename(textureFilename);

	p.setTransformations(transformations);
	p.setAppendedPrimitives(appendedPrimitives);

	p.nPoints = nPoints;
	p.nIndexes = nIndexes;
	p.vBuffer[0] = vBuffer[0];
	p.vBuffer[1] = vBuffer[1];
	p.vBuffer[2] = vBuffer[2];
}


/**
 * @brief Desenho da primitiva
 *
 */
void Primitive::Draw() {

	int totalPoints = nIndexes * 3;

	glPushMatrix();

	for (Transformation* t : transformations) {
		t->Apply();
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Aplicar as componentes das cores (difusa,  especular, etc)
	colorComponents.Apply();

	// Dar bind ao identificador associado da primitiva
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	// Definir o modo de leitura do VBO (3 vértices por triangulo, utilizando floats)
	glVertexPointer(3, GL_FLOAT, 0, 0);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[1]);
	glNormalPointer(GL_FLOAT, 0, 0);
	
	if (textureFilename.compare("")){
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	// Draw da primitiva, a começar no índice 0, nPoints
	glDrawArrays(GL_TRIANGLES, 0, totalPoints);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	// para cada primitiva anexada, desenhá-la
	for (Primitive p : appendedPrimitives) {
		p.Draw();
	}

	glPopMatrix();
}


/**
 * @brief imprime a informação básica relativa a uma primitiva
 *
 */
void Primitive::printInfo() {

	cout << "filename::" << filename << ",texture::" << textureFilename << ",nPoints::" << nPoints << ",nIndexes::" << nIndexes << endl;
	cout << "number of moons: " << appendedPrimitives.size() << endl;
	cout << "\n" << endl;
}