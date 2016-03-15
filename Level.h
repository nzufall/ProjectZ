#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
	Level(int x, int y);

	int height;
	int width;
	/**
	* Places a tile into a level by ID at position X and Y
	* @param x X location of Node
	* @param y Y location of Node
	* @param tileID the tile being placed at the node
	*/
	void setNode(int x, int y, int tileID);
	/**
	* Returns the tileID of a location so collision can be determined
	* @param x requested X location of Node
	* @param y requested Y location of Node
	*/
	int getNode(int x, int y);
private:
	int **grid;
}; 
#endif /* LEVEL_H */