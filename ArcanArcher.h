#pragma once
#include "includes.h"

struct ArcanArcher {
	Sprite AA,arrow;
	int health,speed = 300,power = 1,ArrowSpeed = 1000;
	float cooldown = 10;
	bool alive,hitted;
	Vector2f target;
};

void AACreate();
void AASet(int);
void AAMove(float,Sprite,int,int&);
void AADraw(RenderWindow&);