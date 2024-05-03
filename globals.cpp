#include "includes.h"
#include "Monsters.h"
#include "globals.h"

// Define global variables here
int globalInt = 0;  // Definition
Clock GameClock;

const int number_of_zombies = 3;
Zombie zombies[number_of_zombies];
bool showBODSpell, BODalive;
Sprite Player;
float playerdeltatime = 0;
enum state
{
    idle, run, hit, base, zmove, xmove, cmove, dead, walk
};
state curr_state = state::idle, player_base = state::base, player_zmove = state::zmove, player_xmove = state::xmove, player_cmove = state::cmove;
state player_idle = state::idle, player_run = state::run, player_hit = state::hit, player_dead = state::dead, player_walk = state::walk;


enum BOD {
    BODwalk, BODattack, BODcast, BODhurt, BODdie
};
BOD BODstate = BOD::BODwalk, BODattacks = BOD::BODattack;