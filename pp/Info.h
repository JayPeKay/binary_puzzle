#pragma once
#include <stdlib.h>
#include <string.h>
#include "conio2.h"

class Info {
public:
	int x;
	int y;
	char *lastInfo;

	Info(int x, int y, int width);
	~Info();

	void printInfo(const char *info);
	void clearInfo();

private:
	int width;
	int line = 0;
};