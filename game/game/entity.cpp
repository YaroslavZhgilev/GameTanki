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
Entity::~Entity(){
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
			 health=100;
			 if (name == "Player1"){   
				 //Задаем спрайту один прямоугольник для   
				 //вывода одного игрока. IntRect – для приведения типов		
				 sprite.setTextureRect(IntRect(0, 0, w, h));  
			 }  
		 }
Player::~Player(){
}


		 void Player::control(){    
			 if( Keyboard::isKeyPressed ){
				if (Keyboard::isKeyPressed(Keyboard::Left)) {     
					state = left;   
					speed = 0.1; 
					dx=0;
					dy=0;
				}    
				if (Keyboard::isKeyPressed(Keyboard::Right)) {     
					state = right;  
					speed = 0.1; 
					dx=0;
					dy=0;
				} 
 
			    if (Keyboard::isKeyPressed(Keyboard::Up)) {    
					state = up; 
					speed = 0.1; 
					dx=0;
					dy=0;
				} 
 
			    if (Keyboard::isKeyPressed(Keyboard::Down)) { 
					state = down;   
				    speed = 0.1;  
					dx=0;
					dy=0;
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
					sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32)); 
				    break; 
						  }  
				case left:{//состояние идти влево   
					dx = -speed;  
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;   
					sprite.setTextureRect(IntRect(32 * int(CurrentFrame),96, 32, 32)); 
					break;   
						  }

				case up:{//идти вверх   
					dy = -speed;  
					CurrentFrame += 0.005*time;    
					if (CurrentFrame > 3) CurrentFrame -= 3; 
					sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32)); 
					break; 
						}

				case down:{//идти вниз 
					dy = speed;   
					CurrentFrame += 0.005*time;  
					if (CurrentFrame > 3) CurrentFrame -= 3;    
					sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
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
					 if (TileMap[i][j] == 'h') { 
						 playerScore++; //если взяли камень, переменная playerScore=playerScore+1; 
						 TileMap[i][j] = ' ';  
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

	Enemy::~Enemy(){
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
				state=right;
				dx = -speed;
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3;   
				sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32)); 
				break;  
				   } 
			case 1:{//состояние идти влево 
				state=left;
				dx = -speed;
				CurrentFrame += 0.005*time; 
				if (CurrentFrame > 3) CurrentFrame -= 3; 
				sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32)); 
				break; 
				   }  
			case 2:{//идти вверх   
				state=up;
				dy = -speed;  
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3; 
				sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32));  
				break; 
				   }
			case 3:{//идти вниз
				state=down;
				dy = speed; 
				CurrentFrame += 0.005*time;  
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32)); 
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
			 w = h = 40; //размеры изображения пули   
			 life = true; //пуля жива 
		 } 
		 Bullet::~Bullet(){
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
	  if(x<=0)x=16;//Задержка пули в левой стене
	  if(y<=0)y=16;//Задержка пули в вверху
	  if(x>=800)x=784;//Задержка пули в правой стене
	  if(y>=640)y=624;//Задержка пули внизу
 
   for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты    
	   for (int j = x / 32; j < (x + w) / 32; j++)
	   {
		   if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то     
			   life = false;// то пуля умирает     
				   }    
	   sprite.setPosition(x + w / 2, y + h / 2); //задается позицию пули  
	  } 
	} 
