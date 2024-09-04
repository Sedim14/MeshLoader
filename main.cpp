#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Mesh.h"
#include "Vector3D.h"
#include <vector>
#include "Camera.h"

//Camera vectors
Vector3D up = Vector3D(0.0f, 1.0f, 0.0f);
Vector3D center = Vector3D(0.0f, 0.0f, 0.0f);
Vector3D eye = Vector3D(0.0f, 0.0f, 0.5f);

// Lista de colores RGB representados como Vector3D
std::vector<Vector3D> colorList = {
    // Basic Colors
    Vector3D(1.0f, 0.0f, 0.0f), // Rojo (Red)
    Vector3D(0.0f, 1.0f, 0.0f), // Verde (Green)
    Vector3D(0.0f, 0.0f, 1.0f), // Azul (Blue)
    Vector3D(1.0f, 1.0f, 0.0f), // Amarillo (Yellow)
    Vector3D(0.0f, 1.0f, 1.0f), // Cian (Cyan)
    Vector3D(1.0f, 0.0f, 1.0f), // Magenta
    Vector3D(1.0f, 1.0f, 1.0f), // Blanco (White)
    Vector3D(0.0f, 0.0f, 0.0f), // Negro (Black)

};

Mesh model;
Mesh model2;
Mesh model3;


//Window Height
float width = 800.0f;
float height = 600.0f;

float steps = 0.2f;

void handleKeypress(unsigned char key, int x, int y) {
	
	switch (key)
	{
		//Vector eye
		case 'a': eye.x += steps; break; // Move forward
		case 's': eye.y += steps; break; // Move backward
		case 'd': eye.z += steps; break; // Move left
		case 'z': eye.x -= steps; break; // Move right
		case 'x': eye.y -= steps; break; // Move up
		case 'c': eye.z -= steps; break; // Move down

		//Vector center control
		case 'h': center.x += steps; break; // Move forward
		case 'j': center.y += steps; break; // Move backward
		case 'k': center.z += steps; break; // Move left
		case 'b': center.x -= steps; break; // Move right
		case 'n': center.y -= steps; break; // Move up
		case 'm': center.z -= steps; break; // Move down

		//Vector at
		case 'q': up.x += steps; break; // Move forward
		case 'w': up.y += steps; break; // Move backward
		case 'e': up.z += steps; break; // Move left
		case 't': up.x -= steps; break; // Move right
		case 'u': up.y -= steps; break; // Move up
		case 'i': up.z -= steps; break; // Move down
	}
	glutPostRedisplay(); 
}


void display(void)
{


	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update the camera position and orientation
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);


	model.drawMesh(colorList);
	model2.drawMesh(colorList);
	model3.drawMesh(colorList);


	glutSwapBuffers();
	//glFlush();
}

void init(void)
{
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	gluPerspective(45.0, width / height, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

	glEnable(GL_DEPTH_TEST);

}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MeshRenderer");

	init();

	//Load all models
	model.loadVertices("cube.obj");
	model.createFaces("cube.obj");

	model2.loadVertices("cone.obj");
	model2.createFaces("cone.obj");

	model3.loadVertices("torus.obj");
	model3.createFaces("torus.obj");

	
	glutDisplayFunc(display);
	glutIdleFunc(nullptr);
	glutKeyboardFunc(handleKeypress);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}
