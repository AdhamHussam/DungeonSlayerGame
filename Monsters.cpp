#include "includes.h"
#include "Monsters.h"

int counter;

void MonstersMovment(Zombie zombies[], Sprite &Player) {
    double x = Player.getPosition().x - zombies[0].zombie.getPosition().x, y = zombies[0].zombie.getPosition().y - Player.getPosition().y;
    zombies[0].zombie.move(((x > 0) ? zombies[0].speed : -zombies[0].speed) * (!counter), ((y < 0) ? zombies[0].speed : -zombies[0].speed) * counter);
    counter++, counter %= 2;
}

