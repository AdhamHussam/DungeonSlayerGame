#include "includes.h"
#include "Monsters.h"
#include "globals.h"

void SetMonstersSprites() {
	CreateMonsters();
}

void SetMonstersWave() {
	SetMonsters();
}

void MoveMonsters() {
	MonstersMovment();
}

void ShowMonsters() {
    for (int i = 0; i < BODnumber; i++)
        if (BODalive[i]) {
            window.draw(BODmonsters[i].BOD);
            if (showBODSpell[i])
                window.draw(BODmonsters[i].spell);
        }
}