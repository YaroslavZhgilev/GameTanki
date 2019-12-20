#include <SFML/Graphics.hpp> 
#include "entity.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include "map.h" //���������� ��� � ������ 

using namespace sf;
 
 Entity::Entity(Image &image, float X, float Y, int W, int H, std::string Name){  
	 x = X; y = Y; //���������� ��������� �������  
	 w = W; h = H; 
	 name = Name;  
	 moveTimer = 0; 
	 dx = 0; dy = 0;  
	 speed = 0;
	 CurrentFrame = 0;  
	 health = 100;
	 life = true; //���������������� ���������� ���������� �����, ����� ��� 
	 texture.loadFromImage(image); //������� ���� ����������� � �������� 
	 sprite.setTexture(texture); //�������� ������ ��������� 
 } 
 
FloatRect Entity::getRect(){//����� ��������� ��������������. ��� �����, ������� (���,�����). 
	 //FloatRect FR(x, y, w, w); // ���������� FR ���� FloatRect 
	 return FloatRect(x, y, w, h);   //return FloatRect(x, y, w, h);   //��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� �������������� 
	 //� ����� ���� ��� ���������� �������� ������������ ����� �� �����   
	 //����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� �����  
	 //��� �-��� ����� ��� �������� �����������   
 } 
 
////////////////////////////////////////////////////����� ������//////////////////////// 

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){ 
			 playerScore = 0;
			 state = stay;
			 if (name == "Player1"){   
				 //������ ������� ���� ������������� ���   
				 //������ ������ ������. IntRect � ��� ���������� �����		
				 sprite.setTextureRect(IntRect(0, 0, w, h));  
			 }  
		 }

		 void Player::control(){    
			 if( Keyboard::isKeyPressed ){
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
 }
		 void Player::update(float time) //������� "���������/����������" ������� ������. ��������� � ����   
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
					sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 50, 50)); 
				    break; 
						  }  
				case left:{//��������� ���� �����   
					dx = -speed;  
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;   
					sprite.setTextureRect(IntRect(65 * int(CurrentFrame),150, 50, 60)); 
					break;   
						  }

				case up:{//���� �����   
					dy = -speed;  
					CurrentFrame += 0.005*time;    
					if (CurrentFrame > 3) CurrentFrame -= 3; 
					sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 50, 50, 50)); 
					break; 
						}

				case down:{//���� ���� 
					dy = speed;   
					CurrentFrame += 0.005*time;  
					if (CurrentFrame > 3) CurrentFrame -= 3;    
					sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 100, 50, 60));
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
		 void Player::checkCollisionWithMap(float Dx, float Dy) {
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


////////////////////////////����� �����//////////////////////// 

	
	Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){ 
		if (name == "EasyEnemy"){ 
			//������ ������� ���� ������������� ���   
			//������ ������ ������. IntRect � ��� ���������� �����  
			sprite.setTextureRect(IntRect(0, 0, w, h));   
			direction = rand() % (3); //����������� �������� ����� ����� ��������� ������� 
			//����� ��������� ��������� ����� 
			health=100;
			speed = 0.1;//���� ��������.���� ������ ������ ���������   
			dx = speed;  
		} 
	} 
 
 void Enemy::checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������ 
 {  
	 for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� ����� 
		 for (int j = x / 32; j<(x + w) / 32; j++){
			 if (TileMap[i][j] == '0')//���� ������� - ������ �����   
				{      
					if (Dy > 0) {
						y = i * 32 - h;  dy = -0.1; 
						direction = rand() % (3); //����������� �������� �����
						}//�� Y   
					if (Dy < 0) {   
						y = i * 32 + 32; dy = 0.1;   
						direction = rand() % (3);//����������� �������� �����  
						}//������������ � �������� ������  
					if (Dx > 0) {  
						x = j * 32 - w; dx = -0.1;  
						direction = rand() % (3);//����������� �������� �����  
						}//� ������ ����� �����  
					if (Dx < 0) { 
						x = j * 32 + 32; dx = 0.1;   
						direction = rand() % (3); //����������� �������� �����  
						}// � ����� ����� �����   

			 }
		 }
 } 
 
 void Enemy::update(float time)  { 
	 if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� ����� 
 
	  if (life) {//���������, ��� �� �����  
		  switch (direction)//�������� ��������� �������� � ����������� �� ���������
		  { 
			case 0:{//��������� ���� ������  
				dx = speed;  
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3;   
				sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 50, 50)); 
				break;  
				   } 
			case 1:{//��������� ���� ����� 
				dx = -speed;   
				CurrentFrame += 0.005*time; 
				if (CurrentFrame > 3) CurrentFrame -= 3; 
				sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 150, 50, 60)); 
				break; 
				   }  
			case 2:{//���� �����   
				dy = -speed;  
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3; 
				sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 50, 50, 50));  
				break; 
				   }
			case 3:{//���� ����   
				dy = speed; 
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 100, 50, 60)); 
				break; 
				   } 
		  } 
 
  x += dx*time; //�������� �� �X�   
  checkCollisionWithMap(dx, 0);//������������ ������������ �� �  
  y += dy*time; //�������� �� �Y�  
  checkCollisionWithMap(0, dy);//������������ ������������ �� Y 
  sprite.setPosition(x, y); //������ � ������� (x, y). 
 
  if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������  
	  } 
	 } 
 } 

////////////////////////////����� ����//////////////////////// 

		 Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name){  
			 x = X; //���������� ���� �� ����� ����  
			 y = Y;  
			 direction = dir; //����������� ������ ����   
			 speed = 0.8; 
			 w = h = 16; //������� ����������� ����   
			 life = true; //���� ���� 
		 } 
 
 
 void Bullet::update(float time)  {   
	 switch (direction)   {  
			case 0: dx = -speed; dy = 0;   break;// state = left  
			case 1: dx = speed; dy = 0;   break;// state = right 
			case 2: dx = 0; dy = -speed;   break;// state = up 
			case 3: dx = 0; dy = speed;   break;// state = down 
	 } 
 
  if (life){ // ���� ���� ����   
	  x += dx*time;//���� �������� ���� �� �   
	  y += dy*time;//�� � 
 
   for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����    
	   for (int j = x / 32; j < (x + w) / 32; j++)
	   {
		   if (TileMap[i][j] == '0')//���� ������� ��� ������ �����, ��     
			   life = false;// �� ���� �������     
				   }    
	   sprite.setPosition(x + w / 2, y + h / 2); //�������� ������� ����  
	  } 
	} 