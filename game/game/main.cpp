#include <SFML/Graphics.hpp> 
 
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ 
int main() {  //������ ����  
	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 2"); 
 
	Image heroimage; //������� ������ Image (�����������)  
	heroimage.loadFromFile("images/hero.png");//��������� � ���� ���� 
 
	Texture herotexture;//������� ������ Texture (��������)  
	herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������) 
 
	 Sprite herosprite;//������� ������ Sprite(������)  
	 herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)  
	 herosprite.setPosition(50, 25);//������ ��������� ���������� ��������� ������� 
 
 while (window.isOpen())  //���� ���� �������  
	{   
		 sf::Event event;   
		 while (window.pollEvent(event))  
			 {    
				 if (event.type == sf::Event::Closed)    
				 window.close();   
			} 
 
  window.clear(); //������� �����   
  window.draw(herosprite);//������ ������   
  window.display(); //���������� ������ �� ������ 
	 } 
 
 return 0; 
 } 