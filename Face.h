#pragma once
#include"Vector3D.h"

class Face
{
public:
	int v1, v2, v3; //Vertices son representados por indices en la cara para ahorrar memoria
	Face(int index1, int index2, int index3);
};

