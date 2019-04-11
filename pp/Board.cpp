#include "Board.h"

Board::Board(int x, int y, int boardSize, Info *info, Cursor *cursor) {
	this->x = x;
	this->y = y;
	this->boardSize = boardSize;
	this->info = info;
	this->cursor = cursor;

	autoString = "Tryb automatyczny wlaczony";
	const int autoInfoWidth = strlen(autoString);
	const int autoInfoX = x + boardSize * 2 - strlen(autoString) / 2;
	const int autoInfoY = y - 2;
	autoInfo = new Info(autoInfoX, autoInfoY, autoInfoWidth);
	autoOn = false;

	board = (Field ***)malloc(boardSize * sizeof(*board));

	for (int i = 0; i < boardSize; i++) {
		board[i] = (Field **)malloc(boardSize * sizeof(**board));
	}

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = new Field();
		}
	}
}

Board::~Board() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++)
			delete board[i][j];
		free(board[i]);
	}
	free(board);

	for (int i = 0; i < boardSize * 2 + 3; i++) {
		gotoxy(x - 2, y - 1 + i);
		for (int j = 0; j < boardSize * 4 + 5; j++) {
			putch(' ');
		}
	}

	delete autoInfo;
}

bool Board::setEl(int x, int y, char value) {
	if (value == ' ' && getEl(x, y) != '0' && getEl(x, y) != '1') {
		board[y][x]->value = value;
		return true;
	}
	else {
		Error error = isImpossible(x, y, value);
		if (error == false) {
			board[y][x]->value = value;
			return true;
		}
	}

	return false;
}

char Board::getEl(int x, int y) {
	return board[y][x]->value;
}

Field *Board::getField(int x, int y) {
	return board[y][x];
}

void Board::setDefaultBoard() {
	if (boardSize == 12) {
		char defaultBoard[12][13] = {
				"   1       1",
				" 0      1   ",
				"     0      ",
				" 0 1 0 0 0 0",
				"1 1    0  1 ",
				"     0  1   ",
				"  11    1   ",
				"0     0    0",
				" 1  1     1 ",
				"  0  0 0    ",
				"  0  00    0",
				"   1  0  1  "
		};

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				board[i][j]->value = defaultBoard[i][j];
	}
	else {
		info->clearInfo();
		info->printInfo("Nowa gra jest zdefiniowana tylko dla planszy 12x12.");
	}
}

Error Board::isImpossible(int x, int y, char value) {
	Error error;

	if (getEl(x, y) == '0' || getEl(x, y) == '1')
		error.unmodifiableField = true;

	
	if (y - 1 > 0 && getEl(x, y - 2) != ' ' && getEl(x, y - 1) != ' ')
		if (getEl(x, y - 2) % 2 == getEl(x, y - 1) % 2 && getEl(x, y - 1) % 2 == value % 2) {
			error.ruleOne = true;
			error.ruleOneIsColumn = true;
		}
	if (y > 0 && y + 1 < boardSize && getEl(x, y - 1) != ' ' && getEl(x, y + 1) != ' ')
		if (getEl(x, y - 1) % 2 == getEl(x, y + 1) % 2 && getEl(x, y + 1) % 2 == value % 2) {
			error.ruleOne = true;
			error.ruleOneIsColumn = true;
		}
	if (y + 2 < boardSize && getEl(x, y + 1) != ' ' && getEl(x, y + 2) != ' ')
		if (getEl(x, y + 1) % 2 == getEl(x, y + 2) % 2 && getEl(x, y + 2) % 2 == value % 2) {
			error.ruleOne = true;
			error.ruleOneIsColumn = true;
		}
	if (x - 1 > 0 && getEl(x - 2, y) != ' ' && getEl(x - 1, y) != ' ')
		if (getEl(x - 2, y) % 2 == getEl(x - 1, y) % 2 && getEl(x - 1, y) % 2 == value % 2) {
			error.ruleOne = true;
			error.ruleOneIsColumn = false;
		}
	if (x > 0 && x + 1 < boardSize && getEl(x - 1, y) != ' ' && getEl(x + 1, y) != ' ')
		if (getEl(x - 1, y) % 2 == getEl(x + 1, y) % 2 && getEl(x + 1, y) % 2 == value % 2) {
			error.ruleOne = true;
			error.ruleOneIsColumn = false;
		}
	if (x + 2 < boardSize && getEl(x + 1, y) != ' ' && getEl(x + 2, y) != ' ')
		if (getEl(x + 1, y) % 2 == getEl(x + 2, y) % 2 && getEl(x + 2, y) % 2 == value % 2) {
			error.ruleOne = true;
			error.ruleOneIsColumn = false;
		}

	
	int count = 0;
	for (int i = 0; i < boardSize; i++) {
		if (getEl(x, i) != ' ' && getEl(x, i) % 2 == value % 2)
			count++;
	}
	if (count >= boardSize / 2) {
		error.ruleTwo = true;
		error.ruleTwoIsColumn = true;
	}

	count = 0;
	for (int i = 0; i < boardSize; i++) {
		if (getEl(i, y) != ' ' && getEl(i, y) % 2 == value % 2)
			count++;
	}
	if (count >= boardSize / 2) {
		error.ruleTwo = true;
		error.ruleTwoIsColumn = false;
	}

	
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (i == y)
				break;
			if (getEl(j, i) == ' ')
				break;

			if (x == j) {
				if (getEl(j, i) % 2 != value % 2)
					break;
			}
			else if (getEl(j, y) != ' ') {
				if (getEl(j, i) % 2 != getEl(j, y) % 2)
					break;
			}
			else
				break;

			if (j + 1 == boardSize) {
				error.ruleThree = true;
				error.row = i;
			}
		}
	}

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (i == x)
				break;
			if (getEl(i, j) == ' ')
				break;

			if (y == j) {
				if (getEl(i, j) % 2 != value % 2)
					break;
			}
			else if (getEl(x, j) != ' ') {
				if (getEl(i, j) % 2 != getEl(x, j) % 2)
					break;
			}
			else
				break;

			if (j + 1 == boardSize) {
				error.ruleThree = true;
				error.column = i;
			}
		}
	}

	return error;
}

