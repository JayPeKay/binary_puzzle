#include <windows.h>
#include <time.h>
#include "conio2.h"

#include "Window.h"

int main() {
	SetConsoleOutputCP(437); // ustawienie kodowania
	srand(time(NULL));

	// pobieranie danych do wyÅrodkowania konsoli
	const HWND hwndConsole = GetConsoleWindow();
	const HWND hwndDesktop = GetDesktopWindow();
	RECT desktop;
	GetWindowRect(hwndDesktop, &desktop);

	// pobieranie danych o wielkoÅci czcionki
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFO fontInfo;
	GetCurrentConsoleFont(stdHandle, FALSE, &fontInfo);
	const COORD fontSize = GetConsoleFontSize(stdHandle, fontInfo.nFont);

	// marginesy w pixelach
	const int marginRight = 100;
	const int marginLeft = 100;
	const int marginTop = 100;
	const int marginBot = 100;

	const int widthChar = (desktop.right - marginRight - marginLeft) / fontSize.X; // szerokoÅÄ konsoli w znakach
	const int heightChar = (desktop.bottom - marginTop - marginBot) / fontSize.Y; // wysokoÅÄ konsoli w znakach
	const int width = widthChar * fontSize.X; // szerokoÅÄ konsoli w pixelach
	const int height = heightChar * fontSize.Y; // wysokoÅÄ konsoli w pixelach

	const int x = marginRight; // pozycja x konsoli na ekranie w pixealch
	const int y = marginTop; // pozycja y konsoli na ekranie w pixelach

	MoveWindow(hwndConsole, x, y, width, height, TRUE); // zastosowanie powyÅ¼szych wartoÅci
	settitle("Konrad Sztenderski 171680");

	Window window(widthChar, heightChar);
	return 0;
}