#pragma once
#include "includes.h"

struct BringerOfDeath
{
	Sprite BOD,spell;
	int health = 10;
	float speed = 100, cooldown = 5;
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
};

inline bool operator>(const Cell& lhs, const Cell& rhs) {
	// Compare based on cost
	return lhs.cost > rhs.cost;
}

struct ParentsCostPair
{
	vector<vector<Coordinates>> parents;
	vector<vector<int>> cost;
};