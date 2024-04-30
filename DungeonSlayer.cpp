﻿#include "includes.h"
#include "Menu.h"
#include "Monsters.h"
#include "globals.h"



////////// temp

const int number_of_zombies = 1;
Zombie zombies[number_of_zombies];
bool showBODSpell;
/////////

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
int maximagecounter = 0;
int ImageCounter = 0;

float playerdeltatime = 0;
bool sha8al = false;
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
Texture BaseAttack[8];
Texture Zmove[7];
Texture Xmove[7];
Texture Cmove[8];
Texture walkAnimation[8];


Sprite Player;

Texture room;
Texture mainmenubg;
Sprite bg;
Sprite Room;




// Room 0 Borders
RectangleShape border1(Vector2f({ 150,1080 }));RectangleShape border2(Vector2f({ 150,1080 }));RectangleShape border3(Vector2f({ 2000,100 }));RectangleShape border4(Vector2f({ 1000,100 }));RectangleShape border5(Vector2f({ 1000,100 }));

// Game functions
void menu_handler();
void UpdateAnimationCounter(float st = 0.1 );
void Switch_States();
void Game_play(RenderWindow& window);
void update();
void trackView();
void playerMovement();
void setTextures();
void checkCollisions();
void Draw();
int MonstersMovment(Zombie zombies[], Sprite& Player);
void SetMonsters(Zombie zombies[]);


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
    if (MonstersMovment(zombies, Player) != 0)
        showBODSpell = true;
    else
        showBODSpell = false;
    //checkCollisions();

}

void Draw()
{
    window.clear();
    window.draw(Room);
    window.draw(zombies[0].zombie);
    if (showBODSpell)
        window.draw(zombies[0].spell);
    window.draw(Player);
    window.display();
}

void playerMovement()
{

    if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        velocity.y = -200 * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        
        velocity.y = 200 * playerdeltatime;
    }
    else {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        Player.setScale(-0.2, 0.2);
        velocity.x = -200 * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
    {
        Player.setScale(0.2, 0.2);
        velocity.x = 200* playerdeltatime;
    }
    else {
        velocity.x = 0;
    }
    Player.move(velocity);
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        velocity.y = -100 * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        velocity.y = 100 * playerdeltatime;
    }
    else {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        Player.setScale(-0.2, 0.2);
        velocity.x = -100 * playerdeltatime;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        Player.setScale(0.2, 0.2);
        velocity.x = 100 * playerdeltatime;
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
    room.loadFromFile("mapV4.png");
    Room.setTexture(room);
    Room.setScale(3.8, 3.333);
    Room.setOrigin(room.getSize().x / 2, room.getSize().y / 2);
    Room.setPosition(0, 178 * 16);

    //Player
    Idle.loadFromFile("idle.png");
    Player.setTexture(Idle);
    Player.setScale(0.2, 0.2);
    Player.setOrigin(Idle.getSize().x / 2, Idle.getSize().y / 2);
   Player.setPosition(-500, 7000);

    // walls
    border2.setPosition(1500, 0);
    border3.setPosition(0, 1035);
    border4.setPosition(-150, 150);
    border5.setPosition(1050, 150);

    // monsters
    SetMonsters(zombies);

    Player.setPosition(-500, 7000);
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
}

void checkCollisions()
{
    if (Keyboard::isKeyPressed(Keyboard::A) && Player.getGlobalBounds().intersects(border1.getGlobalBounds()))
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
               case state::base: maximagecounter = 8;
                   ImageCounter = 0; sha8al = true ; break; 
               case state::zmove: maximagecounter = 7;
                   ImageCounter = 0; sha8al = true; break;
               case state::xmove: maximagecounter = 7;
                   ImageCounter = 0; sha8al = true; break;
               case state::cmove: maximagecounter = 8;
                   ImageCounter = 0; sha8al = true; break;
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

    }
     
}

void UpdateAnimationCounter(float st )
{
     AnimationCounter += playerdeltatime;
     if (AnimationCounter >= st)
     {
            AnimationCounter = 0;
            ImageCounter++;
            if (ImageCounter >= maximagecounter)
            {            
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
