#ifndef GLOBALS_H
#define GLOBALS_H

// Declare global variables here
extern int globalInt;  // Declaration
extern Clock GameClock;
extern View view;

extern int ArcaneArcherNumber, NightBroneNumber, SkeletonNumber, ShardSoulNumber, BrainMoleNumber, RogueNumber;
extern RenderWindow window;
/*

*/
extern int current_room,current_wave,BODnumber;
extern Sprite Player;
extern float playerdeltatime;
enum state;
extern state curr_state, player_idle, player_run, player_hit, player_base,  player_xmove, player_cmove, player_vmove, player_dead, player_walk;
enum BOD;
extern BOD BODstate[], BODattacks;
extern int Player_Health;
extern bool ishit;
extern float cooldown[5];
#endif // GLOBALS_H
