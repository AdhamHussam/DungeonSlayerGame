#pragma once
#include "includes.h"

enum GoblinState {
	Hit,
	Attack,
	Run,
	Death,
	Spawn
};

struct Goblin {
	Sprite GBLN_run, G_Attack, G_Hit, G_Bomb, current;
	int speed, power, cooldown, health, animationSpeed, currentFrame, cooldownMax;
	int runAttackFrameHeight, runAttackFrameWidth, runAttackTotalFrames;
	int deathFrameHeight, deathFrameWidth, deathTotalFrames;
	int bombFrameHeight, bombFrameWidth, bomTotalFrames;
	float MonsterCounter = 0;
	Vector2f position;
	bool isAlive, throwBomb;
	IntRect textureRect;
	GoblinState state;
};

void GBLNcreate();
void GBLNset(int);
void GoblinSwitchState(Goblin&, GoblinState);
void GBLNupdateBomb(Goblin&);
void GBLNupdateDeath(Goblin&);
void GBLNupdateRunAttack(Goblin&);
void GBLNdie(Goblin&);
void GBLNhit(Goblin&);
void GBLNspawn(Goblin&);
void GBLNmove(Goblin&);
void GBLNdraw(int);
void GBLattack(int, int, Goblin&);
void GoblinDynamics(int, int);
