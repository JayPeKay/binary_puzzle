#pragma once

class Cursor {
public:
	int x;
	int y;

	Cursor(int x, int y);
	~Cursor();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

private:

};