#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cmath>
#include <sstream>
#include "map.h" //���������� ��� � ������ 
#include <list>
 
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ 

class Entity { 
public:  enum { left, right, up, down, stay} state;// ��� ������������ - ��������� ������� 
		 float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����  
		 int w, h, health; //���������� �health�, �������� ����� ������  
		 bool life; //���������� �life� �����, ����������  
		 Texture texture;//���� �������� 
		 Sprite sprite;//���� ������ 
		 float CurrentFrame;//������ ������� ���� 
		 std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������  //������� ����� ���� ���� �������� � update() � ����������� �� ����� 
 
 Entity(Image &image, float X, float Y, int W, int H, std::string Name){  
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
 
 FloatRect getRect(){//����� ��������� ��������������. ��� �����, ������� (���,�����). 
	 FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect 
	 return FR;   //return FloatRect(x, y, w, h);   //��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� �������������� 
	 //� ����� ���� ��� ���������� �������� ������������ ����� �� �����   
	 //����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� �����  
	 //��� �-��� ����� ��� �������� �����������   
 } 
 
 virtual void update(float time) = 0; 
};
////////////////////////////////////////////////////����� ������//////////////////////// 
class Player :public Entity { // ����� ������
public: 
		 int playerScore;//����� ����������, �������� ���� ��� //����������� (direction) �������� ������

		 Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){ 
			 playerScore = 0;
			 state = stay;
			 if (name == "Player1"){   
				 //������ ������� ���� ������������� ���   
				 //������ ������ ������. IntRect � ��� ���������� �����   
				 sprite.setTextureRect(IntRect(0, 0, w, h));  
			 }  
		 }

		 void control(){    
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

};

////////////////////////////����� �����//////////////////////// 
class Enemy :public Entity{ 
public:  
	int direction;//����������� �������� ����� 
	
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){ 
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
 
 void checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������ 
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
 
 void update(float time)  { 
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
};//����� Enemy ������

////////////////////////////����� ����//////////////////////// 
class Bullet :public Entity{//����� ���� 
public:  int direction;//����������� ���� 
		 Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name){  
			 x = X; //���������� ���� �� ����� ����  
			 y = Y;  
			 direction = dir; //����������� ������ ����   
			 speed = 0.8; 
			 w = h = 16; //������� ����������� ����   
			 life = true; //���� ���� 
		 } 
 
 
 void update(float time)  {   
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
 }; 

int main() {
	//������ ���� 
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
	sf::RenderWindow window(sf::VideoMode(800, 640, desktop.bitsPerPixel), "Lesson 6"); 


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
 
	Image heroImage;  
	heroImage.loadFromFile("images/hero.png"); // ��������� ����������� ������ 
 
    Image easyEnemyImage; 
	easyEnemyImage.loadFromFile("images/enemy.png"); // ��������� ����������� ����� 
	
	Image BulletImage;//����������� ��� ����  
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ ����������� 

    Player p(heroImage, 100, 100, 96, 96, "Player1");//������ ������ ������ 

	std::list<Entity*>  enemies; //������ ������  
	std::list<Entity*>  Bullets; //������ ����
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������ 
	std::list<Entity*>::iterator it2;
 
 const int ENEMY_COUNT = 3; //������������ ���������� ������ � ����  
 int enemiesCount = 0;      //������� ���������� ������ � ���� 
 
 //��������� ������ ��������� �������  
 for (int i = 0; i < ENEMY_COUNT; i++)  {
	 float xr = 150 + rand() % 500; //��������� ���������� ����� �� ���� ���� �� ��� �x� 
	 float yr = 150 + rand() % 350; //��������� ���������� ����� �� ���� ���� �� ��� �y�   //������� ������ � �������� � ������ 
	 enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 96, 96, "EasyEnemy"));  
	 enemiesCount += 1; //��������� ������� ������  
}

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
		//if (createObjectForMapTimer>3000){    
			//randomMapGenerate();//���������  ������   
			//createObjectForMapTimer = 0;//�������� ������   
 //}
		    
