#include "Camera.h"

Camera::Camera(int height, int width) {
	maxX = x + screenX;
	maxY = y + screenY;
	x = (maxX / 2) * -1;
	y = 0;
}

void Camera::moveCamera(int newX, int newY) {
	x = newX;
	y = newY;
	maxX = x + screenX;
	maxY = y + screenY;
}