void Board::clearBoard() {
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			board[i][j]->value = ' ';
}

void Board::randBoard() {
	clearBoard();

	const int maxTryNumber = boardSize * boardSize * boardSize;
	const int minFieldNumber = 20;
	const int maxFieldNumber = 50;

	const int fieldNumber = (rand() % (maxFieldNumber - minFieldNumber) + minFieldNumber) * boardSize * boardSize / 100;

	int x = 0;
	int y = 0;
	int value = 0;
	int fieldCount = 0;
	int count = 0;

	do {
		count++;
		x = rand() % boardSize;
		y = rand() % boardSize;
		value = rand() % 2;

		if (setEl(x, y, value + '0'))
			fieldCount++;
	} while (fieldCount < fieldNumber && count < maxTryNumber);
}

void Board::showPrompt(int x, int y) {
	Error error0 = isImpossible(x, y, '2');
	Error error1 = isImpossible(x, y, '3');

	if (error0.unmodifiableField) {
		info->printInfo("Pole jest niemodyfikowalne.");
		return;
	}

	if (getEl(x, y) != '2' && error0 == true) {
		info->printInfo("Nie mozna wpisac 0 poniewaz:");
		if (error0.ruleOne)
			if (error0.ruleOneIsColumn)
				info->printInfo("-nie moga wystepowac w tej samej kolumnie obok siebie wiecej niz dwa 0");
			else
				info->printInfo("-nie moga wystepowac w tym samym wierszu obok siebie wiecej niz dwa 0");

		if (error0.ruleTwo)
			if (error0.ruleTwoIsColumn)
				info->printInfo("-nie moze byc wiecej 0 niz 1 w tej samej kolumnie");
			else
				info->printInfo("-nie moze byc wiecej 0 niz 1 w tym samym wierszu");

		if (error0.ruleThree) {
			if (error0.row > -1) {
				char* pos = posToChar(error0.row);
				char* message = "-wiersz bedzie identyczny z wierszem numer ";
				char* res = (char *)malloc(strlen(message) + strlen(pos) + 4);
				strcpy(res, message);
				strcat(res, pos);

				info->printInfo(res);
				free(res);
			}
			if (error0.column > -1) {
				char* pos = posToChar(error0.column);
				char* message = "-kolumna bedzie identyczny z kolumna numer ";
				char* res = (char *)malloc(strlen(message) + strlen(pos) + 4);
				strcpy(res, message);
				strcat(res, pos);

				info->printInfo(res);
				free(res);
			}
		}
	}
	else
		info->printInfo("Mozna wpisac 0.");

	if (getEl(x, y) != '3' && error1 == true) {
		info->printInfo("Nie mozna wpisac 1 poniewaz:");
		if (error1.ruleOne)
			if (error1.ruleOneIsColumn)
				info->printInfo("-nie moga wystepowac w tej samej kolumnie obok siebie wiecej niz dwie 1");
			else
				info->printInfo("-nie moga wystepowac w tym samym wierszu obok siebie wiecej niz dwie 1");

		if (error1.ruleTwo)
			if (error1.ruleTwoIsColumn)
				info->printInfo("-nie moze byc wiecej 1 niz 0 w tej samej kolumnie");
			else
				info->printInfo("-nie moze byc wiecej 1 niz 0 w tym samym wierszu");

		if (error1.ruleThree) {
			if (error1.row > -1) {
				char* pos = posToChar(error1.row);
				char* message = "-wiersz bedzie identyczny z wierszem numer ";
				char* res = (char *)malloc(strlen(message) + strlen(pos) + 4);
				strcpy(res, message);
				strcat(res, pos);

				info->printInfo(res);
				free(res);
			}
			if (error1.column > -1) {
				char* pos = posToChar(error1.column);
				char* message = "-kolumna bedzie identyczny z kolumna numer ";
				char* res = (char *)malloc(strlen(message) + strlen(pos) + 4);
				strcpy(res, message);
				strcat(res, pos);

				info->printInfo(res);
				free(res);
			}
		}
	}
	else
		info->printInfo("Mozna wpisac 1.");
}

