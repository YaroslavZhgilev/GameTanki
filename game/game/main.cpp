#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cmath>
 
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ 
int main() {  //������ ����   
	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 6"); 
 
	Image heroimage; //������� ������ Image (�����������)  
	heroimage.loadFromFile("images/hero.png");//��������� � ���� ���� 
 
	Texture herotexture;//������� ������ Texture (��������)  
	herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������) 

	float CurrentFrame=0; //������ ������� ���� 
	Clock clock;   //������� ���������� ������� � ������������ ��������� ����!
 
	 Sprite herosprite;//������� ������ Sprite(������)  
	 herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)  
	 herosprite.setTextureRect(IntRect(0, 192, 96, 96));//�������� ������ ������������� 
	 herosprite.setPosition(250, 250);//������ ��������� ���������� ��������� ������� 
 
 while (window.isOpen())  //���� ���� �������  
	{   

		// ���� ����� � ���������� ����������� �����, � ������ ������ �����, ��������� �              
		//���������� �������� � ������ restart();   
		float time = clock.getElapsedTime().asMicroseconds();    
		clock.restart(); //���������� �����   
		time = time / 800; //�������� ����   
		    
		 sf::Event event;   
		 while (window.pollEvent(event))  
			 {    
				 if (event.type == sf::Event::Closed)    
				 window.close();   
			} 
		 //"-0,1" - ����� ������� ���������, �������� � �� ���� ����� �time� � ��������    
		 //���������� ���������� 
 
		 if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) 
		 { 
			 //���� ������ ������� ������� ����� ��� ���� ����� �  
			 CurrentFrame += 0.005*time;  //������ ��� ����������� �� "������". ���������� ������� �� ����, �������� ������������ 
			 //������� � ��������. ������� 0.005, ����� �������� �������� ��������  
			 if (CurrentFrame > 3) CurrentFrame -= 3; //���� ������ � �������� ����� - ������������ 
			 //�����.  
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //�������� �� 
			 //����������� �. ����������, ��� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0  
			 herosprite.move(-0.1*time, 0); //���������� �������� ��������� ����� 
		 } 

		 if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) 
		 {   
			 CurrentFrame += 0.005*time;     
			 if (CurrentFrame > 3) CurrentFrame -= 3;     
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));     //�������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96 
		     herosprite.move(0.1*time, 0); //�������� ��������� ������ 
 
		 }

		 if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) 
		 {    
			 CurrentFrame += 0.005*time;     
			 if (CurrentFrame > 3) CurrentFrame -= 3;     
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));     //�������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96   
			 herosprite.move(0, -0.1*time); //�������� ��������� �����   
		 } 

         if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) 
		 {    
			 CurrentFrame += 0.005*time;     
			 if (CurrentFrame > 3) CurrentFrame -= 3;     
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));     //�������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96    
			 herosprite.move(0, 0.1*time); // �������� ��������� ����   
		 }

  window.clear(); //������� �����   
  window.draw(herosprite);//������ ������   
  window.display(); //���������� ������ �� ������ 
	 } 
 
 return 0; 
 } 