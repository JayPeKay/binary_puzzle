#include "Window.h"

Window::Window(int width, int height) {
	this->width = width;
	this->height = height;

	cursor = new Cursor(0, 0);

	const int legendWidth = width / 2 - 1; // szerokoÅÄ legendy w znakach razem z ramka
	const int legendX = 2; // pozycja legendy x w znakach
	const int legendY = 3; // pozycja legendy y w znakach
	legend = new Legend(legendX, legendY, legendWidth, cursor); // moÅ¼liwoÅÄ przypisania pozycji x, y

	const int infoWidth = legend->width - 2; // szerokoÅÄ podpowiedzi w znakach
	const int infoX = legend->x + 1; // pozycja podpowiedzi x w znakach
	const int infoY = legend->height + legend->y + 1; // pozycja podpowiedzi y w znakach
	info = new Info(infoX, infoY + 1, infoWidth); // moÅ¼liwoÅÄ przypisania pozycji x, y

	const int boardSize = 12; // wielkoÅÄ planszy w iloÅci komÃ³rek
	const int boardX = (legend->x + legend->width + 2) + (width - legend->x - legend->width - 2) / 2 - boardSize * 2 - 2; // pozycja planszy x w znakach
	const int boardY = height / 2 - boardSize; // pozycja planszy y w znakach
	board = new Board(boardX, boardY, boardSize, info, cursor); // moÅ¼liwoÅÄ przypisania pozycji x, y


	gotoxy(infoX, infoY);
	textcolor(WHITE);
	cputs("Podpowiedz:");

	int lastZn = 0;
	int zn = 0;
	do {
		legend->printLegend();
		board->printBoard();
		gotoxy(board->x + 2 + cursor->x * 4, board->y + 1 + cursor->y * 2);

		lastZn = zn;
		zn = getch();

		if (zn >= 'A' && zn <= 'Z')
			zn = zn + ('a' - 'A');
		if (lastZn >= 'A' && lastZn <= 'Z')
			lastZn = lastZn + ('a' - 'A');

		if (lastZn == 'b' && zn != 'b')
			board->clearExample();

		if (zn != 's' && (lastZn == 'k' || zn != 'w'))
			board->clearColors();
		if (zn != 's')
			info->clearInfo();

		if (zn == 0) {
			zn = getch();
			if (zn == 0x48 && cursor->y > 0)
				cursor->moveUp();
			else if (zn == 0x50 && cursor->y + 1 < board->boardSize)
				cursor->moveDown();
			else if (zn == 0x4b && cursor->x > 0)
				cursor->moveLeft();
			else if (zn == 0x4d && cursor->x + 1 < board->boardSize)
				cursor->moveRight();
		}

		switch (zn) {
		case '0':
			board->setEl(cursor->x, cursor->y, '2');
			board->checkEnd();
			break;
		case '1':
			board->setEl(cursor->x, cursor->y, '3');
			board->checkEnd();
			break;
		case 8:
			board->setEl(cursor->x, cursor->y, ' ');
			break;
		case 'n':
			board->setDefaultBoard();
			break;
		case 'o':
			board->randBoard();
			break;
		case 'p':
			board->showPrompt(cursor->x, cursor->y);
			break;
		case 'r':
			while (!resizeBoard(startInput("Podaj rozmiar planszy: ", 2)));
			break;
		case 'k':
			board->checkNoInput();
			break;
		case 'd':
			if (board->ruleTwoOn) {
				board->ruleTwoOn = false;
			}
			else {
				board->ruleTwoOn = true;
			}
			break;
		case 'a':
			if (board->autoOn) {
				board->autoOn = false;
			}
			else {
				board->autoOn = true;
			}
			break;
		case 'j':
			board->findOnlyOneInput();
			break;
		case 'w':
			if (lastZn == 'j' || lastZn == 's')
				board->fillOnlyOneInput();
			break;
		case 's':
			board->saveBoard(startInput("Podaj nazwe pliku do zapisu: ", 20));
			break;
		case 'l':
			board->loadBoard(startInput("Podaj nazwe pliku do odczytania: ", 20));
			break;
		case 'b':
			if (lastZn == 'b')
				board->showExample = true;
			else
				board->fullCheckEnd();
		}
	} while (zn != 27);
}

