#include "includes.h"
#include "Monsters.h"

int WalkCounter = 0, AttackCounter = 0, CastCounter = 0, TimeCounter = 0;
string getBOD(string event, int phase) {
    return "enemies/Bringer-Of-Death/Individual Sprite/" + event + "/Bringer-of-Death_" + event + "_" + to_string(phase) + ".png";
}
void reset_exept(int& place, int mod) {
    int value = place;
    WalkCounter = 0;
    AttackCounter = 0;
    CastCounter = 0;
    place = value + 1;
    place %= mod;
}
string walk_path = "enemies/Bringer-Of-Death/Individual Sprite/Walk/Bringer-of-Death_Walk_0.png";
string attack_path = "enemies/Bringer-Of-Death/Individual Sprite/Attack/Bringer-of-Death_Attack_0.png";
void MonstersMovment(Zombie zombies[], Sprite &Player) {
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    if (x > 0)
        zombies[0].zombie.setScale(Vector2f(-1, 1));
    else
        zombies[0].zombie.setScale(Vector2f(1, 1));
    if(abs(x) < 100 && abs(y) < 10 && !(CastCounter/100)) {
        // Attack
        zombies[0].zombie.setTexture(zombies[0].attack[AttackCounter / 100]);
        reset_exept(AttackCounter, 1000);
    }
    else if ((long long)abs(x)*abs(x) + abs(y)*abs(y) < 100000 || CastCounter/100) {
        // Cast
        zombies[0].zombie.setTexture(zombies[0].Cast[CastCounter / 100]);
        reset_exept(CastCounter, 900);
    }
    else{
        // Walk
        zombies[0].zombie.setTexture(zombies[0].walk[WalkCounter / 100]);
        zombies[0].zombie.move(((abs(x) > 1) ? ((x > 0) ? zombies[0].speed : -zombies[0].speed) : 0), ((y < 0) ? zombies[0].speed : -zombies[0].speed));
        reset_exept(WalkCounter, 800);
    }
    TimeCounter++;
}

void SetMonsters(Zombie zombies[]) {
    zombies[0].zombie.setPosition(500, 500);
    for (int i = 1; i <= 8; i++)
        zombies[0].walk[i-1].loadFromFile(getBOD("Walk", i));
    for (int i = 1; i <= 10; i++)
        zombies[0].attack[i-1].loadFromFile(getBOD("Attack", i));
    for (int i = 1; i <= 9; i++)
        zombies[0].Cast[i - 1].loadFromFile(getBOD("Cast", i));

    zombies[0].zombie.setTexture(zombies[0].walk[0]);
    zombies[0].zombie.setOrigin(zombies[0].walk[0].getSize().x / 4 * 3, zombies[0].walk[0].getSize().y / 3 * 2);
    zombies[0].zombie.setPosition(-500, 7000);
}