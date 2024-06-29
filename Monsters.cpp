#include "includes.h"
#include "Monsters.h"
#include "globals.h"
#include "Skeleton.h"
#include "ShardSoul.h"
#include "BrainMole.h"
#include "Rogue.h"
#include "RandomizePlaces.h"

void SetMonstersSprites() {
	CreateMonsters();
    AACreate();
    NBcreate();
    create_goblins();
    Screate();
    SScreate();
    BMcreate();
    Rcreate();
}

void SetMonstersWave() {
    MonsterNumber();
	SetMonsters();
    NBset(NightBroneNumber);
    AASet(ArcaneArcherNumber);
    set_goblins(GoblinNumber);
    Sset(SkeletonNumber);
    SSset(ShardSoulNumber);
    BMset(BrainMoleNumber);
    Rset(RogueNumber);
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
    room_cleared = true;
	MonstersMovment();
    Rmove(playerdeltatime, Player, attct, Player_Health);
    NBmove(playerdeltatime, Player, attct, Player_Health, ishit);
    AAMove(playerdeltatime,Player,attct,Player_Health,ishit);
    goblins_move(GoblinNumber, attct);
    Smove(playerdeltatime, Player, attct, Player_Health, ishit);
    SSmove(playerdeltatime, Player, attct, Player_Health);
    BMmove(playerdeltatime, Player, attct, Player_Health);
 //   room_cleared = true;

}

void ShowMonsters() {
    for (int i = 0; i < BODnumber; i++)
        if (BODalive[i]) {
            window.draw(BODmonsters[i].BOD);
            gui.drawBODHP(BODmonsters[i].BOD.getPosition(), BODmonsters[i].health / 10.0);
            if (showBODSpell[i])
                window.draw(BODmonsters[i].spell);
        }
    AADraw(window);
    NBdraw(window);
    draw_goblin(window, GoblinNumber);
    Sdraw(window);
    SSdraw(window);
    BMdraw(window);
    Rdraw(window);
}

void ResetMonsters() {
    BODnumber = 0;
    ArcaneArcherNumber = 0;
    NightBroneNumber = 0;
    SkeletonNumber = 0;
    ShardSoulNumber = 0;
    BrainMoleNumber = 0;
    RogueNumber = 0;
    GoblinNumber = 0;
}