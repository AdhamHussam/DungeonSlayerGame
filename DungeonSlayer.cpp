#include "includes.h"
#include "Menu.h"
#include <iostream>

// Game properties
enum state
{
    idle, run, hit, base, zmove, xmove, cmove, vmove, dead, walk
};
state curr_state = state::idle;

int pagenum = 69;

int Player_Health = 100;
Vector2f velocity = { 0, 0 };

float slow_multi = 1;
float AnimationCounter = 0;
float AnimationSwitchTime = 0.1f;
int ImageCounter = 0;

float playerdeltatime = 0;    
Clock GameClock;
bool isAttack = false;
bool ishit = false;
bool finishedanimationonce = false;

RenderWindow window(VideoMode(1920, 1080), "Dungeon Slayer");
Menu menu(1920, 1080);
View view(Vector2f(0, 0), Vector2f(1920, 1080));

// Textures
Texture Idle;
Texture RunAnimation[8];
Texture DeathAnimation[3];
Texture HitAnimation[3];
Texture BaseAttack[5];
Texture Zmove[5];
Texture Xmove[6];
Texture Cmove[6];
Texture Vmove[2];
Texture walkAnimation[6];


Sprite Player;
Texture room;
Texture mainmenubg;
Sprite bg;
Sprite Room;


// Room 0 Borders


// Game functions
void menu_handler();
void UpdateAnimationCounter(int maximagecounter);
void Switch_States();
void Game_play(RenderWindow& window);
void update();
void trackView();
void playerMovement();
void setTextures();
void checkCollisions();
void Draw();

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
    //checkCollisions();
}

void Draw()
{
    window.clear();
    window.draw(Room);
    window.draw(Player);
    window.display();
}

void playerMovement()
{
    if (Keyboard::isKeyPressed(Keyboard::W)&& Keyboard::isKeyPressed(Keyboard::LShift))
    {
        velocity.y = -0.1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        velocity.y = 0.1;
    }
    else {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        Player.setScale(-0.125, 0.125);
        velocity.x = -0.1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        Player.setScale(0.125, 0.125);
        velocity.x = 0.1;
    }
    else {
        velocity.x = 0;
    }
    Player.move(velocity);
     if (Keyboard::isKeyPressed(Keyboard::W))
    {
        velocity.y = -0.05;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        velocity.y = 0.05;
    }
    else {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        Player.setScale(-0.125, 0.125);
        velocity.x = -0.05;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        Player.setScale(0.125, 0.125);
        velocity.x = 0.05;
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
    bg.setTexture(mainmenubg);
    bg.setScale(0.5, 0.5);
    
    // Room
    room.loadFromFile("mapV2.png");
    Room.setTexture(room);
    Room.setScale(3.8, 3.333);
    Room.setOrigin(room.getSize().x/2,room.getSize().y/2 );
    Room.setPosition(0,178*16);
    
    // Player
    Idle.loadFromFile("Idle.png");
    Player.setTexture(Idle);
    Player.setScale(0.125, 0.125);
    Player.setOrigin(Idle.getSize().x / 2, Idle.getSize().y / 2);
    Player.setPosition(-500, 7000);
    for (int i = 0; i < 8; i++) {
        RunAnimation[i].loadFromFile("Run/run" + to_string(i) + ".png");
    } 
    for (int i = 0; i < 5; i++) {
        Zmove[i].loadFromFile("Z move/Zmove" + to_string(i) + ".png");
    }
    for (int i = 0; i < 6; i++) {
       walkAnimation[i].loadFromFile("walk/Walk" + to_string(i) + ".png");
    }

}

void checkCollisions()
{
  /*  if (Keyboard::isKeyPressed(Keyboard::A) && Player.getGlobalBounds().intersects(border1.getGlobalBounds()))
    {
        velocity.x = 0;
    } 
    if (Keyboard::isKeyPressed(Keyboard::D) && Player.getGlobalBounds().intersects(border2.getGlobalBounds()))
    {
        velocity.x = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && Player.getGlobalBounds().intersects(border3.getGlobalBounds()))
    {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && (Player.getGlobalBounds().intersects(border4.getGlobalBounds())))
    {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && Player.getGlobalBounds().intersects(border5.getGlobalBounds()))
    {
        velocity.y = 0;
    }*/
}

void trackView()
{  
    view.setCenter(Player.getPosition()); //update
    window.setView(view);
}

void Switch_States()
{

    if ((Keyboard::isKeyPressed(Keyboard::A)  || Keyboard::isKeyPressed(Keyboard::D)  || Keyboard::isKeyPressed(Keyboard::S)  || Keyboard::isKeyPressed(Keyboard::W)) && Keyboard::isKeyPressed(Keyboard::LShift))
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
    if (Keyboard::isKeyPressed(Keyboard::V))
    {
        curr_state = state::vmove;
    }
    if (Player_Health <= 0)
    {
        curr_state = state::dead;
    }
 
    switch (curr_state)
    {
        case state::run: UpdateAnimationCounter(8); Player.setTexture(RunAnimation[ImageCounter]); break;
        case state::walk: UpdateAnimationCounter(6); Player.setTexture(walkAnimation[ImageCounter]); break;
        case state::idle:; Player.setTexture(Idle); break;
        case state::zmove: UpdateAnimationCounter(5); Player.setTexture(Zmove[ImageCounter]); break;
    }
}

void UpdateAnimationCounter(int maximagecounter)
{
    AnimationCounter += playerdeltatime;
    if (AnimationCounter >= AnimationSwitchTime)
    {
        AnimationCounter = 0;
        ImageCounter++;
        if (ImageCounter >= maximagecounter)
        {
            finishedanimationonce = true;
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
                        if (event.key.code == Keyboard::Enter) {
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
    }
}
