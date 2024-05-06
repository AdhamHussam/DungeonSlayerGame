#pragma once
#include "includes.h"

enum GoblinState {
	Hit,
	Attack,
	Run,
	Death
};

struct Goblin {
	Sprite GBLN_run, G_Attack, G_Hit, G_Bomb, current;
	int speed, power, cooldown, health, animationSpeed, currentFrame;
	int runAttackFrameHeight, runAttackFrameWidth, runAttackTotalFrames;
	int deathFrameHeight, deathFrameWidth, deathTotalFrames;
	int bombFrameHeight, bombFrameWidth, bomTotalFrames;
	Vector2f position;
	//bool isAttacking, isWalking, isHit, isDead;
	IntRect textureRect;
	Clock clock;
	GoblinState state;
};

void GBLNcreate();
void GBLNset(int);
void GBLNmove(Goblin&);
void GBLNdraw(int);
void GBLattack(int, int, Goblin&);
void GoblinDynamics(int);
