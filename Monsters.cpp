#include "includes.h"
#include "Monsters.h"
#include "globals.h"

enum BOD {
    BODwalk, BODattack, BODcast, BODhurt, BODdie
};
BOD BODstate = BOD::BODwalk;

// animation counters
int MovmentCounter;
float MonsterCounter;

// function for setting rectangle of texture
IntRect getRect(int pos) {
    int x = pos%8;
    int y = pos/8;
    return IntRect(x*140, y*93, 140, 93);
}

// updating sprites animation
void UpdateMonsterAnimationCounter(float st = 0.15){
    MonsterCounter += playerdeltatime;
    if (MonsterCounter >= st)
    {
        MonsterCounter = 0;
        MovmentCounter++;
    }
}

// make monster walk
void walk(int x, int y) {
    zombies[0].zombie.setTextureRect(getRect(8 + MovmentCounter));
    zombies[0].zombie.move(((abs(x) > 1) ? ((x > 0) ? zombies[0].speed : -zombies[0].speed) : 0), ((y < 0) ? zombies[0].speed : -zombies[0].speed));
    UpdateMonsterAnimationCounter();
    MovmentCounter %= 8;
}

// make monster attack
void attack() {
    zombies[0].zombie.setTextureRect(getRect(16 + MovmentCounter));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 10) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster cast his spell
void cast() {
    zombies[0].zombie.setTextureRect(getRect(39 + MovmentCounter));
    zombies[0].spell.setTextureRect(getRect(52 + MovmentCounter));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 9) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster take damage
void hurt() {
    zombies[0].zombie.setTextureRect(getRect(27 + ((MovmentCounter > 4)?8- MovmentCounter : MovmentCounter)));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 9) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster die
void die() {
    zombies[0].zombie.setTextureRect(getRect(29 + MovmentCounter));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 10)
        BODalive = false;
}

// update monster
void MonstersMovment() {

    // hide BOD spell
    showBODSpell = false;

    // check that BOD is alive
    if(!BODalive)
        return;
    if (BODstate == BOD::BODdie){
        die();
        return;
    }

    // check distance between BOD and Player and make BOD look forward Player
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    if (x > 0)
        zombies[0].zombie.setScale(Vector2f(-2, 2));
    else
        zombies[0].zombie.setScale(Vector2f(2, 2));


    // passing time for cooldown
    zombies[0].cooldown -= playerdeltatime;

    // check if BOD is being attacked
    if (curr_state == player_base && abs(x) < 100 && abs(y) < 100 && BODstate != BOD::BODhurt) {
        zombies[0].health--;
        MovmentCounter = 0;
        BODstate = BOD::BODhurt;
    }

    // check if BOD is doing somthing
    if (BODstate == BOD::BODhurt) {
        if (MovmentCounter > 4 && zombies[0].health <= 0) {
            die();
            BODstate = BOD::BODdie;
        }
        else
            hurt();
        return;
    }
    else if (BODstate == BOD::BODcast) {
        cast();
        showBODSpell = true;
        return;
    }
    else if (BODstate == BOD::BODattack){
        attack();
        return;
    }



    // making BOD decision
    if ((long long)abs(x) * abs(x) + abs(y) * abs(y) < 100000 && zombies[0].cooldown <= 0) {
        zombies[0].spell.setPosition(Player.getPosition().x - 100, Player.getPosition().y - 200);
        MovmentCounter = 0;
        BODstate = BOD::BODcast;
        cast();
        showBODSpell = true;
        zombies[0].cooldown = 5;
    }
    else if (abs(x) < 300 && abs(y) < 30){
        MovmentCounter = 0;
        BODstate = BOD::BODattack;
        attack();
    }
    else
        walk(x,y);
}

// set monsters at the begining of the wave
void SetMonsters() {
    BODalive = true;
    zombies[0].zombie.setPosition(500, 500);
    zombies[0].health = 10;
    zombies[0].texture.loadFromFile("enemies/Bringer-Of-Death/SpriteSheet/Bringer-of-Death-SpritSheet.png");
    zombies[0].spell.setTexture(zombies[0].texture);
    zombies[0].spell.setTextureRect(getRect(48));
    zombies[0].spell.setScale(2, 2);
    zombies[0]. zombie.setTexture(zombies[0].texture);
    zombies[0].zombie.setTextureRect(getRect(0));
    zombies[0].zombie.setOrigin(105, 62);
    zombies[0].zombie.setPosition(500, 7000);
}