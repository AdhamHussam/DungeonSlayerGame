#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Clock gameClock;
float deltaTime = 0;

Vector2f velocity = { 0, 0 };
RenderWindow window(VideoMode(1920, 1080), "Game");

// Game textures

Texture Player;
Sprite player;
Texture room;
Sprite Room;
RectangleShape border1(Vector2f({ 150,1080 }));
RectangleShape border2(Vector2f({ 150,1080 }));
RectangleShape border3(Vector2f({ 2000,100 }));
RectangleShape border4(Vector2f({ 1000,100 }));
RectangleShape border5(Vector2f({ 1000,100 }));





// Game functions
void update();
void playerMovement();
void setTextures();
void checkCollisions();
void Draw();


int main()
{   
    setTextures();
    window.setMouseCursorVisible(false);
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
    border2.setPosition(1550, 0);
    border3.setPosition(0, 1035);
    border4.setPosition(-150, 150);
    border5.setPosition(1050, 150);

}


void checkCollisions()
{
    if (Keyboard::isKeyPressed(Keyboard::A) && player.getGlobalBounds().intersects(border1.getGlobalBounds()))
    {
        velocity.x=0;
    } 
    if (Keyboard::isKeyPressed(Keyboard::D) && player.getGlobalBounds().intersects(border2.getGlobalBounds()))
    {
        velocity.x=0;
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && player.getGlobalBounds().intersects(border3.getGlobalBounds()))
    {
        velocity.y=0;
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && (player.getGlobalBounds().intersects(border4.getGlobalBounds())))
    {
        velocity.y=0;
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && player.getGlobalBounds().intersects(border5.getGlobalBounds()))
    {
        velocity.y = 0;
    }

}