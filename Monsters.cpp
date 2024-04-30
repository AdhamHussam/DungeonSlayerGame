#include "includes.h"
#include "Monsters.h"
#include "globals.h"

void someFunction() {
    // Access and modify globalInt here
    globalInt++;
}

int WalkCounter = 0, AttackCounter = 0, CastCounter = 0, TimeCounter = 0, SpellCounter = 0;
IntRect getRect(int pos) {
    int x = pos%8;
    int y = pos/8;
    return IntRect(x*140, y*93, 140, 93);
}
void reset_exept(int& place, int mod) {
    int value = place;
    WalkCounter = 0;
    AttackCounter = 0;
    CastCounter = 0;
    place = value + 1;
    place %= mod;
}
int MonstersMovment(Zombie zombies[], Sprite &Player) {
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    if (x > 0)
        zombies[0].zombie.setScale(Vector2f(-2, 2));
    else
        zombies[0].zombie.setScale(Vector2f(2, 2));
    if (SpellCounter != 0) {
        SpellCounter++;
        SpellCounter %= 1600;
        zombies[0].spell.setTextureRect(getRect(48 + SpellCounter / 100));
    }
    if(abs(x) < 100 && abs(y) < 10 && !(CastCounter/100)) {
        // Attack
        zombies[0].zombie.setTextureRect(getRect(16 + AttackCounter / 100));
        reset_exept(AttackCounter, 1000);
    }
    else if ((long long)abs(x)*abs(x) + abs(y)*abs(y) < 100000 || CastCounter/100) {
        // Cast
        if (CastCounter == 0) {
            zombies[0].spell.setPosition(Player.getPosition().x - 100, Player.getPosition().y-200);
            SpellCounter = 1;
        }
        zombies[0].zombie.setTextureRect(getRect(39 + CastCounter / 100));
        reset_exept(CastCounter, 900);
    }
    else{
        // Walk
        zombies[0].zombie.setTextureRect(getRect(8+WalkCounter/100));
        zombies[0].zombie.move(((abs(x) > 1) ? ((x > 0) ? zombies[0].speed : -zombies[0].speed) : 0), ((y < 0) ? zombies[0].speed : -zombies[0].speed));
        reset_exept(WalkCounter, 800);
    }
    TimeCounter++;
    return SpellCounter;
}

void SetMonsters(Zombie zombies[]) {
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