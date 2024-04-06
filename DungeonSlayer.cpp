#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace std;
using namespace sf;

// Game properties
int pagenum = 69;
Clock gameClock;
float deltaTime = 0;    
Vector2f velocity = { 0, 0 };
RenderWindow window(VideoMode(1920, 1080), "Dungeon Slayer");
Menu menu(1920, 1080);
View view(Vector2f(0, 0), Vector2f(1920, 1080));

// Game textures

Texture Player;
Sprite player;
Texture room;
Texture mainmenubg;
Sprite bg;
Sprite Room;
RectangleShape border1(Vector2f({ 150,1080 }));
RectangleShape border2(Vector2f({ 150,1080 }));
RectangleShape border3(Vector2f({ 2000,100 }));
RectangleShape border4(Vector2f({ 1000,100 }));
RectangleShape border5(Vector2f({ 1000,100 }));

// Game functions
void menu_handler();
void Game_play(RenderWindow& window);
void update();
void updateView();
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


void update()
{
    updateView();
    playerMovement();
    checkCollisions();
    player.move(velocity);

}

void Draw()
{
    window.clear();
    window.draw(Room);
    window.draw(player);
    window.display();

}

void playerMovement()
{
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        velocity.y = -1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        velocity.y = 1;
    }
    else {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        player.setScale(-0.125, 0.125);
        velocity.x = -1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        player.setScale(0.125, 0.125);
        velocity.x = 1;
    }
    else {
        velocity.x = 0;
    }
}

void setTextures() 
{
    // Menu   
    mainmenubg.loadFromFile("Main Menu.jpg");
    bg.setTexture(mainmenubg);
    bg.setScale(0.5, 0.5);
    

    // Room
    room.loadFromFile("Room0.png");
    Room.setTexture(room);
    Room.setScale(3.8, 3.333);
    Room.setOrigin(room.getSize().x / 2, room.getSize().y / 2);
    Room.setPosition(1920 / 2 + 50, 1080 / 2 - 100);
    // Player
    player.setPosition(500, 500);
    Player.loadFromFile("Idle.png");
    player.setTexture(Player);
    player.setScale(0.125, 0.125);
    player.setOrigin(Player.getSize().x / 2, Player.getSize().y / 2);

    // walls
    border2.setPosition(1500, 0);
    border3.setPosition(0, 1035);
    border4.setPosition(-150, 150);
    border5.setPosition(1050, 150);

}


void checkCollisions()
{
    if (Keyboard::isKeyPressed(Keyboard::A) && player.getGlobalBounds().intersects(border1.getGlobalBounds()))
    {
        velocity.x = 0;
    } 
    if (Keyboard::isKeyPressed(Keyboard::D) && player.getGlobalBounds().intersects(border2.getGlobalBounds()))
    {
        velocity.x = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && player.getGlobalBounds().intersects(border3.getGlobalBounds()))
    {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && (player.getGlobalBounds().intersects(border4.getGlobalBounds())))
    {
        velocity.y = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && player.getGlobalBounds().intersects(border5.getGlobalBounds()))
    {
        velocity.y = 0;
    }

}

void updateView()
{  
    view.setCenter(player.getPosition()); //update
    window.setView(view);
}


void Game_play(RenderWindow& window) 
{
    
    while (window.isOpen()) {
        Event event1;
        while (window.pollEvent(event1)) {
            if (event1.type == Event::Closed) {
                window.close();
            }
        }
        update();
        Draw();
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