Window::~Window() {
	delete(board);
	delete(info);
}

char* Window::startInput(char *inputText, int limit) {
	int zn = 0;

	char *res = (char *)malloc(limit + 1);
	int counter = 0;

	gotoxy(1, 1);
	textcolor(DARKGRAY);
	cputs(inputText);
	textcolor(WHITE);

	do {
		if (counter < limit) {
			zn = getch();
			if (zn == 8 && counter != 0) { // backspace
				gotoxy(strlen(inputText) + counter, 1);
				putch(' ');
				gotoxy(strlen(inputText) + counter, 1);
				counter--;
			}
			else if (zn >= 33 && zn <= 126) { // od ! (pierwszy normalny znak bez ' ') do ~ ( ostatni normalny znak)
				gotoxy(strlen(inputText) + counter + 1, 1);
				res[counter] = zn;
				putch(zn);
				counter++;
			}
		}
		else {
			info->clearInfo();
			info->printInfo("Limit znakow wyczerpany - przerwij (ESC) lub zatwierdz (ENTER)");
			gotoxy(strlen(inputText) + counter + 1, 1);
			zn = getch();
			info->clearInfo();
			if (zn == 8 && counter != 0) { // backspace
				gotoxy(strlen(inputText) + counter, 1);
				putch(' ');
				gotoxy(strlen(inputText) + counter, 1);
				counter--;
			}
		}
	} while (zn != 13 && zn != 27); // enter | esc

	gotoxy(1, 1);
	for (int i = 0; i < strlen(inputText) + counter + 1; i++)
		putch(' ');

	if (zn == 13)
		res[counter] = '\0';
	else
		res[0] = '\0';
	return res;
}

bool Window::resizeBoard(char *input) {
	if (input[0] == '\0')
		return true;

	const int minSize = 2;
	const int freeWidth = (board->x > legend->x) ? (width - legend->width - legend->x - 2) : (legend->x);
	const int maxSize = ((freeWidth / 4 > height / 2) ? (height / 2 / 2 * 2) - 2 : (freeWidth / 4 / 2 * 2)) - 4;
	int size = 0;
	int counter = 0;

	while (input[counter] != '\0') {
		if (input[counter] >= '0' && input[counter] <= '9') {
			size += (input[counter++] - '0') * pow(10, strlen(input) - 1 - counter);
		}
		else {
			info->clearInfo();
			info->printInfo("Wielkosc musi byc liczba");
			return false;
		}
	}

	if (size < minSize) {
		char* message = "Minimalna wielkosc musi wynosic ";
		char* res = (char *)malloc(strlen(message) + 2);
		strcpy(res, message);
		res[strlen(message)] = minSize + '0';
		res[strlen(message) + 1] = '\0';

		info->clearInfo();
		info->printInfo(res);
		free(res);
		return false;
	}

	if (size > maxSize) {
		char* message = "Maksymalna wielkosc moze wynosic ";
		char* res;

		if (maxSize > 10) {
			res = (char *)malloc(strlen(message) + 3);
			strcpy(res, message);
			res[strlen(message)] = (maxSize / 10) + '0';
			res[strlen(message) + 1] = (maxSize % 10) + '0';
			res[strlen(message) + 2] = '\0';
		}
		else {
			res = (char *)malloc(strlen(message) + 2);
			strcpy(res, message);
			res[strlen(message)] = maxSize + '0';
			res[strlen(message) + 1] = '\0';
		}

		info->clearInfo();
		info->printInfo(res);
		free(res);
		return false;
	}

	if (size % 2 == 1) {
		info->clearInfo();
		info->printInfo("Wielkosc musi byc parzysta");
		return false;
	}

	delete board;

	const int newBoardX = (legend->x + legend->width + 2) + (width - legend->x - legend->width - 2) / 2 - size * 2 - 2;
	const int newBoardY = height / 2 - size;
	board = new Board(newBoardX, newBoardY, size, info, cursor);
	cursor->x = 0;
	cursor->y = 0;
	board->importFromFile();

	return true;
}