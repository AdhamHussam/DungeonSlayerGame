#include "includes.h"
#include "Monsters.h"
const int monster_types = 1,boss_types = 1;
Enemy monsters[monster_types],bosses[boss_types];

// Comparision for sorting arrays monsters and bosses decsending based on xp
bool compare_xp(Enemy &a, Enemy &b) {
	return a.xp > b.xp;
}

// Called at the begin of the game only once
// making monster types and adding them to array monsters
void classifying_monsters() {
	// making first monster (zombie for example)
	Enemy current_monster;
	current_monster.health = 1000;
	current_monster.strenth = 10;
	current_monster.base_atack();
	monsters[0] = current_monster;

	// sorting monsters decsending based on xp
	sort(monsters, monsters + monster_types, compare_xp);
}

// Called at the begin of the game only once
// making boss types and adding them to array bosses
void classifying_bosses() {

}