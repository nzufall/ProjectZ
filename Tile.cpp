#include "Tile.h"

Tile::Tile(bool x, int y, string z, int h, int w) {
	collides = x;
	tileID = y;
	name = z;
	height = h;
	width = w;
}
