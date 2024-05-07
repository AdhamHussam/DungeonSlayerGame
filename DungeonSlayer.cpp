#include "includes.h"
#include "Menu.h"
#include "GameOver.h"
#include "Monsters.h"
#include "globals.h"
#include "PauseMenu.h"
#include "GUI.h"


// Game properties
enum state
{
    idle, run, hit, base,  xmove, cmove, vmove, dead, walk
};

int doors = 5;
int right_walls = 25;
int left_walls = 25;
int up_walls = 24;
int down_walls = 26;

// music triggers

bool openertrigger = false;
bool map_opener_trigger = false;
bool death_trigger = false;

// menu number
int pagenum = 10;

// gui struct
GUI gui;


// player attributes
float lastX = 0 , lastY = 0;
int walk_speed = 100;
int run_speed = 200;
Vector2f velocity = { 0, 0 };
float AnimationCounter = 0;
float dash_duration = 0.075;
int maximagecounter = 0;
int ImageCounter = 0;
bool animation_running = false;
bool isDead = false;

bool ispassing = false;
bool passed_door = false;
bool isdashing = false;
bool finishedanimationonce = false;


Menu menu(1920, 1080);
PauseMenu pause(1920, 1080);

Clock pausetimer;
Clock attacktimer;
Clock dashtimer;


Vector2f initial_position(-500, 7000);

// Textures

Texture Idle;
Texture RunAnimation[8];
Texture DeathAnimation[3];
Texture HitAnimation[3];
Texture BaseAttack[8];
Texture Vmove[7];
Texture Xmove[7];
Texture Cmove[8];
Texture walkAnimation[8];

Texture map1;
Texture mainmenubg;
Texture instructs;
Texture death_screen;
Sprite DeathScreen;
Sprite Instructions;
Sprite bg;
Sprite Room;
Texture pausebg;
Sprite pausemenu;
Sprite Map1;


// Room 0 Borders
RectangleShape gate1(Vector2f({ 1, 1 }));
RectangleShape gate2(Vector2f({ 1, 1 }));
RectangleShape gate3(Vector2f({ 1, 1 }));
RectangleShape gate4(Vector2f({ 1, 1 }));
RectangleShape gate5(Vector2f({ 1, 1 }));
RectangleShape gates[] = { gate1, gate2 , gate3, gate4, gate5 };

SoundBuffer menu_opener;
Sound MenuOpener;

SoundBuffer death_sound;
Sound DeathSound;

SoundBuffer game_music;
Sound GameMusic;


// Game functions

void menu_handler();
void music_handler();
void Switch_States();
void Game_play(RenderWindow& window);
void PauseMenuHandler(RenderWindow& window);
void Instructions_Menu(RenderWindow& window);
void Instructions_Draw();
void update();
void dash();
void checkpause();
void check_room();
void fell();
void death_handler();
void trackView();
void playerMovement();
void setTextures();
void checkCollisions();
void Draw();
void UpdateAnimationCounter(float st = 0.1);
void game_reset();

// Main 
int main()
{
    window.setMouseCursorVisible(false);
    SetMonstersSprites();
    setTextures();
    menu_handler();
}

// Definitions;
void update()
{
    if (!isDead) {
        fell();
        Switch_States();
        playerMovement();
        MoveMonsters();
        check_room();
        trackView();
        checkCollisions();
        checkpause();
        dash();
    }
    else {
        death_handler();
    } 
}

