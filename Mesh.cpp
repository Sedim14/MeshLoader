#include "Mesh.h"
#include <GL/freeglut.h>
#include <iostream>
#include"Vector3D.h"
#include<vector>
#include <cstdio>  // For FILE, fopen_s, fclose, fscanf_s
#include "matrixTransformations.h"

void Mesh::loadVertices(const char* obj) {
    FILE* file = nullptr;

    // Open the .obj file using fopen_s
    if (fopen_s(&file, obj, "r") == 0) {
        std::cout << "File opened successfully" << std::endl;
        char type;
        float x, y, z;
        int result;

        // Read data from the file using fscanf_s
        while ((result = fscanf_s(file, "%c %f %f %f", &type, sizeof(type), &x, &y, &z)) != EOF) {
            if (result == 4 && type == 'v') 
            {
                vertices.push_back(Vector3D(x, y, z));
                //std::cout << "Vertex: (" << x << ", " << y << ", " << z << ")" << std::endl;
            }   
        }

        // Close the file
        fclose(file);
    }
    else {
        // File not found
        std::cerr << "The .obj file was not found" << std::endl;
    }
}

void Mesh::createFaces(const char* obj)
{
    FILE* file = nullptr;

    // Open the .obj file using fopen_s
    if (fopen_s(&file, obj, "r") == 0) {
        //std::cout << "File opened successfully" << std::endl;
        char type;
        float v1, v2, v3;
        int result;

        // Read data from the file using fscanf_s
        while ((result = fscanf_s(file, "%c %f %f %f", &type, sizeof(type), &v1, &v2, &v3)) != EOF) {
            if (result == 4 && type == 'f')
            {
                std::vector<Vector3D*> face = {&vertices[v1 - 1], &vertices[v2 - 1], &vertices[v3 - 1] }; //Pass the addreses of each vertexs
                faces.push_back(face);
                //std::cout << "Face composed by vertices: (" << v1 << ", " << v2 << ", " << v3 << ")" << std::endl;
            }
        }

        // Close the file
        fclose(file);
    }
    else {
        // File not found
        std::cerr << "The .obj file was not found" << std::endl;
    }
}

//Este metodo se dedica unicamente a dibujar los vertices en su posicion actual
void Mesh::drawMesh(const std::vector<Vector3D>& colors)
{
    //std::cout<<"AngleX: "<<angleX<<" AngleY: "<<angleY<<std::endl;
    //std::cout << "New frame"<<std::endl;
    //Actualiza la posicion de los vertices antes de dibujarlos
    updateVertices();

    glBegin(GL_TRIANGLES);

    int iColor = 0;

    for (int face = 0; face < faces.size(); face++)
    {
        if (iColor >= colors.size())
        {
            iColor = 0;
        }

        //Start new color for the current face
        Vector3D currentColor = colors[iColor];
        glColor3f(currentColor.getX(), currentColor.getY(), currentColor.getZ());
        //std::cout << "Face color: (" << currentColor.getX() << ", " << currentColor.getY() << ", " << currentColor.getZ() << ")" << std::endl;
        //std::cout<<"Face "<<face+1 << ":" << std::endl;
        //Draw all the vertices of the current face
        std::vector<Vector3D*> currentFace = faces[face];
        for (int i = 0; i < currentFace.size(); i++)
        {
            Vector3D *currentVertex = currentFace[i];
            glVertex3f(currentVertex->getX(), currentVertex->getY(), currentVertex->getZ());
            //std::cout << "Vertex Posicion: (" << currentVertex->getX() << ", " << currentVertex->getY() << ", " << currentVertex->getY() << ")" << std::endl;
        }

        iColor++;
    }
    glEnd();
}

//Metodos de Actualizacion de los vertices
void Mesh::updateVertices()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] = rotateX(vertices[i],angleX);
        vertices[i] = rotateY(vertices[i], angleY);
    }
    
}

