
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
    GUIskill skills[4];
    int framenum = 1;

    RectangleShape skills_background;
    void setSkillsTexture();
    void updateSkill();
    void drawGUI(RenderWindow& window);

    GUI() = default;
};