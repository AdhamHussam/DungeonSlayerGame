#include "ArcanArcher.h"

Texture AAtexture;
ArcanArcher AAoriginal;

IntRect AAgetRect(int pos) {
    int x = pos % 8;
    int y = pos / 8;
    return IntRect(x * 64, y * 64, 64, 64);
}

void AACreate() {
    AAtexture.loadFromFile("enemies/Arcane archer/projectile.png");
    AAoriginal.health = 7;
    AAoriginal.arow.setTexture(AAtexture);
    AAoriginal.arow.setScale(2, 2);
    AAtexture.loadFromFile("enemies/Arcane archer/spritesheet.png");
    AAoriginal.AA.setTexture(AAtexture);
    AAoriginal.AA.setTextureRect(AAgetRect(0));
    AAoriginal.AA.setOrigin(32, 32);
    AAoriginal.AA.setScale(2, 2);
}

void AASet() {

}

void AAMove() {
    AAoriginal.AA.setPosition(300, 6700);
    AAoriginal.arow.setPosition(200, 6500);
}

void AADraw(RenderWindow &window) {
    window.draw(AAoriginal.AA);
    window.draw(AAoriginal.arow);
}