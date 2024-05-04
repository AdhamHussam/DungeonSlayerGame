#pragma once
#include "includes.h"

struct BringerOfDeath
{
	Sprite BOD,spell;
	Texture texture;

	int health = 10;
	int speed = 100, cooldown = 5;
};