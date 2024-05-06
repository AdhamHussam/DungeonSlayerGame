#include "includes.h"
#include "Menu.h"
#include "Monsters.h"
#include "globals.h"
#include "PauseMenu.h"


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

// menu number
int pagenum = 69;


// player attributes

int walk_speed = 100;
int run_speed = 200;
Vector2f velocity = { 0, 0 };
float AnimationCounter = 0;
int maximagecounter = 0;
int ImageCounter = 0;
bool sha8al = false;
bool isDead = false;
bool openertrigger = false;
bool map_opener_trigger = false;
bool death_trigger = false;
bool ispassing = false;
bool wave_cleared = true;
bool finishedanimationonce = false;
float cooldown[4];

//RenderWindow window(VideoMode(1920, 1080), "Dungeon Slayer" ,Style::Fullscreen);
Menu menu(1920, 1080);
PauseMenu pause(1920, 1080);
Clock pausetimer;
Clock attacktimer;


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


RectangleShape borderR1(Vector2f({ 100,1000 }));
RectangleShape borderR2(Vector2f({ 50,200 }));
RectangleShape borderR3(Vector2f({ 50,800 }));
RectangleShape borderR4(Vector2f({ 50,100 }));
RectangleShape borderR5(Vector2f({ 50,1000 }));
RectangleShape borderR6(Vector2f({ 50,200 }));
RectangleShape borderR7(Vector2f({ 50,150 }));
RectangleShape borderR8(Vector2f({ 50,150 }));
RectangleShape borderR9(Vector2f({ 50,1000 }));
RectangleShape borderR10(Vector2f({ 100,50 }));
RectangleShape borderR11(Vector2f({ 50,250 }));
RectangleShape borderR12(Vector2f({ 150,50 }));
RectangleShape borderR13(Vector2f({ 50,900 }));
RectangleShape borderR14(Vector2f({ 75,50 }));
RectangleShape borderR15(Vector2f({ 50,200 }));
RectangleShape borderR16(Vector2f({ 50,500 }));
RectangleShape borderR17(Vector2f({ 50,600 }));
RectangleShape borderR18(Vector2f({ 50,600 }));
RectangleShape borderR19(Vector2f({ 50,800 }));
RectangleShape borderR20(Vector2f({ 50,775 }));
RectangleShape borderR21(Vector2f({ 10,10 }));
RectangleShape borderR22(Vector2f({ 10,10 }));
RectangleShape borderR23(Vector2f({ 10,10 }));
RectangleShape borderR24(Vector2f({ 10,10 }));
RectangleShape borderR25(Vector2f({ 10,10 }));

RectangleShape borderL1(Vector2f({ 50,1000 })); 
RectangleShape borderL2(Vector2f({ 50,200 })); 
RectangleShape borderL3(Vector2f({ 50,800 })); 
RectangleShape borderL4(Vector2f({ 50, 100 })); 
RectangleShape borderL5(Vector2f({ 50, 1000 }));
RectangleShape borderL6(Vector2f({ 50, 200 }));
RectangleShape borderL7(Vector2f({ 50, 150 }));
RectangleShape borderL8(Vector2f({ 50, 150 }));
RectangleShape borderL9(Vector2f({ 50, 1000 }));
RectangleShape borderL10(Vector2f({ 100, 50 }));
RectangleShape borderL11(Vector2f({ 50, 250 }));
RectangleShape borderL12(Vector2f({ 150, 50 }));
RectangleShape borderL13(Vector2f({ 50, 900 }));
RectangleShape borderL14(Vector2f({ 75,50 }));
RectangleShape borderL15(Vector2f({ 50,200 }));
RectangleShape borderL16(Vector2f({ 50,500 }));
RectangleShape borderL17(Vector2f({ 50,600 }));
RectangleShape borderL18(Vector2f({ 50,600 }));
RectangleShape borderL19(Vector2f({ 50, 775 }));
RectangleShape borderL20(Vector2f({ 50,800 }));
RectangleShape borderL21(Vector2f({ 10,10 }));
RectangleShape borderL22(Vector2f({ 10,10 }));
RectangleShape borderL23(Vector2f({ 10,10 }));
RectangleShape borderL24(Vector2f({ 10,10 }));
RectangleShape borderL25(Vector2f({ 10,10 }));

