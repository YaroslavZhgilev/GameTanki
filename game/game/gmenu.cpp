#include "gmenu.h"
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать 

void menu(RenderWindow & window) {
		Music men;
		men.openFromFile("men.ogg");
		men.play();
		men.setVolume(40);
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground,tank;
	tank.loadFromFile("images/tank.png");
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/vladik.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground),tank1(tank);
	bool isMenu = true;
	int menuNum = 0;
	tank1.setPosition(250,0);
	menu1.setPosition(100, 150);
	menu2.setPosition(100, 210);
	menu3.setPosition(100, 270);
	menuBg.setPosition(345, 200);
 
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{	
		tank1.setColor(Color::White);
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(0, 0, 0));
 
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; }
		if (IntRect(100, 210, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Green); menuNum = 2; }
		if (IntRect(100, 270, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Green); menuNum = 3; }
 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
		window.draw(tank1);
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		
		window.display();
	}
	////////////////////////////////////////////////////
}