void Board::printBoard() {
	autoInfo->clearInfo();
	if (autoOn) {
		textcolor(LIGHTMAGENTA);
		autoInfo->printInfo(autoString);
		textcolor(WHITE);
	}

	printNumbers();

	for (int i = 0; i < boardSize; i++) {
		if (i == 0) {
			gotoxy(x, y);
			for (int j = 0; j < boardSize; j++) {
				textcolor(getField(j, i)->borderColor);

				if (j == 0)
					putch(0xc9);
				putch(0xcd);
				putch(0xcd);
				putch(0xcd);
				if (j + 1 == boardSize)
					putch(0xbb);
				else {
					if (getField(j + 1, i)->borderColor < getField(j, i)->borderColor)
						textcolor(getField(j + 1, i)->borderColor);
					else
						textcolor(getField(j, i)->borderColor);
					putch(0xd1);
				}
			}
		}
		else if (i + 1 == boardSize) {
			gotoxy(x, y + boardSize * 2);
			for (int j = 0; j < boardSize; j++) {
				textcolor(getField(j, i)->borderColor);
				
				if(j == 0)
					putch(0xc8);
				putch(0xcd);
				putch(0xcd);
				putch(0xcd);

				if (j + 1 == boardSize)
					putch(0xbc);
				else {
					if (getField(j + 1, i)->borderColor < getField(j, i)->borderColor)
						textcolor(getField(j + 1, i)->borderColor);
					else
						textcolor(getField(j, i)->borderColor);
					putch(0xcf);
				}
			}
		}

		gotoxy(x, y + 1 + i * 2);

		for (int j = 0; j < boardSize; j++) {
			textcolor(getField(j, i)->borderColor);

			if (j == 0)
				putch(0xba);
			putch(' ');
			if (getEl(j, i) == '2') {
				textcolor(LIGHTBLUE);
				putch('0');
			}
			else if (getEl(j, i) == '3') {
				textcolor(LIGHTBLUE);
				putch('1');
			}
			else {
				if (showExample) {
					if (getEl(j, i) == '4') {
						textcolor(GREEN);
						putch('0');
					}
					else if (getEl(j, i) == '5') {
						textcolor(GREEN);
						putch('1');
					}
					else {
						textcolor(WHITE);
						putch(getEl(j, i));
					}
				}
				else {
					if (getEl(j, i) == '4') {
						putch(' ');
					}
					else if (getEl(j, i) == '5') {
						putch(' ');
					}
					else {
						textcolor(WHITE);
						putch(getEl(j, i));
					}
				}
			}

			putch(' ');
			textcolor(getField(j, i)->borderColor);
			if (j + 1 == boardSize)
				putch(0xba); 
			else {
				if (getField(j + 1, i)->borderColor < getField(j, i)->borderColor)
					textcolor(getField(j + 1, i)->borderColor);
				else
					textcolor(getField(j, i)->borderColor);
				putch(0xb3); 
			}
		}

		gotoxy(x, y + 1 + i * 2 + 1);

		if (i + 1 != boardSize) {
			for (int j = 0; j < boardSize; j++) {
				if (getField(j, i + 1)->borderColor < getField(j, i)->borderColor)
					textcolor(getField(j, i + 1)->borderColor);
				else
					textcolor(getField(j, i)->borderColor);

				if (j == 0)
					putch(0xc7); 
				putch(0xc4); 
				putch(0xc4); 
				putch(0xc4); 
				if (j + 1 == boardSize)
					putch(0xb6); 
				else {
					if (getField(j + 1, i)->borderColor < getField(j, i)->borderColor)
						textcolor(getField(j + 1, i)->borderColor);
					else if (getField(j, i + 1)->borderColor < getField(j, i)->borderColor)
						textcolor(getField(j, i + 1)->borderColor);
					else if (getField(j + 1, i + 1)->borderColor < getField(j, i)->borderColor)
						textcolor(getField(j + 1, i + 1)->borderColor);
					else
						textcolor(getField(j, i)->borderColor);
					putch(0xc5); 
				}
			}
		}
	}
	textcolor(WHITE);
}

