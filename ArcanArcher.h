#pragma once
#include "includes.h"

struct ArcanArcher {
	Sprite AA,arow;
	int health;
};

void AACreate();
void AASet();
void AAMove();
void AADraw(RenderWindow&);