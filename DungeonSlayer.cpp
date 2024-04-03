﻿#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Clock gameClock;
float deltaTime = 0;

Vector2f velocity = { 0, 0 };
RenderWindow window(VideoMode(1920, 1080), "Game");
RectangleShape back;
Texture Player;
Sprite player;
Texture room;
Sprite Room;


void update();
void playerMovement();
void Draw();







int main()
{
    
    room.loadFromFile("Room0.png");
    Room.setTexture(room);
    Room.setScale(3.5, 3.5);
    Room.setOrigin(room.getSize().x/2, room.getSize().y/2);
    Room.setPosition(1920 / 2 + 50, 1080 / 2 - 100);
   
    player.setPosition(200, 200);
    Player.loadFromFile("Idle.png");
    player.setTexture(Player);
    player.setScale(0.15, 0.15);
    player.setOrigin(Player.getSize().x / 2, Player.getSize().y / 2);
    while (window.isOpen()) {
        // restart the clock at the start of the game loop
        gameClock.restart();
        Event close;

        while (window.pollEvent(close)) {
            if (close.type == Event::Closed) {
                window.close();
            }
        }
        update();
        Draw();

    }
}




void update()
{
    playerMovement();
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
        player.setScale(-0.15, 0.15);
        velocity.x = -1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        player.setScale(0.15, 0.15);
        velocity.x = 1;
    }
    else {

        velocity.x = 0;
    }
}