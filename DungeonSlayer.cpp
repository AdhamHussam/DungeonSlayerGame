#include "includes.h"
#include "Menu.h"
#include "Monsters.h"
#include "globals.h"
#include "PauseMenu.h"


// Game properties
enum state
{
    idle, run, hit, base, zmove, xmove, cmove, dead, walk
};

// menu number
int pagenum = 69;
int doors = 2;
int right_walls = 11;
int left_walls = 11;
int up_walls = 10;
int down_walls = 11;



// player attributes
int walk_speed = 100;
int run_speed = 200;
Vector2f velocity = { 0, 0 };
float AnimationCounter = 0;
int maximagecounter = 0;
int ImageCounter = 0;
bool sha8al = false;
bool isAttack = false;
bool ispassing = false;
bool finishedanimationonce = false;

RenderWindow window(VideoMode(1920, 1080), "Dungeon Slayer");
Menu menu(1920, 1080);
PauseMenu pause(1920, 1080);
Clock pausetimer;
Clock attacktimer;
View view(Vector2f(0, 0), Vector2f(1920, 1080));
Vector2f initial_position(-500, 7000);

// Textures

Texture Idle;
Texture RunAnimation[8];
Texture DeathAnimation[3];
Texture HitAnimation[3];
Texture BaseAttack[8];
Texture Zmove[7];
Texture Xmove[7];
Texture Cmove[8];
Texture walkAnimation[8];

Texture map1;
Texture mainmenubg;
Texture instructs;
Sprite Instructions;
Sprite bg;
Sprite Room;
Texture pausebg;
Sprite pausemenu;
Sprite Map1;

// Room 0 Borders
RectangleShape gate1(Vector2f({ 1, 1 }));
RectangleShape gate2(Vector2f({ 1, 1 }));

RectangleShape borderR1(Vector2f({ 100,1000 }));
RectangleShape borderR2(Vector2f({ 50,200 }));
RectangleShape borderR3(Vector2f({ 50,800 }));
RectangleShape borderR4(Vector2f({ 50,100 }));
RectangleShape borderR5(Vector2f({ 50,1000 }));
RectangleShape borderR6(Vector2f({ 50,200 }));
RectangleShape borderR7(Vector2f({ 50,150 }));
RectangleShape borderR8(Vector2f({ 50,150 }));
RectangleShape borderR9(Vector2f({ 50,1000 }));
RectangleShape borderR10(Vector2f({ 100,50 }));
RectangleShape borderR11(Vector2f({ 50,300 }));

RectangleShape borderL1(Vector2f({ 50,1000 })); 
RectangleShape borderL2(Vector2f({ 50,200 })); 
RectangleShape borderL3(Vector2f({ 50,800 })); 
RectangleShape borderL4(Vector2f({ 50, 100 })); 
RectangleShape borderL5(Vector2f({ 50, 1000 }));
RectangleShape borderL6(Vector2f({ 50, 200 }));
RectangleShape borderL7(Vector2f({ 50, 150 }));
RectangleShape borderL8(Vector2f({ 50, 150 }));
RectangleShape borderL9(Vector2f({ 50, 1000 }));
RectangleShape borderL10(Vector2f({ 100, 50 }));
RectangleShape borderL11(Vector2f({ 50, 300 }));


RectangleShape borderU1(Vector2f({ 700,50 }));
RectangleShape borderU2(Vector2f({ 700,50 }));
RectangleShape borderU3(Vector2f({ 100,50 }));
RectangleShape borderU4(Vector2f({ 100,50 }));
RectangleShape borderU5(Vector2f({ 900,50 }));
RectangleShape borderU6(Vector2f({ 900,50 }));
RectangleShape borderU7(Vector2f({ 100,50 }));
RectangleShape borderU8(Vector2f({ 100,50 }));
RectangleShape borderU9(Vector2f({ 600,50 }));
RectangleShape borderU10(Vector2f({ 600,50 }));

