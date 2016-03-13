#include "Level.h"

Level::Level(int x, int y) {
	height = y;
	width = x;
	grid = new int*[height];
	for (int i = 0; i < height; i++) {
		grid[i] = new int[width];
	}
	for (int j = 0; j < height; j++) {
		for (int k = 0; k < width; k++) {
			grid[j][j] = -1;
		}
	}
}
void Level::setNode(int x, int y, int tileID) {
	grid[y][x] = tileID;
}
int Level::getNode(int x, int y) {
	return grid[y][x];
}
