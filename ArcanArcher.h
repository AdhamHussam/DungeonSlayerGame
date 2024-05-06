#pragma once
#include "includes.h"

struct ArcanArcher {
	Sprite AA,arow;
	int health,speed = 200;
};

void AACreate();
void AASet();
void AAMove(float,Sprite);
void AADraw(RenderWindow&);