RectangleShape borderD1(Vector2f({ 2000,50 }));
RectangleShape borderD2(Vector2f({ 700,50 }));
RectangleShape borderD3(Vector2f({ 700,50 }));
RectangleShape borderD4(Vector2f({ 100,50 }));
RectangleShape borderD5(Vector2f({ 100,50 }));
RectangleShape borderD6(Vector2f({ 600,50 }));
RectangleShape borderD7(Vector2f({ 600,50 }));
RectangleShape borderD8(Vector2f({ 50,50 }));
RectangleShape borderD9(Vector2f({ 50,50 }));
RectangleShape borderD10(Vector2f({ 50,50 }));
RectangleShape borderD11(Vector2f({ 50,50 }));

RectangleShape gates[] = { gate1, gate2 };
RectangleShape right_borders[] = { borderR1 , borderR2 , borderR3 , borderR4 ,borderR5, borderR6, borderR7, borderR8, borderR9, borderR10 ,borderR11 };
RectangleShape left_borders[] = { borderL1,borderL2 , borderL3 , borderL4, borderL5 , borderL6 , borderL7, borderL8, borderL9, borderL10, borderL11 };
RectangleShape up_borders[] = { borderU1, borderU2 , borderU3 , borderU4, borderU5, borderU6, borderU7, borderU8, borderU9, borderU10 };
RectangleShape down_borders[] = { borderD1,borderD2, borderD3 , borderD4, borderD5, borderD6, borderD7, borderD8, borderD9 ,borderD10, borderD11 };

// Game functions
void menu_handler();
void Switch_States();
void Game_play(RenderWindow& window);
void PauseMenuHandler(RenderWindow& window);
void Instructions_Menu(RenderWindow& window);
void Instructions_Draw();
void update();
void trackView();
void playerMovement();
void setTextures();
void checkCollisions();
void Draw();
void MonstersMovment();
void SetMonsters();
void UpdateAnimationCounter(float st = 0.1);
void game_reset();

// Main 
int main()
{
    window.setMouseCursorVisible(false);
    setTextures();
    menu_handler();
}

// Definitions
void update()
{
    Switch_States();
    trackView();
    checkCollisions();
    playerMovement();
    MonstersMovment();
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        if (pausetimer.getElapsedTime().asSeconds() > 0.2) {
            PauseMenuHandler(window);
            pausetimer.restart();
        }
    }
}

void checkCollisions() 
{
    if (Player.getGlobalBounds().intersects(gate1.getGlobalBounds())) ispassing = true;
    else ispassing = false;
    
    // right
    for (int i = 0; i < right_walls; i++) {
        if (Keyboard::isKeyPressed(Keyboard::D) && Player.getGlobalBounds().intersects(right_borders[i].getGlobalBounds())) {
            velocity.x = 0;
        }
    }

    //left
    for (int i = 0; i < left_walls; i++) {
        if (Keyboard::isKeyPressed(Keyboard::A) && Player.getGlobalBounds().intersects(left_borders[i].getGlobalBounds())) {
            velocity.x = 0;
        }
    }

    // up
    for (int i = 0; i < up_walls; i++) {
        if (Keyboard::isKeyPressed(Keyboard::W) && Player.getGlobalBounds().intersects(up_borders[i].getGlobalBounds())) {
            velocity.y = 0;
        }
    }

    //down
    for (int i = 0; i < down_walls; i++) {
        if (Keyboard::isKeyPressed(Keyboard::S) && Player.getGlobalBounds().intersects(down_borders[i].getGlobalBounds())) {
            velocity.y = 0;
        }
    }
  
}

