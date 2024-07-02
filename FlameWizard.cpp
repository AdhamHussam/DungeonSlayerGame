#include "FlameWizard.h"
#include "globals.h"
#include "RandomizePlaces.h"

Texture FWattackTexture, FWdeathTexture, FWhitTexture, FWidleTexture, FWrunTexture;
FlameWizard FWoriginal;
int FWmovementCounter[30];
float FWmonsterCounter[30], FWdeltatime;

const int FW_ATTACK_SPRITES = 8;
const int FW_DEATH_SPRITES = 5;
const int FW_HIT_SPRITES = 4;
const int FW_IDLE_SPRITES = 8;
const int FW_RUN_SPRITES = 8;

const int FW_SPRITE_HEIGHT = 150;
const int FW_ATTACK_WIDTH = 1200;
const int FW_DEATH_WIDTH = 750;
const int FW_HIT_WIDTH = 600;
const int FW_IDLE_WIDTH = 1200;
const int FW_RUN_WIDTH = 1200;

IntRect FWgetRect(int pos, FWState state) {
    int y = 0, x;
    switch (state) {
    case FWState::FW_idle:
    case FWState::FW_run:
        x = pos % FW_IDLE_SPRITES;
        return IntRect(x * FW_IDLE_WIDTH / FW_IDLE_SPRITES, y * FW_SPRITE_HEIGHT, FW_IDLE_WIDTH / FW_IDLE_SPRITES, FW_SPRITE_HEIGHT);
    case FWState::FW_attack:
        x = pos % FW_ATTACK_SPRITES;
        return IntRect(x * FW_ATTACK_WIDTH / FW_ATTACK_SPRITES, y * FW_SPRITE_HEIGHT, FW_ATTACK_WIDTH / FW_ATTACK_SPRITES, FW_SPRITE_HEIGHT);
    case FWState::FW_hit:
        x = pos % FW_HIT_SPRITES;
        return IntRect(x * FW_HIT_WIDTH / FW_HIT_SPRITES, y * FW_SPRITE_HEIGHT, FW_HIT_WIDTH / FW_HIT_SPRITES, FW_SPRITE_HEIGHT);
    case FWState::FW_die:
        x = pos % FW_DEATH_SPRITES;
        return IntRect(x * FW_DEATH_WIDTH / FW_DEATH_SPRITES, y * FW_SPRITE_HEIGHT, FW_DEATH_WIDTH / FW_DEATH_SPRITES, FW_SPRITE_HEIGHT);
    default:
        return IntRect(0, 0, 0, 0);
    }
}

void FWupdateAnimationCounter(int i, float interval = 0.15) {
    FWmonsterCounter[i] += FWdeltatime;
    if (FWmonsterCounter[i] >= interval) {
        FWmonsterCounter[i] = 0;
        FWmovementCounter[i]++;
    }
}

void FWclearState(int i, FWState state) {
    if (state != FWState::FW_attack) FWmonsters[i].FWattack.setPosition(-6000, -6000);
    if (state != FWState::FW_die) FWmonsters[i].FWdie.setPosition(-6000, -6000);
    if (state != FWState::FW_run) FWmonsters[i].FWrun.setPosition(-6000, -6000);
    if (state != FWState::FW_hit) FWmonsters[i].FWhit.setPosition(-6000, -6000);
    if (state != FWState::FW_idle) FWmonsters[i].FWidle.setPosition(-6000, -6000);
}

void FWidle(int i) {
    FWmonsters[i].FW.setPosition(FWmonsters[i].FW.getPosition()); // Update position here
    FWmonsters[i].FW.setTextureRect(FWgetRect(FWmovementCounter[i], FWState::FW_idle));
    FWupdateAnimationCounter(i);
    FWmovementCounter[i] %= FW_IDLE_SPRITES;
}

void FWattack(int x, int y, int i) {
    FWmonsters[i].FW.setPosition(FWmonsters[i].FW.getPosition()); // Update position here
    FWmonsters[i].FW.setTextureRect(FWgetRect(FWmovementCounter[i], FWState::FW_attack));
    int initial = FWmovementCounter[i];
    FWupdateAnimationCounter(i, FWmonsters[i].AttackSpeed);
    if (FWmovementCounter[i] == FW_ATTACK_SPRITES - 1 && FWmovementCounter[i] > initial) {
        if (abs(x) < 100 && abs(y) < 30) {
            Player_Health -= FWmonsters[i].damage;
            ishit = true;
        }
    }
    if (FWmovementCounter[i] == FW_ATTACK_SPRITES) {
        FWmovementCounter[i] = 0;
        FWmonsters[i].state = FWState::FW_idle;
        FWclearState(i, FWState::FW_idle);
        FWmonsters[i].FW = FWmonsters[i].FWidle;
    }
}

void FWhit(int i) {
    FWmonsters[i].FW.setPosition(FWmonsters[i].FW.getPosition()); // Update position here
    FWmonsters[i].FW.setTextureRect(FWgetRect(FWmovementCounter[i], FWState::FW_hit));
    FWupdateAnimationCounter(i);
    if (FWmovementCounter[i] == FW_HIT_SPRITES) {
        FWmovementCounter[i] = 0;
        FWmonsters[i].state = FWState::FW_idle;
        FWclearState(i, FWState::FW_idle);
        FWmonsters[i].FW = FWmonsters[i].FWidle;
    }
}

