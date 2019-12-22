#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SFML/Graphics.hpp> 
using namespace sf;


class Entity { 
public:  enum { left, right, up, down, stay} state;// ��� ������������ - ��������� ������� 
		 float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����  
		 int w, h, health; //���������� �health�, �������� ����� ������  
		 bool life; //���������� �life� �����, ����������  
		 Texture texture;//���� �������� 
		 Sprite sprite;//���� ������ 
		 float CurrentFrame;//������ ������� ���� 
		 std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������  //������� ����� ���� ���� �������� � update() � ����������� �� �����
		 Entity(Image &image, float X, float Y, int W, int H, std::string Name);
		 virtual ~Entity();
    FloatRect getRect();
	virtual void update(float time) = 0;
};

class Player :public Entity { // ����� ������
public: 
		 int playerScore;//����� ����������, �������� ���� ��� //����������� (direction) �������� ������

		 Player(Image &image, float X, float Y, int W, int H, std::string Name);
		 ~Player();
		 void control();
		 void update(float time);
		 void checkCollisionWithMap(float Dx, float Dy);
};

class Enemy :public Entity{ 
public:  
	int direction;//����������� �������� ����� 
	
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
	~Enemy();
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
};

	class Bullet :public Entity{//����� ���� 
public:  int direction;//����������� ���� 
		 Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);
		 ~Bullet();
		 void update(float time);
	};
#endif