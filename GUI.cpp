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

void GUI::drawGUI(RenderWindow& window) {
	updateSkill();
	/*skills_background.setSize(Vector2f(560, 90));
	skills_background.setTexture(&back);
	window.draw(skills_background);*/
	for (int i = 0; i < 4; i++)
	{
		skills[i].drawSkill(window, i);
	}

}



