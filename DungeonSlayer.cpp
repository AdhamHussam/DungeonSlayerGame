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



// player attributes
int walk_speed = 100;
int run_speed = 200;
int Player_Health = 10000;
Vector2f velocity = { 0, 0 };
float AnimationCounter = 0;
int maximagecounter = 0;
int ImageCounter = 0;
bool sha8al = false;
bool isAttack = false;
bool ishit = false;
bool finishedanimationonce = false;

RenderWindow window(VideoMode(1920, 1080), "Dungeon Slayer");
Menu menu(1920, 1080);
PauseMenu pause(1920, 1080);
Clock pausetimer;
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
RectangleShape border1(Vector2f({ 150,1080 })); RectangleShape border2(Vector2f({ 150,1080 })); RectangleShape border3(Vector2f({ 2000,100 })); RectangleShape border4(Vector2f({ 1000,100 })); RectangleShape border5(Vector2f({ 1000,100 }));

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
    setTextures();
    window.setMouseCursorVisible(false);
    menu_handler();
}

// Definitions
void update()
{
    Switch_States();
    trackView();
    playerMovement();
    MonstersMovment();
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        if (pausetimer.getElapsedTime().asSeconds() > 0.2) {
            PauseMenuHandler(window);
            pausetimer.restart();
        }
    }
    checkCollisions();
}


void Draw()
{
    window.clear();
    window.draw(Map1);
    window.draw(Player);
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

    Player.move(velocity);

}


void setTextures()
{
    // Menu   
    mainmenubg.loadFromFile("Main Menu.jpg");
    instructs.loadFromFile("instructions.png");
    pausebg.loadFromFile("pausebg.png");
    pausebg.loadFromFile("pausebg.png");

    bg.setTexture(mainmenubg);
    Instructions.setTexture(instructs);
    pausemenu.setTexture(pausebg);

    bg.setScale(0.5, 0.5);
    Instructions.setScale(0.5, 0.5);
    pausemenu.setScale(0.5, 0.5);
    pausemenu.setTexture(pausebg);
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
    border2.setPosition(1500, 0);
    border3.setPosition(0, 1035);
    border4.setPosition(-150, 150);
    border5.setPosition(1050, 150);

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
}

int i = 1;
void checkCollisions()
{
    


   if(BODmonsters[0].BOD.getGlobalBounds().intersects(Player.getGlobalBounds()))
     if (BODstate == BODattacks) {

          Player_Health -= 2/i;
          i++;
          if (i >= 20)
              i = i % 20 + 1;
        //  ishit= true;


    }
    
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


        if (Player_Health <= 0)
        {
            curr_state = state::dead;


        }
       /* if (ishit)
        {
            curr_state = state::hit;


        }*/



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
            ImageCounter = 0;

            ishit = false;
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
    case state::hit: Player.setTexture(HitAnimation[ImageCounter]); UpdateAnimationCounter(0.05); break;
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
            if (ishit)
                ishit = false;
            if (sha8al)
                sha8al = false;
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
        // cout << Player.getPosition().x << " " << Player.getPosition().y << endl;
        cout << Player_Health << endl;
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
    int Player_Health = 100;
    Player.setPosition(initial_position);
    float AnimationCounter = 0;
    int maximagecounter = 0;
    int ImageCounter = 0;
    int globalInt = 0;
    int number_of_BODmonsters = 1;
    float playerdeltatime = 0;
    SetMonsters();
}
