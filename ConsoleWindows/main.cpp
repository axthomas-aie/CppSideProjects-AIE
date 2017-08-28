

#include <windows.h>
#include <iostream>
#include <time.h>



struct vec2
{
	int x;
	int y;
};





DWORD getInput(INPUT_RECORD **eventBuffer);
//Returns the distance between two points
float dist(int x1, int y1, int x2, int y2);

void simulate();
void renderWindow();

void rain(int chance);


// ---------- FANCY CONSOLE STUFF ---------- //
vec2 lastpos{ 0, 0 };

const int WIN_WIDTH = 100;
const int WIN_HEIGHT = 50;
const int MAP_HEIGHT = WIN_HEIGHT - 1;

//Each CHAR_INFO contains data for a single character: its ASCII char and color
CHAR_INFO consoleBuffer[WIN_WIDTH * WIN_HEIGHT];
COORD charBufferSize = { WIN_WIDTH, WIN_HEIGHT };
COORD charPosition = { 0, 0 };
SMALL_RECT consoleWriteArea{ 0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1 };

HANDLE hstdin;
HANDLE hstdout;

INPUT_RECORD* eventBuffer;
DWORD numEventsRead;
// ----------------------------------------- //

int framePause = 100;

int rainChance = 50;

vec2 mouse{ 0, 0 };
bool left = false;
bool right = false;
bool up = false;
bool down = false;
bool lclick = false;
bool rclick = false;







//Fancy console stuff learned/copied from:
//http://cecilsunkure.blogspot.com/2011/11/windows-console-game-setting-up-window.html


int main()
{
	srand(time(NULL));


	//Window size coordinates, must start at 0
	SMALL_RECT winSize = { 0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1 };

	//COORD struct for specifying screen buffer simensions
	COORD bufferSize = { WIN_WIDTH, WIN_HEIGHT };

	//Get window handles
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle("Mouse Painter");

	//Set screen buffer size
	SetConsoleScreenBufferSize(hstdout, bufferSize);

	//Set window size
	SetConsoleWindowInfo(hstdout, TRUE, &winSize);










	while (true)
	{
		numEventsRead = getInput(&eventBuffer);

		if (numEventsRead)
		{
			for (int i = 0; i < numEventsRead; ++i)
			{
				switch (eventBuffer[i].EventType)
				{
				case KEY_EVENT:
					if (eventBuffer[i].Event.KeyEvent.bKeyDown)
					{
						switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
						{
						case VK_ESCAPE:
							return 0;
						case 0x57: //W
							up = true;
							break;
						case 0x41: //A
							left = true;
							break;
						case 0x53: //S
							down = true;
							break;
						case 0x44: //D
							right = true;
							break;
						}
					}
					break;
				case MOUSE_EVENT:
					if (eventBuffer[i].Event.MouseEvent.dwButtonState == 0x0001)
					{
						lclick = true;
					}
					if (eventBuffer[i].Event.MouseEvent.dwButtonState == 0x0002)
					{
						rclick = true;
					}
					if (eventBuffer[i].Event.MouseEvent.dwEventFlags == 0x0001)
					{
						mouse.x = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
						mouse.y = MAP_HEIGHT - 1 - eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;

					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags == 0x0000)
					{

					}
					break;
				}
			}
		}



		renderWindow();

		Sleep(framePause);
	}



	std::cin.get();

	return 0;
}



//I did not write this function
DWORD getInput(INPUT_RECORD **evB)
{
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;

	GetNumberOfConsoleInputEvents(hstdin, &numEvents);

	if (numEvents)
	{
		*evB = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD) * numEvents);
		//ORIGINAL CODE
		//*eventBuffer = malloc(sizeof(INPUT_RECORD) * numEvents);

		ReadConsoleInput(hstdin, *evB, numEvents, &numEventsRead);
	}

	return numEventsRead;
}

float dist(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(((float)x2 - (float)x1), 2) + pow(((float)y2 - (float)y1), 2));
}





void renderWindow()
{

	//Renders from top-left to bottom-right
	//The y loop increments backwards here so tiles can be set intuitively elsewhere
	int bufferCoord = 0;
	for (int y = MAP_HEIGHT - 1; y >= 0; --y)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			char chr = 0;
			int frontColor = 0;
			int backColor = 0;

			
			if (mouse.x == x && mouse.y == y)
			{
				backColor = 0x00F0;
			}

			

			consoleBuffer[bufferCoord].Char.AsciiChar = chr;
			consoleBuffer[bufferCoord].Attributes = frontColor + backColor;
			++bufferCoord;
		}
	}



	

	WriteConsoleOutputA(hstdout, consoleBuffer, charBufferSize, charPosition, &consoleWriteArea);
}
