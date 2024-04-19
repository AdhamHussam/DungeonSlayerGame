#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace std;
using namespace sf;

// Game properties
enum state
{
    idle, walk, hit, ablaze, dead
};
state current_state = state::idle;

int pagenum = 69;
float deltaTime = 0;    
Clock gameClock;
Vector2f velocity = { 0, 0 };
bool isAttack = false;
RenderWindow window(VideoMode(1920, 1080), "Dungeon Slayer");
Menu menu(1920, 1080);
View view(Vector2f(0, 0), Vector2f(1920, 1080));

// Game items
Texture Idle;
Texture Walk[8];
Texture BaseAttack[5];
Texture Stomp[2];
Texture AblazeCombo[17];
Sprite Player;
Texture room;
Texture mainmenubg;
Sprite bg;
Sprite Room;


// Room 0 Borders


// Game functions
void menu_handler();
void HandleAnimations();
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
        Player.setScale(-0.125, 0.125);
        velocity.x = -1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        Player.setScale(0.125, 0.125);
        velocity.x = 1;
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
    Player.setPosition(500, 500);
    Idle.loadFromFile("Idle.png");
    Player.setTexture(Idle);
    Player.setScale(0.125, 0.125);
    Player.setOrigin(Idle.getSize().x / 2, Idle.getSize().y / 2);
    Player.setPosition(-500, 7000);

    // walls
  
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

void HandleAnimations() 
{
    
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
        Event Play;
        while (window.pollEvent(Play)) {
            if (Play.type == Event::Closed) {
                window.close();
            }
        }
        update();
        Draw();
        cout << Player.getPosition().x << " " << Player.getPosition().y << endl;
    }
}
