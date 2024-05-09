
#pragma once

#include "includes.h"

struct GUIskill {
    Font font;
    Texture photo;
    Texture myFrame;
    pair<int, int> pos;

    void drawSkill(RenderWindow& window, int id);


    GUIskill() = default;
};






struct GUI {
    Texture skillframe;
    Texture loadingframe;
    Texture PlayerInfoTexture;
    Texture healthBarTexture;
    Texture armorBarTexture;
    Texture staminaBarTexture;
    Texture loadingEffectTexture;
    Texture monsterHPBackTexture;
Texture monsterHPTexture;
    GUIskill skills[4];
    Sprite PlayerInfo;
    Sprite healthBar;
    Sprite armorBar;
    Sprite staminaBar;
    Sprite loadingEffect;
    Sprite monsterHPBack;
    Sprite monsterHP;
    int framenum = 1;

    RectangleShape skills_background;
    void setSkillsTexture();
    void updateSkill();
    void updatePlayerInfo(RenderWindow&window);
    void drawGUI(RenderWindow& window);
    void DrawloadingEffect(RenderWindow& window);
    void setPlayerInfoTexture();

    void setMonstersHPTexture();

    void DrawMonsterHP(Vector2f pos, float health, int origHealth, int xdif, int ydif);
    void drawBODHP(Vector2f pos, float health);
    void drawBossHP(float health);

    GUI() = default;
};