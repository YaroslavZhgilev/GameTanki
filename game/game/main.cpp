#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cmath>
#include <sstream>
#include "map.h" //���������� ��� � ������ 
 
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ 

////////////////////////////////////////////////////����� ������//////////////////////// 
class Player { // ����� ������
private: float x,y;
public:  float w, h, dx, dy, speed; //���������� ������ � � �, ������ � ������,        
		 //��������� (�� � � �� �), ���� ��������  
		 float CurrentFrame;//������ ������� ���� 
		 int playerScore,health;//����� ����������, �������� ���� ��� //����������� (direction) �������� ������
		 bool life;
		 enum {left, right, up, down, stay} state;//��������� ��� ������������ - ��������� �������
		 std::string File; //���� � �����������  
		 Image image;//���� �����������  
		 Texture texture;//���� ��������  
		 Sprite sprite;//���� ������ 
		 //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ �� ����� �������� 
		 //��� �����, ���������� � � �, ������ � ������ 

		 Player(std::string F, float X, float Y, float W, float H){
			 dx=0; dy=0; speed = 0; playerScore = 0;health=100;
			 CurrentFrame=0;
			 state=stay;
			 life=true;
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
			 sprite.setTextureRect(IntRect(0, 0, w, h)); //������ ������� ���� ������������� ���  //������ ������ ����. IntRect � ��� ���������� ����� 
}

		 void control(){    
				if (Keyboard::isKeyPressed(Keyboard::Left)) {     
					state = left;   
					speed = 0.1;   
				}    
				if (Keyboard::isKeyPressed(Keyboard::Right)) {     
					state = right;  
					speed = 0.1; 
				} 
 
			    if (Keyboard::isKeyPressed(Keyboard::Up)) {    
					state = up; 
					speed = 0.1; 
				} 
 
			    if (Keyboard::isKeyPressed(Keyboard::Down)) { 
					state = down;   
				    speed = 0.1;  
				}  
}
		 void update(float time) //������� "���������/����������" ������� ������. ��������� � ����   
			 //����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������. 
		 {  
			 if(life){//��� �� �����
				 control();//������� ���������� ����������
			 switch (state)//��������� ��������� � ����������� �� �����������. ������ ����� 
				 //������������� �����������.  
			 {
				case right:{//��������� ���� ������    
					dx = speed;    
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); 
				    break; 
						  }  
				case left:{//��������� ���� �����   
					dx = -speed;  
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;   
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); 
					break;   
						  }

				case up:{//���� �����   
					dy = -speed;  
					CurrentFrame += 0.005*time;    
					if (CurrentFrame > 3) CurrentFrame -= 3; 
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); 
					break; 
						}

				case down:{//���� ���� 
					dy = speed;   
					CurrentFrame += 0.005*time;  
					if (CurrentFrame > 3) CurrentFrame -= 3;    
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
					break; 
						  }   
				case stay:{//�����    
					dy = speed;   
					dx = speed;    
				    break;     
						  } 
			 }
 
		 x += dx*time; //�������� �� �X�   
		 checkCollisionWithMap(dx, 0);//������������ ������������ �� � 
	     y += dy*time; //�������� �� �Y� 
		 checkCollisionWithMap(0, dy);//������������ ������������ �� Y 
		 speed = 0;    //�������� ��������, ����� �������� �����������.   //state = stay; //��������� - ����� 
	     sprite.setPosition(x, y); //������������ ������ � ����� ������� (x, y). 
 
		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
			 } 
		 }

	//������� �������� ������������ � ���������� ����� 
		 void checkCollisionWithMap(float Dx, float Dy) {
			 for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� ����� 
				 for (int j = x / 32; j<(x + w) / 32; j++)  { 
					 if (TileMap[i][j] == '0')//���� ������� ������ �����   
					 { 
						 if (Dy > 0) { y = i * 32 - h;  dy = 0; }//�� Y   
						 if (Dy < 0) { y = i * 32 + 32; dy = 0; }//������������ � �������� ������ �����  
						 if (Dx > 0) { x = j * 32 - w; dx = 0; }//� ������ ����� �����   
						 if (Dx < 0) { x = j * 32 + 32; dx = 0; }// � ����� ����� ����� 
					 }   
					 if (TileMap[i][j] == 's') { 
						 playerScore++; //���� ����� ������, ���������� playerScore=playerScore+1; 
						 TileMap[i][j] = ' ';  
							} 
					 if (TileMap[i][j] == 'f') {  
						 health -= 40;//���� ����� �������� ������,�� ���������� health=health-40;    
						 TileMap[i][j] = ' ';//������ ������  
							} 
					 if (TileMap[i][j] == 'h') {  
						 health += 20;//���� ����� ��������,�� ���������� health=health+20; 
						 TileMap[i][j] = ' ';//������ ��������  
					 }
				 }
		 }

		 FloatRect getRect(){
			 //����� ��������� ��������������. ��� �����, ������� (���,�����). 
			 FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect  
			 return FR;  //��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� �������������� 
			 //� ����� ���� ��� ���������� �������� ������������ ����� �� ����� 
			 //����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� �����   
			 //��� �-��� ����� ��� �������� �����������   
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
	map_image.loadFromFile("images/map_new.png");//��������� ���� ��� ����� 
	Texture map;//�������� ����� 
	map.loadFromImage(map_image);//�������� �������� ���������  
	Sprite s_map;//������ ������ ��� ����� 
	s_map.setTexture(map);//�������� �������� ��������   
 
	Clock clock;   //������� ���������� ������� � ������������ ��������� ����!
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ����  
	int gameTime = 0;//�������� ������� �����, ����������������.
 
	int createObjectForMapTimer = 0;//���������� ��� ����� ��� ������������� ������ 

 while (window.isOpen())  //���� ���� �������  
	{   

		// ���� ����� � ���������� ����������� �����, � ������ ������ �����, ��������� �              
		//���������� �������� � ������ restart();   
		float time = clock.getElapsedTime().asMicroseconds();
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();   
		//������� ����� � �������� ��� ������, ���� ��� �����.     
		//������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
		clock.restart(); //���������� �����   
		time = time / 800; //�������� ����  

		createObjectForMapTimer += time;//���������� ������   
		if (createObjectForMapTimer>100){    
			randomMapGenerate();//���������  ������   
			createObjectForMapTimer = 0;//�������� ������   
 }
		    
		 sf::Event event;   
		 while (window.pollEvent(event))  
			 {    
				 if (event.type == sf::Event::Closed)    
				 window.close();   
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
		  if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//������  
		  if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//������ 
  s_map.setPosition(j * 32, i * 32);//������������ ���������� � �����. 
 
  window.draw(s_map);//������ ���������� �� ����� 
	  }

	  std::ostringstream playerHealthString, gameTimeString;//�������� ���������� �������� � ������� 
	  playerHealthString << p.health; gameTimeString << gameTime;//��������� ������ 
	  text.setString("��������: " + playerHealthString.str() + "\n����� ����: " + gameTimeString.str());//������ ������ ������ 
	  text.setPosition(50, 50);//������ ������� ������ 
	  window.draw(text);//������ ���� �����

  window.draw(p.sprite);//������ ������   
  window.display(); //���������� ������ �� ������ 
	 } 
 
 return 0; 
 } 