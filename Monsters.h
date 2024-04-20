#pragma once
#include "includes.h"

struct Zombie
{
	Sprite zombie;
	Texture photo[8];
	int level;
	double factor_level = level / 10 + 1;
	int health = 100*factor_level;
	int strenth = 10;
	double speed = 0.1;
	void base_atack() {

	}
	void skill() {

	}
	void ultimate() {

	}
};