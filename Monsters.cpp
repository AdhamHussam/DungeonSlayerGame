#include "includes.h"
#include "Monsters.h"
#include "globals.h"

enum BOD {
    BODwalk, BODattack, BODcast, BODhurt, BODdie
};


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
    BODmonsters[0].BOD.setTextureRect(getRect(8 + MovmentCounter));
    BODmonsters[0].BOD.move(((abs(x) > 1) ? ((x > 0) ? BODmonsters[0].speed : -BODmonsters[0].speed) : 0), ((y < 0) ? BODmonsters[0].speed : -BODmonsters[0].speed));
    UpdateMonsterAnimationCounter();
    MovmentCounter %= 8;
}

// make monster attack
void attack(int x,int y) {
    BODmonsters[0].BOD.setTextureRect(getRect(16 + MovmentCounter));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 10) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
        if (abs(x) < 200 && abs(y) < 30) {
            ishit = true;
            Player_Health -= 5;
        }
    }
}

// make monster cast his spell
void cast() {
    BODmonsters[0].BOD.setTextureRect(getRect(39 + MovmentCounter));
    BODmonsters[0].spell.setTextureRect(getRect(52 + MovmentCounter));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 9) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster take damage
void hurt() {
    BODmonsters[0].BOD.setTextureRect(getRect(27 + ((MovmentCounter > 4)?8- MovmentCounter : MovmentCounter)));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 9) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster die
void die() {
    BODmonsters[0].BOD.setTextureRect(getRect(29 + MovmentCounter));
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
    if (BODstate == BOD::BODdie) {
        die();
        return;
    }

    // check distance between BOD and Player and make BOD look forward Player
    double x = Player.getPosition().x - BODmonsters[0].BOD.getPosition().x, y = BODmonsters[0].BOD.getPosition().y - Player.getPosition().y;
    if (x > 0)
        BODmonsters[0].BOD.setScale(Vector2f(-2, 2));
    else
        BODmonsters[0].BOD.setScale(Vector2f(2, 2));


    // passing time for cooldown
    BODmonsters[0].cooldown -= playerdeltatime;

    // check if BOD is being attacked
    if(BODstate != BOD::BODhurt && abs(x) < 100 && abs(y) < 100){
        if (curr_state == player_base) {
            BODmonsters[0].health --;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
        else if(curr_state == player_zmove) {
            BODmonsters[0].health -= 2;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
        else if (curr_state == player_xmove) {
            BODmonsters[0].health -= 3;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
        else if (curr_state == player_cmove) {
            BODmonsters[0].health -= 10;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
    }

    // check if BOD is doing somthing
    if (BODstate == BOD::BODhurt) {
        if (BODmonsters[0].health <= 0) {
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
        attack(x,y);
        return;
    }



    // making BOD decision
    if ((long long)abs(x) * abs(x) + abs(y) * abs(y) < 100000 && BODmonsters[0].cooldown <= 0) {
        BODmonsters[0].spell.setPosition(Player.getPosition().x - 100, Player.getPosition().y - 200);
        MovmentCounter = 0;
        BODstate = BOD::BODcast;
        cast();
        showBODSpell = true;
        BODmonsters[0].cooldown = 5;
    }
    else if (abs(x) < 300 && abs(y) < 30){
        MovmentCounter = 0;
        BODstate = BOD::BODattack;
        attack(x,y);
    }
    else
        walk(x,y);
}

// set monsters at the begining of the wave
void SetMonsters() {
        BODalive = true;
        BODmonsters[0].health = 10;
        BODstate = BOD::BODwalk;
        BODmonsters[0].texture.loadFromFile("enemies/Bringer-Of-Death/SpriteSheet/Bringer-of-Death-SpritSheet.png");
        BODmonsters[0].spell.setTexture(BODmonsters[0].texture);
        BODmonsters[0].spell.setTextureRect(getRect(48));
        BODmonsters[0].spell.setScale(2, 2);
        BODmonsters[0].BOD.setTexture(BODmonsters[0].texture);
        BODmonsters[0].BOD.setTextureRect(getRect(0));
        BODmonsters[0].BOD.setOrigin(105, 62);
        BODmonsters[0].BOD.setPosition(500, 7000);
    
}