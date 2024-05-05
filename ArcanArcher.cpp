#include "ArcanArcher.h"

Texture AAtexture;
ArcanArcher AAoriginal,AAmonsters[30];
int AAMovmentCounter[30];
float AAMonsterCounter[30],AAdeltatime;
Sprite player;

IntRect AAgetRect(int pos) {
    int x = pos % 8;
    int y = pos / 8;
    return IntRect(x * 64, y * 64, 64, 64);
}

void AAUpdateMonsterAnimationCounter(int i, float st = 0.15) {
    AAMonsterCounter[i] += AAdeltatime;
    if (AAMonsterCounter[i] >= st)
    {
        AAMonsterCounter[i] = 0;
        AAMovmentCounter[i]++;
    }
}

void AAwalk(int i) {
    AAmonsters[i].AA.setTextureRect(AAgetRect(AAMovmentCounter[i]));
    Vector2f Direction = player.getPosition() - AAmonsters[i].AA.getPosition();
    float magnitude = sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    Vector2f norm_direction = Direction / magnitude;
    AAmonsters[i].AA.move(Vector2f(norm_direction.x * AAmonsters[i].speed * AAdeltatime, norm_direction.y * AAmonsters[i].speed * AAdeltatime));
    AAUpdateMonsterAnimationCounter(i);
    AAMovmentCounter[i] %= 8;
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

    AAoriginal.AA.setPosition(300, 6700);
    AAoriginal.arow.setPosition(200, 6500);
}

void AASet() {
    AAmonsters[0] = AAoriginal;
}

void AAMove(float time,Sprite p) {
    player = p;
    AAdeltatime = time;
    double x = player.getPosition().x - AAmonsters[0].AA.getPosition().x, y = AAmonsters[0].AA.getPosition().y - player.getPosition().y;
    if (x < 0)
        AAmonsters[0].AA.setScale(Vector2f(-2, 2));
    else
        AAmonsters[0].AA.setScale(Vector2f(2, 2));
    AAwalk(0);
}

void AADraw(RenderWindow &window) {
    window.draw(AAmonsters[0].AA);
    window.draw(AAoriginal.arow);
}