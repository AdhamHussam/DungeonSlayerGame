#include "Rogue.h"
#include "globals.h"
#include "Skeleton.h"

Texture Rtexture,Dtexture;
Rogue Roriginal, Rmonsters[30];
int RmovmentCounter[30], Rnumber;
float RmonsterCounter[30], Rdeltatime;

enum Renum {
    R_walk, R_attack, R_hurt, R_die, R_spawn
};
Renum Rstate[30];

IntRect RgetRect(int pos) {
    int x = pos % 10;
    int y = pos / 10;
    return IntRect(x * 50, y * 37, 50, 37);
}

void RupdateMonsterAnimationCounter(int i, float st = 0.15) {
    RmonsterCounter[i] += Rdeltatime;
    if (RmonsterCounter[i] >= st)
    {
        RmonsterCounter[i] = 0;
        RmovmentCounter[i]++;
    }
}

void Rwalk(int i) {
    Rmonsters[i].R.setTextureRect(RgetRect(10 + RmovmentCounter[i]));
    Vector2f Direction = Player.getPosition() - Rmonsters[i].R.getPosition();
    float magnitude = sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    Vector2f norm_direction = Direction / magnitude;
    Rmonsters[i].R.move(Vector2f(norm_direction.x * Rmonsters[i].speed * Rdeltatime, norm_direction.y * Rmonsters[i].speed * Rdeltatime));
    RupdateMonsterAnimationCounter(i);
    RmovmentCounter[i] %= 6;
}

void Rattack(int x, int y, int i) {
    Rmonsters[i].R.setTextureRect(RgetRect(40 + RmovmentCounter[i]));
    int initial = RmovmentCounter[i];
    RupdateMonsterAnimationCounter(i);
    if ((RmovmentCounter[i] == 3 || RmovmentCounter[i] == 7 || RmovmentCounter[i] == 12) && RmovmentCounter[i] > initial) {
        if (abs(x) < 100 && abs(y) < 30) {
            Player_Health -= Rmonsters[i].damage;
            ishit = true;
        }
    }
    if (RmovmentCounter[i] == 20) {
        RmovmentCounter[i] = 0;
        Rstate[i] = Renum::R_walk;
    }
}

void Rhurt(int i) {
    Rmonsters[i].R.setTextureRect(RgetRect(60 + RmovmentCounter[i]));
    RupdateMonsterAnimationCounter(i,0.1);
    if (RmovmentCounter[i] == 7) {
        RmovmentCounter[i] = 0;
        Rstate[i] = Renum::R_walk;
    }
}

void Rdie(int i) {
    Rmonsters[i].R.setTextureRect(RgetRect(90 + RmovmentCounter[i]));
    RupdateMonsterAnimationCounter(i,0.5);
    if (RmovmentCounter[i] == 5)
        Rmonsters[i].alive = false;
}

void Rspawn(int i) {
    Rmonsters[i].R.setTextureRect(RgetRect(30 + RmovmentCounter[i]));
    RupdateMonsterAnimationCounter(i,0.3);
    if (RmovmentCounter[i] == 9) {
        RmovmentCounter[i] = 0;
        NewSkeleton(Rmonsters[i].R.getPosition());
        Rstate[i] = Renum::R_walk;
        Rmonsters[i].cooldown = 15;
    }
}

void Rcreate() {
    Rtexture.loadFromFile("enemies/Rogue.png");
    Dtexture.loadFromFile("enemies/Rogue2.png");
    Roriginal.health = 30;
    Roriginal.R.setTexture(Rtexture);
    Roriginal.R.setTextureRect(RgetRect(0));
    Roriginal.R.setOrigin(26, 23);
    Roriginal.R.setScale(5, 5);

    Roriginal.R.setPosition(300, 6700);
}

void Rset(int Rn) {
    Rnumber = Rn;
    for (int i = 0; i < Rnumber; i++) {
        Rmonsters[i] = Roriginal;
        RmonsterCounter[i] = 0;
        RmovmentCounter[i] = 0;
        Rmonsters[i].R.setPosition(300 + rand() % 100, 6900 + rand() % 1000);
        Rmonsters[i].alive = true;
        Rstate[i] = Renum::R_spawn;
    }
}

void Rmove(float time, Sprite p, int attct, int& PlayerHealth) {
    Rdeltatime = time;
    for (int i = 0; i < Rnumber; i++) {

        // check if alive
        if (!Rmonsters[i].alive)
            continue;

        // check if R will die
        if (Rmonsters[i].health <= 0 && Rstate[i] != Renum::R_die) {
            Rmonsters[i].R.setTexture(Dtexture);
            RmovmentCounter[i] = 0;
            Rstate[i] = Renum::R_die;
        }

        double x = p.getPosition().x - Rmonsters[i].R.getPosition().x, y = Rmonsters[i].R.getPosition().y - p.getPosition().y;

        // check if R is dying
        if (Rstate[i] == Renum::R_die) {
            int initial = RmovmentCounter[i];
            Rdie(i);
            if (RmovmentCounter[i] == 13 && RmovmentCounter[i] > initial && abs(x) < 100 && abs(y) < 100) {
                ishit = true;
                PlayerHealth -= 30;
            }
            continue;
        }

        if (x < 0)
            Rmonsters[i].R.setScale(Vector2f(-3, 3));
        else
            Rmonsters[i].R.setScale(Vector2f(3, 3));

        Rmonsters[i].cooldown -= Rdeltatime;

        if (Rmonsters[i].cooldown < 7) {
            Rmonsters[i].AttackSpeed = 0.15;
            Rmonsters[i].speed = 100;
        }

        // check if R is spawning
        if (Rstate[i] == Renum::R_spawn) {
            Rspawn(i);
            continue;
        }

        // check if R is being attacked
        if (Rstate[i] != Renum::R_hurt && abs(x) < 100 && abs(y) < 100 && attct) {
            Rmonsters[i].health -= attct;
            RmovmentCounter[i] = 0;
            Rstate[i] = Renum::R_hurt;
        }

        // check if doing something
        if (Rstate[i] == Renum::R_hurt) {
            Rhurt(i);
            continue;
        }
        else if (Rstate[i] == Renum::R_attack) {
            Rattack(x, y, i);
            continue;
        }

        // make decision
        if (Rmonsters[i].cooldown <= 0) {
            Rspawn(i);
            Rstate[i] = Renum::R_spawn;
        }
        else if (abs(x) < 100 && abs(y) < 30) {
            Rstate[i] = Renum::R_attack;
            Rattack(x, y, i);
        }

        else Rwalk(i);
    }
}

void Rdraw(RenderWindow& window) {
    for (int i = 0; i < Rnumber; i++) {
        if (Rmonsters[i].alive) {
            window.draw(Rmonsters[i].R);
        }
    }
}

