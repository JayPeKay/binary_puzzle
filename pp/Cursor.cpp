#include "Cursor.h"

Cursor::Cursor(int x, int y) {
	this->x = x;
	this->y = y;
}

Cursor::~Cursor() {}

void Cursor::moveUp() {
	y--;
}

void Cursor::moveDown() {
	y++;
}

void Cursor::moveRight() {
	x++;
}

void Cursor::moveLeft() {
	x--;
}