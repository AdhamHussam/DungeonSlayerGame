#include "includes.h"
#include "Monsters.h"
#include "globals.h"
#include "Skeleton.h"
#include "ShardSoul.h"
#include "BrainMole.h"

void SetMonstersSprites() {
	CreateMonsters();
    AACreate();
    NBcreate();
    Screate();
    SScreate();
    BMcreate();
}

void SetMonstersWave() {
    BODnumber = 1;
    int AAnumber = 1, NBnumber = 1,Snumber = 1,SSnumber = 1,BMnumber = 2;
	SetMonsters();
    NBset(NBnumber);
    AASet(AAnumber);
    Sset(Snumber);
    SSset(SSnumber);
    BMset(BMnumber);
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
    NBmove(playerdeltatime, Player, attct, Player_Health, ishit);
    AAMove(playerdeltatime,Player,attct,Player_Health,ishit);
    Smove(playerdeltatime, Player, attct, Player_Health, ishit);
    SSmove(playerdeltatime, Player, attct, Player_Health);
    BMmove(playerdeltatime, Player, attct, Player_Health);
}

void ShowMonsters() {
    for (int i = 0; i < BODnumber; i++)
        if (BODalive[i]) {
            window.draw(BODmonsters[i].BOD);
            if (showBODSpell[i])
                window.draw(BODmonsters[i].spell);
        }
    AADraw(window);
    NBdraw(window);
    Sdraw(window);
    SSdraw(window);
    BMdraw(window);
}