RectangleShape borderU1(Vector2f({ 700,50 }));
RectangleShape borderU2(Vector2f({ 700,50 }));
RectangleShape borderU3(Vector2f({ 100,50 }));
RectangleShape borderU4(Vector2f({ 100,50 }));
RectangleShape borderU5(Vector2f({ 900,50 }));
RectangleShape borderU6(Vector2f({ 900,50 }));
RectangleShape borderU7(Vector2f({ 100,50 }));
RectangleShape borderU8(Vector2f({ 100,50 }));
RectangleShape borderU9(Vector2f({ 600,50 }));
RectangleShape borderU10(Vector2f({ 600,50 }));
RectangleShape borderU11(Vector2f({ 75,50 }));
RectangleShape borderU12(Vector2f({ 75,50 }));
RectangleShape borderU13(Vector2f({ 1000,50 }));
RectangleShape borderU14(Vector2f({ 1000,50 }));
RectangleShape borderU15(Vector2f({ 250,50 }));
RectangleShape borderU16(Vector2f({ 600,50 }));
RectangleShape borderU17(Vector2f({ 600,50 }));
RectangleShape borderU18(Vector2f({ 250,50 }));
RectangleShape borderU19(Vector2f({ 2000,50 }));
RectangleShape borderU20(Vector2f({ 10,10 }));
RectangleShape borderU21(Vector2f({ 10,10 }));
RectangleShape borderU22(Vector2f({ 10,10 }));
RectangleShape borderU23(Vector2f({ 10,10 }));
RectangleShape borderU24(Vector2f({ 10,10 }));

RectangleShape borderD1(Vector2f({ 2000,50 }));
RectangleShape borderD2(Vector2f({ 700,50 }));
RectangleShape borderD3(Vector2f({ 700,50 }));
RectangleShape borderD4(Vector2f({ 100,50 }));
RectangleShape borderD5(Vector2f({ 100,50 }));
RectangleShape borderD6(Vector2f({ 600,50 }));
RectangleShape borderD7(Vector2f({ 600,50 }));
RectangleShape borderD8(Vector2f({ 50,50 }));
RectangleShape borderD9(Vector2f({ 50,50 }));
RectangleShape borderD10(Vector2f({ 50,50 }));
RectangleShape borderD11(Vector2f({ 50,50 }));
RectangleShape borderD12(Vector2f({ 1000,50 }));
RectangleShape borderD13(Vector2f({ 1000,50 }));
RectangleShape borderD14(Vector2f({ 150,50 }));
RectangleShape borderD15(Vector2f({ 150,50 }));
RectangleShape borderD16(Vector2f({ 750,50 }));
RectangleShape borderD17(Vector2f({ 750,50 }));
RectangleShape borderD18(Vector2f({ 250,50 }));
RectangleShape borderD19(Vector2f({ 250,50 }));
RectangleShape borderD20(Vector2f({ 550,50 }));
RectangleShape borderD21(Vector2f({ 550,50 }));
RectangleShape borderD22(Vector2f({ 10,10 }));
RectangleShape borderD23(Vector2f({ 10,10 }));
RectangleShape borderD24(Vector2f({ 10,10 }));
RectangleShape borderD25(Vector2f({ 10,10 }));
RectangleShape borderD26(Vector2f({ 10,10 }));

RectangleShape gates[] = { gate1, gate2 , gate3, gate4, gate5};

RectangleShape right_borders[] = { borderR1 , borderR2 , borderR3 , borderR4 ,borderR5, borderR6, borderR7, borderR8, borderR9, borderR10 ,
    borderR11, borderR12 , borderR13 , borderR14 , borderR15 , borderR16 , borderR17, borderR18, borderR19 ,borderR20, borderR21 , borderR22,
    borderR23, borderR24 , borderR25
};

RectangleShape left_borders[] = { borderL1,borderL2 , borderL3 , borderL4, borderL5 , borderL6 , borderL7, borderL8, borderL9, borderL10,
    borderL11 , borderL12 , borderL13 , borderL14 , borderL15 , borderL16 ,borderL17, borderL18, borderL19 , borderL20, borderL21, borderL22,
    borderL23 ,borderL24 , borderL25
};

RectangleShape up_borders[] = { borderU1, borderU2 , borderU3 , borderU4, borderU5, borderU6, borderU7, borderU8, borderU9, borderU10,
    borderU11,borderU12 ,borderU13, borderU14 , borderU15 , borderU16, borderU17, borderU18, borderU19,borderU20 , borderU21, borderU22,
    borderU23 , borderU24
};

RectangleShape down_borders[] = { borderD1,borderD2, borderD3 , borderD4, borderD5, borderD6, borderD7, borderD8, borderD9 ,borderD10,
    borderD11 , borderD12 , borderD13 , borderD14 , borderD15 , borderD16, borderD17, borderD18 , borderD19 ,borderD20, borderD21 , 
    borderD22 , borderD23, borderD24 , borderD25 , borderD26
};

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
        Switch_States();
        playerMovement();
        MoveMonsters();
    }
    else {
        Player.setTexture(DeathAnimation[2]);
        GameMusic.stop();
        if (DeathSound.getStatus() != Sound::Playing && !death_trigger) {
            DeathSound.setBuffer(death_sound);
            DeathSound.setVolume(80);
            DeathSound.play();
            death_trigger = true;
        }
      
    }
    trackView();
    checkCollisions();
    
    if (Keyboard::isKeyPressed(Keyboard::Escape) && !isDead) {
        if (pausetimer.getElapsedTime().asSeconds() > 0.2) {
            PauseMenuHandler(window);
            pausetimer.restart();
        }
    }
}

