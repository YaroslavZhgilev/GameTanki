#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SFML/Graphics.hpp> 
using namespace sf;


class Entity { 
public:  enum { left, right, up, down, stay} state;// тип перечислени€ - состо€ние объекта 
		 float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер дл€ будущих целей  
		 int w, h, health; //переменна€ УhealthФ, хран€ща€ жизни игрока  
		 bool life; //переменна€ УlifeФ жизнь, логическа€  
		 Texture texture;//сфмл текстура 
		 Sprite sprite;//сфмл спрайт 
		 float CurrentFrame;//хранит текущий кадр 
		 std::string name;//враги могут быть разные, врагов можно различать по именам  //каждому можно дать свое действие в update() в зависимости от имени
		 Entity(Image &image, float X, float Y, int W, int H, std::string Name);
		 virtual ~Entity();
    FloatRect getRect();
	virtual void update(float time) = 0;
};

class Player :public Entity { // класс »грока
public: 
		 int playerScore;//нова€ переменна€, хран€ща€ очки игр //направление (direction) движени€ игрока

		 Player(Image &image, float X, float Y, int W, int H, std::string Name);
		 ~Player();
		 void control();
		 void update(float time);
		 void checkCollisionWithMap(float Dx, float Dy);
};

class Enemy :public Entity{ 
public:  
	int direction;//направление движени€ врага 
	
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
	~Enemy();
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
};

	class Bullet :public Entity{//класс пули 
public:  int direction;//направление пули 
		 Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);
		 ~Bullet();
		 void update(float time);
	};
#endif