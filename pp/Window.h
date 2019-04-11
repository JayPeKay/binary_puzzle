#pragma once
#include <windows.h>
#include <math.h>
#include "conio2.h"

#include "Legend.h"
#include "Board.h"
#include "Info.h"
#include "Cursor.h"

class Window
{
public:
	int width;
	int height;

	Window(int width, int height);
	~Window();

private:
	Legend *legend;
	Board *board;
	Info *info;
	Info *autoInfo;
	Cursor *cursor;

	char* startInput(char *inputText, int limit);
	bool resizeBoard(char *input);
};