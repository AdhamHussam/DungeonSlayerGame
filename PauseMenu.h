#pragma once
#include "includes.h"

class PauseMenu
{
public:
    Text pausemenu[4];
    PauseMenu(float width, float height);
    void draw(RenderWindow& window);
    void moveup();
    void movedown();

    void setSelected(int n);
    int pressed() {
        return selectedp;

    }
    ~PauseMenu();
    int selectedp;
private:
    Font Pfont;
};

