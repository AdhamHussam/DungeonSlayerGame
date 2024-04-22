#include "includes.h"
#include "Monsters.h"

// testing
int counter = 0;
string path = "enemies/Bringer-Of-Death/Individual Sprite/Walk/Bringer-of-Death_Walk_0.png";
void MonstersMovment(Zombie zombies[], Sprite &Player) {
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    zombies[0].zombie.move(((x > 0) ? zombies[0].speed : -zombies[0].speed), ((y < 0) ? zombies[0].speed : -zombies[0].speed));
    counter++;
    counter %= 800;
    zombies[0].zombie.setTexture(zombies[0].photo[counter/100]);
}

void SetMonsters(Zombie zombies[]) {
    zombies[0].zombie.setPosition(500, 500);
    for (int i = 0; i < 8; i++){
        string s = to_string(i + 1);
        path[70] = s[0];
        zombies[0].photo[i].loadFromFile(path);
    }
    zombies[0].zombie.setTexture(zombies[0].photo[counter / 100]);
    zombies[0].zombie.setOrigin(zombies[0].photo[counter / 100].getSize().x / 2, zombies[0].photo[counter / 100].getSize().y / 2);
    zombies[0].zombie.setPosition(-500, 7000);
}