void setTextures()
{
    // Menus   
    mainmenubg.loadFromFile("Main Menu.jpg");
    instructs.loadFromFile("instructions.png");
    pausebg.loadFromFile("pausebg.png");

    bg.setTexture(mainmenubg);
    Instructions.setTexture(instructs);
    pausemenu.setTexture(pausebg);

    bg.setScale(0.5, 0.5);
    Instructions.setScale(0.5, 0.5);
    pausemenu.setScale(0.5, 0.5);
    
    // Room

    map1.loadFromFile("lvl2.png");
    Map1.setTexture(map1);
    Map1.setScale(3.8, 3.333);
    Map1.setOrigin(map1.getSize().x / 2, map1.getSize().y / 2);
    Map1.setPosition(0, 178 * 16);

    //Player
    
    Idle.loadFromFile("idle.png");
    Player.setTexture(Idle);
    Player.setScale(0.2, 0.2);
    Player.setOrigin(Idle.getSize().x / 2, Idle.getSize().y / 2);
    Player.setPosition(initial_position);

    // walls

    gate1.setPosition(-60, 6500);
    gate2.setPosition(-60, 4600);
    gates[0].setPosition(-60, 6500);
    gates[1].setPosition(-60, 4600);

    right_borders[0].setPosition(650, 6700);
    right_borders[1].setPosition(100, 6330);
    right_borders[2].setPosition(880, 5650);
    right_borders[3].setPosition(750, 5525);
    right_borders[4].setPosition(1050, 4750);
    right_borders[5].setPosition(100, 4450);
    right_borders[6].setPosition(675, 4250);
    right_borders[7].setPosition(805, 4025);
    right_borders[8].setPosition(925, 3100);
    right_borders[9].setPosition(800, 3100);
    right_borders[10].setPosition(100, 2600);

    left_borders[0].setPosition(-990, 6700);
    left_borders[1].setPosition(-250, 6330);
    left_borders[2].setPosition(-1050, 5650);
    left_borders[3].setPosition(-925,5525);
    left_borders[4].setPosition(-1225,4750);
    left_borders[5].setPosition(-250,4450);
    left_borders[6].setPosition(-850,4250);
    left_borders[7].setPosition(-975,4025);
    left_borders[8].setPosition(-1085,3100);
    left_borders[9].setPosition(-1025, 3100);
    left_borders[10].setPosition(-250, 2600);
    
    up_borders[0].setPosition(-1000, 6500);
    up_borders[1].setPosition(120, 6500);
    up_borders[2].setPosition(-1000, 5600);
    up_borders[3].setPosition(800, 5600);
    up_borders[4].setPosition(-1150, 4700);
    up_borders[5].setPosition(125 , 4700);
    up_borders[6].setPosition(-1025 , 3100);
    up_borders[7].setPosition(825 , 3100);
    up_borders[8].setPosition(-825 , 2900);
    up_borders[9].setPosition(100 , 2900);

    down_borders[0].setPosition(-900, 7450);
    down_borders[1].setPosition(-970, 6300);
    down_borders[2].setPosition(130, 6300);
    down_borders[3].setPosition(-975, 5500);
    down_borders[4].setPosition(750, 5500);
    down_borders[5].setPosition(-840, 4425);
    down_borders[6].setPosition(110, 4425);
    down_borders[7].setPosition(-850, 4225);
    down_borders[8].setPosition(675, 4225);
    down_borders[9].setPosition(805, 4025);
    down_borders[10].setPosition(-975, 4025);
   


    // monsters
    SetMonsters();

    for (int i = 0; i < 8; i++) {
        RunAnimation[i].loadFromFile("Run/run" + to_string(i) + ".png");
    }
    for (int i = 0; i < 7; i++) {
        Zmove[i].loadFromFile("Z move/Zmove" + to_string(i) + ".png");
    }
    for (int i = 0; i < 7; i++) {
        Xmove[i].loadFromFile("X move/Xmove" + to_string(i) + ".png");
    }
    for (int i = 0; i < 8; i++) {
        Cmove[i].loadFromFile("C move/Cmove" + to_string(i) + ".png");
    }
    for (int i = 0; i < 8; i++) {
        walkAnimation[i].loadFromFile("walk/Walk" + to_string(i) + ".png");
    }

    for (int i = 0; i < 8; i++) {
        BaseAttack[i].loadFromFile("base/Base" + to_string(i) + ".png");
    }
    for (int i = 0; i < 3; i++) {
        HitAnimation[i].loadFromFile("hit/Hit" + to_string(i) + ".png");
    }
    for (int i = 0; i < 3; i++) {
        DeathAnimation[i].loadFromFile("Dead/Dead" + to_string(i) + ".png");
    }
}

