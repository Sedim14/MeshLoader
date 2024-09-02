#pragma once
#include"Vector3D.h"
#include<vector>
#include <GL/freeglut.h>
#include <math.h>
#include "matrixTransformations.h"


class Mesh
{
private:
	std::vector<Vector3D>vertices;//Vector que representara todos los vertices
	std::vector<std::vector<Vector3D*>>faces;//Vector vectores donde los vertices de cada cara almacenara las direciones de los vertices
	float angleX = 1.0;
	float angleY = 1.0;
	float angleZ = 1.0;

public:
	Mesh() = default; //Constructor
	~Mesh() = default; //Deconstructor
	void loadVertices(const char *obj);
	void createFaces(const char* obj);
	void drawMesh(const std::vector<Vector3D>& colors);
	//Metodo para manipular mesh
	void updateVertices();

};