		 sf::Event event;   
		 while (window.pollEvent(event))  
			 {    
				 if (event.type == sf::Event::Closed)    
				 window.close();    

		 //�������� �� ������� ������� "P"   
		 if (event.type == sf::Event::KeyPressed)
		 {
			 if (event.key.code == sf::Keyboard::P)
			 {
				 Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state));    
			 } 
		 }   
 }

		 p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml, 
		 // ��������� ����� � �������� ��������� ������� update.

		 for (it = enemies.begin(); it != enemies.end(); it++)//���������� �� ��-��� ������
		{
			if ((*it)->getRect().intersects(p.getRect()))//���� ������������� ������� ������� ������������ � �������
			{
				if ((*it)->name == "EasyEnemy"){//� ��� ���� ��� ������� EasyEnemy,��..
					if ((*it)->dx>0)//���� ���� ���� ������
					{
						std::cout << "(*it)->x" << (*it)->x << "\n";//����� ������
						std::cout << "p.x" << p.x << "\n\n";//����� �����
 
						(*it)->x = p.x - (*it)->w; //����������� ��� �� ������ ����� (�������)
						(*it)->dx = 0;//�������������
 
						std::cout << "new (*it)->x" << (*it)->x << "\n";//����� ����� �����
						std::cout << "new p.x" << p.x << "\n\n";//����� ����� ������ (��������� �������)
					}
					if ((*it)->dx < 0)//���� ���� ���� �����
					{
						(*it)->x = p.x + p.w; //���������� - ����������� ������
						(*it)->dx = 0;//�������������
					}

					//������������ ������
					//if (p.dx < 0) { p.x = (*it)->x + (*it)->w;  }//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
					//if (p.dx > 0) { p.x = (*it)->x - p.w; }//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
				}
			}
			for (it2 = enemies.begin(); it2 != enemies.end(); it2++){
				if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
				if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//���� ����������� ��� ������� � ��� �����
				{
					(*it)->dx *= -1;//������ ����������� �������� �����
					(*it)->sprite.scale(-1, 1);//�������� ������ �� �����������
				}
			}
		}


		 for (it = enemies.begin(); it != enemies.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			//b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->life == false)	{ it = enemies.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}



		 for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)//���������� �� ��-��� ������
		{
			for (it = enemies.begin(); it != enemies.end(); it++){
			if ((*it)->getRect().intersects((*it2)->getRect()))//���� ������������� ������� ������� ������������ � �������
			{    (*it2)->life=0;
				if ((*it)->name == "EasyEnemy"){//� ��� ���� ��� ������� EasyEnemy,��..
						(*it)->health -= 50;	//����� ���� ������� � ��� ����� � ����� ����
					}
				}
			}
		}
		 //�������� ������  
		 for (it = enemies.begin(); it != enemies.end(); it++)   {  
			 (*it)->update(time); //��������� ����� update() 
		} 
 

		 //�������� ����   
		 for (it = Bullets.begin(); it != Bullets.end(); it++)   {
			 (*it)->update(time); //��������� ����� update()   
		 } 
 
  //��������� ������ �� ������� "�������" ���� � ������� �� 
		 for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� ����� 
		 {
			 // ���� ���� ������ �����, �� ������� ���   
			 if ((*it)-> life == false) { it = Bullets.erase(it); }    
			 else  it++;//� ���� �������� (����������) � ���� �������.    
} 
		 for (it = enemies.begin(); it != enemies.end(); )//������� ��� ���������� �� ������ �� ����� 
		 {
			 // ���� ���� ������ �����, �� ������� ���   
			 if ((*it)-> life == false) { it = enemies.erase(it); }    
			 else  it++;//� ���� �������� (����������) � ���� �������.    
} 
	
//�������� ����������� ������ � ������� 
		 //���� ����������� ���������, �� "health = 0", ����� ��������������� �  
		 //��������� ��������� "you are lose" 
		// if (p.life == true){//���� ����� ��� 
				//for (it = enemies.begin(); it != enemies.end(); it++){
					//����� �� ������ ������   
				//	if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy")){
					//	p.health = 0;
					//	std::cout << "you are lose"; 
					//} 
				//}   
 //}

  window.clear(); //������� �����   

  /////////////////////////////������ �����///////////////////// 
  for (int i = 0; i < HEIGHT_MAP; i++) 
	  for (int j = 0; j < WIDTH_MAP; j++)  {  
		  if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 32, 32)); //����        
		  //��������� ������ ������, �� ������ 1-� ���������   
		  if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//����   
		  //��������� ������ s, �� ������ 2� ���������   
		  if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//���� 
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
 //������ ������   
  for (it = enemies.begin(); it != enemies.end(); it++){
	  window.draw((*it)->sprite); //������ enemies �������   
 } 
  //������ ����  
  for (it = Bullets.begin(); it != Bullets.end(); it++)   {   
	  if ((*it)->life) //���� ���� ����    
		  window.draw((*it)->sprite); //������ �������  
 }

  window.display(); //���������� ������ �� ������ 
	 } 
 
 return 0; 
 } 