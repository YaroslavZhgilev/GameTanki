#include <SFML\Graphics.hpp> 
#include "map.h"
#include "random.h"

void randomMapGenerate(){//�������� ����������� ����� 
 
int randomElementX = 0;//���������� ��� �������� ���������� �������� �� ����������� 
int randomElementY = 0;//���������� ��� �������� ���������� �������� �� ���������
int countStone = 5;//���������� ������ 
 
 while (countStone>0){  randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������������� �������� �� �x� �� 1 �� 
 //������ �����-1. ����������� ������� ����� �� �������� ����� ������� ����� 
 randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� �y� 
 
 if (TileMap[randomElementY][randomElementX] == ' ') {
	 //���� ��������� ������ ������, 
	 TileMap[randomElementY][randomElementX] = 's';  //�� ������ ���� ������.    
	 countStone--; 
	 } 
	} 
 };