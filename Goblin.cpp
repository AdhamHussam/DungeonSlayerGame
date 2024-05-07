#include "Goblin.h"
#include "globals.h"

Texture goblinTexture, bombTexture, attackTexture, hitTexture;
Goblin Base, goblins[30];
int animation_speed = 0.05;
Vector2f scale = { 1.7, 1.7 };
Vector2f oppos = { -1.7, 1.7 };

void GBLNcreate() {
    goblinTexture.loadFromFile("enemies/Goblin/Run.png");
    Base.GBLN_run.setTexture(goblinTexture);
    attackTexture.loadFromFile("enemies/Goblin/Attack2.png");
    Base.G_Attack.setTexture(attackTexture);
    hitTexture.loadFromFile("enemies/Goblin/Take Hit.png");
    Base.G_Hit.setTexture(hitTexture);
    bombTexture.loadFromFile("enemies/Goblin/Bomb_sprite.png");
    Base.G_Bomb.setTexture(bombTexture);
    Base.current = Base.GBLN_run;
    Base.current.setPosition(300, 1700);

    Base.position = Vector2f(0, 0);
    Base.speed = 100;
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
    Base.current.setOrigin(32, 32);
    Base.current.setScale(scale);
    Base.isAlive = true;
    Base.throwBomb = false;
}

void GBLNset(int gbln_num) {
    for (int i = 0; i < gbln_num; i++) {
        goblins[i] = Base;
    }
}

void GBLNdraw(int gbln_num) {
    for (int i = 0; i < gbln_num; i++) {
        // goblins[i].current.setScale(2.5, 2.5);
        window.draw(goblins[i].current);
    }
}

void GBLNupdateRunAttack(Goblin& goblin) {
    goblin.MonsterCounter += playerdeltatime;
    if (goblin.MonsterCounter > goblin.animationSpeed) {
        goblin.MonsterCounter = 0;
        goblin.currentFrame = (goblin.currentFrame + 1) % goblin.runAttackTotalFrames;
        goblin.textureRect.left = goblin.currentFrame * goblin.runAttackFrameWidth;
        goblin.textureRect.top = 0; // each png has one row only
        goblin.textureRect.height = goblin.runAttackFrameHeight;
        goblin.textureRect.width = goblin.runAttackFrameWidth;
        goblin.current.setTextureRect(goblin.textureRect);
    }
}

