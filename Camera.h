#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
	/**
	* Constructor 
	* @param height sets the screen height
	* @param width sets the screen width
	*/
	Camera(int height, int width);
	int x;
	int y;
	int screenX;
	int screenY;
	int maxX;
	int maxY;
	/**
	* Moves the camera to a new location
	* @param newX sets the new X location of the camera
	* @param newY sets the new Y location of the camera
	*/
	void moveCamera(int newX, int newY);
private:

};

#endif /* CAMERA_H */