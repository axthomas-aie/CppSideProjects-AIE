
#include "WindowSetup.h"


CHAR_INFO consoleBuffer[WIN_WIDTH * WIN_HEIGHT];
COORD charBufferSize = { WIN_WIDTH, WIN_HEIGHT };
COORD charPosition = { 0, 0 };
SMALL_RECT consoleWriteArea{ 0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1 };

CONSOLE_CURSOR_INFO cursorInfo;

HANDLE hstdin;
HANDLE hstdout;



void WindowSetup(char title[])
{

	//Window size coordinates, must start at 0
	SMALL_RECT winSize = { 0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1 };

	//COORD struct for specifying screen buffer simensions
	COORD bufferSize = { WIN_WIDTH, WIN_HEIGHT };

	//Get window handles
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle(title);

	//Set screen buffer size
	SetConsoleScreenBufferSize(hstdout, bufferSize);

	//Set window size
	SetConsoleWindowInfo(hstdout, TRUE, &winSize);

	//Hide cursor
	GetConsoleCursorInfo(hstdout, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hstdout, &cursorInfo);
}