#include "includes.h"
#include "Menu.h"
#include "Monsters.h"


////////// temp

const int number_of_zombies = 1;
Zombie zombies[number_of_zombies];

/////////


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
RectangleShape border1(Vector2f({ 150,1080 }));RectangleShape border2(Vector2f({ 150,1080 }));RectangleShape border3(Vector2f({ 2000,100 }));RectangleShape border4(Vector2f({ 1000,100 }));RectangleShape border5(Vector2f({ 1000,100 }));

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
void MonstersMovment(Zombie zombies[], Sprite& Player);

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
    MonstersMovment(zombies,Player);
    //checkCollisions();
    Player.move(velocity);
}

void Draw()
{
    window.clear();
    window.draw(Room);
    window.draw(Player);
    window.draw(zombies[0].zombie);
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
    border2.setPosition(1500, 0);
    border3.setPosition(0, 1035);
    border4.setPosition(-150, 150);
    border5.setPosition(1050, 150);

    // Monsters
    zombies[0].zombie.setPosition(-500, 7000);
    zombies[0].zombie.setFillColor(Color::Magenta);
    zombies[0].zombie.setSize(Vector2f(100, 200));

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
        Event Play;
        while (window.pollEvent(Play)) {
            if (Play.type == Event::Closed) {
                window.close();
            }
        }
        update();
        Draw();
    }
}
