#pragma once
#include <string.h>
#include "conio2.h"

#include "Cursor.h"
#include "posToChar.h"

struct Control {
	char *name;
	char *desc;
};

class Legend {
public:
	int x;
	int y;
	int width;
	int height;

	Legend(int x, int y, int width, Cursor *cursor);
	~Legend();

	void printLegend();

private:
	const char *title = "Binary Puzzle";
	const char *implemented = "Zaimplementowano: a, b, c, d, e, f, g, h, i, j, k, l, m, n, o";
	int legendLength;
	Cursor *cursor;
	Control legend[15] = {
			{"strzalki", "przemieszczanie sie kursorem po polach planszy"},
			{"esc", "wyjscie z programu"},
			{"n", "nowa gra"},
			{"01", "wpisanie cyfry na plansze"},
			{"o", "losowe wypelnianie planszy"},
			{"p", "prosta podpowiedz"},
			{"r", "zmiana rozmiaru planszy"},
			{"k", "proste sprawdzanie mozliwosci ukonczenia gry"},
			{"d", "sprawdzenie reguly (2)"},
			{"a", "automatyczna detekcja konca gry"},
			{"j", "podswietlenie \"jednoznacznych\" pol"},
			{"w", "wypelnienie podswietlonych \"jednoznacznych\" pol"},
			{"s", "zapisanie stanu gry"},
			{"l", "odczytanie stanu gry"},
			{"b", "pelne sprawdzenie i pokazanie przykladowego wypelnienia pol"}
	};
};