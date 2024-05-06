#include "includes.h"
#include "Monsters.h"
#include "globals.h"

void SetMonstersSprites() {
	CreateMonsters();
    AACreate();
}

void SetMonstersWave() {
    int AAnumber = 3;
	SetMonsters();
    AASet(AAnumber);
}

void MoveMonsters() {
    int attct = 0;
    if (curr_state == player_base)
        attct = 1;
    else if (curr_state == player_xmove)
        attct = 3;
    else if (curr_state == player_cmove)
        attct = 5;
    else if (curr_state == player_vmove)
        attct = 10;
	MonstersMovment();
    AAMove(playerdeltatime,Player,attct,Player_Health);
}

void ShowMonsters() {
    for (int i = 0; i < BODnumber; i++)
        if (BODalive[i]) {
            window.draw(BODmonsters[i].BOD);
            if (showBODSpell[i])
                window.draw(BODmonsters[i].spell);
        }
    AADraw(window);
}