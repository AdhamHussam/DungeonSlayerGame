#pragma once
#include "includes.h"

struct BringerOfDeath
{
	Sprite BOD,spell;
	Texture texture;

	int health = 10;
	float speed = 0.1, cooldown = 5;
};

struct Coordinates
{
	int x;
	int y;
};

struct Cell
{
	int cost;
	Coordinates node;

	bool operator<(const Cell& other) const {
		return cost > other.cost; // Compare based on cost
	}
};

struct ParentsCostPair
{
	vector<vector<Coordinates>> parents;
	vector<vector<int>> cost;
	int speed = 100, cooldown = 5;
};