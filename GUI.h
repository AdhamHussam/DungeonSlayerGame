
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
    GUIskill skills[4];
    Sprite PlayerInfo;
    Sprite healthBar;
    Sprite armorBar;
    Sprite staminaBar;
    int framenum = 1;

    RectangleShape skills_background;
    void setSkillsTexture();
    void updateSkill();
    void updatePlayerInfo(RenderWindow&window);
    void drawGUI(RenderWindow& window);
    void setPlayerInfoTexture();

    GUI() = default;
};