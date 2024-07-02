#pragma once
#include "includes.h"

enum class FWState {
    FW_idle,
    FW_attack,
    FW_hit,
    FW_die,
    FW_run,
    FW_spawn
};

struct FlameWizard {
    Sprite FW;
    Sprite FWidle;
    Sprite FWattack;
    Sprite FWhit;
    Sprite FWdie;
    Sprite FWrun;
    FWState state;
    int health, speed = 100, power = 3, damage = 10;
    float cooldown = 10, AttackSpeed = 0.15;
    bool alive;
};

extern FlameWizard FWmonsters[30];

void FWcreate();
void FWset(int);
void FWmove(float, Sprite, int, int&, bool&);
void FWdraw(RenderWindow&);
