#pragma once
#include "includes.h"

struct Enemy
{
	string name;
	int health;
	int strenth;
	int xp = health/10 + strenth;
	void base_atack() {
		int relative_power = 0;
		xp += relative_power;
	}
	void skill() {
		int relative_power = 0;
		xp += relative_power;
	}
	void ultimate() {
		int relative_power = 0;
		xp += relative_power;
	}
};