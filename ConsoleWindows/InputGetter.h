#pragma once


#include "WindowSetup.h"



struct vec2
{
	int x;
	int y;
};



extern INPUT_RECORD* eventBuffer;
extern DWORD numEventsRead;

extern vec2 mouse;
extern bool lclick;
extern bool rclick;
extern bool shouldExit;


DWORD getInput(INPUT_RECORD **evB);

void checkInput();

