#include "matrixTransformations.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>

#define M_PI 3.14159265358979323846

//Metodos de 
Vector3D rotateX(Vector3D vertex,float degrees) 
{
	//std::cout << "AngleX: " << degrees<<std::endl;
	float radians = degrees * ( M_PI/ 180.0);
	float newX = vertex.getX();
	float newY = (vertex.getY() * cos(radians))-(vertex.getZ()*sin(radians));
	float newZ = (vertex.getY() * sin(radians)) + (vertex.getZ() * cos(radians));
	return Vector3D(newX, newY, newZ);
}

Vector3D rotateY(Vector3D vertex, float degrees)
{
	//std::cout << "AngleY: " << degrees << std::endl;
	float radians = degrees * (M_PI / 180.0);
	float newX = (vertex.getX()*cos(radians))-(vertex.getY()*sin(radians));
	float newY = (vertex.getX() * sin(radians)) + (vertex.getY() * cos(radians));
	float newZ = vertex.getZ();
	return Vector3D(newX, newY, newZ);
}