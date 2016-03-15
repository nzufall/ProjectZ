#include "Projectile.h"
#include <cmath>
Projectile::Projectile(int x, int y, int dir) {
	originX = x;
	originY = y;
	this->x = originX;
	this->y = originY;
	direction = dir;
	time = 0;
}

bool Projectile::killProjectile() {
	double distance = sqrt(abs(pow((x - originX), 2) + (pow((y - originY), 2))));
	if (time > 120) return true;
	if (distance > 1000) return true;
	else return false;
}

void Projectile::update() {
	x += (30 * direction);
	time++;
}





