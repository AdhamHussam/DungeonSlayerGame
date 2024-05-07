#include "Skeleton.h"
#include "globals.h"

Texture Stexture;
Skeleton Soriginal, Smonsters[100];
int SmovmentCounter[100], Snumber;
float SmonsterCounter[100], Sdeltatime;

enum Senum {
    S_walk, S_attack, S_hurt, S_die
};
Senum Sstate[100];

IntRect SgetRect(int pos) {
    int x = pos % 13;
    int y = pos / 13;
    return IntRect(x * 64, y * 64, 64, 64);
}

void SupdateMonsterAnimationCounter(int i, float st = 0.15) {
    SmonsterCounter[i] += Sdeltatime;
    if (SmonsterCounter[i] >= st)
    {
        SmonsterCounter[i] = 0;
        SmovmentCounter[i]++;
    }
}

void Swalk(int i) {
    Smonsters[i].S.setTextureRect(SgetRect(26 + SmovmentCounter[i]));
    Vector2f Direction = Player.getPosition() - Smonsters[i].S.getPosition();
    float magnitude = sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    Vector2f norm_direction = Direction / magnitude;
    Smonsters[i].S.move(Vector2f(norm_direction.x * Smonsters[i].speed * Sdeltatime, norm_direction.y * Smonsters[i].speed * Sdeltatime));
    SupdateMonsterAnimationCounter(i);
    SmovmentCounter[i] %= 12;
}

void Sattack(int x, int y, int i) {
    Smonsters[i].S.setTextureRect(SgetRect(SmovmentCounter[i]));
    int initial = SmovmentCounter[i];
    SupdateMonsterAnimationCounter(i);
    if ((SmovmentCounter[i] == 4 || SmovmentCounter[i] == 8) && SmovmentCounter[i] > initial) {
        if (abs(x) < 100 && abs(y) < 30) {
            Player_Health--;
            ishit = true;
        }
    }
    if (SmovmentCounter[i] == 13) {
        SmovmentCounter[i] = 0;
        Sstate[i] = Senum::S_walk;
    }
}

void Shurt(int i) {
    Smonsters[i].S.setTextureRect(SgetRect(52 + SmovmentCounter[i]));
    SupdateMonsterAnimationCounter(i);
    if (SmovmentCounter[i] == 3) {
        SmovmentCounter[i] = 0;
        Sstate[i] = Senum::S_walk;
    }
}

void Sdie(int i) {
    Smonsters[i].S.setTextureRect(SgetRect(13 + SmovmentCounter[i]));
    SupdateMonsterAnimationCounter(i);
    if (SmovmentCounter[i] == 13)
        Smonsters[i].alive = false;
}

void Screate() {
    Stexture.loadFromFile("enemies/Skeleton enemy.png");
    Soriginal.health = 5;
    Soriginal.S.setTexture(Stexture);
    Soriginal.S.setTextureRect(SgetRect(26));
    Soriginal.S.setOrigin(32, 32);
    Soriginal.S.setScale(2.5, 2.5);
}

void Sset(int Sn) {
    Snumber = Sn;
    for (int i = 0; i < Snumber; i++) {
        Smonsters[i] = Soriginal;
        SmonsterCounter[i] = 0;
        SmovmentCounter[i] = 0;
        Smonsters[i].S.setPosition(300 + rand() % 100, 6900 + rand() % 1000);
        Smonsters[i].alive = true;
        Sstate[i] = Senum::S_hurt;
    }
}

void Smove(float time, Sprite p, int attct, int& PlayerHealth, bool& IsHit) {
    Sdeltatime = time;
    for (int i = 0; i < Snumber; i++) {

        // check if alive
        if (!Smonsters[i].alive)
            continue;

        // check if S will die
        if (Smonsters[i].health <= 0 && Sstate[i] != Senum::S_die) {
            SmovmentCounter[i] = 0;
            Sstate[i] = Senum::S_die;
        }

        double x = p.getPosition().x - Smonsters[i].S.getPosition().x, y = Smonsters[i].S.getPosition().y - p.getPosition().y;

        // check if S is dying
        if (Sstate[i] == Senum::S_die) {
            Sdie(i);
            continue;
        }

        if (x < 0)
            Smonsters[i].S.setScale(Vector2f(-3, 3));
        else
            Smonsters[i].S.setScale(Vector2f(3, 3));

        // check if S is being attacked
        if (Sstate[i] != Senum::S_hurt && abs(x) < 100 && abs(y) < 100 && attct) {
            Smonsters[i].health -= attct;
            SmovmentCounter[i] = 0;
            Sstate[i] = Senum::S_hurt;
        }

        // check if doing something
        if (Sstate[i] == Senum::S_hurt) {
            Shurt(i);
            continue;
        }
        else if (Sstate[i] == Senum::S_attack) {
            Sattack(x, y, i);
            continue;
        }

        // make decision
        if (abs(x) < 100 && abs(y) < 30) {
            Sstate[i] = Senum::S_attack;
            Sattack(x, y, i);
        }
        else 
            Swalk(i);
    }
}

void Sdraw(RenderWindow& window) {
    for (int i = 0; i < Snumber; i++)
        if (Smonsters[i].alive)
            window.draw(Smonsters[i].S);
}

void NewSkeleton(Vector2f x) {
    if (Snumber >= 100) return;
    int i = Snumber;
    Smonsters[i] = Soriginal;
    SmonsterCounter[i] = 0;
    SmovmentCounter[i] = 0;
    Smonsters[i].S.setPosition(x);
    Smonsters[i].alive = true;
    Sstate[i] = Senum::S_hurt;
    Snumber++;
}