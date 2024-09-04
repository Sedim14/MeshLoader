#include "Camera.h"
#include <iostream>
#include "Vector3D.h"
#include <gl/freeglut.h>

Camera::Camera()
{
	up = Vector3D(0.0f, 1.0f, 0.0f);
	center = Vector3D(0.0f, 0.0f, 0.0f);
	eye = Vector3D(0.0f, 0.0f, 0.5f);
}

void Camera::cameraController(unsigned char key, int x, int y)
{
	switch (key)
	{
        switch (key) {
        case 'w': eye.z -= 0.2f; break; // Move forward
        case 's': eye.z += 0.2f; break; // Move backward
        case 'a': eye.x -= 0.2f; break; // Move left
        case 'd': eye.x += 0.2f; break; // Move right
        case 'r': eye.y += 0.2f; break; // Move up
        case 'f': eye.y -= 0.2f; break; // Move down
        case 'q': center.x -= 0.2f; break; // Rotate left
        case 'e': center.x += 0.2f; break; // Rotate right
        }
        std::cout << "Eye: (" << eye.x << ", " << eye.y << ", " << eye.z << ")\n";
        std::cout << "Center: (" << center.x << ", " << center.y << ", " << center.z << ")\n";
        std::cout << "Up: (" << up.x << ", " << up.y << ", " << up.z << ")\n";
	}

}

void Camera::updateCamera()
{
	gluLookAt(eye.x,eye.y,eye.z,center.x,center.y,center.z,up.x,up.y,up.z);
}