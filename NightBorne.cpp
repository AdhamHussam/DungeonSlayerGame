#include "NightBorne.h"
#include "globals.h"

Texture NBtexture;
NightBrone NBoriginal, NBmonsters[30];
int NBmovmentCounter[30], NBnumber;
float NBmonsterCounter[30], NBdeltatime;

enum NBenum {
    NB_walk, NB_attack, NB_hurt, NB_die, NB_spawn
};
NBenum NBstate[30];

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

void NBattack(int x, int y, int i) {
    NBmonsters[i].NB.setTextureRect(NBgetRect(46 + NBmovmentCounter[i]));
    int initial = NBmovmentCounter[i];
    NBupdateMonsterAnimationCounter(i);
    if (NBmovmentCounter[i] == 9 && NBmovmentCounter[i] > initial) {
        if (abs(x) < 200 && abs(y) < 30) {
            Player_Health -= NBmonsters[i].damage;
            ishit = true;
        }
    }
    if (NBmovmentCounter[i] == 12) {
        NBmovmentCounter[i] = 0;
        NBstate[i] = NBenum::NB_walk;
    }
}

void NBhurt(int i) {
    NBmonsters[i].NB.setTextureRect(NBgetRect(69 + NBmovmentCounter[i]));
    NBupdateMonsterAnimationCounter(i);
    if (NBmovmentCounter[i] == 5) {
        NBmovmentCounter[i] = 0;
        NBstate[i] = NBenum::NB_walk;
    }
}

void NBdie(int i) {
    NBmonsters[i].NB.setTextureRect(NBgetRect(92 + NBmovmentCounter[i]));
    NBupdateMonsterAnimationCounter(i);
    if (NBmovmentCounter[i] == 23)
        NBmonsters[i].alive = false;
}

void NBspawn(int i) {
    NBmonsters[i].NB.setTextureRect(NBgetRect(NBmovmentCounter[i]));
    NBupdateMonsterAnimationCounter(i, 0.3);
    if (NBmovmentCounter[i] == 9) {
        NBmovmentCounter[i] = 0;
        NBmonsters[i].power *= 2;
        NBmonsters[i].health += 5;
        NBstate[i] = NBenum::NB_walk;
        NBmonsters[i].cooldown = 10;
    }
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

void NBset(int NBn) {
    NBnumber = NBn;
    for (int i = 0; i < NBnumber; i++) {
        NBmonsters[i] = NBoriginal;
        NBmonsterCounter[i] = 0;
        NBmovmentCounter[i] = 0;
        NBmonsters[i].NB.setPosition(400 + rand() % 100, 6200 + rand() % 1000);
        NBmonsters[i].alive = true;
        NBstate[i] = NBenum::NB_spawn;
    }
}

void NBmove(float time, Sprite p, int attct, int& PlayerHealth, bool& IsHit) {
    NBdeltatime = time;
    for (int i = 0; i < NBnumber; i++) {

        // check if alive
        if (!NBmonsters[i].alive)
            continue;

        // check if NB will die
        if (NBmonsters[i].health <= 0 && NBstate[i] != NBenum::NB_die) {
            NBmovmentCounter[i] = 0;
            NBstate[i] = NBenum::NB_die;
        }

        // check if NB is dying
        if (NBstate[i] == NBenum::NB_die) {
            NBdie(i);
            continue;
        }

        // check if NB is spawning
        if (NBstate[i] == NBenum::NB_spawn) {
            NBspawn(i);
            continue;
        }

        double x = p.getPosition().x - NBmonsters[i].NB.getPosition().x, y = NBmonsters[i].NB.getPosition().y - p.getPosition().y;
        if (x < 0)
            NBmonsters[i].NB.setScale(Vector2f(-2.5, 2.5));
        else
            NBmonsters[i].NB.setScale(Vector2f(2.5, 2.5));
        NBmonsters[i].cooldown -= NBdeltatime;

        // check if NB is being attacked
        if (NBstate[i] != NBenum::NB_hurt && abs(x) < 100 && abs(y) < 100 && attct) {
            NBmonsters[i].health -= attct;
            NBmovmentCounter[i] = 0;
            NBstate[i] = NBenum::NB_hurt;
        }

        // check if doing something
        if (NBstate[i] == NBenum::NB_hurt) {
            NBhurt(i);
            continue;
        }
        else if (NBstate[i] == NBenum::NB_attack) {
            NBattack(x, y, i);
            continue;
        }

        // make decision
        if (NBmonsters[i].cooldown <= 0) {
            NBspawn(i);
            NBstate[i] = NBenum::NB_spawn;
        }
        else if (abs(x) < 300 && abs(y) < 30) {
            NBstate[i] = NBenum::NB_attack;
            NBattack(x, y, i);
        }
        
        else NBwalk(i);                                                                        
    }
}

void NBdraw(RenderWindow& window) {
    for (int i = 0; i < NBnumber; i++) {
        if (NBmonsters[i].alive) {
            window.draw(NBmonsters[i].NB);
        }
    }
}

