#include "includes.h"
#include "Monsters.h"
#include "globals.h"
#define LENGTH 1921
#define WIDTH 1081

enum BOD {
    BODwalk, BODattack, BODcast, BODhurt, BODdie
};

bool inBound(int row, int col) {
    return (row >= 0 && col >= 0 && row < LENGTH && col < WIDTH);
}

int heuristic(int startx, int starty, int endx, int endy) {
    // calculate the heuristic term h essential to A* Algorithm
    int dx = abs(startx - endx);
    int dy = abs(starty - endy);
    int h = 1 * (dx + dy) + (1 - 2 * 1) * min(dx, dy);
    return h;
}

// Time to move
int grid[LENGTH][WIDTH];
// traversing the grid using A* algrithm to find the shortest path 
ParentsCostPair Astar(int startx, int starty, int endx, int endy) {   
    for (int x = 0; x < LENGTH; x++) {
        for (int y = 0; y < WIDTH; y++) {
            grid[x][y] = 1; // cost of every cell movement
        }
    }

    vector<vector<Coordinates>> parents;
    vector<vector<int>> cost(LENGTH, vector<int>(WIDTH, INT32_MAX));
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    Cell start_cell;
    start_cell.cost = 0;
    start_cell.node.x = startx;
    start_cell.node.y = starty;
    pq.push(start_cell); // Our Monster Location 
    int rd[] = {0, 0, -1, +1, -1, +1, -1, +1};
    int cd[] = {-1, +1, 0, 0, -1, +1, +1, -1};
    cost[startx][starty] = 0;

    while (!pq.empty()) {
        Cell current_cell = pq.top();
        int row = current_cell.node.x;
        int col = current_cell.node.y;
        int cur_cost = current_cell.cost;

        if (cur_cost > cost[row][col])
            continue;

        // Visit neighbors of current cell
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int ch_row = row + rd[i]; // child row
                int ch_col = row + cd[i]; // child column
                int h = heuristic(ch_row, ch_col, endx, endy);
                bool is_better_cost = cost[ch_row][ch_col] > cur_cost + grid[ch_row][ch_col] + h;

                if (inBound(ch_row, ch_col) && is_better_cost) {
                    cost[ch_row][ch_col] = cur_cost + grid[ch_row][ch_col] + h;
                    Cell child_cell;
                    child_cell.cost = cost[ch_row][ch_col];
                    child_cell.node = { ch_row, ch_col };
                    parents[ch_row][ch_col] = current_cell.node;
                    pq.push(child_cell);

                    if (ch_row == endx && ch_col == endy) {
                        return { parents, cost };
                    }
                }
            }
        }

        return { parents, cost };
    }
}

// animation counters
int MovmentCounter[30];
float MonsterCounter[30];

// function for setting rectangle of texture
IntRect getRect(int pos) {
    int x = pos%8;
    int y = pos/8;
    return IntRect(x*140, y*93, 140, 93);
}

// updating sprites animation
void UpdateMonsterAnimationCounter(int i,float st = 0.15){
    MonsterCounter[i] += playerdeltatime;
    if (MonsterCounter[i] >= st)
    {
        MonsterCounter[i] = 0;
        MovmentCounter[i]++;
    }
}

// make monster walk
/*
void walk(int x, int y) {
    BODmonsters[0].BOD.setTextureRect(getRect(8 + MovmentCounter));
    
    BODmonsters[0].BOD.move(((abs(x) > 1) ? ((x > 0) ? BODmonsters[0].speed : -BODmonsters[0].speed) : 0), ((y < 0) ? BODmonsters[0].speed : -BODmonsters[0].speed));
    
    sf::Vector2f player_position = Player.getPosition();
    sf::Vector2f monster_position = BODmonsters[0].BOD.getPosition();
    ParentsCostPair front = Astar(monster_position.x, monster_position.y, player_position.x + 1, player_position.y);
    int to_x = front.parents[player_position.x + 1][player_position.y].x;
    int to_y = front.parents[player_position.x + 1][player_position.y].y;
    BODmonsters[0].BOD.move(to_x, to_y);
    //
    UpdateMonsterAnimationCounter();
    MovmentCounter %= 8;
}
*/
    
void walk(int x, int y, int i) {
    BODmonsters[i].BOD.setTextureRect(getRect(8 + MovmentCounter[i]));
    //BODmonsters[i].BOD.move(((abs(x) > 1) ? ((x > 0) ? BODmonsters[i].speed*playerdeltatime : -BODmonsters[i].speed* playerdeltatime) : 0), ((y < 0) ? BODmonsters[i].speed* playerdeltatime : -BODmonsters[i].speed* playerdeltatime));
    sf::Vector2f player_position = Player.getPosition();
    sf::Vector2f monster_position = BODmonsters[i].BOD.getPosition();
    ParentsCostPair front = Astar(monster_position.x, monster_position.y, player_position.x + 1, player_position.y);
    int to_x = front.parents[player_position.x + 1][player_position.y].x;
    int to_y = front.parents[player_position.x + 1][player_position.y].y;
    BODmonsters[i].BOD.move(to_x, to_y);
    UpdateMonsterAnimationCounter(i);
    MovmentCounter[i] %= 8;

}