void Board::importFromFile() {
	const char *fileNameBegin = "board";
	char *num = posToChar(boardSize);

	char *fileName = (char *)malloc(strlen(fileNameBegin) + strlen(num) + 5);
	strcpy(fileName, fileNameBegin);
	strcat(fileName, num);
	strcat(fileName, ".txt");

	clearBoard();

	FILE *f;
	f = fopen(fileName, "r");
	if (f == NULL)
		randBoard();
	else {
		int x = 0, y = 0;
		char zn;
		while ((zn = fgetc(f)) != EOF) {
			if (zn == '\n') {
				x = 0;
				y++;
			}
			else {
				setEl(x, y, zn);
				x++;
			}
		}

		fclose(f);
	}

	free(fileName);
}

bool Board::checkNoInput(bool onlyCheck) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (getEl(j, i) == ' ') {
				if (isImpossible(j, i, '0') == true && isImpossible(j, i, '1') == true) {
					if (onlyCheck)
						return true;
					else
						getField(j, i)->borderColor = LIGHTRED;
				}
			}
		}
	}

	if (onlyCheck)
		return false;
	else {
		noInputChecked = true;
		return false;
	}
}

void Board::clearColors() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			getField(j, i)->setDefaultColor();
		}
	}

	oneInputChecked = false;
	noInputChecked = false;
}

void Board::printNumbers() {
	if (ruleTwoOn) {
		int counter0 = 0;
		int counter1 = 0;

		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (getEl(i, j) != ' ') {
					if (showExample) {
						if (getEl(i, j) % 2 == 0)
							counter0++;
						else
							counter1++;
					}
					else if (getEl(i, j) != '4' && getEl(i, j) != '5') {
						if (getEl(i, j) % 2 == 0)
							counter0++;
						else
							counter1++;
					}
				}
			}

			if (counter0 > 9)
				gotoxy(x + 1 + i * 4, y - 1);
			else
				gotoxy(x + 2 + i * 4, y - 1);
			cputs(posToChar(counter0));

			if (counter1 > 9)
				gotoxy(x + 1 + i * 4, y + boardSize * 2 + 1);
			else
				gotoxy(x + 2 + i * 4, y + boardSize * 2 + 1);
			cputs(posToChar(counter1));

			counter0 = 0;
			counter1 = 0;
		}

		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (getEl(j, i) != ' ') {
					if (showExample) {
						if (getEl(j, i) % 2 == 0)
							counter0++;
						else
							counter1++;
					}
					else if (getEl(j, i) != '4' && getEl(j, i) != '5') {
						if (getEl(j, i) % 2 == 0)
							counter0++;
						else
							counter1++;
					}
				}
			}

			if (counter0 > 9)
				gotoxy(x - 3, y + 1 + i * 2);
			else
				gotoxy(x - 2, y + 1 + i * 2);
			cputs(posToChar(counter0));
			gotoxy(x + boardSize * 4 + 2, y + 1 + i * 2);
			cputs(posToChar(counter1));

			counter0 = 0;
			counter1 = 0;
		}
	}
	else {
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				gotoxy(x + 1 + i * 4, y - 1);
				cputs("  ");
				gotoxy(x + 1 + i * 4, y + boardSize * 2 + 1);
				cputs("  ");

				gotoxy(x - 3, y + 1 + i * 2);
				cputs("  ");
				gotoxy(x + boardSize * 4 + 2, y + 1 + i * 2);
				cputs("  ");
			}
		}
	}
}