void checkCollisions() 
{
    //doors
    for (int i = 0; i < doors; i++) {
        if (Player.getGlobalBounds().intersects(gates[i].getGlobalBounds())) {
            
            if (room_cleared)
            {
                ispassing = true;
                Player.move(0, -500 * playerdeltatime);
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::S) && i == current_room - 1)
                    velocity.y = 0; 
                if (Keyboard::isKeyPressed(Keyboard::W) && i == current_room)
                    velocity.y = 0;
            }
          
            break;
        }
        else ispassing = false;
    }
    
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
    death_screen.loadFromFile("death_screen.png");

    bg.setTexture(mainmenubg);
    Instructions.setTexture(instructs);
    pausemenu.setTexture(pausebg);
    DeathScreen.setTexture(death_screen);
    
    bg.setScale(0.5, 0.5);
    Instructions.setScale(0.75, 0.8);
    pausemenu.setScale(0.5, 0.5);
    DeathScreen.setScale(0.7, 0.7);
    
    // Room

    map1.loadFromFile("lvl1.png");
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

    // GUI
    gui.setSkillsTexture();
    gui.setPlayerInfoTexture();

    // walls

    gates[0].setPosition(-60, 6500);
    gates[1].setPosition(-60, 4640);
    gates[2].setPosition(-60, 2830);
    gates[3].setPosition(-60, 1540);
    gates[4].setPosition(-60, -275);

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
    right_borders[10].setPosition(100, 2625);
    right_borders[11].setPosition(1225, 2535);
    right_borders[12].setPosition(1420, 1800);
    right_borders[13].setPosition(1250, 1675);
    right_borders[14].setPosition(100, 1350);
    right_borders[15].setPosition(650, 940);
    right_borders[16].setPosition(650, -400);
    right_borders[17].setPosition(1075, 180);
    right_borders[18].setPosition(100, -1015);
    right_borders[19].setPosition(850, -2000);
    right_borders[20].setPosition(-120, 5940);
    right_borders[21].setPosition(-145, 5240);
    right_borders[22].setPosition(-145, 2160);
    right_borders[23].setPosition(-900, 2150);
    right_borders[24].setPosition(655, 2150);

    left_borders[0].setPosition(-990, 6700);
    left_borders[1].setPosition(-275, 6330);
    left_borders[2].setPosition(-1050, 5650);
    left_borders[3].setPosition(-925,5525);
    left_borders[4].setPosition(-1225,4750);
    left_borders[5].setPosition(-275,4450);
    left_borders[6].setPosition(-850,4250);
    left_borders[7].setPosition(-975,4025);
    left_borders[8].setPosition(-1085,3100);
    left_borders[9].setPosition(-1025, 3100);
    left_borders[10].setPosition(-275, 2625);
    left_borders[11].setPosition(-1500, 2525);
    left_borders[12].setPosition(-1600, 1800);
    left_borders[13].setPosition(-1450, 1675);
    left_borders[14].setPosition(-275, 1350);
    left_borders[15].setPosition(-850, 940);
    left_borders[16].setPosition(-1250, 180);
    left_borders[17].setPosition(-850, -400);
    left_borders[18].setPosition(-275, -1015);
    left_borders[19].setPosition(-1000, -2000);
    left_borders[20].setPosition(0, 5940);
    left_borders[21].setPosition(25, 5240);
    left_borders[22].setPosition(25, 2160);
    left_borders[23].setPosition(-825, 2150);
    left_borders[24].setPosition(755, 2150);
    
    up_borders[0].setPosition(-1000, 6500);
    up_borders[1].setPosition(150, 6500);
    up_borders[2].setPosition(-1000, 5600);
    up_borders[3].setPosition(800, 5600);
    up_borders[4].setPosition(-1150, 4700);
    up_borders[5].setPosition(150 , 4700);
    up_borders[6].setPosition(-1025 , 3100);
    up_borders[7].setPosition(825 , 3100);
    up_borders[8].setPosition(-875 , 2850);
    up_borders[9].setPosition(150 , 2850);
    up_borders[10].setPosition(-1450 , 1675);
    up_borders[11].setPosition(1250 , 1675);
    up_borders[12].setPosition(150 , 1575);
    up_borders[13].setPosition(-1275 , 1575);
    up_borders[14].setPosition(-1100 , 180);
    up_borders[15].setPosition(-850, -250);
    up_borders[16].setPosition( 150 , -250);
    up_borders[17].setPosition( 720 , 180);
    up_borders[18].setPosition( -1000 , -2100);
    up_borders[19].setPosition( -60 , 5950);
    up_borders[20].setPosition( -60 , 5300);
    up_borders[21].setPosition( -60 , 2175);
    up_borders[22].setPosition( -850 , 2160);
    up_borders[23].setPosition( 730 , 2160);

    down_borders[0].setPosition(-900, 7450);
    down_borders[1].setPosition(-970, 6300);
    down_borders[2].setPosition(130, 6300);
    down_borders[3].setPosition(-1000, 5500);
    down_borders[4].setPosition(775, 5500);
    down_borders[5].setPosition(-840, 4425);
    down_borders[6].setPosition(110, 4425);
    down_borders[7].setPosition(-875, 4225);
    down_borders[8].setPosition(700, 4225);
    down_borders[9].setPosition(825, 4025);
    down_borders[10].setPosition(-1000, 4025);
    down_borders[11].setPosition(-1275, 2600);
    down_borders[12].setPosition(150, 2600);
    down_borders[13].setPosition(-1525, 2500);
    down_borders[14].setPosition(1250, 2500);
    down_borders[15].setPosition(-1020, 1325);
    down_borders[16].setPosition(150, 1325);
    down_borders[17].setPosition(-1100, 900);
    down_borders[18].setPosition(720, 900);
    down_borders[19].setPosition(150, -1020);
    down_borders[20].setPosition(-850, -1020);
    down_borders[21].setPosition(-60, 5900);
    down_borders[22].setPosition(-60, 5150);
    down_borders[23].setPosition(-60, 2050);
    down_borders[24].setPosition(-850, 2100);
    down_borders[25].setPosition(730, 2100);

    for (int i = 0; i < 8; i++) {
        RunAnimation[i].loadFromFile("Run/run" + to_string(i) + ".png");
    }
    for (int i = 0; i < 7; i++) {
        Vmove[i].loadFromFile("V move/Vmove" + to_string(i) + ".png");
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

    menu_opener.loadFromFile("Title card.mp3");
    death_sound.loadFromFile("Death Sound.mp3");
    game_music.loadFromFile("Game music.mp3");
}


