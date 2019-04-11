#pragma once
#include "conio2.h"

class Field {
public:
	const int defaultBorderColor = WHITE;
	int borderColor = WHITE;
	char value = ' ';

	Field();
	~Field();

	void setDefaultColor();

private:

};