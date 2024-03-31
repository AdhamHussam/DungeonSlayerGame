#include <iostream>
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


void update();
void playerMovement();
void Draw();







int main()
{
    back.setFillColor(Color::Black);
    back.setSize(Vector2f(2000, 2000));
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







//ؤلاقثرلاثعرلاقثرلاثقرلاعلارهعلا

void update()
{
    playerMovement();
    player.move(velocity);

}

void Draw()
{
    window.clear();
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