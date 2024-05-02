#pragma once
#include "includes.h"

struct Zombie
{
	Sprite zombie,spell;
	Texture texture;

	int level = 1;
	double factor_level = level / 10 + 1;
	int health = 100*factor_level;
	int strenth = 10*factor_level;
	double speed = 0.1;
};