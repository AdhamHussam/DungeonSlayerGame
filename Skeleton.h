#pragma once
#include "includes.h"

struct Skeleton {
	Sprite S;
	int health, speed = 100;
	bool alive;
};

void Screate();
void Sset(int);
void Smove(float, Sprite, int, int&, bool&);
void Sdraw(RenderWindow&);