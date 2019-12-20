#include <SFML/Graphics.hpp> 
#include "entity.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include "map.h" //подключили код с картой 

using namespace sf;
 
 Entity::Entity(Image &image, float X, float Y, int W, int H, std::string Name){  
	 x = X; y = Y; //координата появления спрайта  
	 w = W; h = H; 
	 name = Name;  
	 moveTimer = 0; 
	 dx = 0; dy = 0;  
	 speed = 0;
	 CurrentFrame = 0;  
	 health = 100;
	 life = true; //инициализировали логическую переменную жизни, герой жив 
	 texture.loadFromImage(image); //заносим наше изображение в текстуру 
	 sprite.setTexture(texture); //заливаем спрайт текстурой 
 } 
 
FloatRect Entity::getRect(){//метод получения прямоугольника. его коорд, размеры (шир,высот). 
	 //FloatRect FR(x, y, w, w); // переменная FR типа FloatRect 
	 return FloatRect(x, y, w, h);   //return FloatRect(x, y, w, h);   //Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника 
	 //в нашей игре это координаты текущего расположения тайла на карте   
	 //далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте  
	 //эта ф-ция нужна для проверки пересечений   
 } 
 
////////////////////////////////////////////////////КЛАСС ИГРОКА//////////////////////// 

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){ 
			 playerScore = 0;
			 state = stay;
			 if (name == "Player1"){   
				 //Задаем спрайту один прямоугольник для   
				 //вывода одного игрока. IntRect – для приведения типов		
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
		 void Player::update(float time) //функция "оживления/обновления" объекта класса. Принимает в себя   
			 //время SFML, вследствие чего работает бесконечно, давая персонажу движение. 
		 {  
			 if(life){//жив ли герой
				 control();//функция управления персонажем
			 switch (state)//реализуем поведение в зависимости от направления. Каждая цифра 
				 //соответствует направлению.  
			 {
				case right:{//состояние идти вправо    
					dx = speed;    
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 50, 50)); 
				    break; 
						  }  
				case left:{//состояние идти влево   
					dx = -speed;  
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;   
					sprite.setTextureRect(IntRect(65 * int(CurrentFrame),150, 50, 60)); 
					break;   
						  }

				case up:{//идти вверх   
					dy = -speed;  
					CurrentFrame += 0.005*time;    
					if (CurrentFrame > 3) CurrentFrame -= 3; 
					sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 50, 50, 50)); 
					break; 
						}

				case down:{//идти вниз 
					dy = speed;   
					CurrentFrame += 0.005*time;  
					if (CurrentFrame > 3) CurrentFrame -= 3;    
					sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 100, 50, 60));
					break; 
						  }    
			 }
 
		 x += dx*time; //движение по “X”   
		 checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х 
	     y += dy*time; //движение по “Y” 
		 checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y 
		 speed = 0;    //обнуляем скорость, чтобы персонаж остановился.   //state = stay; //состояние - стоит 
	     sprite.setPosition(x, y); //переставляем спрайт в новую позицию (x, y). 
 
		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
			 } 
		 }

	//Функция проверки столкновений с элементами карты 
		 void Player::checkCollisionWithMap(float Dx, float Dy) {
			 for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты 
				 for (int j = x / 32; j<(x + w) / 32; j++)  { 
					 if (TileMap[i][j] == '0')//если элемент тайлик земли   
					 { 
						 if (Dy > 0) { y = i * 32 - h;  dy = 0; }//по Y   
						 if (Dy < 0) { y = i * 32 + 32; dy = 0; }//столкновение с верхними краями карты  
						 if (Dx > 0) { x = j * 32 - w; dx = 0; }//с правым краем карты   
						 if (Dx < 0) { x = j * 32 + 32; dx = 0; }// с левым краем карты 
					 }   
					 if (TileMap[i][j] == 's') { 
						 playerScore++; //если взяли камень, переменная playerScore=playerScore+1; 
						 TileMap[i][j] = ' ';  
							} 
					 if (TileMap[i][j] == 'f') {  
						 health -= 40;//если взяли ядовитый цветок,то переменная health=health-40;    
						 TileMap[i][j] = ' ';//убрали цветок  
							} 
					 if (TileMap[i][j] == 'h') {  
						 health += 20;//если взяли сердечко,то переменная health=health+20; 
						 TileMap[i][j] = ' ';//убрали сердечко  
					 }
				 }
		 }


