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
int MovmentCounter;
float MonsterCounter;

// function for setting rectangle of texture
IntRect getRect(int pos) {
    int x = pos%8;
    int y = pos/8;
    return IntRect(x*140, y*93, 140, 93);
}

// updating sprites animation
void UpdateMonsterAnimationCounter(float st = 0.15){
    MonsterCounter += playerdeltatime;
    if (MonsterCounter >= st)
    {
        MonsterCounter = 0;
        MovmentCounter++;
    }
}

// make monster walk
void walk(int x, int y) {
    BODmonsters[0].BOD.setTextureRect(getRect(8 + MovmentCounter));
    /*
    BODmonsters[0].BOD.move(((abs(x) > 1) ? ((x > 0) ? BODmonsters[0].speed : -BODmonsters[0].speed) : 0), ((y < 0) ? BODmonsters[0].speed : -BODmonsters[0].speed));
    */
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

// make monster attack
void attack(int x,int y) {
    BODmonsters[0].BOD.setTextureRect(getRect(16 + MovmentCounter));
    int initial = MovmentCounter;
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 5 && MovmentCounter > initial) {
        if (abs(x) < 200 && abs(y) < 30) {
            Player_Health -= 5;
            ishit = true;
        }
    }
    if (MovmentCounter == 10) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster cast his spell
void cast() {
    BODmonsters[0].BOD.setTextureRect(getRect(39 + MovmentCounter));
    BODmonsters[0].spell.setTextureRect(getRect(52 + MovmentCounter));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 9) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster take damage
void hurt() {
    BODmonsters[0].BOD.setTextureRect(getRect(27 + ((MovmentCounter > 4)?8- MovmentCounter : MovmentCounter)));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 9) {
        MovmentCounter = 0;
        BODstate = BOD::BODwalk;
    }
}

// make monster die
void die() {
    BODmonsters[0].BOD.setTextureRect(getRect(29 + MovmentCounter));
    UpdateMonsterAnimationCounter();
    if (MovmentCounter == 10)
        BODalive = false;
}

// update monster
void MonstersMovment() {

    // hide BOD spell
    showBODSpell = false;

    // check that BOD is alive
    if(!BODalive)
        return;
    if (BODstate == BOD::BODdie) {
        die();
        return;
    }

    // check distance between BOD and Player and make BOD look forward Player
    double x = Player.getPosition().x - BODmonsters[0].BOD.getPosition().x, y = BODmonsters[0].BOD.getPosition().y - Player.getPosition().y;
    if (x > 0)
        BODmonsters[0].BOD.setScale(Vector2f(-2, 2));
    else
        BODmonsters[0].BOD.setScale(Vector2f(2, 2));


    // passing time for cooldown
    BODmonsters[0].cooldown -= playerdeltatime;

    // check if BOD is being attacked
    if(BODstate != BOD::BODhurt && abs(x) < 100 && abs(y) < 100){
        if (curr_state == player_base) {
            BODmonsters[0].health --;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
        else if(curr_state == player_zmove) {
            BODmonsters[0].health -= 2;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
        else if (curr_state == player_xmove) {
            BODmonsters[0].health -= 3;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
        else if (curr_state == player_cmove) {
            BODmonsters[0].health -= 10;
            MovmentCounter = 0;
            BODstate = BOD::BODhurt;
        }
    }

    // check if BOD is doing somthing
    if (BODstate == BOD::BODhurt) {
        if (BODmonsters[0].health <= 0) {
            die();
            BODstate = BOD::BODdie;
        }
        else
            hurt();
        return;
    }
    else if (BODstate == BOD::BODcast) {
        cast();
        showBODSpell = true;
        return;
    }
    else if (BODstate == BOD::BODattack){
        attack(x,y);
        return;
    }



    // making BOD decision
    if ((long long)abs(x) * abs(x) + abs(y) * abs(y) < 100000 && BODmonsters[0].cooldown <= 0) {
        BODmonsters[0].spell.setPosition(Player.getPosition().x - 100, Player.getPosition().y - 200);
        MovmentCounter = 0;
        BODstate = BOD::BODcast;
        cast();
        showBODSpell = true;
        BODmonsters[0].cooldown = 5;
    }
    else if (abs(x) < 300 && abs(y) < 30){
        MovmentCounter = 0;
        BODstate = BOD::BODattack;
        attack(x,y);
    }
    else
        walk(x,y);
}

// set monsters at the begining of the wave
void SetMonsters() {
        BODalive = true;
        BODmonsters[0].health = 10;
        BODstate = BOD::BODwalk;
        BODmonsters[0].texture.loadFromFile("enemies/Bringer-Of-Death/SpriteSheet/Bringer-of-Death-SpritSheet.png");
        BODmonsters[0].spell.setTexture(BODmonsters[0].texture);
        BODmonsters[0].spell.setTextureRect(getRect(48));
        BODmonsters[0].spell.setScale(2, 2);
        BODmonsters[0].BOD.setTexture(BODmonsters[0].texture);
        BODmonsters[0].BOD.setTextureRect(getRect(0));
        BODmonsters[0].BOD.setOrigin(105, 62);
        BODmonsters[0].BOD.setPosition(500, 7000);
    
}