void Board::checkEnd() {
	if (autoOn) {
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (getEl(j, i) == ' ') {
					if (isImpossible(j, i, '0') == true && isImpossible(j, i, '1') == true) {
						info->printInfo("Nie mozna ukonczyc gry");
						return;
					}
				}
			}
		}
	}
}

void Board::findOnlyOneInput() {
	Error error0;
	Error error1;

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (getEl(j, i) == ' ') {
				error0 = isImpossible(j, i, '0');
				error1 = isImpossible(j, i, '1');

				if ((error0 == true && error1 == false) || (error0 == false && error1 == true)) {
					getField(j, i)->borderColor = LIGHTGREEN;
				}
			}
		}
	}

	oneInputChecked = true;
	oneInputFilled = false;
}

void Board::fillOnlyOneInput() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (getField(j, i)->borderColor == LIGHTGREEN) {
				if (!setEl(j, i, '2') && !setEl(j, i, '3'))
					getField(j, i)->borderColor = LIGHTRED;
			}
		}
	}

	oneInputFilled = true;
}

void Board::saveBoard(char *fileName) {
	if (fileName[0] != '\0') {
		Field *field;
		FILE *f = fopen(fileName, "w");
		if (f != NULL) {
			for (int i = 0; i < boardSize; i++) {
				for (int j = 0; j < boardSize; j++) {
					field = getField(j, i);
					if (field->borderColor != field->defaultBorderColor && field->value != ' ')
						fputc(' ', f);
					else
						fputc(getEl(j, i), f);
				}

				fputc('\n', f);
			}
			if (oneInputChecked)
				fputc('j', f);
			if (oneInputFilled)
				fputc('w', f);
			if (noInputChecked)
				fputc('k', f);
			if (ruleTwoOn)
				fputc('d', f);
			if (autoOn)
				fputc('a', f);
			fputc('\n', f);
			fprintf(f, "%d", cursor->x);
			fputc('\n', f);
			fprintf(f, "%d", cursor->y);
			if (info->lastInfo != NULL)
				fprintf(f, "%s", info->lastInfo);

			fclose(f);

			info->clearInfo();
			info->printInfo("Pomyslnie zapisano dane do pliku:");
			info->printInfo(fileName);
		}
		else {
			info->clearInfo();
			info->printInfo("Nie udalo sie otworzyc pliku:");
			info->printInfo(fileName);
		}
	}
}

void Board::loadBoard(char *fileName) {
	if (fileName[0] != '\0') {
		Field *field;
		FILE *f = fopen(fileName, "r");

		if (f != NULL) {
			char modes;
			int counter = 0;

			while (fgetc(f) != '\n')
				counter++;
			fseek(f, 0, 0);

			if (counter == boardSize) {
				clearBoard();

				for (int i = 0; i < boardSize; i++) {
					for (int j = 0; j < boardSize; j++) {
						setEl(j, i, fgetc(f));
					}

					fgetc(f);
				}

				while ((modes = fgetc(f)) != EOF && modes != '\n') {
					if (modes == 'k')
						checkNoInput();
					else if (modes == 'j')
						findOnlyOneInput();
					else if (modes == 'w')
						fillOnlyOneInput();
					else if (modes == 'd')
						ruleTwoOn = true;
					else if (modes == 'a')
						autoOn = true;
				}

				int pos = 0;
				fscanf(f, "%d", &pos);
				cursor->x = pos;
				fscanf(f, "%d", &pos);
				cursor->y = pos;

				fpos_t currPos;
				fpos_t endPos;
				int length;

				fgetpos(f, &currPos);
				fseek(f, 0, SEEK_END);
				fgetpos(f, &endPos);
				fsetpos(f, &currPos);

				length = endPos - currPos;
				char *inf = (char *)malloc(length + 1);

				for (int i = 0; i < length; i++)
					inf[i] = fgetc(f);
				inf[length] = '\0';

				info->clearInfo();
				info->printInfo(inf);
				free(inf);

				fclose(f);
			}
			else if (counter > boardSize) {
				info->clearInfo();
				info->printInfo("Plansza ktora chcesz zaladowac jest za duza.");
			}
			else {
				info->clearInfo();
				info->printInfo("Plansza ktora chcesz zaladowac jest za mala.");
			}
		}
		else {
			info->clearInfo();
			info->printInfo("Nie udalo sie otworzyc pliku:");
			info->printInfo(fileName);
		}
	}
}

