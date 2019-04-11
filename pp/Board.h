#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "Error.h"
#include "Info.h"
#include "Field.h"
#include "Cursor.h"
#include "posToChar.h"

class Board
{

public:
	int boardSize;
	int x;
	int y;
	bool oneInputChecked = false;
	bool oneInputFilled = false;
	bool noInputChecked = false;
	bool ruleTwoOn = false;
	bool autoOn = false;
	bool showExample = false;

	Board(int x, int y, int boardSize, Info *info, Cursor *cursor);
	~Board();

	bool setEl(int x, int y, char value);
	char getEl(int x, int y);
	Field *getField(int x, int y);
	void setDefaultBoard();
	void clearBoard();
	void randBoard();
	void showPrompt(int x, int y);
	void printBoard();
	void importFromFile();
	bool checkNoInput(bool onlyCheck = false);
	void clearColors();
	void printNumbers();
	void checkEnd();
	void findOnlyOneInput();
	void fillOnlyOneInput();
	void saveBoard(char *fileName);
	void loadBoard(char *fileName);
	void fullCheckEnd();
	void clearExample();

private:
	Field ***board;
	Info *info;
	Info *autoInfo;
	const char *autoString;
	Cursor *cursor;

	Error isImpossible(int x, int y, char value);
};