#include "includes.h"
#include "Monsters.h"

int counter = 0;
string walk_path = "enemies/Bringer-Of-Death/Individual Sprite/Walk/Bringer-of-Death_Walk_0.png";
string attack_path = "enemies/Bringer-Of-Death/Individual Sprite/Attack/Bringer-of-Death_Attack_0.png";
void MonstersMovment(Zombie zombies[], Sprite &Player) {
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    zombies[0].zombie.move(((x > 0) ? zombies[0].speed : -zombies[0].speed), ((y < 0) ? zombies[0].speed : -zombies[0].speed));
    if (abs(x) > 100 || true) {
        counter++;
        counter %= 800;
        zombies[0].zombie.setTexture(zombies[0].attack[counter / 100]);
    }
    else {

    }
}

void SetMonsters(Zombie zombies[]) {
    zombies[0].zombie.setPosition(500, 500);
    for (int i = 0; i < 8; i++){
        string s = to_string(i + 1);
        walk_path[70] = s[0];
        zombies[0].walk[i].loadFromFile(walk_path);
    }
    for (int i = 0; i < 9; i++) {
        string s = to_string(i + 1);
        attack_path[74] = s[0];
        zombies[0].attack[i].loadFromFile(attack_path);
    }
    zombies[0].zombie.setTexture(zombies[0].walk[counter / 100]);
    zombies[0].zombie.setOrigin(zombies[0].walk[counter / 100].getSize().x / 2, zombies[0].walk[counter / 100].getSize().y / 2);
    zombies[0].zombie.setPosition(-500, 7000);
}