void Board::fullCheckEnd() {
	Error error0;
	Error error1;
	bool lastOneInput = true;
	bool noInput = false;
	int stage = 0;
	int lastCorrectStage = 0;
	bool *stages = (bool *)calloc(boardSize*boardSize, sizeof(bool));

	while (true) {
		noInput = checkNoInput(true);
		if (lastOneInput && !noInput) {
			lastOneInput = false;
			for (int i = 0; i < boardSize; i++) {
				for (int j = 0; j < boardSize; j++) {
					if (getEl(j, i) == ' ') {
						error0 = isImpossible(j, i, '0');
						error1 = isImpossible(j, i, '1');

						if (error0 == true && error1 == false) {
							getField(j, i)->value = '5';
							lastOneInput = true;
						}
						else if (error0 == false && error1 == true) {
							getField(j, i)->value = '4';
							lastOneInput = true;
						}
					}
				}
			}
		}
		else {
			if (noInput && stage > 0) {
				bool test = stages[lastCorrectStage - 1];
				if (stages[lastCorrectStage - 1]) {
					for (int i = lastCorrectStage - 1; i >= 0; i--) {
						if (!stages[i]) {
							stages[i] = true;
							break;
						}
						else
							stages[i] = false;
						if (i == 0) {
							info->clearInfo();
							info->printInfo("Nie ma rozwiazania");
							return;
						}
					}
				}
				clearExample();
				stage = 0;
				lastOneInput = true;
			}
			else if (noInput) {
				info->clearInfo();
				info->printInfo("Nie ma rozwiazania");
				return;
			}
			else {
				for (int i = 0; i < boardSize; i++) {
					for (int j = 0; j < boardSize; j++) {
						if (i + 1 == boardSize && j + 1 == boardSize) {
							info->clearInfo();
							info->printInfo("Znaleziono przykladowe rozwiazanie - sprawdz (b)");
							return;
						}

						if (getField(j, i)->value == ' ') {
							if (stage + 1 == lastCorrectStage) {
								getField(j, i)->value = '5';
								stages[stage] = true;
							}
							else {
								if (stages[stage])
									getField(j, i)->value = '5';
								else
									getField(j, i)->value = '4';

								if (stage == lastCorrectStage)
									lastCorrectStage++;
							}
							stage++;

							lastOneInput = true;
							i = boardSize;
							break;
						}
					}
				}
			}
		}
	}



	/* inna wersja algorytmu sprawdzajacego
	while(true) {
			for(int i = 0; i < boardSize; i++) {
					for(int j = 0; j < boardSize; j++) {
							if(getField(j, i)->value == ' ') {
									if(stages[stage]) {
											getField(j, i)->value = '5';
											stage++;
									} else {
											error0 = isImpossible(j, i, '0');
											error1 = isImpossible(j, i, '1');

											if(error0 == false) {
													getField(j, i)->value = '4';
													stages[stage] = false;
													stage++;
											} else if(error1 == false) {
													getField(j, i)->value = '5';
													stages[stage] = true;
													stage++;
											} else if(error0 == true && error1 == true) {
													for(int k = stage - 1; k >= 0; k--) {
															if(stages[k]) {
																	stages[k] = false;
															} else {
																	stages[k] = true;
																	break;
															}
													}
													clearExample();
													stage = 0;
													i = boardSize;
													break;
											}
									}
							}

							if((i + 1 == boardSize) && (j + 1 == boardSize)) {
									info->clearInfo();
									info->printInfo("test");
									return;
							}
					}
			}
	}*/
}

void Board::clearExample() {
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (getField(j, i)->value == '4' || getField(j, i)->value == '5')
				getField(j, i)->value = ' ';

	showExample = false;
}