#include "includes.h"
#include "GUI.h"
#include "globals.h"

using namespace std;
using namespace sf;

Texture skillframe1;
Clock frameClock;
float frameDelay = 0.11f;
void GUIskill::drawSkill(sf::RenderWindow& window, int id) {
	font.loadFromFile("Ungai.ttf");
	Sprite border;
	border.setScale(Vector2f(3.5, 3.5));
	border.setPosition(pos.first, pos.second);
	border.setTexture(myFrame);
	window.draw(border);
	Text key;
	key.setFont(font);
	//key.setColor(color::White);
	if (id == 0) {
		key.setString("Left \n Click");
		key.setCharacterSize(14);
		key.setPosition(pos.first + 20, pos.second - 50);
	}
	else if (id == 1) key.setString(" X ");
	else if (id == 2) key.setString(" C ");
	else if (id == 3) key.setString(" V ");
	if (id != 0)key.setPosition(pos.first + 20, pos.second - 50);
	window.draw(key);
	RectangleShape avatar(sf::Vector2f(80, 80));
	avatar.setPosition(pos.first, pos.second);
	avatar.setTexture(&photo);
	window.draw(avatar);
}
void GUI::setSkillsTexture() {

	skills[0].photo.loadFromFile(R"(GUI\Base5.png)");

	skills[1].photo.loadFromFile(R"(GUI\Xmove4.png)");

	skills[2].photo.loadFromFile(R"(GUI\Cmove2.png)");

	skills[3].photo.loadFromFile(R"(GUI\Vmove3.png)");
}
void GUI::updateSkill() {
	string framename;
	framename = "GUI\\frame" + to_string(framenum);
	framename += ".png";
	string loadingname;
	loadingname = "GUI\\loading" + to_string(framenum);
	loadingname += ".png";
	loadingframe.loadFromFile(loadingname);
	skillframe.loadFromFile(framename);
	pair<int, int> firstposition = { Player.getPosition().x - 40 ,Player.getPosition().y + window.getSize().y / 3 - 20 };

	//skills_background.setPosition(firstposition.first-240, firstposition.second);
	firstposition.second += 10;
	skills[0].pos = { firstposition.first - 180, firstposition.second };
	if (cooldown[0])
		skills[0].myFrame = loadingframe;
	else
		skills[0].myFrame = skillframe;

	skills[1].pos = { firstposition.first - 60, firstposition.second };
	if (cooldown[1])
		skills[1].myFrame = loadingframe;
	else
		skills[1].myFrame = skillframe;

	skills[2].pos = { firstposition.first + 60, firstposition.second };
	if (cooldown[2])
		skills[2].myFrame = loadingframe;
	else
		skills[2].myFrame = skillframe;

	skills[3].pos = { firstposition.first + 180, firstposition.second };
	if (cooldown[3])
		skills[3].myFrame = loadingframe;
	else
		skills[3].myFrame = skillframe;

	if (frameClock.getElapsedTime().asSeconds() > frameDelay) {
		framenum %= 4;
		framenum++;
		frameClock.restart();
	}

}

void GUI::setPlayerInfoTexture() {
	PlayerInfoTexture.loadFromFile(R"(GUI\playerInfo.png)");
	PlayerInfo.setTexture(PlayerInfoTexture);
	healthBarTexture.loadFromFile(R"(GUI\hp_bar.png)");
	healthBar.setTexture(healthBarTexture);
	staminaBarTexture.loadFromFile(R"(GUI\stamina_bar.png)");
	staminaBar.setTexture(staminaBarTexture);
	armorBarTexture.loadFromFile(R"(GUI\armor.png)");
	armorBar.setTexture(armorBarTexture);

	loadingEffectTexture.loadFromFile(R"(GUI\loading_effect.png)");
	loadingEffect.setTexture(loadingEffectTexture);
	loadingEffect.setScale(3.15,3.15);

}

void GUI::setMonstersHPTexture() {
	monsterHPBackTexture.loadFromFile(R"(GUI\monster_bar_back.png)");
	monsterHPBack.setTexture(monsterHPBackTexture);

	bossHPBackTexture.loadFromFile(R"(GUI\boss_empty.png)");
	bossHPBack.setTexture(bossHPBackTexture);

	monsterHPTexture.loadFromFile(R"(GUI\monster_bar.png)");
	monsterHP.setTexture(monsterHPTexture);
	bossHPTexture.loadFromFile(R"(GUI\boss_full.png)");
	bossHP.setTexture(bossHPTexture);

}

