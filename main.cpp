#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Mesh.h"
#include "Vector3D.h"
#include <vector>

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


//Window Height
float width = 800.0f;
float height = 600.0f;


Mesh model;






void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model.drawMesh(colorList);


	glutSwapBuffers();
	glFlush();
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

	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(5.7f, 3.0f, 7.0f,    0.0f, 0.0, 0.0f,    0.0, 1.0, 0.0);

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

	model.loadVertices("cube.obj");
	model.createFaces("cube.obj");
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MeshRenderer");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}
