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
	vBuffer[0] = -1; vBuffer[1] = -1; vBuffer[2] = -1;
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
	vBuffer[0] = -1; vBuffer[1] = -1; vBuffer[2] = -1;
	transformations = vector<Transformation*>();
	appendedPrimitives = vector<Primitive>();
	colorComponents = Color();
	textureID = 0;
}


void Primitive::loadTexture() {

	unsigned int t, tw, th;
	ILubyte* textureData;
	string realPath = DBPATH + textureFilename;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)realPath.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	//cout << textureFilename << ", W=" << tw << ", H:" << th << endl;

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	textureData = ilGetData();

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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

		// separar todos os dados pela v??rgula que os delimita
		stringstream ss(l);
		while (ss.good()) {
			string subs;
			getline(ss, subs, ',');
			parser.push_back(subs);
		}

		// a primeira linha apenas l?? o n??mero de pontos e de ??ndices utilizados
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

			s = stof(parser.at(22)); t = stof(parser.at(23));
			texs[texsIndex++] = s; texs[texsIndex++] = t;
		}
		parser.clear();
	}

	dFile.close();

	
	// VBOs

	// points
	glGenBuffers(1, &vBuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, pointsArraySize * sizeof(float), points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normals
	glGenBuffers(1, &vBuffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, pointsArraySize * sizeof(float), normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//tex coords
	if (textureFilename.compare("")) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		loadTexture();
		glBindTexture(GL_TEXTURE_2D, textureID);
		glGenBuffers(1, &vBuffer[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vBuffer[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * nIndexes, texs, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
 * @brief get n??mero de ??ndices
 *
 * @return unsigned int
 */
unsigned int Primitive::getNIndexes() {
	return nIndexes;
}


/**
 * @brief devolve uma lista das transforma????es a serem aplicadas ?? corrente primitiva
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
 * @brief set da lista de transforma????es a serem aplicadas
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
 * @brief adiciona uma transforma????o ?? primitiva
 *
 * @param a
 */
void Primitive::addTransformation(Transformation* a) {

	transformations.push_back(a);
}

/**
 * @brief adiciona uma primitiva ??s anexadas
 *
 * @param p
 */
void Primitive::addAppendedPrimitive(Primitive p) {

	appendedPrimitives.push_back(p);
}


/**
 * @brief Desenho da primitiva
 *
 */
void Primitive::Draw() {

	int totalPoints = nIndexes * 3;

	glPushMatrix();

	// Aplicar as componentes das cores (difusa,  especular, etc)
	colorComponents.Apply();

	// aplicar cada transforma????o
	for (Transformation* t : transformations) {
		t->Apply();
	}

	// vertexs buffer
	// Definir o modo de leitura do VBO (3 v??rtices por triangulo, utilizando floats)
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer[1]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// texture coords buffer
	if (textureFilename.compare("")) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindBuffer(GL_ARRAY_BUFFER, vBuffer[2]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Draw da primitiva, a come??ar no ??ndice 0, nPoints
	glDrawArrays(GL_TRIANGLES, 0, totalPoints);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	// para cada primitiva anexada, desenh??-la
	for (Primitive p : appendedPrimitives) {
		p.Draw();
	}

	glPopMatrix();
}


/**
 * @brief imprime a informa????o b??sica relativa a uma primitiva
 *
 */
void Primitive::printInfo() {

	cout << "filename::" << filename << ",texture::" << textureFilename << ",nPoints::" << nPoints << ",nIndexes::" << nIndexes << endl;
	cout << "number of moons: " << appendedPrimitives.size() << endl;
	cout << "\n" << endl;
}