// bm 30,35
void GUI::DrawMonsterHP(Vector2f pos, float health, int origHealth, int xdif,int ydif)
{
	if (health <= 0)
		return;

	pos.x -= xdif;
	pos.y -= ydif;
	monsterHPBack.setPosition(pos);
	monsterHPBack.setScale(2,2);

	monsterHP.setPosition(pos);
	monsterHP.setScale(2,2);

	monsterHP.setTextureRect(IntRect(0, 0, monsterHPTexture.getSize().x * health/origHealth, monsterHPTexture.getSize().y));

	window.draw(monsterHPBack);
	window.draw(monsterHP);
}
void GUI::drawBODHP(Vector2f pos, float health) {
	
	if (health <= 0)
		return;

	pos.x -= 25;
	pos.y -= 60;
	monsterHPBack.setPosition(pos);
	monsterHPBack.setScale(2, 2);

	monsterHP.setPosition(pos);
	monsterHP.setScale(2, 2);

	monsterHP.setTextureRect(IntRect(0, 0, monsterHPTexture.getSize().x * health, monsterHPTexture.getSize().y));

	window.draw(monsterHPBack);
	window.draw(monsterHP);
}

void GUI::drawBossHP(float health, int max_health) {
	Vector2f pos = { Player.getPosition().x - bossHPTexture.getSize().x/2,
								Player.getPosition().y - window.getSize().y / 2 +40 };
	bossHPBack.setPosition(pos);
	bossHPBack.setScale(1, 1);

	bossHP.setPosition(pos);
	bossHP.setScale(1, 1);

	bossHP.setTextureRect(IntRect(0, 0, bossHPTexture.getSize().x * health/max_health, bossHPTexture.getSize().y));

	window.draw(bossHPBack);
	window.draw(bossHP);
}

void GUI::updatePlayerInfo(RenderWindow& window) {
	Vector2f infoPosition = { Player.getPosition().x - window.getSize().x/2-20,
								Player.getPosition().y - window.getSize().y / 2 -20};
	int helath_start = healthBarTexture.getSize().x/3;
	int health = (Player_Health > 100 ? 100 : Player_Health);
	int armor = Player_Health - health;
	PlayerInfo.setPosition(infoPosition);
	healthBar.setPosition(infoPosition.x + helath_start -  10, infoPosition.y);
	armorBar.setPosition(infoPosition.x + helath_start-10, infoPosition.y);
	staminaBar.setPosition(infoPosition.x + helath_start-10, infoPosition.y);

	staminaBar.setTextureRect(IntRect(helath_start - 10, 0,
		(3-cooldown[4]) / 3.0 * staminaBarTexture.getSize().x / 2, PlayerInfoTexture.getSize().y));

	healthBar.setTextureRect(IntRect(helath_start - 10, 0,
		 (float)health * 1.5 * helath_start / 100, PlayerInfoTexture.getSize().y));


	armorBar.setTextureRect(IntRect(helath_start - 10, 0,
		 (float)armor * 1.5 * helath_start / 100, PlayerInfoTexture.getSize().y));

}

void GUI::DrawloadingEffect(RenderWindow& window)
{

	Vector2f firstposition = { Player.getPosition().x - 35 ,Player.getPosition().y + window.getSize().y / 3 - 7 };
	float cooldowns[] = { 1.5, 3, 6, 9 };
	float posx[] = { firstposition.x - 180, firstposition.x - 60, firstposition.x + 60, firstposition.x + 180 };
	float posy = firstposition.y;
	for (int i = 0; i < 4; i++)
	{
		if (cooldown[i] > 0)
		{
			loadingEffect.setPosition(posx[i], posy);
			loadingEffect.setColor(Color(255, 255, 255, 255 * cooldown[i] / cooldowns[i]));
			/*loadingEffect.setTextureRect(IntRect(0, 0,
				 loadingEffectTexture.getSize().x * cooldown[i] / cooldowns[i],
				 loadingEffectTexture.getSize().y));*/
			window.draw(loadingEffect);
		}
	}

}
void GUI::drawGUI(RenderWindow& window) {
	updateSkill();
	updatePlayerInfo(window);
	window.draw(PlayerInfo);
	window.draw(healthBar);
	window.draw(armorBar);
	window.draw(staminaBar);
	for (int i = 0; i < 4; i++)
	{
		skills[i].drawSkill(window, i);

	}
	DrawloadingEffect(window);

}



