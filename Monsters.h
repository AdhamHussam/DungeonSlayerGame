#pragma once
#include "includes.h"

struct Zombie
{
	Sprite zombie,spell;
	Texture texture;

	int health;
	float speed = 0.1, cooldown = 5;
};