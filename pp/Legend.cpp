#include "Legend.h"

Legend::Legend(int x, int y, int width, Cursor *cursor) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->cursor = cursor;

	legendLength = sizeof(legend) / sizeof(Control);
	height = legendLength + 7;
}

Legend::~Legend() {}

void Legend::printLegend() {
	textcolor(LIGHTCYAN);
	gotoxy(x + width / 2 - strlen(title) / 2, y);
	cputs(title);

	textcolor(WHITE);

	gotoxy(x, y + 1);
	putch(0xc9); 
	for (int i = 0; i < width - 2; i++)
		putch(0xcd); 
	putch(0xbb); 

	for (int i = 0; i < legendLength; i++) {
		gotoxy(x, y + i + 2);
		putch(0xba); 
		cputs(legend[i].name);
		cputs(" -");
		gotoxy(x + width - strlen(legend[i].desc) - 1, y + i + 2);
		cputs(legend[i].desc);
		putch(0xba); 
	}

	gotoxy(x, y + legendLength + 2);
	putch(0xcc); 
	for (int i = 0; i < width - 2; i++)
		putch(0xcd); 
	putch(0xb9); 

	gotoxy(x, y + legendLength + 3);
	putch(0xba); 
	cputs(implemented);
	gotoxy(x + width - 1, y + legendLength + 3);
	putch(0xba); 

	gotoxy(x, y + legendLength + 4);
	putch(0xc8); 
	for (int i = 0; i < width - 2; i++)
		putch(0xcd); 
	putch(0xbc); 

	gotoxy(x + width - 6, y + legendLength + 5);
	cputs("     ");
	gotoxy(x + width - 6, y + legendLength + 5);
	cputs("x: ");
	cputs(posToChar(cursor->x)); 

	gotoxy(x + width - 6, y + legendLength + 6);
	cputs("     ");
	gotoxy(x + width - 6, y + legendLength + 6);
	cputs("y: ");
	cputs(posToChar(cursor->y)); 
}