void Draw()
{
    window.clear();
    window.draw(Map1);
    if (!ispassing)
        window.draw(Player);
    ShowMonsters();
    gui.drawGUI(window);
    
 /*   for (int i = 0; i < doors; i++) {
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
      window.draw(down_borders[i]);*/

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
    // cooldown timer
    for (int i = 0; i < 5; i++) {
        cooldown[i] -= playerdeltatime;
        if (cooldown[i] <= 0)
            cooldown[i] = 0;
    }
    // state switch logic 
   
    if (!animation_running) {
        
        if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W)) && Keyboard::isKeyPressed(Keyboard::LShift))
        {
            curr_state = run;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W))
        {
            curr_state = walk;
        }
        else
        {
            curr_state = idle;
        }

        if ((Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(Mouse::Left)) && cooldown[0] == 0)
        {
            curr_state = base;
            cooldown[0] = 1.5;
        } 
        if (Keyboard::isKeyPressed(Keyboard::X) && cooldown[1] == 0)
        {
            curr_state = xmove;
            cooldown[1] = 3;
        }
        if (Keyboard::isKeyPressed(Keyboard::C) && cooldown[2] == 0)
        {
            curr_state = cmove;
            cooldown[2] = 6;
        }
        if (Keyboard::isKeyPressed(Keyboard::V)&& cooldown[3] == 0)
        {  
            curr_state = vmove;
            cooldown[3] = 9;
        }
        if (Keyboard::isKeyPressed(Keyboard::Q) && cooldown[4] == 0) {

            cooldown[4] = 3;
            isdashing = true;
        }
        
        if (ishit)
        {
            curr_state = hit;
        }
        if (Player_Health <= 0)
        {
            curr_state = dead;
        }
        
        // set Animation variables based on state 

        switch (curr_state)
        {
        case base:
            maximagecounter = 8;
            ImageCounter = 0; animation_running = true;
            break;
        case vmove:
            maximagecounter = 7;
            ImageCounter = 0; animation_running = true;
            break;
        case xmove:
            maximagecounter = 7;
            ImageCounter = 0; animation_running = true;
            break;
        case cmove:
            maximagecounter = 8;
            ImageCounter = 0; animation_running = true;
            break;
        case hit:
            maximagecounter = 3;
            ImageCounter = 0; animation_running = true;
            break;
        case dead:
            maximagecounter = 3;
            ImageCounter = 0; animation_running = true;
            break;
        }
    }
    
    // Animate 

    switch (curr_state) {
    case run:maximagecounter = 8; Player.setTexture(RunAnimation[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case walk: maximagecounter = 8; Player.setTexture(walkAnimation[ImageCounter]); UpdateAnimationCounter(0.2); break;
    case idle: Player.setTexture(Idle); UpdateAnimationCounter(0.1); break;
    case base: Player.setTexture(BaseAttack[ImageCounter]); UpdateAnimationCounter(0.08); break;//0.12
    case vmove: Player.setTexture(Vmove[ImageCounter]); UpdateAnimationCounter(0.11); break;
    case xmove: Player.setTexture(Xmove[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case cmove: Player.setTexture(Cmove[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case hit:Player.setTexture(HitAnimation[ImageCounter]); UpdateAnimationCounter(0.15); break;    
    case dead: Player.setTexture(DeathAnimation[ImageCounter]); UpdateAnimationCounter(0.1); break;
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
            if (curr_state != state::dead) {
                if (animation_running) animation_running = false;
                ImageCounter = 0;
            }
            else 
            {
                Player.setTexture(DeathAnimation[2]);
                isDead = true;

            }

        }
    }

}

void menu_handler()
{
    while (true) {
        if (pagenum == 10)
        {
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        break;
                    }
                    if (MenuOpener.getStatus() != Sound::Playing && !openertrigger) {
                        MenuOpener.setVolume(80);
                        MenuOpener.setBuffer(menu_opener);
                        MenuOpener.play();
                        openertrigger = true;
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
                if (pagenum != 10) {
                    break;
                }
                window.draw(bg);
                menu.drawMenu(window);
                window.display();
            }
            if (pagenum == -1) {
                window.close();
                MenuOpener.stop();
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
        music_handler();
        update();
        Draw();
    }
}


void Instructions_Draw() {
    window.clear();
    window.draw(Instructions);
    window.display();
}


void Instructions_Menu(RenderWindow& window) {
    while (window.isOpen()) {
        Event instructionsMenu;
        while (window.pollEvent(instructionsMenu)) {
            if (instructionsMenu.type == Event::Closed) {
                window.close();
            }
        }
        Instructions_Draw();
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            pagenum = 10;
            menu_handler();
        }
    }

}


void PauseMenuHandler(RenderWindow& window)
{
    if (GameMusic.getStatus() == Sound::Playing) 
        GameMusic.pause();

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
                GameMusic.play();
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
                pagenum = 10;
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

void game_reset() 
{
    Player_Health = 100;
    curr_state = idle;
    DeathSound.stop();
    isDead = false;
    for (int i = 0; i < 5; i++) 
        cooldown[i] = 0;
    Player.setPosition(initial_position);
    Player.setScale(0.2, 0.2);
    openertrigger = false;
    map_opener_trigger = false;
    death_trigger = false;
    room_cleared = true;
    ResetMonsters();
    current_room = 0;
    current_wave = 0;
    float AnimationCounter = 0;
    int maximagecounter = 0;
    int ImageCounter = 0;
    int globalInt = 0;
    float playerdeltatime = 0;
}

void music_handler()
{
    if (MenuOpener.getStatus() == Sound::Playing) MenuOpener.stop();
    if (GameMusic.getStatus() != Sound::Playing && !map_opener_trigger) {
        GameMusic.setVolume(5);
        GameMusic.setBuffer(game_music);
        GameMusic.play();
        map_opener_trigger = true;
    }
}

void death_handler()
{
    lastX = Player.getPosition().x;
    lastY = Player.getPosition().y;
    GameOver game_over(1920, 1080, lastX, lastY);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        DeathScreen.setPosition(lastX -675,lastY - 700 );
        Player.setTexture(DeathAnimation[2]);
        GameMusic.stop();


        if (DeathSound.getStatus() != Sound::Playing && !death_trigger) {
            DeathSound.setBuffer(death_sound);
            DeathSound.setVolume(50);
            DeathSound.play();
            death_trigger = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                game_over.moveup();
                GameClock.restart();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                game_over.movedown();
                GameClock.restart();
            }
        }

        // Restart
       
        if (Keyboard::isKeyPressed(Keyboard::Enter) && game_over.selectedp == 0) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                GameClock.restart();
                game_reset();
                break;
            }
        }

        // retrun to Main menu

        if (Keyboard::isKeyPressed(Keyboard::Enter) && game_over.selectedp == 1) {
            if (GameClock.getElapsedTime().asSeconds() > 0.2) {
                GameClock.restart();
                pagenum = 10;
                game_reset();
                view.setCenter(960, 540); //update
                window.setView(view);
                menu_handler();
            }
        }

        window.clear();
        window.draw(Map1);
        if (!ispassing)
            window.draw(Player);

        ShowMonsters();
        window.draw(DeathScreen);
        game_over.draw(window);
        window.display();
    }
}

void fell()
{
    for(int i = 0; i <5; i++)
    if (Player.getGlobalBounds().intersects(left_borders[20+i].getGlobalBounds())
        && Player.getGlobalBounds().intersects(right_borders[20+i].getGlobalBounds()) 
        && Player.getGlobalBounds().intersects(up_borders[19+i].getGlobalBounds()) 
        && Player.getGlobalBounds().intersects(down_borders[21+i].getGlobalBounds())) 
        {
            Player_Health -= 200;
        }

}

void check_room()
{
    int initial = current_room;
    for (int i = 0; i < doors; i++) {
        if (Player.getPosition().y < gates[i].getPosition().y - 200) {
            current_room = max(current_room,i + 1);          
        }
    }
    if (current_room > initial){
        SetMonstersWave();
        room_cleared = false;
        Player_Health += 20 * (current_room - 1);
    }
}


void checkpause()
{
    if (Keyboard::isKeyPressed(Keyboard::Escape) && !isDead) {
        if (pausetimer.getElapsedTime().asSeconds() > 0.2) {
            PauseMenuHandler(window);
            pausetimer.restart();
        }
    }
}


void dash()
{
    if (isdashing) {
        if (dash_duration > 0) {
            run_speed = 1000;
            walk_speed = 1000;
            dash_duration -= playerdeltatime;
        }
        else {
            isdashing = false;
            dash_duration = 0.075;
            run_speed = 200;
            walk_speed = 100;
        }
    }
   
}