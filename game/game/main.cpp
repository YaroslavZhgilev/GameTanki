#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cmath>
#include <sstream>
#include "map.h" //���������� ��� � ������ 
 
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ 

////////////////////////////////////////////////////����� ������//////////////////////// 
class Player { // ����� ������ 
public:  float x, y, w, h, dx, dy, speed; //���������� ������ � � �, ������ � ������,        
		 //��������� (�� � � �� �), ���� ��������  
		 int playerScore;//����� ����������, �������� ���� ������ 
		 int dir; //����������� (direction) �������� ������  
		 std::string File; //���� � �����������  
		 Image image;//���� �����������  
		 Texture texture;//���� ��������  
		 Sprite sprite;//���� ������ 
		 //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ �� ����� �������� 
		 //��� �����, ���������� � � �, ������ � ������ 
		 Player(std::string F, float X, float Y, float W, float H){
			 dir = 0; speed = 0; playerScore = 0; 
			 File = F; //��� �����+����������  
			 w = W; 
			 h = H; //������ � ������  
			 image.loadFromFile("images/" + File);//��������� � image �����������, ������ File  
			 //��������� ��, ��� �������� ��� �������� �������. � ����� ������ ��� "hero.png". ���������  
			 //������, ���������� image.loadFromFile("images/hero/png");  
			 image.createMaskFromColor(Color(41, 33, 59)); //������� �������� �����-����� ���� 
			 texture.loadFromImage(image); //������� ���� ����������� � ��������  
			 sprite.setTexture(texture); //�������� ������ ���������  
			 x = X; 
			 y = Y; //���������� ��������� �������        
			 speed= 0;        
			 dir= 0;  
			 sprite.setTextureRect(IntRect(0, 0, w, h)); //������ ������� ���� ������������� ���  //������ ������ ����. IntRect � ��� ���������� ����� 
}
		 void update(float time) //������� "���������/����������" ������� ������. ��������� � ����   
			 //����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������. 
		 {  
			 switch (dir)//��������� ��������� � ����������� �� �����������. ������ ����� 
				 //������������� �����������.  
			 {
				case 0: dx = speed; dy = 0; break; //�� �X� ������ ������������� ��������, �� �Y� - 0.         
					//�������� ���� ������ ������.  
				case 1: dx = -speed; dy = 0; break;//�� �X� ������ ������������� ��������, �� � �Y� � 0.      
					//�������� ���� ������ �����.  
				case 2: dx = 0; dy = speed; break;//�� �X� ������ ������� ��������, �� �Y�     
					//�������������. ����������, ��� �������� ���� ������ ����  
				case 3: dx = 0; dy = -speed; break;//�� �X� ������ ������� ��������, �� �Y�    
					//�������������. ����������, ��� �������� ���� ������ �����  
			 } 
 
		 x += dx*time; //�������� �� �X�  
		 y += dy*time; //�������� �� �Y�  
		 speed = 0;    //�������� ��������, ����� �������� �����������. 
		 sprite.setPosition(x, y); //������� ������ � ������� (x, y).     
		 //���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
		 interactionWithMap();//�������� �������, ���������� �� �������������� � ������ 
		 }