void checkCollisions() 
{
    //doors
    for (int i = 0; i < doors; i++) {
        if (Player.getGlobalBounds().intersects(gates[i].getGlobalBounds())) {
            ispassing = true;
            Player.move(0, -500 * playerdeltatime);
            wave_cleared = false;
            GameMusic.setVolume(80);
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

    bg.setTexture(mainmenubg);
    Instructions.setTexture(instructs);
    pausemenu.setTexture(pausebg);

    bg.setScale(0.5, 0.5);
    Instructions.setScale(0.5, 0.5);
    pausemenu.setScale(0.5, 0.5);
    
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
   
    // monsters
    SetMonstersWave();

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
    
    /*for (int i = 0; i < doors; i++) {
        window.draw(gates[i]);
    } */ 
    /*for(int i = 0; i < left_walls;i++){
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

    for (int i = 0; i < 4; i++) {
        cooldown[i] -= playerdeltatime;
        if (cooldown[i] <= 0)
            cooldown[i] = 0;
    }
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
            if (cooldown[0] == 0) {
                curr_state = state::base;
                cooldown[0] = 1.5;
            }
        }
     
        if (Keyboard::isKeyPressed(Keyboard::X))
        {
            if (cooldown[1] == 0) {

                curr_state = state::xmove;
                cooldown[1] = 3;
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::C))
        {
            if (cooldown[2] == 0) {
                curr_state = state::cmove;
                cooldown[2] = 6;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::V))
        {
            if (cooldown[3] == 0) {

                curr_state = state::vmove;
                cooldown[3] = 9;
            }
        }
        if (ishit)
        {
            curr_state = state::hit;
        }
        if (Player_Health <= 0)
        {
            curr_state = state::dead;
        }
      


        switch (curr_state)
        {
        case state::base:
            maximagecounter = 8;
            ImageCounter = 0; sha8al = true;
            break;
        case state::vmove:
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
            ImageCounter = 0; sha8al = true;
            break;
        case state::dead:
            maximagecounter = 3;
            ImageCounter = 0; sha8al = true;
            break;
        }
    }

    switch (curr_state) {
    case state::run:maximagecounter = 8; Player.setTexture(RunAnimation[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case state::walk: maximagecounter = 8; Player.setTexture(walkAnimation[ImageCounter]); UpdateAnimationCounter(0.2); break;
    case state::idle: Player.setTexture(Idle); UpdateAnimationCounter(0.1); break;
    case state::base: Player.setTexture(BaseAttack[ImageCounter]); UpdateAnimationCounter(0.08); break;//0.12
    case state::vmove: Player.setTexture(Vmove[ImageCounter]); UpdateAnimationCounter(0.11); break;
    case state::xmove: Player.setTexture(Xmove[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case state::cmove: Player.setTexture(Cmove[ImageCounter]); UpdateAnimationCounter(0.1); break;
    case state::hit:Player.setTexture(HitAnimation[ImageCounter]); UpdateAnimationCounter(0.15); break;    
    case state::dead: Player.setTexture(DeathAnimation[ImageCounter]); UpdateAnimationCounter(0.1); break;
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
                if (sha8al) sha8al = false;
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
                if (pagenum != 69) {
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
        //cout << Player.getPosition().x << " " << Player.getPosition().y << endl;
        //cout << Player_Health << endl;
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
            pagenum = 69;
            menu_handler();
        }
    }

}


void PauseMenuHandler(RenderWindow& window)
{
    if (GameMusic.getStatus() == Sound::Playing) GameMusic.pause();
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
    Player_Health = 100;
    curr_state = state::idle;
    isDead = false;
    for (int i = 0; i < 4; i++) cooldown[i] = 0;
    Player.setPosition(initial_position);
    Player.setScale(0.2, 0.2);
    openertrigger = false;
    map_opener_trigger = false;
    wave_cleared = true;
    float AnimationCounter = 0;
    int maximagecounter = 0;
    int ImageCounter = 0;
    int globalInt = 0;
    float playerdeltatime = 0;
    SetMonstersWave();
}

void music_handler()
{
    if (MenuOpener.getStatus() == Sound::Playing) MenuOpener.stop();
    if (GameMusic.getStatus() != Sound::Playing && !map_opener_trigger) {
        if (wave_cleared)
            GameMusic.setVolume(5);
        else
            GameMusic.setVolume(80);
        GameMusic.setBuffer(game_music);
        GameMusic.play();
        map_opener_trigger = true;
    }
}