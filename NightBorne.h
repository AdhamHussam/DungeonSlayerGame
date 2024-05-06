#pragma once
#include "includes.h"

struct NightBrone {
	Sprite NB;
	int health, speed = 100, power = 3, cooldown = 5, damage = 5;
	bool alive;
};

void NBcreate();
void NBset(int);
void NBmove(float,Sprite,int,int&,bool&);
void NBdraw(RenderWindow&);