void FWdie(int i) {
    FWmonsters[i].FW.setPosition(FWmonsters[i].FW.getPosition()); // Update position here
    FWmonsters[i].FW.setTextureRect(FWgetRect(FWmovementCounter[i], FWState::FW_die));
    FWupdateAnimationCounter(i);
    if (FWmovementCounter[i] == FW_DEATH_SPRITES) {
        FWmonsters[i].alive = false;
        if (level > 1) AblazeCharge += 2;
        else AblazeCharge += 10;
    }
}

void FWrun(int i) {
    FWmonsters[i].FW.setPosition(FWmonsters[i].FW.getPosition()); // Update position here
    FWmonsters[i].FW.setTextureRect(FWgetRect(FWmovementCounter[i], FWState::FW_run));
    Vector2f Direction = Player.getPosition() - FWmonsters[i].FW.getPosition();
    float magnitude = sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    Vector2f norm_direction = Direction / magnitude;
    FWmonsters[i].FW.move(Vector2f(norm_direction.x * FWmonsters[i].speed * FWdeltatime, norm_direction.y * FWmonsters[i].speed * FWdeltatime));
    CheckMonsterCollisions(FWmonsters[i].FW, abs(norm_direction.x * FWmonsters[i].speed * FWdeltatime), abs(norm_direction.y * FWmonsters[i].speed * FWdeltatime));
    FWupdateAnimationCounter(i);
    FWmovementCounter[i] %= FW_RUN_SPRITES;
}

void FWcreate() {
    FWattackTexture.loadFromFile("enemies2/Flame_wizard/attack.png");
    FWdeathTexture.loadFromFile("enemies2/Flame_wizard/death.png");
    FWhitTexture.loadFromFile("enemies2/Flame_wizard/hit.png");
    FWidleTexture.loadFromFile("enemies2/Flame_wizard/idle.png");
    FWrunTexture.loadFromFile("enemies2/Flame_wizard/run.png");

    FWoriginal.health = 7;
    FWoriginal.FWidle.setTexture(FWidleTexture);
    FWoriginal.FWattack.setTexture(FWattackTexture);
    FWoriginal.FWhit.setTexture(FWhitTexture);
    FWoriginal.FWdie.setTexture(FWdeathTexture);
    FWoriginal.FWrun.setTexture(FWrunTexture);

    FWoriginal.FWidle.setTextureRect(FWgetRect(0, FWState::FW_idle));
    FWoriginal.FWidle.setOrigin(FW_SPRITE_HEIGHT / 2, FW_SPRITE_HEIGHT / 2);
    FWoriginal.FWidle.setScale(3, 3);

    FWoriginal.FW = FWoriginal.FWidle;
}

void FWset(int FWn) {
    for (int i = 0; i < FWn; i++) {
        FWmonsters[i] = FWoriginal;
        FWmonsterCounter[i] = 0;
        FWmovementCounter[i] = 0;
        int x, y;
        RandPosition(x, y);
        FWmonsters[i].FW.setPosition(x, y);
        FWmonsters[i].alive = true;
        FWmonsters[i].state = FWState::FW_idle;
    }
}

void FWmove(float time, Sprite p, int attct, int& PlayerHealth, bool& IsHit) {
    FWdeltatime = time;
    for (int i = 0; i < 30; i++) {
        if (!FWmonsters[i].alive)
            continue;

        room_cleared = false;

        if (FWmonsters[i].health <= 0 && FWmonsters[i].state != FWState::FW_die) {
            FWmovementCounter[i] = 0;
            FWmonsters[i].state = FWState::FW_die;
            FWclearState(i, FWState::FW_die);
            FWmonsters[i].FW = FWmonsters[i].FWdie;
            continue;
        }

        double x = p.getPosition().x - FWmonsters[i].FW.getPosition().x;
        double y = FWmonsters[i].FW.getPosition().y - p.getPosition().y;
        if (x < 0)
            FWmonsters[i].FW.setScale(Vector2f(-3, 3));
        else
            FWmonsters[i].FW.setScale(Vector2f(3, 3));

        FWmonsters[i].cooldown -= FWdeltatime;

        if (FWmonsters[i].cooldown <= 0 && abs(x) < 300 && abs(y) < 100) {
            FWmonsters[i].cooldown = 3;
            FWmonsters[i].state = FWState::FW_attack;
            FWclearState(i, FWState::FW_attack);
            FWmonsters[i].FW = FWmonsters[i].FWattack;
            FWmovementCounter[i] = 0;
        }

        if (FWmonsters[i].state == FWState::FW_attack) {
            FWattack(x, y, i);
            continue;
        }

        if (abs(x) < 200 && abs(y) < 30) {
            FWmonsters[i].state = FWState::FW_attack;
            FWattack(x, y, i);
        }
        else {
            FWmonsters[i].state = FWState::FW_run;
            FWrun(i);
        }
    }
}

void FWdraw(RenderWindow& window) {
    for (int i = 0; i < 30; i++) {
        if (FWmonsters[i].alive) {
            window.draw(FWmonsters[i].FW);
            if (level == 1)
                gui.drawBossHP(FWmonsters[i].health, 60);
            else
                gui.DrawMonsterHP(FWmonsters[i].FW.getPosition(), FWmonsters[i].health, 7, 20, 15);
        }
    }
}
