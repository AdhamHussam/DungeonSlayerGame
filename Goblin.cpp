#include "Goblin.h"
#include "globals.h"

Texture goblinTexture, bombTexture, attackTexture, hitTexture;
Goblin Base, goblins[30];
int animation_speed = 0.15;

void GBLNcreate() {
    goblinTexture.loadFromFile("D:/Ali/Dungeon Slayer Final/DungeonSlayerGame/enemies/Goblin/Run.png");
    Base.GBLN_run.setTexture(goblinTexture);
    attackTexture.loadFromFile("D:/Ali/Dungeon Slayer Final/DungeonSlayerGame/enemies/Goblin/Attack2.png");
    Base.G_Attack.setTexture(attackTexture);
    hitTexture.loadFromFile("D:/Ali/Dungeon Slayer Final/DungeonSlayerGame/enemies/Goblin/Take Hit.png");
    Base.G_Hit.setTexture(hitTexture);
    bombTexture.loadFromFile("D:/Ali/Dungeon Slayer Final/DungeonSlayerGame/enemies/Goblin/Bomb_sprite.png");
    Base.G_Bomb.setTexture(bombTexture);
    Base.current = Base.GBLN_run;

    Base.position = Vector2f(0, 0);
    Base.speed = 200;
    Base.power = 10;
    Base.cooldown = 5;
    Base.health = 10;
    Base.state = GoblinState::Run;
    Base.currentFrame = 0;
    Base.runAttackTotalFrames = 8;
    Base.runAttackFrameHeight = 150 / 1;
    Base.runAttackFrameWidth = 1200 / Base.runAttackTotalFrames;
    Base.bomTotalFrames = 19;
    Base.bombFrameHeight = 100 / 1;
    Base.bombFrameWidth = 1900 / 19;
    Base.deathTotalFrames = 4;
    Base.deathFrameHeight = 150 / 1;
    Base.deathFrameWidth = 600 / 4;
    Base.animationSpeed = animation_speed;
}

void GBLNset(int gbln_num) {
    for (int i = 0; i < gbln_num; i++) {
        goblins[i] = Base;
    }
}

void GBLNupdateRunAttack(Goblin& goblin) {
    if (goblin.clock.getElapsedTime().asMilliseconds() > goblin.animationSpeed) {
        goblin.clock.restart();
        goblin.currentFrame = (goblin.currentFrame + 1) % goblin.runAttackTotalFrames;
        goblin.textureRect.left = goblin.currentFrame * goblin.runAttackFrameWidth;
        goblin.textureRect.top = 0; // each png has one row only
        goblin.textureRect.height = goblin.runAttackFrameHeight;
        goblin.textureRect.width = goblin.runAttackFrameWidth;
        goblin.current.setTextureRect(goblin.textureRect);
    }
}

void GBLNupdateDeath(Goblin& goblin) {
    if (goblin.clock.getElapsedTime().asMilliseconds() > goblin.animationSpeed) {
        goblin.clock.restart();
        goblin.currentFrame = (goblin.currentFrame + 1) % goblin.deathTotalFrames;
        goblin.textureRect.left = goblin.currentFrame * goblin.deathFrameWidth;
        goblin.textureRect.top = 0; // each png has one row only
        goblin.textureRect.height = goblin.deathFrameHeight;
        goblin.textureRect.width = goblin.deathFrameWidth;
        goblin.current.setTextureRect(goblin.textureRect);
    }
}

void GBLNupdateBomb(Goblin& goblin) {
    // for animation
    if (goblin.clock.getElapsedTime().asMilliseconds() > goblin.animationSpeed) {
        goblin.clock.restart();
        goblin.currentFrame = (goblin.currentFrame + 1) % goblin.bomTotalFrames;
        goblin.textureRect.left = goblin.currentFrame * goblin.bombFrameWidth;
        goblin.textureRect.top = 0; // each png has one row only
        goblin.textureRect.height = goblin.bombFrameHeight;
        goblin.textureRect.width = goblin.bombFrameWidth;
        goblin.current.setTextureRect(goblin.textureRect);
    }
}

void GBLNmove(Goblin& goblin) {
    // direct goblin towards player
    Vector2f Direction = Player.getPosition() - goblin.current.getPosition();
    float magnitude = sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    Vector2f norm_direction = Direction / magnitude;
    goblin.current.move(Vector2f(norm_direction.x * goblin.speed * playerdeltatime, norm_direction.y * goblin.speed * playerdeltatime));
    GBLNupdateRunAttack(goblin);
}

void GBLNdraw(int gbln_num) {
    for (int i = 0; i < gbln_num; i++) {
        goblins[i].current.setPosition(400 + rand() % 100, 6200 + rand() % 1000);
        goblins[i].current.setOrigin(32, 32);
        goblins[i].current.setScale(2.5, 2.5);
        window.draw(goblins[i].current);
    }
}

void GBLattack(int x, int y, Goblin& goblin) {
    
    /*
    if (goblin.currentFrame == 0) {
        Vector2f position = goblin.current.getPosition();
        goblin.G_Attack.setPosition(position);
        goblin.current = goblin.G_Attack;
    }
    */
    GBLNupdateRunAttack(goblin);

    if (goblin.currentFrame == 7 && (abs(x) < 200 && abs(y) < 30)) {
        Player_Health -= 5;
        ishit = true;
    }

    if (goblin.currentFrame % 8 == 0) {
        goblin.currentFrame = 0;
    }
}

void GoblinDynamics(int gbln_num) {
    for (int i = 0; i < gbln_num; i++) {
        int x = Player.getPosition().x - goblins[i].current.getPosition().x; 
        int y = Player.getPosition().y - goblins[i].current.getPosition().y;

        if (abs(x) < 200 && abs(y) < 30) {
            goblins[i].state = GoblinState::Attack;
        }
        else goblins[i].state = GoblinState::Run;

        if (goblins[i].state == GoblinState::Attack) {
            GBLattack(x, y, goblins[i]);
        }
        else GBLNmove(goblins[i]);
    }
}



void GBLhit(Goblin& goblin) {

}