#include "NightBorne.h"
#include "globals.h"

Texture NBtexture;
NightBrone NBoriginal, NBmonsters[30];
int NBmovmentCounter[30];
float NBmonsterCounter[30], NBdeltatime;

IntRect NBgetRect(int pos) {
    int x = pos % 23;
    int y = pos / 23;
    return IntRect(x * 80, y * 80, 80, 80);
}

void NBupdateMonsterAnimationCounter(int i, float st = 0.15) {
    NBmonsterCounter[i] += NBdeltatime;
    if (NBmonsterCounter[i] >= st)
    {
        NBmonsterCounter[i] = 0;
        NBmovmentCounter[i]++;
    }
}

void NBwalk(int i) {
    NBmonsters[i].NB.setTextureRect(NBgetRect(23 + NBmovmentCounter[i]));
    Vector2f Direction = Player.getPosition() - NBmonsters[i].NB.getPosition();
    float magnitude = sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    Vector2f norm_direction = Direction / magnitude;
    NBmonsters[i].NB.move(Vector2f(norm_direction.x * NBmonsters[i].speed * NBdeltatime, norm_direction.y * NBmonsters[i].speed * NBdeltatime));
    NBupdateMonsterAnimationCounter(i);
    NBmovmentCounter[i] %= 6;
}

void NBcreate() {
    NBtexture.loadFromFile("enemies/NightBorne.png");
    NBoriginal.health = 7;
    NBoriginal.NB.setTexture(NBtexture);
    NBoriginal.NB.setTextureRect(NBgetRect(0));
    NBoriginal.NB.setOrigin(32, 32);
    NBoriginal.NB.setScale(2, 2);

    NBoriginal.NB.setPosition(300, 6700);
}

void NBset() {
    NBmonsters[0] = NBoriginal;
}

void NBmove(float time, Sprite p) {
    NBdeltatime = time;
    double x = p.getPosition().x - NBmonsters[0].NB.getPosition().x, y = NBmonsters[0].NB.getPosition().y - p.getPosition().y;
    if (x < 0)
        NBmonsters[0].NB.setScale(Vector2f(-2, 2));
    else
        NBmonsters[0].NB.setScale(Vector2f(2, 2));
    NBwalk(0);
}

void NBdraw(RenderWindow& window) {
    window.draw(NBmonsters[0].NB);
}

