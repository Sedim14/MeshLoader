#pragma once
#include "Vector3D.h"
#include <gl/freeglut.h>

class Camera
{
public:
	Vector3D up;
	Vector3D eye ;
	Vector3D center ;

	Camera();
	void cameraController(unsigned char key,int x, int y);
	void updateCamera();

};

