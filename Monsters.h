#pragma once
#include "includes.h"

struct Zombie
{
	Sprite zombie,spell;
	Texture texture;

	int health = 10;
	float speed = 0.1, cooldown = 5;
};