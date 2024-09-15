#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Vector3D.h"
#include <vector>
#include "Mesh.h"
#include <chrono>
#include <thread>
#include <string>
#include <sstream>

GLFWwindow* window;

//Frame counter
float frames = 0;

//Time managers
float timeAcumulator = 0;
float timeSlice = 1000; //Time elapse between updates
const int TARGET_FPS = 20;
const float TARGET_FRAME_TIME = 1000.0f / TARGET_FPS; // Frame time in milliseconds
bool canLimitFRameRate = false;

//Camera vectors
Vector3D up = Vector3D(0.0f, 1.0f, 0.0f);
Vector3D center = Vector3D(0.0f, 0.0f, 0.0f);
Vector3D eye = Vector3D(0.0f, 0.0f, 5.0f);

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

//Window Height
float width = 800.0f;
float height = 600.0f;
float steps = 0.2f;



void drawText(const char* text, int lenght, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);

	for (int i = 0; i < lenght; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	switch (key)
	{
		//H
	case GLFW_KEY_A: eye.x += steps; break;
	case GLFW_KEY_S: eye.y += steps; break;
	case GLFW_KEY_D: eye.z += steps; break;
	case GLFW_KEY_Z: eye.x -= steps; break;
	case GLFW_KEY_X: eye.y -= steps; break;
	case GLFW_KEY_C: eye.z -= steps; break;
		//Centro = hacia donde ve la camara
	case GLFW_KEY_H: center.x += steps; break;
	case GLFW_KEY_J: center.y += steps; break;
	case GLFW_KEY_K: center.z += steps; break;
	case GLFW_KEY_B: center.x -= steps; break;
	case GLFW_KEY_N: center.y -= steps; break;
	case GLFW_KEY_M: center.z -= steps; break;

		//eye
	case GLFW_KEY_Q: up.x += steps; break;
	case GLFW_KEY_W: up.y += steps; break;
	case GLFW_KEY_E: up.z += steps; break;
	case GLFW_KEY_I: up.x -= steps; break;
	case GLFW_KEY_O: up.y -= steps; break;
	case GLFW_KEY_P: up.z -= steps; break;

	}

}


float getCurrentTimeMS()
{
	// Get the current time from the system clock
	auto now = std::chrono::high_resolution_clock::now();

	// Convert the current time to time since epoch
	auto duration = now.time_since_epoch();

	// Convert duration to milliseconds
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	return static_cast<float>(milliseconds);;
}

void display(void)
{

	//start drawing the frame
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set camera view
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

	model.drawMesh(colorList);


}

void init(void)
{
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  Set up projection matrix  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, width / height, 0.1, 100.0);

	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

	glEnable(GL_DEPTH_TEST);

}


void gameLoop()
{
	auto lastUpdate = std::chrono::steady_clock::now();

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
	{
		auto frameStart = std::chrono::steady_clock::now(); // Start time of the frame

		// Calculate deltaTime
		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float, std::milli> delta = currentTime - lastUpdate;
		float deltaTime = delta.count();

		if (deltaTime < 0.001f)
			deltaTime = 0.001f; // Avoid extremely small deltaTime values

		// Update lastUpdate
		lastUpdate = currentTime;

		// Time accumulation for fixed timestep
		timeAcumulator += deltaTime;

		while (timeAcumulator > timeSlice)
		{
			timeAcumulator -= timeSlice;
		}

		// Rendering
		display();


		// Calculate FPS after drawing everything before going to the next frame
		frames = 1000.0f / deltaTime;

		//show fps on screen
		std::stringstream ss;
		ss << static_cast<int>(frames);
		std::string strfps = ss.str();
		//std::cout<<strfps<<std::endl;

		drawText(strfps.data(), strfps.size(), 0, 0);

		// Frame limiter: Wait if the frame was rendered too quickly
		auto frameEnd = std::chrono::steady_clock::now();
		std::chrono::duration<float, std::milli> frameDuration = frameEnd - frameStart;
		float frameTime = frameDuration.count();
		//Limit the frame rate
		if (frameTime < TARGET_FRAME_TIME && canLimitFRameRate)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(TARGET_FRAME_TIME - frameTime)));
		}

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glFlush();
		glfwPollEvents();
	}

	glfwTerminate();
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
	/*
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	mainWindow = glutCreateWindow("MeshRenderer");*/


	glutInit(&argc, argv);

	glfwInit();
	window = glfwCreateWindow(width, height, "meshRenderer", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);


	model.loadVertices("cube.obj");
	model.createFaces("cube.obj");



	//glutDisplayFunc(display);
	//glutIdleFunc(display);
	//glutKeyboardFunc(handleKeypress);

	//glutMainLoop();
	glfwSetKeyCallback(window, key_callback);
	init();

	gameLoop();

	return 0;   /* ISO C requires main to return int. */
}