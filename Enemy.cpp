#include "Enemy.h"

Enemy::Enemy() {
	health = 100;
}
void Enemy::update(int pX, int pY) {
	if (pX > x) {
		x += 2;
	}
	if (pY > y) {
		y += 2;
	}
	if (pX < x) {
		x -= 2;
	}
	if (pY < y) {
		y -= 2;
	}
}