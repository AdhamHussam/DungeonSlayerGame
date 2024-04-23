#pragma once
#include "includes.h"

struct Zombie
{
	Sprite zombie;
	Texture walk[8],attack[10],Cast[9];

	int level;
	double factor_level = level / 10 + 1;
	int health = 100*factor_level;
	int strenth = 10*factor_level;
	double speed = 0.1;
};