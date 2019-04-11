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
	putch(0xc9); // â
	for (int i = 0; i < width - 2; i++)
		putch(0xcd); // â
	putch(0xbb); // â

	for (int i = 0; i < legendLength; i++) {
		gotoxy(x, y + i + 2);
		putch(0xba); // â
		cputs(legend[i].name);
		cputs(" -");
		gotoxy(x + width - strlen(legend[i].desc) - 1, y + i + 2);
		cputs(legend[i].desc);
		putch(0xba); // â
	}

	gotoxy(x, y + legendLength + 2);
	putch(0xcc); // â 
	for (int i = 0; i < width - 2; i++)
		putch(0xcd); // â
	putch(0xb9); // â£

	gotoxy(x, y + legendLength + 3);
	putch(0xba); // â
	cputs(implemented);
	gotoxy(x + width - 1, y + legendLength + 3);
	putch(0xba); // â

	gotoxy(x, y + legendLength + 4);
	putch(0xc8); // â
	for (int i = 0; i < width - 2; i++)
		putch(0xcd); // â
	putch(0xbc); // â

	gotoxy(x + width - 6, y + legendLength + 5);
	cputs("     ");
	gotoxy(x + width - 6, y + legendLength + 5);
	cputs("x: ");
	cputs(posToChar(cursor->x)); // 2 znaki

	gotoxy(x + width - 6, y + legendLength + 6);
	cputs("     ");
	gotoxy(x + width - 6, y + legendLength + 6);
	cputs("y: ");
	cputs(posToChar(cursor->y)); // 2 znaki
}