////////////////////////////КЛАСС ВРАГА//////////////////////// 

	
	Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){ 
		if (name == "EasyEnemy"){ 
			//Задаем спрайту один прямоугольник для   
			//вывода одного игрока. IntRect – для приведения типов  
			sprite.setTextureRect(IntRect(0, 0, w, h));   
			direction = rand() % (3); //Направление движения врага задаём случайным образом 
			//через генератор случайных чисел 
			health=100;
			speed = 0.1;//даем скорость.этот объект всегда двигается   
			dx = speed;  
		} 
	} 
 
 void Enemy::checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой 
 {  
	 for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты 
		 for (int j = x / 32; j<(x + w) / 32; j++){
			 if (TileMap[i][j] == '0')//если элемент - тайлик земли   
				{      
					if (Dy > 0) {
						y = i * 32 - h;  dy = -0.1; 
						direction = rand() % (3); //Направление движения врага
						}//по Y   
					if (Dy < 0) {   
						y = i * 32 + 32; dy = 0.1;   
						direction = rand() % (3);//Направление движения врага  
						}//столкновение с верхними краями  
					if (Dx > 0) {  
						x = j * 32 - w; dx = -0.1;  
						direction = rand() % (3);//Направление движения врага  
						}//с правым краем карты  
					if (Dx < 0) { 
						x = j * 32 + 32; dx = 0.1;   
						direction = rand() % (3); //Направление движения врага  
						}// с левым краем карты   

			 }
		 }
 } 
 
 void Enemy::update(float time)  { 
	 if (name == "EasyEnemy"){//для персонажа с таким именем логика будет такой 
 
	  if (life) {//проверяем, жив ли герой  
		  switch (direction)//делаются различные действия в зависимости от состояния
		  { 
			case 0:{//состояние идти вправо  
				dx = speed;  
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3;   
				sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 50, 50)); 
				break;  
				   } 
			case 1:{//состояние идти влево 
				dx = -speed;   
				CurrentFrame += 0.005*time; 
				if (CurrentFrame > 3) CurrentFrame -= 3; 
				sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 150, 50, 60)); 
				break; 
				   }  
			case 2:{//идти вверх   
				dy = -speed;  
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3; 
				sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 50, 50, 50));  
				break; 
				   }
			case 3:{//идти вниз   
				dy = speed; 
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 100, 50, 60)); 
				break; 
				   } 
		  } 
 
  x += dx*time; //движение по “X”   
  checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х  
  y += dy*time; //движение по “Y”  
  checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y 
  sprite.setPosition(x, y); //спрайт в позиции (x, y). 
 
  if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем  
	  } 
	 } 
 } 

////////////////////////////КЛАСС ПУЛИ//////////////////////// 

		 Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name){  
			 x = X; //координаты пули на карте игры  
			 y = Y;  
			 direction = dir; //направление полета пули   
			 speed = 0.8; 
			 w = h = 16; //размеры изображения пули   
			 life = true; //пуля жива 
		 } 
 
 
 void Bullet::update(float time)  {   
	 switch (direction)   {  
			case 0: dx = -speed; dy = 0;   break;// state = left  
			case 1: dx = speed; dy = 0;   break;// state = right 
			case 2: dx = 0; dy = -speed;   break;// state = up 
			case 3: dx = 0; dy = speed;   break;// state = down 
	 } 
 
  if (life){ // если пуля жива   
	  x += dx*time;//само движение пули по х   
	  y += dy*time;//по у 
 
   for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты    
	   for (int j = x / 32; j < (x + w) / 32; j++)
	   {
		   if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то     
			   life = false;// то пуля умирает     
				   }    
	   sprite.setPosition(x + w / 2, y + h / 2); //задается позицию пули  
	  } 
	} 