void Draw()
{
    window.clear();
    window.draw(Map1);
    if (!ispassing)
        window.draw(Player);
    for (int i = 0; i < doors; i++) {
        window.draw(gates[i]);
    }   
    for(int i = 0; i < left_walls;i++){
        window.draw(left_borders[i]);
    }
    for(int i = 0; i < up_walls;i++){
        window.draw(up_borders[i]);
    }
    for(int i = 0; i < right_walls;i++)
      window.draw(right_borders[i]);

     for(int i = 0; i < down_walls;i++)
      window.draw(down_borders[i]);

    if (BODalive) {
        window.draw(BODmonsters[0].BOD);
        if (showBODSpell)
            window.draw(BODmonsters[0].spell);
    }

    window.display();
}

void playerMovement()
{
    
    if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        velocity.y = -run_speed * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::LShift))
    {

        velocity.y = run_speed * playerdeltatime;
    }
    else {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        Player.setScale(-0.2, 0.2);
        velocity.x = -run_speed * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        Player.setScale(0.2, 0.2);
        velocity.x = run_speed * playerdeltatime;
    }
    else {
        velocity.x = 0;
    }

    checkCollisions();
    Player.move(velocity);
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        velocity.y = -walk_speed * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        velocity.y = walk_speed * playerdeltatime;
    }
    else {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        Player.setScale(-0.2, 0.2);
        velocity.x = -walk_speed * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        Player.setScale(0.2, 0.2);
        velocity.x = walk_speed * playerdeltatime;
    }
    else {
        velocity.x = 0;
    }
    checkCollisions();
    Player.move(velocity);

}



void trackView()
{
    view.setCenter(Player.getPosition()); //update
    window.setView(view);
}


