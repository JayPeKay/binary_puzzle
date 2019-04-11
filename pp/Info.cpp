#include "Info.h"

Info::Info(int x, int y, int width) {
	this->x = x;
	this->y = y;
	this->width = width;
}

Info::~Info() {
	clearInfo();
}

void Info::printInfo(const char *info) {
	char *temp = (char *)malloc(strlen(info) + 2); 
	int tempCounter = 0;
	int infoLength = strlen(info);
	int counter = 0;

	if (strlen(info) > width) {
		while (counter < infoLength) {
			gotoxy(x, y + line);

			if (infoLength - counter > width) {
				for (int i = 0; i < width; i++) {
					if (info[counter] == '\n') {
						counter++;
						break;
					}

					putch(info[counter]);
					counter++;
				}
			}
			else {
				for (; counter < infoLength; counter++) {
					if (info[counter] == '\n') {
						counter++;
						break;
					}

					putch(info[counter]);
				}

				if (info[counter - 1] != '\n') {
					line++;
					break;
				}
			}

			if (info[counter] == '\n')
				counter++;
			if (info[counter] != ' ' && info[counter - 1] != ' ' && info[counter - 1] != '\n') {
				int lastCount = counter;
				while (info[--counter] != ' ');

				gotoxy(x + width - (lastCount - counter), y + line);
				for (int i = 0; i < lastCount - counter; i++)
					putch(' ');
				counter++;
			}
			if (info[counter] == ' ')
				counter++;

			line++;
		}
	}
	else {
		while (counter < infoLength) {
			gotoxy(x, y + line);

			for (; counter < infoLength; counter++) {
				if (info[counter] == '\n') {
					counter++;
					break;
				}

				putch(info[counter]);
			}

			line++;
		}
	}

	strcpy(temp, info);
	temp[infoLength] = '\n';
	temp[infoLength + 1] = '\0';

	if (lastInfo != NULL) {
		int len = strlen(lastInfo);
		char *tempLastInfo;

		tempLastInfo = (char *)malloc(len + 1);
		strcpy(tempLastInfo, lastInfo);
		free(lastInfo);
		lastInfo = NULL;

		lastInfo = (char *)malloc(len + strlen(temp) + 1);
		strcpy(lastInfo, tempLastInfo);
		strcat(lastInfo, temp);
	}
	else {
		lastInfo = (char *)malloc(strlen(temp) + 1);
		strcpy(lastInfo, temp);
	}
	int test = 0;
}

void Info::clearInfo() {
	for (int i = 0; i < line; i++) {
		gotoxy(x, y + i);
		for (int j = 0; j < width; j++)
			putch(' ');
	}

	line = 0;
	free(lastInfo);
	lastInfo = NULL;
}