#include "includes.h"
#include "Monsters.h"
#include "globals.h"

// Define global variables here
int globalInt = 0;  // Definition
Clock GameClock;

const int number_of_zombies = 1;
Zombie zombies[number_of_zombies];
bool showBODSpell;

Sprite Player;
float playerdeltatime = 0;
