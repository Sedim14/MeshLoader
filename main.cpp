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

std::vector<Mesh*>models;

std::vector<const char*>objs = {
    "cube.obj",
    "cone.obj",
    "ico.obj",
    "torus.obj"
};


GLFWwindow* window;

//Frame counter
int frames = 0;

//Time managers
float timeAcumulator = 0;
float timeSlice = 60; //Time elapse between updates
const int TARGET_FPS = 4000;
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
int width = 800.0f;
int height = 600.0f;
float steps = 0.2f;

void loadModels() {

    for (int i = 0; i < objs.size(); i++)
    {
        Mesh* newModel = new Mesh();
        newModel->loadVertices(objs[i]);
        newModel->createFaces(objs[i]);
        models.push_back(newModel);
    }

}



void drawText(const char* text, int lenght, int x, int y)
{
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0f, 1.0f, 1.0f);

    glRasterPos2i(x, y);

    for (int i = 0; i < lenght; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
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

    for (int i = 0; i < objs.size(); i++) {
        //glPushMatrix();
        models[i]->drawMesh(colorList);
        //glPopMatrix();
    }


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
    int maxFrameRate = 0;

    auto lastUpdate = std::chrono::steady_clock::now();

    auto lastTime = std::chrono::steady_clock::now();

    int sec = 0;

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

        //Calculate framerate
        frames++;

        // Calculate frame duration
        auto frameEnd = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> frameDuration = frameEnd - frameStart;
        float frameTime = frameDuration.count();


        // check if it has passed one second
        auto actualTime = std::chrono::steady_clock::now();
        //Calculate how many time has pass
        std::chrono::duration<float, std::milli> deltaMS = actualTime - lastTime;

        //Restart processed frames
        if (deltaMS.count() > 1000.0f) {
            maxFrameRate = frames;
            lastTime = actualTime;
            frames = 0;
        }

        //Show frame rate
        std::stringstream ss;
        ss << "FPS:" << static_cast<int>(maxFrameRate); //
        std::string strfps = ss.str();
        drawText(strfps.data(), strfps.size(), 10, 10);



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

    // Clean up and exit
    glfwDestroyWindow(window);

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


    loadModels();


    //glutDisplayFunc(display);
    //glutIdleFunc(display);
    //glutKeyboardFunc(handleKeypress);

    //glutMainLoop();
    glfwSetKeyCallback(window, key_callback);
    init();

    gameLoop();

    return 0;   /* ISO C requires main to return int. */
}
