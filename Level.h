#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
	Level(int x, int y);

	int height;
	int width;
	void setNode(int x, int y, int tileID);
	int getNode(int x, int y);
private:
	int **grid;
}; 
#endif /* LEVEL_H */