void Switch_States()
{
    if (!sha8al) {

        if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W)) && Keyboard::isKeyPressed(Keyboard::LShift))
        {
            curr_state = state::run;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W))
        {
            curr_state = state::walk;
        }
        else
        {
            curr_state = state::idle;
        }

        if (Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(Mouse::Left))
        {
            curr_state = state::base;
        }
        if (Keyboard::isKeyPressed(Keyboard::Z))
        {
            curr_state = state::zmove;
        }
        if (Keyboard::isKeyPressed(Keyboard::X))
        {
            curr_state = state::xmove;
        }
        if (Keyboard::isKeyPressed(Keyboard::C))
        {
            curr_state = state::cmove;
        }
        if (ishit)
        {
            curr_state = state::hit;
        }
        if (Player_Health <= 0)
        {
            curr_state = state::dead;
        }
      


        switch (curr_state)
        {
        case state::base:
            maximagecounter = 8;
            ImageCounter = 0; sha8al = true;
            break;
        case state::zmove:
            maximagecounter = 7;
            ImageCounter = 0; sha8al = true;
            break;
        case state::xmove:
            maximagecounter = 7;
            ImageCounter = 0; sha8al = true;
            break;
        case state::cmove:
            maximagecounter = 8;
            ImageCounter = 0; sha8al = true;
            break;
        case state::hit:
            maximagecounter = 3;
            ImageCounter = 0; sha8al = true;
            break;
        case state::dead:
            maximagecounter = 3;
            ImageCounter = 0; sha8al = true;
            break;
        }
    }

    switch (curr_state) {
    case state::run:maximagecounter = 8; Player.setTexture(RunAnimation[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case state::walk: maximagecounter = 8; Player.setTexture(walkAnimation[ImageCounter]); UpdateAnimationCounter(0.2); break;
    case state::idle: Player.setTexture(Idle); UpdateAnimationCounter(0.1); break;
    case state::base: Player.setTexture(BaseAttack[ImageCounter]); UpdateAnimationCounter(0.08); break;//0.12
    case state::zmove: Player.setTexture(Zmove[ImageCounter]); UpdateAnimationCounter(0.11); break;
    case state::xmove: Player.setTexture(Xmove[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case state::cmove: Player.setTexture(Cmove[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case state::dead: Player.setTexture(DeathAnimation[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case state::hit:Player.setTexture(HitAnimation[ImageCounter]); UpdateAnimationCounter(0.15); break;    
    }

}

void UpdateAnimationCounter(float st)
{
    AnimationCounter += playerdeltatime;
    if (AnimationCounter >= st)
    {
        AnimationCounter = 0;
        ImageCounter++;
        if (ImageCounter >= maximagecounter)
        {
            ishit = false;
            if (sha8al) sha8al = false;
            ImageCounter = 0;

        }
    }

}

void menu_handler()
{
    while (true) {
        if (pagenum == 69)
        {
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        break;
                    }
                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Up)
                            menu.MoveUp();
                        if (event.key.code == Keyboard::Down)
                            menu.MoveDown();
                        if (event.key.code == Keyboard::Return) {
                            if (menu.pressed() == 0) {
                                pagenum = 0;
                            }
                            if (menu.pressed() == 1) {
                                pagenum = 1;
                            }
                            if (menu.pressed() == 2) {
                                pagenum = -1;
                            }
                        }
                    }
                }
                window.clear();
                if (pagenum != 69) {
                    break;
                }
                window.draw(bg);
                menu.drawMenu(window);
                window.display();
            }
            if (pagenum == -1) {
                window.close();
                break;
            }
            if (pagenum == 0) {
                Game_play(window);
            }
            if (pagenum == 1) {
                Instructions_Menu(window);
            }
        }
    }
}

void Game_play(RenderWindow& window)
{
    while (window.isOpen()) {
        float elapsed = GameClock.restart().asSeconds();
        playerdeltatime = elapsed;
        Event Play;
        while (window.pollEvent(Play)) {
            if (Play.type == Event::Closed) {
                window.close();
            }
        }
        update();
        Draw();
        cout << Player.getPosition().x << " " << Player.getPosition().y << endl;
        //cout << Player_Health << endl;
    }
}


void Instructions_Draw() {
    window.clear();
    window.draw(Instructions);
    window.display();
}


void Instructions_Menu(RenderWindow& window) {
    while (window.isOpen()) {
        Instructions_Draw();
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            pagenum = 69;
            menu_handler();
        }
    }

}


void PauseMenuHandler(RenderWindow& window)
{
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        view.setCenter(960, 540); //update
        window.setView(view);

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                pause.moveup();
                GameClock.restart();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                pause.movedown();
                GameClock.restart();
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Enter) && pause.selectedp == 0) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                GameClock.restart();
                break;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter) && pause.selectedp == 1) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                GameClock.restart();
                // options menu
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter) && pause.selectedp == 2) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                GameClock.restart();
                game_reset();
                break;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter) && pause.selectedp == 3) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                GameClock.restart();
                pagenum = 69;
                game_reset();
                menu_handler();
            }
        }

        window.clear();
        window.draw(pausemenu);
        pause.draw(window);
        window.display();
    }

}

void game_reset() {
    Player_Health = 100;
    Player.setPosition(initial_position);
    float AnimationCounter = 0;
    int maximagecounter = 0;
    int ImageCounter = 0;
    int globalInt = 0;
    int number_of_BODmonsters = 1;
    float playerdeltatime = 0;
    SetMonsters();
}
