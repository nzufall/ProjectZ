#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
	Camera(int height, int width);
	int x;
	int y;
	int screenX;
	int screenY;
	int maxX;
	int maxY;
	void moveCamera(int newX, int newY);
private:

};

#endif /* CAMERA_H */