		 void interactionWithMap()//�-��� �������������� � ������ 
		 {
			 //�������� ������ �� ��� ������ (����������� ������� 32*32), ������� ������������ � �������. //�������� ��� ��������� ��������� ��� ������������ ������!   
			 for (int i = y / 32; i < (y + h) / 32; i++)   
				 for (int j = x / 32; j<(x + w) / 32; j++){ 
					 //�x� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. 
					 //�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ������ 
					 //����� ����, j<(x + w)/32 - ������� ����������� ��������� �� �x�, �.�. ���������� ������ 
					 //������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� 
					 // ������� �� ����, ������� �� ������ �������� (���������������� � ������), �� ������� 
					 // �������� (���������������� � ������)   
					 if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� �0�      
						 //(�����), �� ��������� "����������� ��������" ���������:  
					 {   
						 if (dy>0) {
							 //���� �� ��� ����,    
							 y = i * 32 - h;//�� �������� (-h) ���������� �y� ���������.      
							 //������� �������� ���������� �i� ������ ���������� �� ����� �     
							 //����� �������� �� ������ ������� ���������.    
						 }    
						 if (dy<0){    
							 y = i * 32 + 32;//���������� � ��������� �����. 
						 }    
						 if (dx>0){    
							 x = j * 32 - w;//���� ���� ������, �� ���������� �x� �����         
							 //����� (������ 0) ����� ������ ���������    
						 }    
						 if (dx < 0){   
							 x = j * 32 + 32; //���������� ���� �����    
						 }   
					 }     
					 if (TileMap[i][j] == 's') { 
						 //���� ������ ����� 's' (������)     
						 playerScore++;//�����-�� ��������     
						 TileMap[i][j] = ' ';//������� ������    
					 } 
				 }
}
};
int main() {  //������ ����   
	Player p("hero.png", 250, 250, 96.0, 96.0); //������� ������ �p� ������ �Player�, //������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 6"); 


Font font;//�����   
font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������  
Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);
//��� ������ ����� (�� ������)  
text.setColor(Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����  
text.setStyle(Text::Bold);//������ �����.
	Image map_image;//������ ����������� ��� ����� 
	map_image.loadFromFile("images/map.png");//��������� ���� ��� ����� 
	Texture map;//�������� ����� 
	map.loadFromImage(map_image);//�������� �������� ���������  
	Sprite s_map;//������ ������ ��� ����� 
	s_map.setTexture(map);//�������� �������� �������� 

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
			 p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������.   
			 //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���  
			 CurrentFrame += 0.005*time;  
			 if (CurrentFrame > 3) CurrentFrame -= 3;  
			 p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //����� ������ p         
			 //������ player ������ ������, ����� ��������  
		 } 

		 if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) 
		 {   
			 p.dir = 0; p.speed = 0.1;//����������� ������  
			 CurrentFrame += 0.005*time;  
			 if (CurrentFrame > 3) CurrentFrame -= 3; 
			 p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //����� ������ p        
			 //������ player ������ ������, ����� ��������
 
		 }

		 if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) 
		 {    
			 p.dir = 3; p.speed = 0.1;//����������� ����  
			 CurrentFrame += 0.005*time;  
			 if (CurrentFrame > 3) CurrentFrame -= 3; 
			 p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); //����� ������ p    
			 //������ player ������ ������, ����� �������� (��������� �������� �����)   
		 } 

         if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) 
		 {    
			 p.dir = 2; p.speed = 0.1;//����������� ����� 
			 CurrentFrame += 0.005*time; 
			 if (CurrentFrame > 3) CurrentFrame -= 3; 
			 p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));    
		 }

		 p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml, 
		 // ��������� ����� � �������� ��������� ������� update. 
  window.clear(); //������� �����   

  /////////////////////////////������ �����///////////////////// 
  for (int i = 0; i < HEIGHT_MAP; i++) 
	  for (int j = 0; j < WIDTH_MAP; j++)  {  
		  if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //����        
		  //��������� ������ ������, �� ������ 1-� ���������   
		  if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//����   
		  //��������� ������ s, �� ������ 2� ���������   
		  if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//���� 
		  //��������� ������ 0, �� ������ 3� ��������� 
 
  s_map.setPosition(j * 32, i * 32);//������������ ���������� � �����. 
 
  window.draw(s_map);//������ ���������� �� ����� 
	  }

	  std::ostringstream playerScoreString;  // �������� ����������  
	  playerScoreString << p.playerScore;//������� � ��� ����� �����, �� ���� ��������� ������  
	  text.setString("������� ������:" + playerScoreString.str());//������ ������ ������ �       // �������� �������������� ���� ������ ������� .str() 
	  text.setPosition(50, 50);//������ ������� ������, �������� �� ������ ������  
	  window.draw(text);//����� ���� �����

  window.draw(p.sprite);//������ ������   
  window.display(); //���������� ������ �� ������ 
	 } 
 
 return 0; 
 } 