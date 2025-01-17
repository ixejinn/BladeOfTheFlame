#pragma once
#include "AEVec2.h"

const int windowWidth = 1600;
const int windowHeight = 900;

struct Color
{
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
};

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STOP
};

AEVec2 convert(AEVec2 a);