// make monster attack
void attack(int x,int y, int i) {
    BODmonsters[i].BOD.setTextureRect(getRect(16 + MovmentCounter[i]));
    int initial = MovmentCounter[i];
    UpdateMonsterAnimationCounter(i);
    if (MovmentCounter[i] == 5 && MovmentCounter[i] > initial) {
        if (abs(x) < 200 && abs(y) < 30) {
            Player_Health -= 5;
            ishit = true;
        }
    }
    if (MovmentCounter[i] == 10) {
        MovmentCounter[i] = 0;
        BODstate[i] = BOD::BODwalk;
    }
}

// make monster cast his spell
void cast(int i) {
    BODmonsters[i].BOD.setTextureRect(getRect(39 + MovmentCounter[i]));
    BODmonsters[i].spell.setTextureRect(getRect(52 + MovmentCounter[i]));
    UpdateMonsterAnimationCounter(i);
    if (MovmentCounter[i] == 9) {
        MovmentCounter[i] = 0;
        BODstate[i] = BOD::BODwalk;
    }
}

// make monster take damage
void hurt(int i) {
    BODmonsters[i].BOD.setTextureRect(getRect(27 + ((MovmentCounter[i] > 4) ? 8 - MovmentCounter[i] : MovmentCounter[i])));
    UpdateMonsterAnimationCounter(i);
    if (MovmentCounter[i] == 9) {
        MovmentCounter[i] = 0;
        BODstate[i] = BOD::BODwalk;
    }
}

// make monster die
void die(int i) {
    BODmonsters[i].BOD.setTextureRect(getRect(29 + MovmentCounter[i]));
    UpdateMonsterAnimationCounter(i);
    if (MovmentCounter[i] == 10)
        BODalive[i] = false;
}

// update monster
void MonstersMovment() {
    for (int i = 0; i < BODnumber; i++){

        // hide BOD spell
        showBODSpell[i] = false;

        // check that BOD is alive
        if (!BODalive[i])
            continue;
        if (BODstate[i] == BOD::BODdie) {
            die(i);
            continue;
        }

        // check distance between BOD and Player and make BOD look forward Player
        double x = Player.getPosition().x - BODmonsters[i].BOD.getPosition().x, y = BODmonsters[i].BOD.getPosition().y - Player.getPosition().y;
        if (x > 0)
            BODmonsters[i].BOD.setScale(Vector2f(-2, 2));
        else
            BODmonsters[i].BOD.setScale(Vector2f(2, 2));


        // passing time for cooldown
        BODmonsters[i].cooldown -= playerdeltatime;

        // check if BOD is being attacked
        if (BODstate[i] != BOD::BODhurt && abs(x) < 100 && abs(y) < 100) {
            if (curr_state == player_base) {
                BODmonsters[i].health--;
                MovmentCounter[i] = 0;
                BODstate[i] = BOD::BODhurt;
            }
            else if (curr_state == player_xmove) {
                BODmonsters[i].health -= 3;
                MovmentCounter[i] = 0;
                BODstate[i] = BOD::BODhurt;
            }
            else if (curr_state == player_cmove) {
                BODmonsters[i].health -= 5;
                MovmentCounter[i] = 0;
                BODstate[i] = BOD::BODhurt;
            }
            else if (curr_state == player_vmove) {
                BODmonsters[i].health -= 10;
                MovmentCounter[i] = 0;
                BODstate[i] = BOD::BODhurt;
            }
        }

        // check if BOD is doing somthing
        if (BODstate[i] == BOD::BODhurt) {
            if (BODmonsters[i].health <= 0) {
                die(i);
                BODstate[i] = BOD::BODdie;
            }
            else
                hurt(i);
            continue;
        }
        else if (BODstate[i] == BOD::BODcast) {
            cast(i);
            showBODSpell[i] = true;
            continue;
        }
        else if (BODstate[i] == BOD::BODattack) {
            attack(x, y, i);
            continue;
        }



        // making BOD decision
        if ((long long)abs(x) * abs(x) + abs(y) * abs(y) < 100000 && BODmonsters[i].cooldown <= 0) {
            BODmonsters[i].spell.setPosition(Player.getPosition().x - 100, Player.getPosition().y - 200);
            MovmentCounter[i] = 0;
            BODstate[i] = BOD::BODcast;
            cast(i);
            showBODSpell[i] = true;
            BODmonsters[i].cooldown = 5;
        }
        else if (abs(x) < 300 && abs(y) < 30) {
            MovmentCounter[i] = 0;
            BODstate[i] = BOD::BODattack;
            attack(x, y, i);
        }
        else
            walk(x, y, i);
    }
}

// set monsters at the begining of the wave
void SetMonsters() {
    BODnumber = rand()%10 + 1;
    for (int i = 0; i < BODnumber; i++) {
        BODalive[i] = true;
        BODstate[i] = BOD::BODwalk;
        BODmonsters[i] = BODoriginal;
        BODmonsters[i].BOD.setPosition(500 + rand()%100, 7000 + rand() % 1000);
    }
}

// create monsters when opening the game
void CreateMonsters() {
    BODtexture.loadFromFile("enemies/Bringer-Of-Death/SpriteSheet/Bringer-of-Death-SpritSheet.png");
    BODoriginal.health = 10;
    BODoriginal.spell.setTexture(BODtexture);
    BODoriginal.spell.setTextureRect(getRect(48));
    BODoriginal.spell.setScale(2, 2);
    BODoriginal.BOD.setTexture(BODtexture);
    BODoriginal.BOD.setTextureRect(getRect(0));
    BODoriginal.BOD.setOrigin(105, 62);
    BODoriginal.BOD.setScale(2, 2);
}