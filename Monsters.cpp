#include "includes.h"
#include "Monsters.h"

int counter = 0;
string walk_path = "enemies/Bringer-Of-Death/Individual Sprite/Walk/Bringer-of-Death_Walk_0.png";
string attack_path = "enemies/Bringer-Of-Death/Individual Sprite/Attack/Bringer-of-Death_Attack_0.png";
void MonstersMovment(Zombie zombies[], Sprite &Player) {
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    counter++;
    counter %= 800;
    if (x > 0)
        zombies[0].zombie.setScale(Vector2f(-1, 1));
    else
        zombies[0].zombie.setScale(Vector2f(1, 1));
    if(abs(x) < 100 && abs(y) < 10)
        zombies[0].zombie.setTexture(zombies[0].attack[counter / 100]);
    else {
        zombies[0].zombie.setTexture(zombies[0].walk[counter / 100]);
        zombies[0].zombie.move(((x > 0) ? zombies[0].speed : -zombies[0].speed), ((y < 0) ? zombies[0].speed : -zombies[0].speed));
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
    zombies[0].zombie.setOrigin(zombies[0].walk[counter / 100].getSize().x / 4 * 3, zombies[0].walk[counter / 100].getSize().y / 3 * 2);
    zombies[0].zombie.setPosition(-500, 7000);
}