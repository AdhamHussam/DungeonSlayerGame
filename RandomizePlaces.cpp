#include "RandomizePlaces.h"

void RandPosition(int& x, int& y) {
	//srand(time(nullptr));
	if (current_room == 1){
		x = rand() % 1300 - 700;
		y = rand() % 1100 + 4800;
	}
	else if (current_room == 2) {
		x = rand() % 1100 - 650;
		y = rand() % 1100 + 3000;
	}
	else if (current_room == 3) {
		x = rand() % 2000 - 1200;
		y = rand() % 700 + 1500;
	}
	else if (current_room == 4) {
		x = rand() % 1000 - 650;
		y = rand() % 1000 - 50;
	}
	else if (current_room == 5) {
		x = rand() % 1500 - 800;
		y = rand() % 700 - 1900;
	}
}

void MonsterNumber() {
	ifstream file("NumberOfMonsters.csv");
	string row;
	for (int i = 0; i <= current_room; i++)
		getline(file, row);
	stringstream ss(row);
	string cell;
	getline(ss, cell, ',');
	SkeletonNumber = stoi(cell);
	getline(ss, cell, ',');
	BrainMoleNumber = stoi(cell);
	getline(ss, cell, ',');
	ShardSoulNumber = stoi(cell);
	getline(ss, cell, ',');
	BODnumber = stoi(cell);
	getline(ss, cell, ',');
	NightBroneNumber = stoi(cell);
	getline(ss, cell, ',');
	ArcaneArcherNumber = stoi(cell);
	getline(ss, cell, ',');
	RogueNumber = stoi(cell);
}