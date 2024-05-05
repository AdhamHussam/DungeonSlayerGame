#include "includes.h"
#include "Monsters.h"
#include "globals.h"

// Define global variables here
int globalInt = 0;  // Definition
Clock GameClock;
View view(Vector2f(0, 0), Vector2f(1920, 1080));

int BODnumber;
BringerOfDeath BODmonsters[30];
BringerOfDeath BODoriginal;
Texture BODtexture;
bool showBODSpell[30], BODalive[30];
Sprite Player;
float playerdeltatime = 0;
int Player_Health = 100;
bool ishit = false;
enum state
{
    idle, run, hit, base,  xmove, cmove, vmove, dead, walk
};
state curr_state = state::idle, player_base = state::base, player_vmove = state::vmove, player_xmove = state::xmove, player_cmove = state::cmove;
state player_idle = state::idle, player_run = state::run, player_hit = state::hit, player_dead = state::dead, player_walk = state::walk;

BOD BODstate[30], BODattacks = BOD::BODattack;