void GBLNupdateDeath(Goblin& goblin) {
    goblin.MonsterCounter += playerdeltatime;
    if (goblin.MonsterCounter > goblin.animationSpeed) {
        goblin.MonsterCounter = 0;
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
    goblin.MonsterCounter += playerdeltatime;
    if (goblin.MonsterCounter > goblin.animationSpeed) {
        goblin.MonsterCounter = 0;
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
        Player_Health -= 1;
        ishit = true;
    }

    if (goblin.currentFrame % 8 == 0) {
        goblin.currentFrame = 0;
        GoblinSwitchState(goblin, GoblinState::Run);
    }
}

void GBLNdie(Goblin& goblin) {
    GBLNupdateDeath(goblin);
    if (goblin.MonsterCounter == 4) {
        goblin.isAlive = false;
    }
}

void GBLNspawn(Goblin& goblin) {
    goblin.speed = 200;
    goblin.power = 10;
    goblin.cooldown = 5;
    goblin.health = 10;
    GoblinSwitchState(goblin, GoblinState::Run);
    goblin.MonsterCounter = 0;
}

void GBLhit(Goblin& goblin) {
    GBLNupdateDeath(goblin);
    if (goblin.MonsterCounter == 4) {
        goblin.MonsterCounter = 0;
        GoblinSwitchState(goblin, GoblinState::Run);
    }
}

void GoblinSwitchState(Goblin& goblin, GoblinState state) {
    Vector2f position = goblin.current.getPosition();
    switch (state) {
    case GoblinState::Attack:
        goblin.G_Attack.setPosition(position);
        goblin.current = goblin.G_Attack;
        break;
    case GoblinState::Run:
    case GoblinState::Spawn:
        goblin.GBLN_run.setPosition(position);
        goblin.current = goblin.GBLN_run;
        break;
    case GoblinState::Hit:
        goblin.G_Hit.setPosition(position);
        goblin.current = goblin.G_Hit;
        break;
    default:
        break;
    }

    goblin.state = state;
    goblin.MonsterCounter = 0;
}

void GoblinDynamics(int gbln_num, int attct) {
    for (int i = 0; i < gbln_num; i++) {
        if (!goblins[i].isAlive)
            continue;

        // Check if goblin health is depleted
        if (goblins[i].health <= 0 && goblins[i].state != GoblinState::Death) {
            GoblinSwitchState(goblins[i], GoblinState::Death);
            continue;
        }

        // Handle death state
        if (goblins[i].state == GoblinState::Death) {
            GBLNdie(goblins[i]);
            continue;
        }

        // Handle spawn state
        if (goblins[i].state == GoblinState::Spawn) {
            GBLNspawn(goblins[i]);
            continue;
        }

        // Calculate distance between goblin and player
        double x = Player.getPosition().x - goblins[i].current.getPosition().x;
        double y = Player.getPosition().y - goblins[i].current.getPosition().y;

        // Set goblin scale based on player position
        if (x < 0)
            goblins[i].current.setScale(oppos);
        else
            goblins[i].current.setScale(scale);

        // Handle goblin attack cooldown
        goblins[i].cooldown -= playerdeltatime;

        // Check if goblin is hit by player's attack
        if (goblins[i].state != GoblinState::Hit && abs(x) < 100 && abs(y) < 100 && attct > 0) {
            goblins[i].health -= attct;
            GoblinSwitchState(goblins[i], GoblinState::Hit);
            ishit = true;
            continue;
        }

        // Handle goblin hit state
        if (goblins[i].state == GoblinState::Hit) {
            GBLhit(goblins[i]);
            continue;
        }

        // Handle goblin attack state
        if (goblins[i].state == GoblinState::Attack) {
            GBLattack(x, y, goblins[i]);
            continue;
        }

        // Make decision for goblin movement or attack
        if (goblins[i].cooldown <= 0 && abs(x) < 100 && abs(y) < 30 && goblins[i].state != GoblinState::Attack) {
            GoblinSwitchState(goblins[i], GoblinState::Attack);
            GBLattack(x, y, goblins[i]);
        }
        else {
            GBLNmove(goblins[i]);
        }
    }
}
/*
void GoblinDynamics(int gbln_num, int attct) {
    for (int i = 0; i < gbln_num; i++) {
        if (!goblins[i].isAlive) continue;
        /*

        if (goblins[i].health == 0 && goblins[i].state != GoblinState::Death) {
            GoblinSwitchState(goblins[i], GoblinState::Death);
        }

        if (goblins[i].state == GoblinState::Death) {
            GBLNdie(goblins[i]);
            continue;
        }

        if (goblins[i].state == GoblinState::Spawn) {
            GBLNspawn(goblins[i]);
            continue;
        }
        
        double x = Player.getPosition().x - goblins[i].current.getPosition().x; 
        double y = Player.getPosition().y - goblins[i].current.getPosition().y;
        
        // Smoothly transition the scale when turning left or right
        float scaleSpeed = 0.1; // Adjust this value for the transition speed
        Vector2f targetScale = (x < 0) ? oppos : scale;
        goblins[i].current.setScale(goblins[i].current.getScale() + scaleSpeed * (targetScale - goblins[i].current.getScale()));


        goblins[i].cooldown -= playerdeltatime;
        /*
        if (goblins[i].state != GoblinState::Hit && abs(x) < 100 && abs(y) < 100 && attct) {
            goblins[i].health -= attct;
            GoblinSwitchState(goblins[i], GoblinState::Hit);
        }

        // check if doing something
        if (goblins[i].state == GoblinState::Hit) {
            GBLhit(goblins[i]);
            continue;
        }
        else if (goblins[i].state == GoblinState::Attack) {
            GBLattack(x, y, goblins[i]);
            continue;
        }

        // make decision
        if (goblins[i].cooldown <= 0) {
            goblins[i].cooldown = 0;
        }
        else if (abs(x) < 100 && abs(y) < 30 && goblins[i].state != GoblinState::Attack) {
            GoblinSwitchState(goblins[i], GoblinState::Attack);
            GBLattack(x, y, goblins[i]);
        }

        else  GBLNmove(goblins[i]);
    }
}*/
