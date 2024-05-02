#include "includes.h"
#include "Monsters.h"
#include "globals.h"

// animation counters
int WalkCounter, AttackCounter, CastCounter, HurtCounter, DieCounter;
float MonsterCounter;

// function for setting rectangle of texture
IntRect getRect(int pos) {
    int x = pos%8;
    int y = pos/8;
    return IntRect(x*140, y*93, 140, 93);
}

// reset all counters exept current activity
void reset_exept(int& place, int mod) {
    int value = place;
    WalkCounter = 0;
    AttackCounter = 0;
    CastCounter = 0;
    HurtCounter = 0;
    place = value + 1;
    place %= mod;
}

// updating sprites animation
void UpdateAnimationCounter(int& place, int mod, float st = 0.15){
    MonsterCounter += playerdeltatime;
    if (MonsterCounter >= st)
    {
        MonsterCounter = 0;
        reset_exept(place, mod);
    }
}

// make monster walk
void walk(int x, int y) {
    zombies[0].zombie.setTextureRect(getRect(8 + WalkCounter));
    zombies[0].zombie.move(((abs(x) > 1) ? ((x > 0) ? zombies[0].speed : -zombies[0].speed) : 0), ((y < 0) ? zombies[0].speed : -zombies[0].speed));
    UpdateAnimationCounter(WalkCounter, 8);
}

// make monster attack
void attack() {
    zombies[0].zombie.setTextureRect(getRect(16 + AttackCounter));
    UpdateAnimationCounter(AttackCounter, 10);
}

// make monster cast his spell
void cast() {
    if (!CastCounter)
        zombies[0].spell.setPosition(Player.getPosition().x - 100, Player.getPosition().y - 200);
    zombies[0].zombie.setTextureRect(getRect(39 + CastCounter));
    zombies[0].spell.setTextureRect(getRect(52 + CastCounter));
    UpdateAnimationCounter(CastCounter, 9);
}

// make monster take damage
void hurt() {
    zombies[0].zombie.setTextureRect(getRect(27 + ((HurtCounter > 4)?8-HurtCounter:HurtCounter)));
    UpdateAnimationCounter(HurtCounter, 9);
}

// make monster die
void die() {
    zombies[0].zombie.setTextureRect(getRect(29 + DieCounter));
    UpdateAnimationCounter(DieCounter, 11);
    if (DieCounter == 10)
        BODalive = false;
}

// update monster
void MonstersMovment() {
    if (DieCounter) {
        if(BODalive)
            die();
        return;
    }
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    if (x > 0)
        zombies[0].zombie.setScale(Vector2f(-2, 2));
    else
        zombies[0].zombie.setScale(Vector2f(2, 2));
    if ((curr_state == player_base && abs(x) < 100 && abs(y) < 100) || HurtCounter) {
        if (!HurtCounter)
            zombies[0].health--;
        if (HurtCounter > 4 && zombies[0].health <= 0)
            die();
        else
            hurt();
    }
    else if(abs(x) < 100 && abs(y) < 10 && !CastCounter)
        attack();
    else if ((long long)abs(x)*abs(x) + abs(y)*abs(y) < 100000 || CastCounter)
        cast();
    else
        walk(x,y);
    if (CastCounter)
        showBODSpell = true;
    else
        showBODSpell = false;
}

// set monsters at the begining of the wave
void SetMonsters() {
    BODalive = true;
    zombies[0].zombie.setPosition(500, 500);
    zombies[0].texture.loadFromFile("enemies/Bringer-Of-Death/SpriteSheet/Bringer-of-Death-SpritSheet.png");
    zombies[0].spell.setTexture(zombies[0].texture);
    zombies[0].spell.setTextureRect(getRect(48));
    zombies[0].spell.setScale(2, 2);
    zombies[0]. zombie.setTexture(zombies[0].texture);
    zombies[0].zombie.setTextureRect(getRect(0));
    zombies[0].zombie.setOrigin(105, 62);
    zombies[0].zombie.setPosition(500, 7000);
}