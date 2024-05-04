#ifndef GLOBALS_H
#define GLOBALS_H

// Declare global variables here
extern int globalInt;  // Declaration
extern Clock GameClock;

extern const int number_of_BODmonsters;
extern BringerOfDeath BODmonsters[];
extern BringerOfDeath BODoriginal;
extern bool showBODSpell,BODalive;
extern Sprite Player;
extern float playerdeltatime;
enum state;
extern state curr_state, player_idle, player_run, player_hit, player_base, player_zmove, player_xmove, player_cmove, player_dead, player_walk;
enum BOD;
extern BOD BODstate, BODattacks;
extern int Player_Health;
extern bool ishit;
#endif // GLOBALS_H
