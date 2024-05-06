#pragma once
#include "includes.h"

struct NightBrone {
	Sprite NB;
	int health, speed = 100;
};

void NBcreate();
void NBset();
void NBmove(float, Sprite);
void NBdraw(RenderWindow&);