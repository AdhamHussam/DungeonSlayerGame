#include "includes.h"
#include "Monsters.h"
#include "globals.h"
#include "Skeleton.h"
#include "ShardSoul.h"
#include "BrainMole.h"
#include "Rogue.h"

void SetMonstersSprites() {
	CreateMonsters();
    AACreate();
    NBcreate();
    GBLNcreate();
    Screate();
    SScreate();
    BMcreate();
    Rcreate();
}

void SetMonstersWave() {
    BODnumber = 0;
    int AAnumber = 0, NBnumber = 0, Snumber = 0, SSnumber = 0, BMnumber = 0, Rnumber = 0;
	SetMonsters();
    NBset(NBnumber);
    AASet(AAnumber);
    GBLNset(1);
    Sset(Snumber);
    SSset(SSnumber);
    BMset(BMnumber);
    Rset(Rnumber);
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
    GoblinDynamics(1);
    Smove(playerdeltatime, Player, attct, Player_Health, ishit);
    SSmove(playerdeltatime, Player, attct, Player_Health);
    BMmove(playerdeltatime, Player, attct, Player_Health);
    Rmove(playerdeltatime, Player, attct, Player_Health);
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
    GBLNdraw(1);
    Sdraw(window);
    SSdraw(window);
    BMdraw(window);
    Rdraw(window);
}